/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file         stm32u5xx_hal_msp.c
 * @brief        This file provides code for the MSP Initialization
 *               and de-Initialization codes.
 ******************************************************************************
 * @attention
 *
 * Portion Copyright (C) 2024 Semilla3 OÜ.  All Rights Reserved.
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

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
/**
 * Initializes the Global MSP.
 */
void HAL_MspInit(void)
{
	/* USER CODE BEGIN MspInit 0 */

	/* USER CODE END MspInit 0 */

	__HAL_RCC_PWR_CLK_ENABLE();

	/* System interrupt init*/
	/* PendSV_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);

	/* USER CODE BEGIN MspInit 1 */

	/* USER CODE END MspInit 1 */
}

/**
 * @brief CRYP MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hcryp: CRYP handle pointer
 * @retval None
 */
void HAL_CRYP_MspInit(CRYP_HandleTypeDef* hcryp)
{
	if(hcryp->Instance==AES)
	{
		/* USER CODE BEGIN AES_MspInit 0 */

		/* USER CODE END AES_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_AES_CLK_ENABLE();
		/* USER CODE BEGIN AES_MspInit 1 */

		/* USER CODE END AES_MspInit 1 */
	}

}

/**
 * @brief CRYP MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hcryp: CRYP handle pointer
 * @retval None
 */
void HAL_CRYP_MspDeInit(CRYP_HandleTypeDef* hcryp)
{
	if(hcryp->Instance==AES)
	{
		/* USER CODE BEGIN AES_MspDeInit 0 */

		/* USER CODE END AES_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_AES_CLK_DISABLE();
		/* USER CODE BEGIN AES_MspDeInit 1 */

		/* USER CODE END AES_MspDeInit 1 */
	}

}

/**
 * @brief CRC MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hcrc: CRC handle pointer
 * @retval None
 */
void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc)
{
	if(hcrc->Instance==CRC)
	{
		/* USER CODE BEGIN CRC_MspInit 0 */

		/* USER CODE END CRC_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_CRC_CLK_ENABLE();
		/* USER CODE BEGIN CRC_MspInit 1 */

		/* USER CODE END CRC_MspInit 1 */
	}

}

/**
 * @brief CRC MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hcrc: CRC handle pointer
 * @retval None
 */
void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc)
{
	if(hcrc->Instance==CRC)
	{
		/* USER CODE BEGIN CRC_MspDeInit 0 */

		/* USER CODE END CRC_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_CRC_CLK_DISABLE();
		/* USER CODE BEGIN CRC_MspDeInit 1 */

		/* USER CODE END CRC_MspDeInit 1 */
	}

}

/**
 * @brief DCACHE MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hdcache: DCACHE handle pointer
 * @retval None
 */
void HAL_DCACHE_MspInit(DCACHE_HandleTypeDef* hdcache)
{
	if(hdcache->Instance==DCACHE1)
	{
		/* USER CODE BEGIN DCACHE1_MspInit 0 */

		/* USER CODE END DCACHE1_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_DCACHE1_CLK_ENABLE();
		/* USER CODE BEGIN DCACHE1_MspInit 1 */

		/* USER CODE END DCACHE1_MspInit 1 */
	}
	else if(hdcache->Instance==DCACHE2)
	{
		/* USER CODE BEGIN DCACHE2_MspInit 0 */

		/* USER CODE END DCACHE2_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_DCACHE2_CLK_ENABLE();
		/* USER CODE BEGIN DCACHE2_MspInit 1 */

		/* USER CODE END DCACHE2_MspInit 1 */
	}

}

/**
 * @brief DCACHE MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hdcache: DCACHE handle pointer
 * @retval None
 */
