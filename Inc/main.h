/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f2xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
ADC_HandleTypeDef* Get_HADC1_Ptr(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LeftEncoderCh1_Pin GPIO_PIN_0
#define LeftEncoderCh1_GPIO_Port GPIOA
#define LeftEnconderCh2_Pin GPIO_PIN_1
#define LeftEnconderCh2_GPIO_Port GPIOA
#define LeftEmitter_Pin GPIO_PIN_2
#define LeftEmitter_GPIO_Port GPIOA
#define LeftReceiver_Pin GPIO_PIN_6
#define LeftReceiver_GPIO_Port GPIOA
#define FrontLeftEmitter_Pin GPIO_PIN_7
#define FrontLeftEmitter_GPIO_Port GPIOA
#define FrontLeftReceiver_Pin GPIO_PIN_4
#define FrontLeftReceiver_GPIO_Port GPIOC
#define FrontRightReceiver_Pin GPIO_PIN_0
#define FrontRightReceiver_GPIO_Port GPIOB
#define RightReceiver_Pin GPIO_PIN_1
#define RightReceiver_GPIO_Port GPIOB
#define FrontRightEmitter_Pin GPIO_PIN_10
#define FrontRightEmitter_GPIO_Port GPIOB
#define RightEmitter_Pin GPIO_PIN_12
#define RightEmitter_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_14
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_15
#define LED2_GPIO_Port GPIOB
#define M1R_Pin GPIO_PIN_6
#define M1R_GPIO_Port GPIOC
#define M2R_Pin GPIO_PIN_7
#define M2R_GPIO_Port GPIOC
#define RightEncoderCh1_Pin GPIO_PIN_8
#define RightEncoderCh1_GPIO_Port GPIOA
#define RightEncoderCh2_Pin GPIO_PIN_9
#define RightEncoderCh2_GPIO_Port GPIOA
#define M1L_Pin GPIO_PIN_6
#define M1L_GPIO_Port GPIOB
#define M2L_Pin GPIO_PIN_7
#define M2L_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
