/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    rtc.c
 * @brief   This file provides code for the configuration
 *          of the RTC instances.
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
#include "rtc.h"

/* USER CODE BEGIN 0 */
#include "sntp.h"
#include "time.h"
#include "stdio.h"
/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  RTC_AlarmTypeDef sAlarm = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_WEDNESDAY;
  sDate.Month = RTC_MONTH_MAY;
  sDate.Date = 0x8;
  sDate.Year = 0x24;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the Alarm A
  */
  sAlarm.AlarmTime.Hours = 0x0;
  sAlarm.AlarmTime.Minutes = 0x0;
  sAlarm.AlarmTime.Seconds = 0x15;
  sAlarm.AlarmTime.SubSeconds = 0x0;
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY|RTC_ALARMMASK_HOURS
                              |RTC_ALARMMASK_MINUTES;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 0x1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the Alarm B
  */
  sAlarm.AlarmTime.Seconds = 0x30;
  sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY|RTC_ALARMMASK_HOURS;
  sAlarm.Alarm = RTC_ALARM_B;
  if (HAL_RTC_SetAlarm(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the WakeUp
  */
  if (HAL_RTCEx_SetWakeUpTimer(&hrtc, 0, RTC_WAKEUPCLOCK_CK_SPRE_16BITS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/*!
 * @brief 设置 SNTP 的服务器地址，
 * 		 加入多个 IP 以免某个 IP 获取不了时间
 *        执行条件：无
 *
 * @retval: 无
 */
void set_sntp_server_list(void) {
  sntp_setservername(0, "ntp.aliyun.com");
  return;
    uint32_t server_list[SNTP_MAX_SERVERS] = {
        0x0101a0c0
    };
    ip_addr_t sntp_server;

    for (int i = 0; i < SNTP_MAX_SERVERS; i++) {
        sntp_server.addr = server_list[i];
        sntp_setserver(i, &sntp_server); 
    }
}

void bsp_sntp_init(void) {
    // 设置 SNTP 的获取方式 -> 使用向服务器获取方式
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    // 加入授时中心的IP信息
    set_sntp_server_list();
    // SNTP 初始化
    sntp_init();
}

uint32_t get_timestamp(void) {
    struct tm stm;
    static RTC_DateTypeDef g_Date = {0};
    static RTC_TimeTypeDef g_Time = {0};

    /// 获取时间必须在获取日期前
    HAL_RTC_GetTime(&hrtc, &g_Time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &g_Date, RTC_FORMAT_BIN);

    stm.tm_year = g_Date.Year + 100; // RTC_Year rang 0-99,but tm_year since 1900

    stm.tm_mon = g_Date.Month - 1; // RTC_Month rang 1-12,but tm_mon rang 0-11

    stm.tm_mday = g_Date.Date; // RTC_Date rang 1-31 and tm_mday rang 1-31

    stm.tm_hour = g_Time.Hours; // RTC_Hours rang 0-23 and tm_hour rang 0-23

    stm.tm_min = g_Time.Minutes; // RTC_Minutes rang 0-59 and tm_min rang 0-59

    stm.tm_sec = g_Time.Seconds;

    return (mktime(&stm) - (8 * 60 * 60)); /// 配置时由于东八区增加8小时，现为时间戳，需减去
}

void sntp_set_time(uint32_t sntp_time) {
    if (sntp_time == 0) {
        printf("sntp_set_time: wrong!@@\n");
        return;
    }

    printf("sntp_set_time: c00, enter!\n");
    printf("sntp_set_time: c01, get time = %u\n", sntp_time);

#if 1
    struct tm *time;
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    sntp_time += (8 * 60 * 60); /// 北京时间是东8区需偏移8小时

    time = localtime(&sntp_time);

    /*
     * 设置 RTC 的 时间
     */
    sTime.Hours = time->tm_hour;
    sTime.Minutes = time->tm_min;
    sTime.Seconds = time->tm_sec;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
        Error_Handler();
    }

    /*
     * 设置 RTC 的 日期
     */
    sDate.WeekDay = time->tm_wday;
    sDate.Month = (time->tm_mon) + 1;
    sDate.Date = time->tm_mday;
    sDate.Year = (time->tm_year) + 1900 - 2000;
    if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
        Error_Handler();
    }

    printf("sntp_set_time: c02, decode time: 20%d-%02d-%02d %02d:%02d:%02d\n",
           sDate.Year, sDate.Month, sDate.Date, sTime.Hours, sTime.Minutes, sTime.Seconds);

    printf("sntp_set_time: c03, test get = %u\n", get_timestamp());
    printf("sntp_set_time: c04, set rtc time done\n");
#endif
}
/* USER CODE END 1 */
