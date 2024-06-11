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
#include "DTH11.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "fatfs.h"
#include "lwip.h"
#include "mqtt.h"
#include "rng.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "usb_host.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "GNSS.h"
#include "W25QXX.h"
#include "CH455.h"
#include "key.h"
#include "gt9147.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/_types.h>
#include <time.h>
#include "lvgl.h"
#include "ui.h"
#include "w25qxx.h"
#include "MP3IOT.h"
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

float get_adc1_0() {
    int sum = 0;
    for (int i = 0; i < 20; ++i) {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 0xffff);
        sum += HAL_ADC_GetValue(&hadc1);
    }
    return sum * 3.3 / 4096 / 20;
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

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static lv_color_t disp_buf_1[800 * 10];
static lv_color_t disp_buf_2[800 * 10];
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
    MX_DMA_Init();
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
    MX_TIM10_Init();
    MX_USART6_UART_Init();
    MX_RNG_Init();
    /* USER CODE BEGIN 2 */
    //DTH11_IN();
    //DTH11_ReadData();
    W25QXX_Init();
    printf("%04x\n", W25QXX_ReadID());
    LCD_Init();
    LCD_Display_Dir(1);
    LCD_Scan_Dir(U2D_R2L);
    tp_dev.init();
    HAL_TIM_Base_Start_IT(&htim3);
    while (1) {
        MX_USB_HOST_Process();
        extern ApplicationTypeDef Appli_state;
        if (APPLICATION_READY == Appli_state) break;
        if (Appli_state == APPLICATION_DISCONNECT) break;
    }
    HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
    FRESULT res = f_mount(&USBHFatFS, (TCHAR const *)USBHPath, 1);
    if (res == FR_OK) {
        FIL file;
        f_open(&file, "test.txt", FA_CREATE_ALWAYS | FA_WRITE);
        f_write(&file, "Hello World", 11, 0);
        f_close(&file);
    } else if (res == FR_NO_FILESYSTEM) {
        // uint8_t buf[1024] = {0};
        // f_mkfs("0:", FM_FAT32, 4096, ccmram_arr, sizeof(ccmram_arr));
    }
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    printf("Compile Time: %s\n", __TIME__);
    mp3_init();
    lv_init();
    HAL_DMA_RegisterCallback(&hdma_memtomem_dma2_stream0, HAL_DMA_XFER_CPLT_CB_ID, dma_finish_callback);
    __HAL_DMA_ENABLE_IT(&hdma_memtomem_dma2_stream0, DMA_IT_TC);
    displayer = lv_display_create(800, 480);
    lv_display_set_flush_cb(displayer, LCD_LVGL_flush);
    lv_display_set_buffers(displayer, disp_buf_1, disp_buf_2, sizeof(disp_buf_1), LV_DISPLAY_RENDER_MODE_PARTIAL);
    // 更改活动屏幕的背景颜色
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0x000000), LV_PART_MAIN);

    // 创建触摸屏输入设备
    lv_indev_t *indev_drv = lv_indev_create();
    lv_indev_set_type(indev_drv, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_drv, lvgl_input_torch);
    {
        // 读取速度模式
        uint32_t ethres;
        HAL_ETH_ReadPHYRegister(&heth, 0, 31, &ethres);
        ethres &= 0x1c;
        ethres >>= 2;
        printf("eth:%d\n", ethres);
    }
    GNSS_Init();
    ui_init();
    bsp_sntp_init();
    while (1) {
        MX_LWIP_Process();
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
        lv_timer_handler();
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
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
