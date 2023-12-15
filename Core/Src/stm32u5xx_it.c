/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32u5xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 * @attention
 *
 * Portion Copyright (C) 2023 Semilla3 OÜ.  All Rights Reserved.
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
#include "stm32u5xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA2D_HandleTypeDef hdma2d;
extern GPU2D_HandleTypeDef hgpu2d;
extern LTDC_HandleTypeDef hltdc;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim6;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void)
{
	/* USER CODE BEGIN NonMaskableInt_IRQn 0 */
	/* USER CODE END NonMaskableInt_IRQn 0 */
	/* USER CODE BEGIN NonMaskableInt_IRQn 1 */
	while (1)
	{
	}
	/* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)
{
	/* USER CODE BEGIN HardFault_IRQn 0 */
	/* USER CODE END HardFault_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_HardFault_IRQn 0 */
		/* USER CODE END W1_HardFault_IRQn 0 */
	}
}

/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void)
{
	/* USER CODE BEGIN MemoryManagement_IRQn 0 */
	/* USER CODE END MemoryManagement_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
		/* USER CODE END W1_MemoryManagement_IRQn 0 */
	}
}

/**
 * @brief This function handles Prefetch fault, memory access fault.
 */
void BusFault_Handler(void)
{
	/* USER CODE BEGIN BusFault_IRQn 0 */
	/* USER CODE END BusFault_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_BusFault_IRQn 0 */
		/* USER CODE END W1_BusFault_IRQn 0 */
	}
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void)
{
	/* USER CODE BEGIN UsageFault_IRQn 0 */
	/* USER CODE END UsageFault_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_UsageFault_IRQn 0 */
		/* USER CODE END W1_UsageFault_IRQn 0 */
	}
}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void)
{
	/* USER CODE BEGIN DebugMonitor_IRQn 0 */

	/* USER CODE END DebugMonitor_IRQn 0 */
	/* USER CODE BEGIN DebugMonitor_IRQn 1 */

	/* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32U5xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32u5xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles TIM6 global interrupt.
 */
void TIM6_IRQHandler(void)
{
	/* USER CODE BEGIN TIM6_IRQn 0 */

	/* USER CODE END TIM6_IRQn 0 */
	HAL_TIM_IRQHandler(&htim6);
	/* USER CODE BEGIN TIM6_IRQn 1 */

	/* USER CODE END TIM6_IRQn 1 */
}

/**
 * @brief This function handles USART3 global interrupt.
 */
void USART3_IRQHandler(void)
{
	/* USER CODE BEGIN USART3_IRQn 0 */

	/* USER CODE END USART3_IRQn 0 */
	HAL_UART_IRQHandler(&huart3);
	/* USER CODE BEGIN USART3_IRQn 1 */

	/* USER CODE END USART3_IRQn 1 */
}

/**
 * @brief This function handles DMA2D global interrupt.
 */
void DMA2D_IRQHandler(void)
{
	/* USER CODE BEGIN DMA2D_IRQn 0 */

	/* USER CODE END DMA2D_IRQn 0 */
	HAL_DMA2D_IRQHandler(&hdma2d);
	/* USER CODE BEGIN DMA2D_IRQn 1 */

	/* USER CODE END DMA2D_IRQn 1 */
}

/**
 * @brief This function handles GPU2D global interrupt.
 */
void GPU2D_IRQHandler(void)
{
	/* USER CODE BEGIN GPU2D_IRQn 0 */

	/* USER CODE END GPU2D_IRQn 0 */
	HAL_GPU2D_IRQHandler(&hgpu2d);
	/* USER CODE BEGIN GPU2D_IRQn 1 */

	/* USER CODE END GPU2D_IRQn 1 */
}

/**
 * @brief This function handles GPU2D Error interrupt.
 */
void GPU2D_ER_IRQHandler(void)
{
	/* USER CODE BEGIN GPU2D_ER_IRQn 0 */

	/* USER CODE END GPU2D_ER_IRQn 0 */
	HAL_GPU2D_ER_IRQHandler(&hgpu2d);
	/* USER CODE BEGIN GPU2D_ER_IRQn 1 */

	/* USER CODE END GPU2D_ER_IRQn 1 */
}

/**
 * @brief This function handles LCD-TFT global interrupt.
 */
void LTDC_IRQHandler(void)
{
	/* USER CODE BEGIN LTDC_IRQn 0 */

	/* USER CODE END LTDC_IRQn 0 */
	HAL_LTDC_IRQHandler(&hltdc);
	/* USER CODE BEGIN LTDC_IRQn 1 */

	/* USER CODE END LTDC_IRQn 1 */
}

/**
 * @brief This function handles LCD-TFT Error interrupt.
 */
void LTDC_ER_IRQHandler(void)
{
	/* USER CODE BEGIN LTDC_ER_IRQn 0 */

	/* USER CODE END LTDC_ER_IRQn 0 */
	HAL_LTDC_IRQHandler(&hltdc);
	/* USER CODE BEGIN LTDC_ER_IRQn 1 */

	/* USER CODE END LTDC_ER_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
