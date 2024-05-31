/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "LCD.h"
#include "adc.h"
#include "dac.h"
#include "fatfs.h"
#include "lwip.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "usb_host.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "W25QXX.h"
#include "CH455.h"
#include "key.h"
#include "gt9147.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "image_fll.h"
#include <sys/_types.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t waterlampflag = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance != TIM3)
        return;
    KeyIRQHandler();
    static uint16_t count = 0;
    ++count;
    if (count == 0) HAL_GPIO_TogglePin(LED8_GPIO_Port, LED8_Pin);
}

float get_adc1_0() {
    int sum = 0;
    for (int i = 0; i < 20; ++i) {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 0xffff);
        sum += HAL_ADC_GetValue(&hadc1);
    }
    return sum * 3.3 / 4096 / 20;
}
const u16 POINT_COLOR_TBL[5] = {RED, GREEN, BLUE, BROWN, GRED};
void torch_process(void) {
    tp_dev.scan(0);
    if (tp_dev.x[0] < image_width && tp_dev.y[0] < image_height) {
        HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    }
}
// 重定向printf
// gcc是这样的
int _write(int fd, char *pBuffer, int size) {
    if (fd != stdout->_file)
        return -1;

    HAL_UART_Transmit_IT(&huart3, pBuffer, size);
    return size;
}
int _read(int fd, char *pBuffer, int size) {
    HAL_UART_Receive(&huart3, pBuffer, size, 0xffff);
    return size;
}
int get_key1_lib(void) {
    return HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0;
}
int get_key2_lib(void) {
    return HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0;
}
int get_key3_lib(void) {
    return HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == 0;
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == 5) {
        ch455_key = CH455_Read();
    }
}
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc) {
    HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6);
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;
    HAL_RTC_GetTime(hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(hrtc, &sDate, RTC_FORMAT_BIN);
    char str[20] = {0};
    sprintf(str, "%02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
    // LCD_ShowString(0, 400, str, BLACK, WHITE);
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_FSMC_Init();
    MX_USART3_UART_Init();
    MX_TIM3_Init();
    MX_UART5_Init();
    MX_RTC_Init();
    MX_ADC1_Init();
    MX_DAC_Init();
    MX_LWIP_Init();
    MX_USB_HOST_Init();
    MX_FATFS_Init();
    /* USER CODE BEGIN 2 */
    LCD_Init();
    // LCD_Display_Dir(1);
    // LCD_Scan_Dir(U2D_R2L);
    tp_dev.init();
    HAL_TIM_Base_Start_IT(&htim3);
    while (1) {
        MX_USB_HOST_Process();
        extern ApplicationTypeDef Appli_state;
        if (APPLICATION_READY == Appli_state) break;
        if (Appli_state == APPLICATION_DISCONNECT) break;
    }

    FRESULT res = f_mount(&USBHFatFS, (TCHAR const *)USBHPath, 1);
    LCD_ShowString(0, 32, (res == FR_OK ? "USBH OK" : "USBH Fail"), RED, WHITE);
    char tmp[20] = {0};
    sprintf(tmp, "%d", res);
    LCD_ShowString(128, 32, tmp, BLACK, WHITE);
    sprintf(tmp, "%d %d", lcddev.height, lcddev.width);
    LCD_ShowString(128, 0, tmp, BLACK, WHITE);
    if (res == FR_OK) {
        FIL file;
        f_open(&file, "test.txt", FA_CREATE_ALWAYS | FA_WRITE);
        f_write(&file, "Hello World", 11, 0);
        f_close(&file);
    } else if (res == FR_NO_FILESYSTEM) {
        uint8_t buf[1024] = {0};
        f_mkfs("0:", FM_FAT32, 4096, buf, 1024);
    }
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    LCD_ShowString(0, 0, "Compile Time", BLACK, WHITE);
    LCD_ShowString(0, 16, __TIME__, BLACK, WHITE);
    LCD_DrawPicture(0, 48, image_width, image_height, image);
    LCD_Draw_area(0, 300, 50, 50, ~(uint16_t)(1 << 0));
    LCD_Draw_area(50, 300, 50, 50, ~(uint16_t)(1 << 1));
    LCD_Draw_area(100, 300, 50, 50, ~(uint16_t)(1 << 2));
    LCD_Draw_area(150, 300, 50, 50, ~(uint16_t)(1 << 3));
    LCD_Draw_area(0, 350, 50, 50, ~(uint16_t)(1 << 4));
    LCD_Draw_area(50, 350, 50, 50, ~(uint16_t)(1 << 5));
    LCD_Draw_area(100, 350, 50, 50, ~(uint16_t)(1 << 6));
    LCD_Draw_area(150, 350, 50, 50, ~(uint16_t)(1 << 7));
    LCD_Draw_area(0, 400, 50, 50, ~(uint16_t)(1 << 8));
    LCD_Draw_area(50, 400, 50, 50, ~(uint16_t)(1 << 9));
    LCD_Draw_area(100, 400, 50, 50, ~(uint16_t)(1 << 10));
    LCD_Draw_area(150, 400, 50, 50, ~(uint16_t)(1 << 11));
    LCD_Draw_area(0, 450, 50, 50, ~(uint16_t)(1 << 12));
    LCD_Draw_area(50, 450, 50, 50, ~(uint16_t)(1 << 13));
    LCD_Draw_area(100, 450, 50, 50, ~(uint16_t)(1 << 14));
    LCD_Draw_area(150, 450, 50, 50, ~(uint16_t)(((unsigned)1) << 15));

    LCD_Draw_area(0, 600, 50, 50, ~(uint16_t)(0xF800));
    LCD_Draw_area(50, 600, 50, 50, ~(uint16_t)(0x07E0));
    LCD_Draw_area(100, 600, 50, 50, ~(uint16_t)(0x001F));
#define DL1(y) LCD_Draw_area(0, y, 160, 1, RED)
#define DL2(y) LCD_Draw_area(160, y, 160, 1, GREEN)
#define DL3(y) LCD_Draw_area(320, y, 160, 1, BLUE)
#define DLA(y)  \
    do {        \
        DL1(y); \
        DL2(y); \
        DL3(y); \
    } while (0)
    DLA(550);
    LCD_Draw_area(0, 551, 160, 1, BLUE);
    LCD_Draw_area(160, 551, 160, 1, RED);
    LCD_Draw_area(320, 551, 160, 1, GREEN);
    DLA(552);
    DLA(554);

#undef DL1
#undef DL2
#undef DL3
#undef DLA
    while (1) {
        /*
        static uint16_t color=RED;
        LCD_SetCursor(0, 0);
        LCD_WriteRAM_Prepare();
        for (uint32_t i = 0; i < 800 * 480; ++i) {
            LCD->LCD_RAM = color;
        }
        continue;
        */
        torch_process();
        HAL_Delay(5);

        /* USER CODE END WHILE */
        MX_USB_HOST_Process();

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
