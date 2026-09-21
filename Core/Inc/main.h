/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
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
 *********************************************************************************************************************************************************************************************************/
#include <string.h>
#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "inttypes.h"
#include "ctype.h"
#include "cmsis_os2.h"
#include "bip39_lib.h"
#include "slip39_lib.h"
#include "xmr_lib.h"
#include "info_codec.h"
/*********************************************************************************************************************************************************************************************************
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
 *********************************************************************************************************************************************************************************************************/

/*** Printf's ***/
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

/*********************************************************************************************************************************************************************************************************
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
 *********************************************************************************************************************************************************************************************************/

/*
 * DEFINE's
 */

#define FIRMWARE_VERSION			"1.2.0"		//Firmware version
#define HARDWARE_VERSION() 			('1' + ((HAL_GPIO_ReadPin(GPIOC, HW_VER_3_Pin) == GPIO_PIN_SET) << 2) + ((HAL_GPIO_ReadPin(GPIOC, HW_VER_2_Pin) == GPIO_PIN_SET) << 1) + ((HAL_GPIO_ReadPin(GPIOC, HW_VER_1_Pin) == GPIO_PIN_SET) << 0))
#define FW_VER_F1   				(FIRMWARE_VERSION[0] - '0')
#define FW_VER_F2   				(FIRMWARE_VERSION[2] - '0')
#define FW_VER_F3   				(FIRMWARE_VERSION[4] - '0')

//#define DEBUG_PRINTF
//#define DEBUG_NFC_PRINTF
//#define DEBUG_PSBT_PRINTF
//#define DEBUG_PRINTF_ENCRYPT
//#define DEBUG_PRINTF_DECRYPT

#define SIZE_UID 					25
#define SIZE_ALIAS 					25
#define SIZE_INFORMATION			50
#define SIZE_MULTISIGN				1300
#define SIZE_CRYPT					768
#define SIZE_CRYPT_MSG				SIZE_CRYPT/4

#define DEV_ALIAS_ADDR				0x083FA000		//"DEV_ALIAS" (bank 2) 	--> Address
#define DEV_ALIAS_PAGE				253				//"DEV_ALIAS" (bank 2) 	--> Page number
#define DEV_ALIAS_SIZE				30				//"DEV_ALIAS" (bank 2) 	--> Máx size
#define EEPROM_ADDR					0x083FC000		//"EEPROM" (bank 2) 	--> Address
#define EEPROM_PAGE					254				//"EEPROM" (bank 2) 	--> Page number
#define EEPROM_SIZE					112				//"EEPROM" (bank 2)		--> Máx size
#define SIGNATURE_ADDR				0x083FE000		//"SIGNATURE" (bank 2) 	--> Address
#define SIGNATURE_PAGE				255				//"SIGNATURE" (bank 2) 	--> Page number
#define SIGNATURE_SIZE				62				//"SIGNATURE" (bank 2) 	--> Máx size

#define FROM_NFC_SEED				250
#define FROM_NFC_PASS_DERIV			250
#define FROM_NFC_PRIVATE_KEY		250
#define FROM_NFC_PUBLIC_KEY			250
#define FROM_NFC_PLAIN_TEXT			500

#define FROM_PSBT_BASE64_MAX_SIZE	7000			//Mifare DESFire ev1 8K (real size < 8KB)
#define FROM_PSBT_T2T_MAX_SIZE		866				//NTAG216 (real size < 888B)

/*
 * STRUCT's
 */

struct tag
{
	/*** Flags ***/
	uint8_t action;
	uint8_t type;
	bool flag_readed;
	bool flag_readed_writed;
	bool flag_readed_from_nfc;
	bool flag_readed_from_psbt;
	bool flag_readed_writed_from_psbt;
	bool flag_readed_writed_from_psbt_size_warning;

	/*** Tag data stored/readed directly ***/
	uint8_t uid[SIZE_UID];
	uint8_t alias[SIZE_ALIAS];
	uint8_t cryptogram[SIZE_CRYPT];
	uint8_t information[SIZE_INFORMATION];
	uint8_t multisignature[SIZE_MULTISIGN];