void HAL_DCACHE_MspDeInit(DCACHE_HandleTypeDef* hdcache)
{
	if(hdcache->Instance==DCACHE1)
	{
		/* USER CODE BEGIN DCACHE1_MspDeInit 0 */

		/* USER CODE END DCACHE1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_DCACHE1_CLK_DISABLE();
		/* USER CODE BEGIN DCACHE1_MspDeInit 1 */

		/* USER CODE END DCACHE1_MspDeInit 1 */
	}
	else if(hdcache->Instance==DCACHE2)
	{
		/* USER CODE BEGIN DCACHE2_MspDeInit 0 */

		/* USER CODE END DCACHE2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_DCACHE2_CLK_DISABLE();
		/* USER CODE BEGIN DCACHE2_MspDeInit 1 */

		/* USER CODE END DCACHE2_MspDeInit 1 */
	}

}

/**
 * @brief DMA2D MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hdma2d: DMA2D handle pointer
 * @retval None
 */
void HAL_DMA2D_MspInit(DMA2D_HandleTypeDef* hdma2d)
{
	if(hdma2d->Instance==DMA2D)
	{
		/* USER CODE BEGIN DMA2D_MspInit 0 */

		/* USER CODE END DMA2D_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_DMA2D_CLK_ENABLE();
		/* DMA2D interrupt Init */
		HAL_NVIC_SetPriority(DMA2D_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(DMA2D_IRQn);
		/* USER CODE BEGIN DMA2D_MspInit 1 */

		/* USER CODE END DMA2D_MspInit 1 */
	}

}

/**
 * @brief DMA2D MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hdma2d: DMA2D handle pointer
 * @retval None
 */
void HAL_DMA2D_MspDeInit(DMA2D_HandleTypeDef* hdma2d)
{
	if(hdma2d->Instance==DMA2D)
	{
		/* USER CODE BEGIN DMA2D_MspDeInit 0 */

		/* USER CODE END DMA2D_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_DMA2D_CLK_DISABLE();

		/* DMA2D interrupt DeInit */
		HAL_NVIC_DisableIRQ(DMA2D_IRQn);
		/* USER CODE BEGIN DMA2D_MspDeInit 1 */

		/* USER CODE END DMA2D_MspDeInit 1 */
	}

}

/**
 * @brief GPU2D MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hgpu2d: GPU2D handle pointer
 * @retval None
 */
void HAL_GPU2D_MspInit(GPU2D_HandleTypeDef* hgpu2d)
{
	if(hgpu2d->Instance==GPU2D)
	{
		/* USER CODE BEGIN GPU2D_MspInit 0 */

		/* USER CODE END GPU2D_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_GPU2D_CLK_ENABLE();
		__HAL_RCC_DCACHE2_CLK_ENABLE();
		/* GPU2D interrupt Init */
		HAL_NVIC_SetPriority(GPU2D_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(GPU2D_IRQn);
		HAL_NVIC_SetPriority(GPU2D_ER_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(GPU2D_ER_IRQn);
		/* USER CODE BEGIN GPU2D_MspInit 1 */

		/* USER CODE END GPU2D_MspInit 1 */
	}

}

/**
 * @brief GPU2D MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hgpu2d: GPU2D handle pointer
 * @retval None
 */
void HAL_GPU2D_MspDeInit(GPU2D_HandleTypeDef* hgpu2d)
{
	if(hgpu2d->Instance==GPU2D)
	{
		/* USER CODE BEGIN GPU2D_MspDeInit 0 */

		/* USER CODE END GPU2D_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_GPU2D_CLK_DISABLE();
		__HAL_RCC_DCACHE2_CLK_DISABLE();

		/* GPU2D interrupt DeInit */
		HAL_NVIC_DisableIRQ(GPU2D_IRQn);
		HAL_NVIC_DisableIRQ(GPU2D_ER_IRQn);
		/* USER CODE BEGIN GPU2D_MspDeInit 1 */

		/* USER CODE END GPU2D_MspDeInit 1 */
	}

}

/**
 * @brief HASH MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hhash: HASH handle pointer
 * @retval None
 */
void HAL_HASH_MspInit(HASH_HandleTypeDef* hhash)
{
	/* USER CODE BEGIN HASH_MspInit 0 */

	/* USER CODE END HASH_MspInit 0 */
	/* Peripheral clock enable */
	__HAL_RCC_HASH_CLK_ENABLE();
	/* USER CODE BEGIN HASH_MspInit 1 */

	/* USER CODE END HASH_MspInit 1 */

}

/**
 * @brief HASH MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hhash: HASH handle pointer
 * @retval None
 */
void HAL_HASH_MspDeInit(HASH_HandleTypeDef* hhash)
{
	/* USER CODE BEGIN HASH_MspDeInit 0 */

	/* USER CODE END HASH_MspDeInit 0 */
	/* Peripheral clock disable */
	__HAL_RCC_HASH_CLK_DISABLE();
	/* USER CODE BEGIN HASH_MspDeInit 1 */

	/* USER CODE END HASH_MspDeInit 1 */

}

/**
 * @brief I2C MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
	if(hi2c->Instance==I2C1)
	{
		/* USER CODE BEGIN I2C1_MspInit 0 */

		/* USER CODE END I2C1_MspInit 0 */

		/** Initializes the peripherals clock
		 */
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
		PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* Peripheral clock enable */
		__HAL_RCC_I2C1_CLK_ENABLE();
		/* USER CODE BEGIN I2C1_MspInit 1 */

		/* USER CODE END I2C1_MspInit 1 */
	}

}

/**
 * @brief I2C MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
	if(hi2c->Instance==I2C1)
	{
		/* USER CODE BEGIN I2C1_MspDeInit 0 */

		/* USER CODE END I2C1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_I2C1_CLK_DISABLE();

		/**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
		 */
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

		/* USER CODE BEGIN I2C1_MspDeInit 1 */

		/* USER CODE END I2C1_MspDeInit 1 */
	}

}

