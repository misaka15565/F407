/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void UpdateTime(size_t t);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOF
#define LED3_Pin GPIO_PIN_2
#define LED3_GPIO_Port GPIOF
#define LED4_Pin GPIO_PIN_3
#define LED4_GPIO_Port GPIOF
#define LED5_Pin GPIO_PIN_4
#define LED5_GPIO_Port GPIOF
#define LED6_Pin GPIO_PIN_5
#define LED6_GPIO_Port GPIOF
#define LED7_Pin GPIO_PIN_6
#define LED7_GPIO_Port GPIOF
#define LED8_Pin GPIO_PIN_7
#define LED8_GPIO_Port GPIOF
#define KEY1_Pin GPIO_PIN_8
#define KEY1_GPIO_Port GPIOF
#define KEY2_Pin GPIO_PIN_9
#define KEY2_GPIO_Port GPIOF
#define KEY3_Pin GPIO_PIN_10
#define KEY3_GPIO_Port GPIOF
#define CTP_SCL_Pin GPIO_PIN_10
#define CTP_SCL_GPIO_Port GPIOB
#define CTP_SDA_Pin GPIO_PIN_15
#define CTP_SDA_GPIO_Port GPIOB
#define SOFTIIC_SCL_Pin GPIO_PIN_2
#define SOFTIIC_SCL_GPIO_Port GPIOG
#define USB_PWR_Pin GPIO_PIN_3
#define USB_PWR_GPIO_Port GPIOG
#define SOFTIIC_SDA_Pin GPIO_PIN_4
#define SOFTIIC_SDA_GPIO_Port GPIOG
#define CTP_INT_Pin GPIO_PIN_8
#define CTP_INT_GPIO_Port GPIOG
#define LCD_BL_Pin GPIO_PIN_9
#define LCD_BL_GPIO_Port GPIOA
#define ETH_RESET_Pin GPIO_PIN_3
#define ETH_RESET_GPIO_Port GPIOD
#define CTP_RST_Pin GPIO_PIN_15
#define CTP_RST_GPIO_Port GPIOG
#define SPI3_CS_Pin GPIO_PIN_6
#define SPI3_CS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
