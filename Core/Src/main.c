/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
#include "cmsis_os2.h"
#include "app_touchgfx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/*********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************/

#include "stm32u5xx_hal_cryp_ex.h"

/*********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************/
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
CRYP_HandleTypeDef hcryp;
uint32_t pKeyAES[8] = {0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000};
uint32_t pInitVectAES[4] = {0x00000000,0x00000000,0x00000000,0x00000000};
__ALIGN_BEGIN static const uint32_t HeaderAES[1] __ALIGN_END = {0x00000000};

CRC_HandleTypeDef hcrc;

DCACHE_HandleTypeDef hdcache1;
DCACHE_HandleTypeDef hdcache2;

DMA2D_HandleTypeDef hdma2d;

GPU2D_HandleTypeDef hgpu2d;

HASH_HandleTypeDef hhash;

I2C_HandleTypeDef hi2c1;

LTDC_HandleTypeDef hltdc;

TIM_HandleTypeDef htim1;

#ifdef DEBUG_PRINTF
UART_HandleTypeDef huart4;
#endif
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
/*********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************/

struct cuvex cuvex = {0};

/*********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************/
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void SystemPower_Config(void);
void MX_FREERTOS_Init(void);
static void MX_GPIO_Init(void);
static void MX_LTDC_Init(void);
static void MX_I2C1_Init(void);
#ifdef DEBUG_PRINTF
static void MX_UART4_Init(void);
#endif
static void MX_USART2_UART_Init(void);
static void MX_DCACHE1_Init(void);
static void MX_DCACHE2_Init(void);
static void MX_DMA2D_Init(void);
static void MX_ICACHE_Init(void);
static void MX_CRC_Init(void);
static void MX_GPU2D_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_AES_Init(void);
static void MX_HASH_Init(void);
/* USER CODE BEGIN PFP */

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

	/* Configure the System Power */
	SystemPower_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_LTDC_Init();
	MX_I2C1_Init();
#ifdef DEBUG_PRINTF
	MX_UART4_Init();
#endif
	MX_USART2_UART_Init();
	MX_DCACHE1_Init();
	MX_DCACHE2_Init();
	MX_DMA2D_Init();
	MX_ICACHE_Init();
	MX_CRC_Init();
	MX_GPU2D_Init();
	MX_USART3_UART_Init();
	MX_TIM1_Init();
	MX_AES_Init();
	MX_HASH_Init();
	MX_TouchGFX_Init();
	/* Call PreOsInit function */
	MX_TouchGFX_PreOSInit();
	/* USER CODE BEGIN 2 */

#ifdef DEBUG_PRINTF
	printf("App Code is running...\r\n\r\n");
#endif

	/* USER CODE END 2 */

	/* Init scheduler */
	osKernelInitialize();

	/* Call init function for freertos objects (in freertos.c) */
	MX_FREERTOS_Init();

	/* Start scheduler */
	osKernelStart();

	/* We should never get here as control is now taken by the scheduler */
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
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
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV1;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 80;
	RCC_OscInitStruct.PLL.PLLP = 2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLR = 2;
	RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_0;
	RCC_OscInitStruct.PLL.PLLFRACN = 0;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
			|RCC_CLOCKTYPE_PCLK3;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief Power Configuration
 * @retval None
 */