/**
 * @brief LTDC MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hltdc: LTDC handle pointer
 * @retval None
 */
void HAL_LTDC_MspInit(LTDC_HandleTypeDef* hltdc)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
	if(hltdc->Instance==LTDC)
	{
		/* USER CODE BEGIN LTDC_MspInit 0 */

		/* USER CODE END LTDC_MspInit 0 */

		/** Initializes the peripherals clock
		 */
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
		PeriphClkInit.LtdcClockSelection = RCC_LTDCCLKSOURCE_PLL3;
		PeriphClkInit.PLL3.PLL3Source = RCC_PLLSOURCE_HSE;
		PeriphClkInit.PLL3.PLL3M = 4;
		PeriphClkInit.PLL3.PLL3N = 120;
		PeriphClkInit.PLL3.PLL3P = 2;
		PeriphClkInit.PLL3.PLL3Q = 2;
		PeriphClkInit.PLL3.PLL3R = 70;
		PeriphClkInit.PLL3.PLL3RGE = RCC_PLLVCIRANGE_0;
		PeriphClkInit.PLL3.PLL3FRACN = 0;
		PeriphClkInit.PLL3.PLL3ClockOut = RCC_PLL3_DIVR;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
		{
			Error_Handler();
		}

		/* Peripheral clock enable */
		__HAL_RCC_LTDC_CLK_ENABLE();

		__HAL_RCC_GPIOE_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**LTDC GPIO Configuration
    PE2     ------> LTDC_R0
    PE3     ------> LTDC_R1
    PE4     ------> LTDC_B0
    PE5     ------> LTDC_G0
    PE6     ------> LTDC_G1
    PB2     ------> LTDC_B1
    PE7     ------> LTDC_B6
    PE8     ------> LTDC_B7
    PE9     ------> LTDC_G2
    PE10     ------> LTDC_G3
    PE11     ------> LTDC_G4
    PE12     ------> LTDC_G5
    PE13     ------> LTDC_G6
    PE14     ------> LTDC_G7
    PE15     ------> LTDC_R2
    PD8     ------> LTDC_R3
    PD9     ------> LTDC_R4
    PD10     ------> LTDC_R5
    PD11     ------> LTDC_R6
    PD12     ------> LTDC_R7
    PD13     ------> LTDC_VSYNC
    PD14     ------> LTDC_B2
    PD15     ------> LTDC_B3
    PD0     ------> LTDC_B4
    PD1     ------> LTDC_B5
    PD3     ------> LTDC_CLK
    PD6     ------> LTDC_DE
    PE0     ------> LTDC_HSYNC
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
				|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
				|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
				|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF8_LTDC;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF8_LTDC;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
				|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
				|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF8_LTDC;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

		/* LTDC interrupt Init */
		HAL_NVIC_SetPriority(LTDC_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(LTDC_IRQn);
		HAL_NVIC_SetPriority(LTDC_ER_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(LTDC_ER_IRQn);
		/* USER CODE BEGIN LTDC_MspInit 1 */

		/* USER CODE END LTDC_MspInit 1 */
	}

}

/**
 * @brief LTDC MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hltdc: LTDC handle pointer
 * @retval None
 */
void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* hltdc)
{
	if(hltdc->Instance==LTDC)
	{
		/* USER CODE BEGIN LTDC_MspDeInit 0 */

		/* USER CODE END LTDC_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_LTDC_CLK_DISABLE();

		/**LTDC GPIO Configuration
    PE2     ------> LTDC_R0
    PE3     ------> LTDC_R1
    PE4     ------> LTDC_B0
    PE5     ------> LTDC_G0
    PE6     ------> LTDC_G1
    PB2     ------> LTDC_B1
    PE7     ------> LTDC_B6
    PE8     ------> LTDC_B7
    PE9     ------> LTDC_G2
    PE10     ------> LTDC_G3
    PE11     ------> LTDC_G4
    PE12     ------> LTDC_G5
    PE13     ------> LTDC_G6
    PE14     ------> LTDC_G7
    PE15     ------> LTDC_R2
    PD8     ------> LTDC_R3
    PD9     ------> LTDC_R4
    PD10     ------> LTDC_R5
    PD11     ------> LTDC_R6
    PD12     ------> LTDC_R7
    PD13     ------> LTDC_VSYNC
    PD14     ------> LTDC_B2
    PD15     ------> LTDC_B3
    PD0     ------> LTDC_B4
    PD1     ------> LTDC_B5
    PD3     ------> LTDC_CLK
    PD6     ------> LTDC_DE
    PE0     ------> LTDC_HSYNC
		 */
		HAL_GPIO_DeInit(GPIOE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
				|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
				|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
				|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0);

		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2);

		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
				|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
				|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_6);

		/* LTDC interrupt DeInit */
		HAL_NVIC_DisableIRQ(LTDC_IRQn);
		HAL_NVIC_DisableIRQ(LTDC_ER_IRQn);
		/* USER CODE BEGIN LTDC_MspDeInit 1 */

		/* USER CODE END LTDC_MspDeInit 1 */
	}

}

