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
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "W25QXX.h"
#include "CH455.h"
#include "WIFI.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"
#include "w25qxx.h"
#include <stdio.h>
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
/* USER CODE BEGIN PFP */
// 重定向printf
// gcc是这样的
int _write(int fd, char *pBuffer, int size) {
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
    MX_TIM10_Init();
    MX_TIM1_Init();
    MX_FSMC_Init();
    MX_USART3_UART_Init();
    MX_TIM3_Init();
    MX_UART5_Init();
    /* USER CODE BEGIN 2 */
    W25QXX_Init();
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

    LCD_Init();
    HAL_TIM_Base_Start_IT(&htim3);
    volatile unsigned short temp = 0;
    unsigned char WriteBuf[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned char ReadBuf[10] = {0};
    volatile unsigned char value = 0;
    temp = W25QXX_ReadID();
    if (temp == 0xEF14 || temp == 0x0B15) {
        LCD_ShowString(0, 32, "W25Q16 OK", BLACK, WHITE);
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
    } else {
        LCD_ShowString(0, 32, "W25Q16 ERROR", BLACK, WHITE);
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
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
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    // WIFI_Config2();
    LCD_ShowString(0, 0, "Compile Time", BLACK, WHITE);
    LCD_ShowString(0, 16, __TIME__, BLACK, WHITE);
    CH455_Write(CH455_SYSON);
    CH455_Write(CH455_SYSON_8);
    uint8_t showL[2] = {};
    uint8_t showH[2] = {};
    showL[0] = BCD_decode_tab[0];
    showH[0] = BCD_decode_tab[0];
    showL[1] = BCD_decode_tab[0];
    showH[1] = BCD_decode_tab[0];
    CH455_Write(CH455_DIG3 | showL[0]);
    CH455_Write(CH455_DIG2 | showH[0]);
    CH455_Write(CH455_DIG1 | showL[1]);
    CH455_Write(CH455_DIG0 | showH[1]);
    uint8_t i;
    for (i = 1; i < 8; i++) {
        HAL_Delay(500);
        CH455_Write(CH455_SYSON | i << 4); // 1-7级亮度显示
    }

    HAL_Delay(500);
    CH455_Write(CH455_SYSON_8);
    CH455_Write(CH455_DIG0 | CH455_A);
    CH455_Write(CH455_DIG1 | CH455_b);
    CH455_Write(CH455_DIG2 | CH455_C);
    CH455_Write(CH455_DIG3 | CH455_d);
    HAL_Delay(1000);
    while (1) {
        ch455_key = CH455_Read();
        sprintf(temp_str, "%02X", ch455_key);
        LCD_ShowString(0, 80, temp_str, BLACK, WHITE);
        i = ch455_key & 0x3f; // 按键值
        if (i <= 7) {
            i = i - 3;
        } else if (12 <= i & i <= 15) {
            i = i - 7;
        } else if (20 <= i & i <= 23) {
            i = i - 11;
        } else {
            i = i - 15;
        }

        if (i < 10) {
            showH[0] = BCD_decode_tab[0];
            showL[0] = BCD_decode_tab[i];
        } else {
            showH[0] = BCD_decode_tab[i / 10];
            showL[0] = BCD_decode_tab[i - 10];
        }
        // 数码管显示之间的移位操作
        CH455_Write(CH455_DIG3 | showL[0]);
        CH455_Write(CH455_DIG2 | showH[0]);
        CH455_Write(CH455_DIG1 | showL[1]);
        CH455_Write(CH455_DIG0 | showH[1]);

        // 判断按键有没有释放
        while (1) {
            i = CH455_Read(); // 读按键数值
            if (i & 0x40)     // 按键按下没有释放
            {
                // 闪烁
                CH455_Write(CH455_DIG3);
                CH455_Write(CH455_DIG2);
                HAL_Delay(50);
                CH455_Write(CH455_DIG3 | showL[0]);
                CH455_Write(CH455_DIG2 | showH[0]);
                HAL_Delay(50);
            } else // 按键已经释放
            {
                break;
            }
        }
        /* USER CODE END WHILE */

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
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
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
