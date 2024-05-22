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
    if(tp_dev.x[0]<image_width&&tp_dev.y[0]<image_height){
        HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
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
    char str[20] = {};
    sprintf(str, "%02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
    LCD_ShowString(400, 700, str, BLACK, WHITE);
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

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

    W25QXX_Init();
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET);

    LCD_Init();
    tp_dev.init();
    HAL_TIM_Base_Start_IT(&htim3);
    volatile unsigned short temp = 0;
    unsigned char WriteBuf[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned char ReadBuf[10] = {0};
    volatile unsigned char value = 0;
    temp = W25QXX_ReadID();
    if (temp == 0xEF14 || temp == 0x0B15) {
        LCD_ShowString(0, 32, "W25Q16 OK", BLACK, WHITE);
        //HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
    } else {
        LCD_ShowString(0, 32, "W25Q16 ERROR", BLACK, WHITE);
        //HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
    }
    // 将temp转为字符串显示出来
    char temp_str[20];
    sprintf(temp_str, "ID:%4X", temp);
    LCD_ShowString(0, 64, temp_str, BLACK, WHITE);
    W25QXX_Write((u8 *)WriteBuf, sizeof(WriteBuf) - 100, sizeof(WriteBuf)); //  从倒数第100个地址处开始,写入SIZE长度的数据

    W25QXX_Read((u8 *)ReadBuf, sizeof(ReadBuf) - 100, sizeof(WriteBuf));

    for (volatile uint8_t i = 0; i < 10; i++) {
        if (ReadBuf[i] != WriteBuf[i]) {
            value = 1;
            break;
        }
    }

    if (value == 0) {
        LCD_ShowString(0, 48, "W25Q16 Read&Write OK", BLACK, WHITE);
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
    } else {
        LCD_ShowString(0, 48, "W25Q16 Read&Write ERROR", BLACK, WHITE);
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
    }
    W25QXX_Erase_Sector(0);
    memset(ReadBuf, 0, sizeof(ReadBuf));
    W25QXX_Write_Page((u8 *)WriteBuf, 0, sizeof(WriteBuf));
    W25QXX_Read((u8 *)ReadBuf, 0, sizeof(WriteBuf));

    for (volatile uint8_t i = 0; i < 10; i++) {
        if (ReadBuf[i] != WriteBuf[i]) {
            value = 1;
            break;
        }
    }
    if (value == 0) {
        LCD_ShowString(0, 96, "W25Q16 Erase&Write OK", BLACK, WHITE);
        HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
    } else {
        LCD_ShowString(0, 96, "W25Q16 Erase&Write ERROR", BLACK, WHITE);
        HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
    }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    LCD_ShowString(0, 0, "Compile Time", BLACK, WHITE);
    LCD_ShowString(0, 16, __TIME__, BLACK, WHITE);
    uint8_t i;
    uint16_t DAC_value = 0;
    LCD_DrawPicture(0, 0, image_width, image_height, image);
    LCD_Draw_Circle(400, 400, 50, BLUE);
    LCD_ShowString(400, 300, "\xc4\xe3\xcb\xb5\xb5\xc3\xb6\xd4", BLACK, WHITE);
    uint16_t t = 0;
    while (1) {
        torch_process();
        LCD_sudoer_Draw_Triangle_Wave(0, 400, 300, 450, BLACK, t);
        ++t;
        HAL_Delay(5);
        continue;
        sprintf(temp_str, "%02X", ch455_key);
        LCD_ShowString(0, 80, temp_str, BLACK, WHITE);

        if (get_key1_lib()) {
            DAC_value += 200;
            if (DAC_value > 4000) DAC_value = 4000;
        }
        if (get_key2_lib()) {
            if (DAC_value < 200)
                DAC_value = 0;
            else
                DAC_value -= 200;
        }
        float adc1_0 = get_adc1_0();
        char str[20] = "AD:";
        str[3] = (int)adc1_0 + '0';
        str[4] = '.';
        str[5] = ((int)(adc1_0 * 10) % 10) + '0';
        str[6] = ((int)(adc1_0 * 100) % 10) + '0';
        str[7] = ((int)(adc1_0 * 1000) % 10) + '0';
        str[8] = 'V';
        LCD_ShowString(0, 128, str, BLACK, WHITE);
        sprintf(str, "DAC:%d", DAC_value);
        LCD_ShowString(0, 144, str, BLACK, WHITE);
        // CH455_Show_float(adc1_0);
        KEY_MSG_t msg = key_getmsg();
        if (msg.key != KEY_MAX) {
            if (msg.status == KEY_DOWN) {
                HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_RESET);
            }
        } else {
            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_SET);
        }
    /* USER CODE END WHILE */
    MX_USB_HOST_Process();

    /* USER CODE BEGIN 3 */
        HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, DAC_value);
        HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
        HAL_Delay(100);
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