/**
 * @brief TIM_PWM MSP Initialization
 * This function configures the hardware resources used in this example
 * @param htim_pwm: TIM_PWM handle pointer
 * @retval None
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{
	if(htim_pwm->Instance==TIM1)
	{
		/* USER CODE BEGIN TIM1_MspInit 0 */

		/* USER CODE END TIM1_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_TIM1_CLK_ENABLE();
		/* USER CODE BEGIN TIM1_MspInit 1 */

		/* USER CODE END TIM1_MspInit 1 */
	}

}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(htim->Instance==TIM1)
	{
		/* USER CODE BEGIN TIM1_MspPostInit 0 */

		/* USER CODE END TIM1_MspPostInit 0 */

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**TIM1 GPIO Configuration
    PA8     ------> TIM1_CH1
		 */
		GPIO_InitStruct.Pin = LCD_BACKLIGHT_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
		HAL_GPIO_Init(LCD_BACKLIGHT_GPIO_Port, &GPIO_InitStruct);

		/* USER CODE BEGIN TIM1_MspPostInit 1 */

		/* USER CODE END TIM1_MspPostInit 1 */
	}

}
/**
 * @brief TIM_PWM MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param htim_pwm: TIM_PWM handle pointer
 * @retval None
 */
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm)
{
	if(htim_pwm->Instance==TIM1)
	{
		/* USER CODE BEGIN TIM1_MspDeInit 0 */

		/* USER CODE END TIM1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM1_CLK_DISABLE();
		/* USER CODE BEGIN TIM1_MspDeInit 1 */

		/* USER CODE END TIM1_MspDeInit 1 */
	}

}

