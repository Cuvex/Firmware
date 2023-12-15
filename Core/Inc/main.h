/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Portion Copyright (C) 2023 Semilla3 OÜ.  All Rights Reserved.
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
#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/*********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************/

#include <string.h>
#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "cmsis_os2.h"
#include "bip39_lib.h"

/*********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************/
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
/*********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************/

///*** Printf's ***/
//#ifdef __GNUC__
//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#else
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
//#endif

/*********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************/
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BLE_EN_Pin GPIO_PIN_13
#define BLE_EN_GPIO_Port GPIOC
#define LED_RED_Pin GPIO_PIN_1
#define LED_RED_GPIO_Port GPIOC
#define LED_GREEN_Pin GPIO_PIN_2
#define LED_GREEN_GPIO_Port GPIOC
#define BLE_BOOT_Pin GPIO_PIN_1
#define BLE_BOOT_GPIO_Port GPIOA
#define BLE_UART2_TX_Pin GPIO_PIN_2
#define BLE_UART2_TX_GPIO_Port GPIOA
#define BLE_UART2_RX_Pin GPIO_PIN_3
#define BLE_UART2_RX_GPIO_Port GPIOA
#define BLE_WAKEUP_Pin GPIO_PIN_4
#define BLE_WAKEUP_GPIO_Port GPIOA
#define NFC_NSS_Pin GPIO_PIN_0
#define NFC_NSS_GPIO_Port GPIOB
#define HW_VER_1_Pin GPIO_PIN_6
#define HW_VER_1_GPIO_Port GPIOC
#define HW_VER_2_Pin GPIO_PIN_7
#define HW_VER_2_GPIO_Port GPIOC
#define HW_VER_3_Pin GPIO_PIN_8
#define HW_VER_3_GPIO_Port GPIOC
#define LCD_BACKLIGHT_Pin GPIO_PIN_8
#define LCD_BACKLIGHT_GPIO_Port GPIOA
#define LCD_RESET_Pin GPIO_PIN_9
#define LCD_RESET_GPIO_Port GPIOA
#define NFC_EN_Pin GPIO_PIN_12
#define NFC_EN_GPIO_Port GPIOC
#define TOUCH_RESET_Pin GPIO_PIN_4
#define TOUCH_RESET_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
/*********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************/

/*
 * DEFINE's
 */

#define FIRMWARE_VERSION	"1.0.0"			//Versión de firmware
//#define DEBUG_NFC_PRINTF					//Macro para depurar con printf's "nfcTask"

#define SIZE_UID 			25				//14B siempre
#define SIZE_ALIAS 			25				//20B máx.
#define SIZE_INFORMATION	50				//30B aprox.
#define SIZE_CRYPT			768				//(128*4B)+128B+100B+19B = 759B máx. ...(words*bytes/word)+delimitador+passphrase+cabeceras... Múltiplo de 16B
#define SIZE_CRYPT_MSG		SIZE_CRYPT/4	//...

#define EEPROM_ADDR			0x083FC000		//Dirección de memoria sector "EEPROM" (bank 2)
#define EEPROM_PAGE			254				//Página de memoria sector "EEPROM" (bank 2)
#define EEPROM_SIZE			112				//Tamaño máximo ocupado en sector "EEPROM"
#define SIGNATURE_ADDR		0x083FE000		//Dirección de memoria sector "SIGNATURE" (bank 2)
#define SIGNATURE_PAGE		255				//Página de memoria sector "SIGNATURE" (bank 2)
#define SIGNATURE_SIZE		62				//Tamaño máximo ocupado en sector "SIGNATURE"

/*
 * STRUCT's
 */

struct tag
{
	uint8_t action;
	/***/
	bool flag_readed;
	bool flag_readed_writed_flow_1;
	bool flag_readed_writed_flow_2;
	bool flag_readed_writed_flow_4;
	/***/
	uint8_t uid[SIZE_UID];
	uint8_t alias[SIZE_ALIAS];
	uint8_t cryptogram[SIZE_CRYPT];
	uint8_t information[SIZE_INFORMATION];	//"ENC,vXX.XX.XX(Y),M-X,P-X,C-X"
	/***/
	uint8_t new_uid[SIZE_UID];
	uint8_t new_alias[SIZE_ALIAS];
	uint8_t new_cryptogram[SIZE_CRYPT];
	uint8_t new_information[SIZE_INFORMATION];
	/***/
	uint8_t encripted;		//0:no, 1:yes
	uint8_t multisigned;	//1-6
	uint8_t packed;			//0:no, 1:yes
	uint8_t cloned;			//0:no, 1:yes
};

struct nfc
{
	bool flag_enabled;
	bool flag_initialized;
	bool flag_notify_init;
	struct tag tag;
};

struct info
{
	uint8_t fw_version[25];
	uint8_t hw_version[2];
	uint8_t brightness;
	uint8_t language;
	uint8_t mode;
	uint8_t errors;
};

struct cuvex
{
	uint8_t screen;
	char eeprom_buffer[EEPROM_SIZE];
	char signature_buffer[SIGNATURE_SIZE];
	struct nfc nfc;
	struct info info;
};

/*
 * ENUM's
 */

enum gui_to_main_queue_msg
{
	/*** GUI Screen's ***/
	GUI_TO_MAIN_SCREEN_INIT = 0,
	GUI_TO_MAIN_SCREEN_MAIN_MENU,
	GUI_TO_MAIN_SCREEN_FLOW_1,
	GUI_TO_MAIN_SCREEN_FLOW_2,
	GUI_TO_MAIN_SCREEN_FLOW_3,
	GUI_TO_MAIN_SCREEN_FLOW_4,
	GUI_TO_MAIN_SCREEN_FLOW_5,

	/*** NFC actions ***/
	GUI_TO_MAIN_NFC_DISABLE,
	GUI_TO_MAIN_NFC_ENABLE,
	GUI_TO_MAIN_NFC_TAG_NONE,
	GUI_TO_MAIN_NFC_TAG_READ,
	GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_1,
	GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_2,
	GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_4,

	/*** Flash actions ***/
	GUI_TO_MAIN_FLASH_SAVE_SETTINGS,
	GUI_TO_MAIN_FLASH_ERASE_SIGNATURE
};

enum main_to_gui_queue_msg
{
	MAIN_TO_GUI_NFC_ERROR = 0,
	MAIN_TO_GUI_NFC_INITIALIZED,
	MAIN_TO_GUI_NFC_TAG_READED,
	MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_1,
	MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_2,
	MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_4
};

enum led_colour_state
{
	NONE = 0,
	RED,
	GREEN,
	YELLOW
};

enum screen_state
{
	SCREEN_INIT = 0,
	SCREEN_MAIN_MENU,
	SCREEN_FLOW_1,
	SCREEN_FLOW_2,
	SCREEN_FLOW_3,
	SCREEN_FLOW_4,
	SCREEN_FLOW_5
};

enum nfc_tag_actions
{
	NFC_TAG_NONE = 0,
	NFC_TAG_READ,
	NFC_TAG_READ_WRITE_FLOW_1,
	NFC_TAG_READ_WRITE_FLOW_2,
	NFC_TAG_READ_WRITE_FLOW_4
};

enum mode
{
	LIGHT = 0,
	DARK
};

enum language
{
	ENGLISH = 0,
	SPANISH
};

/*********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************/
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
