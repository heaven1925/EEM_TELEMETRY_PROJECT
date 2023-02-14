/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "FreeRTOS.h"

typedef StaticTimer_t osStaticTimerDef_t;

#define 	DEBUG_MODE
#undef 		DEBUG_MODE   				/* Debug mode close */

#define	BSP_PROCESS_TELEMETRYMAIN

#define	BSP_PROCESS_FLASH
#define	BSP_PROCESS_CAN
#define	BSP_PROCESS_RTC
#define	BSP_PROCESS_SDCARD
#define	BSP_PROCESS_WIFI
#define	BSP_PROCESS_NEXTION

extern 	 void             	  MAIN_App (void);

extern   ADC_HandleTypeDef    hadc1;
extern   I2C_HandleTypeDef    hi2c1;
extern   I2C_HandleTypeDef    hi2c2;
extern   I2C_HandleTypeDef    hi2c3;
extern   SPI_HandleTypeDef    hspi1;
extern   SPI_HandleTypeDef    hspi2;
extern   SPI_HandleTypeDef    hspi3;
extern   TIM_HandleTypeDef    htim3;
extern   TIM_HandleTypeDef    htim4;
extern   UART_HandleTypeDef   huart1;
extern   UART_HandleTypeDef   huart2;
extern   UART_HandleTypeDef   huart6;

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define S0_Pin GPIO_PIN_13
#define S0_GPIO_Port GPIOC
#define S1_Pin GPIO_PIN_14
#define S1_GPIO_Port GPIOC
#define S2_Pin GPIO_PIN_15
#define S2_GPIO_Port GPIOC
#define BUSY_Pin GPIO_PIN_4
#define BUSY_GPIO_Port GPIOC
#define RESET_Pin GPIO_PIN_5
#define RESET_GPIO_Port GPIOC
#define DIO2_Pin GPIO_PIN_14
#define DIO2_GPIO_Port GPIOB
#define DIO1_Pin GPIO_PIN_15
#define DIO1_GPIO_Port GPIOB
#define RXEN_Pin GPIO_PIN_6
#define RXEN_GPIO_Port GPIOC
#define TXEN_Pin GPIO_PIN_7
#define TXEN_GPIO_Port GPIOC
#define SET_Pin GPIO_PIN_8
#define SET_GPIO_Port GPIOC
#define DS_Pin GPIO_PIN_4
#define DS_GPIO_Port GPIOB
#define SQ_Pin GPIO_PIN_5
#define SQ_GPIO_Port GPIOB
#define LED_RESET_Pin GPIO_PIN_9
#define LED_RESET_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