	/*** Tag data stored/readed directly --> Auxiliar ***/
	uint8_t new_uid[SIZE_UID];
	uint8_t new_alias[SIZE_ALIAS];
	uint8_t new_cryptogram[SIZE_CRYPT];
	uint8_t new_information[SIZE_INFORMATION];
	uint8_t new_multisignature[SIZE_MULTISIGN];

	/*** Tag data getted/setted ***/
	uint8_t encripted;
	uint8_t multisigned_total;
	uint8_t multisigned_mandatory;
	uint8_t fw_version[10];
	uint8_t salt_pbkdf2[16];
	uint8_t iv_aes_gcm[16];

	/***  ***/
	uint8_t from_nfc_type;
	uint8_t from_nfc_seed[FROM_NFC_SEED];
	uint8_t from_nfc_pass_deriv[FROM_NFC_PASS_DERIV];
	uint8_t from_nfc_private_key[FROM_NFC_PRIVATE_KEY];
	uint8_t from_nfc_public_key[FROM_NFC_PUBLIC_KEY];
	uint8_t from_nfc_plain_text[FROM_NFC_PLAIN_TEXT];

	/***  ***/
	uint8_t from_psbt_type;
	uint8_t from_psbt_base64[FROM_PSBT_BASE64_MAX_SIZE];
	uint8_t from_psbt_base64_signed[FROM_PSBT_BASE64_MAX_SIZE];

	/*** Variables to use in AES-256 processing ***/
	uint32_t new_text_to_encrypt[SIZE_CRYPT_MSG];
	uint32_t new_text_encrypted[SIZE_CRYPT_MSG];
	uint32_t new_text_to_decrypt[SIZE_CRYPT_MSG];
	uint32_t new_text_decrypted[SIZE_CRYPT_MSG];
	uint32_t new_pKeyAES[8];
	uint32_t new_ivAES[4];
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
	uint8_t brightness;
	uint8_t language;
	uint8_t mode;
	uint8_t errors;
};

struct encrypt
{
	uint8_t  text_type;
	uint16_t total_words;
	uint8_t  actual_pwd;
	uint8_t  words_to_encrypt[55][5];	//54 words... 4 characters per word...
	uint8_t  buff_passphrase[105];		//100 characters
	uint8_t  buff_plain_text[505];		//500 characters
};

struct decrypt
{
	uint8_t cryptogram_decrypted[SIZE_CRYPT];
	uint8_t derivation_path[50];
	uint8_t derived_address[100];
	uint8_t descriptor_acount_number[5];
	bool descriptor_is_multisignature;
};

struct wallet
{
	bool flag_new;
	bool flag_reuse_seed;
	uint8_t dice_selected[4];
	uint8_t coin_dice_values[5];
	uint8_t words_to_encrypt[24][5];
	uint8_t pass_deriv[250];
	uint8_t zprv_key[125];
	uint8_t zpub_key[125];
};

struct cuvex
{
	uint8_t screen;
	char device_alias_buffer[DEV_ALIAS_SIZE];
	char eeprom_buffer[EEPROM_SIZE];
	char signature_buffer[SIGNATURE_SIZE];
	struct info info;
	struct nfc nfc;
	struct encrypt encrypt;
	struct decrypt decrypt;
	struct wallet wallet;
};

/*
 * ENUM's
 */

enum gui_to_main_queue_msg
{
	/*** GUI Screen's ***/
	GUI_TO_MAIN_SCREEN_INIT = 0,
	GUI_TO_MAIN_SCREEN_MAIN_MENU,
	GUI_TO_MAIN_SCREEN_FLOW_ENCRYPT,
	GUI_TO_MAIN_SCREEN_FLOW_DECRYPT,
	GUI_TO_MAIN_SCREEN_FLOW_CLONE,
	GUI_TO_MAIN_SCREEN_FLOW_WALLET,
	GUI_TO_MAIN_SCREEN_FLOW_PSBT,
	GUI_TO_MAIN_SCREEN_FLOW_SETTINGS,