/**
 * @brief UART MSP Initialization
 * This function configures the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
	if(huart->Instance==UART4)
	{
		/* USER CODE BEGIN UART4_MspInit 0 */

		/* USER CODE END UART4_MspInit 0 */

		/** Initializes the peripherals clock
		 */
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_UART4;
		PeriphClkInit.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
		{
			Error_Handler();
		}

		/* Peripheral clock enable */
		__HAL_RCC_UART4_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**UART4 GPIO Configuration
    PA0     ------> UART4_TX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_0;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN UART4_MspInit 1 */

		/* USER CODE END UART4_MspInit 1 */
	}
	else if(huart->Instance==USART2)
	{
		/* USER CODE BEGIN USART2_MspInit 0 */

		/* USER CODE END USART2_MspInit 0 */

		/** Initializes the peripherals clock
		 */
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
		PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
		{
			Error_Handler();
		}

		/* Peripheral clock enable */
		__HAL_RCC_USART2_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
		 */
		GPIO_InitStruct.Pin = BLE_UART2_TX_Pin|BLE_UART2_RX_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN USART2_MspInit 1 */

		/* USER CODE END USART2_MspInit 1 */
	}
	else if(huart->Instance==USART3)
	{
		/* USER CODE BEGIN USART3_MspInit 0 */

		/* USER CODE END USART3_MspInit 0 */

		/** Initializes the peripherals clock
		 */
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART3;
		PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
		{
			Error_Handler();
		}

		/* Peripheral clock enable */
		__HAL_RCC_USART3_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART3 GPIO Configuration
    PA5     ------> USART3_RX
    PA7     ------> USART3_TX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USART3 interrupt Init */
		HAL_NVIC_SetPriority(USART3_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(USART3_IRQn);
		/* USER CODE BEGIN USART3_MspInit 1 */

		/* USER CODE END USART3_MspInit 1 */
	}

}

/**
 * @brief UART MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
	if(huart->Instance==UART4)
	{
		/* USER CODE BEGIN UART4_MspDeInit 0 */

		/* USER CODE END UART4_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_UART4_CLK_DISABLE();

		/**UART4 GPIO Configuration
    PA0     ------> UART4_TX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);

		/* USER CODE BEGIN UART4_MspDeInit 1 */

		/* USER CODE END UART4_MspDeInit 1 */
	}
	else if(huart->Instance==USART2)
	{
		/* USER CODE BEGIN USART2_MspDeInit 0 */

		/* USER CODE END USART2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART2_CLK_DISABLE();

		/**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
		 */
		HAL_GPIO_DeInit(GPIOA, BLE_UART2_TX_Pin|BLE_UART2_RX_Pin);

		/* USER CODE BEGIN USART2_MspDeInit 1 */

		/* USER CODE END USART2_MspDeInit 1 */
	}
	else if(huart->Instance==USART3)
	{
		/* USER CODE BEGIN USART3_MspDeInit 0 */

		/* USER CODE END USART3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART3_CLK_DISABLE();

		/**USART3 GPIO Configuration
    PA5     ------> USART3_RX
    PA7     ------> USART3_TX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_7);

		/* USART3 interrupt DeInit */
		HAL_NVIC_DisableIRQ(USART3_IRQn);
		/* USER CODE BEGIN USART3_MspDeInit 1 */

		/* USER CODE END USART3_MspDeInit 1 */
	}

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