static void SystemPower_Config(void)
{

	/*
	 * Switch to SMPS regulator instead of LDO
	 */
	if (HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN PWR */
	/* USER CODE END PWR */
}

/**
 * @brief AES Initialization Function
 * @param None
 * @retval None
 */
static void MX_AES_Init(void)
{

	/* USER CODE BEGIN AES_Init 0 */

	/* USER CODE END AES_Init 0 */

	/* USER CODE BEGIN AES_Init 1 */

	/* USER CODE END AES_Init 1 */
	hcryp.Instance = AES;
	hcryp.Init.DataType = CRYP_NO_SWAP;
	hcryp.Init.KeySize = CRYP_KEYSIZE_256B;
	hcryp.Init.pKey = (uint32_t *)pKeyAES;
	hcryp.Init.pInitVect = (uint32_t *)pInitVectAES;
	hcryp.Init.Algorithm = CRYP_AES_GCM_GMAC;
	hcryp.Init.Header = (uint32_t *)HeaderAES;
	hcryp.Init.HeaderSize = 1;
	hcryp.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
	hcryp.Init.HeaderWidthUnit = CRYP_HEADERWIDTHUNIT_WORD;
	hcryp.Init.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ALWAYS;
	hcryp.Init.KeyMode = CRYP_KEYMODE_NORMAL;
	if (HAL_CRYP_Init(&hcryp) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN AES_Init 2 */

	/* USER CODE END AES_Init 2 */

}

/**
 * @brief CRC Initialization Function
 * @param None
 * @retval None
 */
static void MX_CRC_Init(void)
{

	/* USER CODE BEGIN CRC_Init 0 */

	/* USER CODE END CRC_Init 0 */

	/* USER CODE BEGIN CRC_Init 1 */

	/* USER CODE END CRC_Init 1 */
	hcrc.Instance = CRC;
	hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
	hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
	hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
	hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
	hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
	if (HAL_CRC_Init(&hcrc) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN CRC_Init 2 */

	/* USER CODE END CRC_Init 2 */

}

/**
 * @brief DCACHE1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_DCACHE1_Init(void)
{

	/* USER CODE BEGIN DCACHE1_Init 0 */

	/* USER CODE END DCACHE1_Init 0 */

	/* USER CODE BEGIN DCACHE1_Init 1 */

	/* USER CODE END DCACHE1_Init 1 */
	hdcache1.Instance = DCACHE1;
	hdcache1.Init.ReadBurstType = DCACHE_READ_BURST_INCR;
	if (HAL_DCACHE_Init(&hdcache1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN DCACHE1_Init 2 */

	/* USER CODE END DCACHE1_Init 2 */

}

/**
 * @brief DCACHE2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_DCACHE2_Init(void)
{

	/* USER CODE BEGIN DCACHE2_Init 0 */

	/* USER CODE END DCACHE2_Init 0 */

	/* USER CODE BEGIN DCACHE2_Init 1 */

	/* USER CODE END DCACHE2_Init 1 */
	hdcache2.Instance = DCACHE2;
	hdcache2.Init.ReadBurstType = DCACHE_READ_BURST_INCR;
	if (HAL_DCACHE_Init(&hdcache2) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN DCACHE2_Init 2 */

	/* USER CODE END DCACHE2_Init 2 */

}

/**
 * @brief DMA2D Initialization Function
 * @param None
 * @retval None
 */
static void MX_DMA2D_Init(void)
{

	/* USER CODE BEGIN DMA2D_Init 0 */

	/* USER CODE END DMA2D_Init 0 */

	/* USER CODE BEGIN DMA2D_Init 1 */

	/* USER CODE END DMA2D_Init 1 */
	hdma2d.Instance = DMA2D;
	hdma2d.Init.Mode = DMA2D_R2M;
	hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB888;
	hdma2d.Init.OutputOffset = 0;
	hdma2d.Init.BytesSwap = DMA2D_BYTES_REGULAR;
	hdma2d.Init.LineOffsetMode = DMA2D_LOM_PIXELS;
	if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN DMA2D_Init 2 */

	/* USER CODE END DMA2D_Init 2 */

}

/**
 * @brief GPU2D Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPU2D_Init(void)
{

	/* USER CODE BEGIN GPU2D_Init 0 */

	/* USER CODE END GPU2D_Init 0 */

	/* USER CODE BEGIN GPU2D_Init 1 */

	/* USER CODE END GPU2D_Init 1 */
	hgpu2d.Instance = GPU2D;
	if (HAL_GPU2D_Init(&hgpu2d) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN GPU2D_Init 2 */

	/* USER CODE END GPU2D_Init 2 */

}

/**
 * @brief HASH Initialization Function
 * @param None
 * @retval None
 */
static void MX_HASH_Init(void)
{

	/* USER CODE BEGIN HASH_Init 0 */

	/* USER CODE END HASH_Init 0 */

	/* USER CODE BEGIN HASH_Init 1 */

	/* USER CODE END HASH_Init 1 */
	hhash.Init.DataType = HASH_DATATYPE_8B;
	if (HAL_HASH_Init(&hhash) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN HASH_Init 2 */

	/* USER CODE END HASH_Init 2 */

}

/**
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void)
{

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x30909DEC;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

}

/**
 * @brief ICACHE Initialization Function
 * @param None
 * @retval None
 */
static void MX_ICACHE_Init(void)
{

	/* USER CODE BEGIN ICACHE_Init 0 */

	/* USER CODE END ICACHE_Init 0 */

	/* USER CODE BEGIN ICACHE_Init 1 */

	/* USER CODE END ICACHE_Init 1 */

	/** Enable instruction cache in 1-way (direct mapped cache)
	 */
	if (HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_ICACHE_Enable() != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN ICACHE_Init 2 */

	/* USER CODE END ICACHE_Init 2 */

}

/**
 * @brief LTDC Initialization Function
 * @param None
 * @retval None
 */
static void MX_LTDC_Init(void)
{

	/* USER CODE BEGIN LTDC_Init 0 */

	/* USER CODE END LTDC_Init 0 */

	LTDC_LayerCfgTypeDef pLayerCfg = {0};

	/* USER CODE BEGIN LTDC_Init 1 */

	/* USER CODE END LTDC_Init 1 */
	hltdc.Instance = LTDC;
	hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
	hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
	hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
	hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
	hltdc.Init.HorizontalSync = 1;
	hltdc.Init.VerticalSync = 9;
	hltdc.Init.AccumulatedHBP = 69;
	hltdc.Init.AccumulatedVBP = 27;
	hltdc.Init.AccumulatedActiveW = 389;
	hltdc.Init.AccumulatedActiveH = 267;
	hltdc.Init.TotalWidth = 409;
	hltdc.Init.TotalHeigh = 271;
	hltdc.Init.Backcolor.Blue = 0;
	hltdc.Init.Backcolor.Green = 0;
	hltdc.Init.Backcolor.Red = 0;
	if (HAL_LTDC_Init(&hltdc) != HAL_OK)
	{
		Error_Handler();
	}
	pLayerCfg.WindowX0 = 0;
	pLayerCfg.WindowX1 = 320;
	pLayerCfg.WindowY0 = 0;
	pLayerCfg.WindowY1 = 240;
	pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
	pLayerCfg.Alpha = 255;
	pLayerCfg.Alpha0 = 0;
	pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
	pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
	pLayerCfg.FBStartAdress = 0;
	pLayerCfg.ImageWidth = 320;
	pLayerCfg.ImageHeight = 240;
	pLayerCfg.Backcolor.Blue = 0;
	pLayerCfg.Backcolor.Green = 0;
	pLayerCfg.Backcolor.Red = 0;
	if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN LTDC_Init 2 */

	/* USER CODE END LTDC_Init 2 */

}

/**
 * @brief TIM1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM1_Init(void)
{

	/* USER CODE BEGIN TIM1_Init 0 */

	/* USER CODE END TIM1_Init 0 */

	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

	/* USER CODE BEGIN TIM1_Init 1 */

	/* USER CODE END TIM1_Init 1 */
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 1000-1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 99;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.BreakFilter = 0;
	sBreakDeadTimeConfig.BreakAFMode = TIM_BREAK_AFMODE_INPUT;
	sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
	sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
	sBreakDeadTimeConfig.Break2Filter = 0;
	sBreakDeadTimeConfig.Break2AFMode = TIM_BREAK_AFMODE_INPUT;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM1_Init 2 */
	TIM1->CCR1 = 100;
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	/* USER CODE END TIM1_Init 2 */
	HAL_TIM_MspPostInit(&htim1);

}

#ifdef DEBUG_PRINTF
/**
 * @brief UART4 Initialization Function
 * @param None
 * @retval None
 */
static void MX_UART4_Init(void)
{

	/* USER CODE BEGIN UART4_Init 0 */

	/* USER CODE END UART4_Init 0 */

	/* USER CODE BEGIN UART4_Init 1 */

	/* USER CODE END UART4_Init 1 */
	huart4.Instance = UART4;
	huart4.Init.BaudRate = 115200;
	huart4.Init.WordLength = UART_WORDLENGTH_8B;
	huart4.Init.StopBits = UART_STOPBITS_1;
	huart4.Init.Parity = UART_PARITY_NONE;
	huart4.Init.Mode = UART_MODE_TX;
	huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart4.Init.OverSampling = UART_OVERSAMPLING_16;
	huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart4.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_HalfDuplex_Init(&huart4) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart4, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart4, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart4) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN UART4_Init 2 */

	/* USER CODE END UART4_Init 2 */

}
#endif

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void)
{

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**
 * @brief USART3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART3_UART_Init(void)
{

	/* USER CODE BEGIN USART3_Init 0 */

	/* USER CODE END USART3_Init 0 */

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 57600;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart3) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART3_Init 2 */

	/* USER CODE END USART3_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, BLE_EN_Pin|NFC_EN_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, LED_RED_Pin|LED_GREEN_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, BLE_BOOT_Pin|BLE_WAKEUP_Pin|LCD_RESET_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(NFC_NSS_GPIO_Port, NFC_NSS_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(TOUCH_RESET_GPIO_Port, TOUCH_RESET_Pin, GPIO_PIN_SET);

	/*Configure GPIO pins : BLE_EN_Pin LED_RED_Pin LED_GREEN_Pin NFC_EN_Pin */
	GPIO_InitStruct.Pin = BLE_EN_Pin|LED_RED_Pin|LED_GREEN_Pin|NFC_EN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : BLE_BOOT_Pin BLE_WAKEUP_Pin LCD_RESET_Pin */
	GPIO_InitStruct.Pin = BLE_BOOT_Pin|BLE_WAKEUP_Pin|LCD_RESET_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : NFC_NSS_Pin */
	GPIO_InitStruct.Pin = NFC_NSS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(NFC_NSS_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : HW_VER_1_Pin HW_VER_2_Pin HW_VER_3_Pin */
	GPIO_InitStruct.Pin = HW_VER_1_Pin|HW_VER_2_Pin|HW_VER_3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : TOUCH_RESET_Pin */
	GPIO_InitStruct.Pin = TOUCH_RESET_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(TOUCH_RESET_GPIO_Port, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/*********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************/

#ifdef DEBUG_PRINTF
/***************************************************************************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ***************************************************************************************************************************************************************************************************/
PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart4, (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}
#endif

/***************************************************************************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ***************************************************************************************************************************************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART3)
	{
		st25r95UartTxCpltCallback();
	}
}

/***************************************************************************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ***************************************************************************************************************************************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART3)
	{
		st25r95UartRxCpltCallback();
	}
}

/***************************************************************************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ***************************************************************************************************************************************************************************************************/
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART3)
	{
		st25r95UartErrorCallback();
	}
}

/*********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************/
/* USER CODE END 4 */

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM6 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM6) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
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