	/*** NFC actions ***/
	GUI_TO_MAIN_NFC_DISABLE,
	GUI_TO_MAIN_NFC_ENABLE,
	GUI_TO_MAIN_NFC_TAG_NONE,
	GUI_TO_MAIN_NFC_TAG_READ,
	GUI_TO_MAIN_NFC_TAG_READ_FROM_NFC,
	GUI_TO_MAIN_NFC_TAG_READ_FROM_PSBT,
	GUI_TO_MAIN_NFC_TAG_READ_WRITE_FROM_PSBT,
	GUI_TO_MAIN_NFC_TAG_READ_WRITE_FROM_PSBT_T4T_8K,
	GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_ENCRYPT,
	GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_ENCRYPT_T4T_8K,
	GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_CLONE,
	GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_CLONE_T4T_8K,

	/*** Flash actions ***/
	GUI_TO_MAIN_FLASH_SAVE_SETTINGS,
	GUI_TO_MAIN_FLASH_SAVE_SETTINGS_AND_DEVICE_ALIAS,
	GUI_TO_MAIN_FLASH_ERASE_SIGNATURE
};

enum main_to_gui_queue_msg
{
	MAIN_TO_GUI_NFC_ERROR = 0,
	MAIN_TO_GUI_NFC_INITIALIZED,
	MAIN_TO_GUI_NFC_TAG_READED,
	MAIN_TO_GUI_NFC_TAG_READED_FROM_NFC,
	MAIN_TO_GUI_NFC_TAG_READED_FROM_PSBT,
	MAIN_TO_GUI_NFC_TAG_READED_WRITED_FROM_PSBT,
	MAIN_TO_GUI_NFC_TAG_READED_WRITED_FROM_PSBT_T4T_8K,
	MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_ENCRYPT,
	MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_ENCRYPT_T4T_8K,
	MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_CLONE,
	MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_CLONE_T4T_8K
};

enum screen_state
{
	SCREEN_INIT = 0,
	SCREEN_MAIN_MENU,
	SCREEN_FLOW_ENCRYPT,
	SCREEN_FLOW_DECRYPT,
	SCREEN_FLOW_CLONE,
	SCREEN_FLOW_WALLET,
	SCREEN_FLOW_PSBT,
	SCREEN_FLOW_SETTINGS
};

enum nfc_tag_actions
{
	NFC_TAG_NONE = 0,
	NFC_TAG_READ,
	NFC_TAG_READ_FROM_NFC,
	NFC_TAG_READ_FROM_PSBT,
	NFC_TAG_READ_WRITE_FROM_PSBT,
	NFC_TAG_READ_WRITE_FROM_PSBT_T4T_8K,
	NFC_TAG_READ_WRITE_FLOW_ENCRYPT,
	NFC_TAG_READ_WRITE_FLOW_ENCRYPT_T4T_8K,
	NFC_TAG_READ_WRITE_FLOW_CLONE,
	NFC_TAG_READ_WRITE_FLOW_CLONE_T4T_8K
};

enum nfc_tag_type
{
	NFC_TAG_TYPE_NONE = 0,
	NFC_TAG_TYPE_T2T_NTAG216,	//NTAG216
	NFC_TAG_TYPE_T4T_8K			//MIFARE DESFire EV1 8K
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

enum text_type
{
	TEXT_TYPE_NONE = 0,
	TEXT_TYPE_BIP39,
	TEXT_TYPE_SLIP39,
	TEXT_TYPE_XMR,
	TEXT_TYPE_PLAINTEXT,
	TEXT_TYPE_FROM_NFC_BIP39,
	TEXT_TYPE_FROM_NFC_PLAINTEXT,
	TEXT_TYPE_FROM_WALLET_BIP39
};

enum dice_colour
{
	DICE_COLOUR_1 = 1,
	DICE_COLOUR_2,
	DICE_COLOUR_3,
	DICE_COLOUR_4,
	DICE_COLOUR_5,
	DICE_COLOUR_6,
	DICE_COLOUR_7,
	DICE_COLOUR_8
};

enum dice_selected_value
{
	DICE_SELECTED_VALUE_1 = 101,
	DICE_SELECTED_VALUE_2,
	DICE_SELECTED_VALUE_3,
	DICE_SELECTED_VALUE_4
};

enum psbt_type
{
	PSBT_TYPE_NONE = 0,
	PSBT_TYPE_V0_NOT_SIGNED,
	PSBT_TYPE_V0_SIGNED,
	PSBT_TYPE_OTHER_STATE
};

/*********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************
 *********************************************************************************************************************************************************************************************************/
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
