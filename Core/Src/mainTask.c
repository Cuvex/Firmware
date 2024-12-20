/**
 ******************************************************************************
 * @file           : mainTask.c
 * @brief          : Main task (freeRTOS)
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

#include "mainTask.h"

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void main_Task(void const * argument)
{
	/*** EEPROM/SIGNATURE sector reading + initialization + data loading into RAM ***/
	readFlash(DEV_ALIAS_ADDR, cuvex.device_alias_buffer, DEV_ALIAS_SIZE);
	readFlash(EEPROM_ADDR, cuvex.eeprom_buffer, EEPROM_SIZE);
	readFlash(SIGNATURE_ADDR, cuvex.signature_buffer, SIGNATURE_SIZE);

	if(memcmp(cuvex.eeprom_buffer + 96, ">>>>>Footer<<<<<", 16) != 0){
		initEEPROM();
	}

	loadEEPROM();

	/*** Initialization of peripherals and variables + delay ****/
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
	getCuvexVersions();
	clearNfc_all();
	osDelay(250);

	/*** Main loop ***/
	for(;;)
	{
		processGuiToMainQueue();
		stateMachineScreens();
		osDelay(10);
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void processGuiToMainQueue(void)
{
	uint16_t rcv_data_gui = 0;

	if((osMessageQueueGetCount(guiToMainQueueHandle) > 0) && (osMessageQueueGet(guiToMainQueueHandle, &rcv_data_gui, 0, 0) == osOK))
	{
		switch(rcv_data_gui)
		{
		default:
			break;

			/********************************************************/
		case GUI_TO_MAIN_SCREEN_INIT:
			cuvex.screen = SCREEN_INIT;
			clearNfc_all();
			clearWallet();
			break;

		case GUI_TO_MAIN_SCREEN_MAIN_MENU:
			cuvex.screen = SCREEN_MAIN_MENU;
			clearNfc_all();
			clearWallet();
			break;

		case GUI_TO_MAIN_SCREEN_FLOW_ENCRYPT:
			cuvex.screen = SCREEN_FLOW_ENCRYPT;
			break;

		case GUI_TO_MAIN_SCREEN_FLOW_DECRYPT:
			cuvex.screen = SCREEN_FLOW_DECRYPT;
			break;

		case GUI_TO_MAIN_SCREEN_FLOW_CLONE:
			cuvex.screen = SCREEN_FLOW_CLONE;
			break;

		case GUI_TO_MAIN_SCREEN_FLOW_WALLET:
			cuvex.screen = SCREEN_FLOW_WALLET;
			break;

		case GUI_TO_MAIN_SCREEN_FLOW_PSBT:
			cuvex.screen = SCREEN_FLOW_PSBT;
			break;

		case GUI_TO_MAIN_SCREEN_FLOW_SETTINGS:
			cuvex.screen = SCREEN_FLOW_SETTINGS;
			break;

			/********************************************************/
		case GUI_TO_MAIN_NFC_DISABLE:
			clearNfc_readerFlags();
			clearNfc_tagFlags();
			cuvex.nfc.flag_enabled = false;
			break;

		case GUI_TO_MAIN_NFC_ENABLE:
			clearNfc_readerFlags();
			clearNfc_tagFlags();
			cuvex.nfc.flag_enabled = true;
			break;

		case GUI_TO_MAIN_NFC_TAG_NONE:
			clearNfc_tagFlags();
			cuvex.nfc.tag.action = NFC_TAG_NONE;
			break;

		case GUI_TO_MAIN_NFC_TAG_READ:
			clearNfc_tagFlags();
			cuvex.nfc.tag.action = NFC_TAG_READ;
			break;

		case GUI_TO_MAIN_NFC_TAG_READ_FROM_NFC:
			clearNfc_tagFlags();
			cuvex.nfc.tag.action = NFC_TAG_READ_FROM_NFC;
			break;

		case GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_ENCRYPT:
			clearNfc_tagFlags();
			cuvex.nfc.tag.action = NFC_TAG_READ_WRITE_FLOW_ENCRYPT;
			break;

		case GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_ENCRYPT_T4T_8K:
			clearNfc_tagFlags();
			cuvex.nfc.tag.action = NFC_TAG_READ_WRITE_FLOW_ENCRYPT_T4T_8K;
			break;

		case GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_CLONE:
			clearNfc_tagFlags();
			cuvex.nfc.tag.action = NFC_TAG_READ_WRITE_FLOW_CLONE;
			break;

		case GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_CLONE_T4T_8K:
			clearNfc_tagFlags();
			cuvex.nfc.tag.action = NFC_TAG_READ_WRITE_FLOW_CLONE_T4T_8K;
			break;

			/********************************************************/
		case GUI_TO_MAIN_FLASH_SAVE_SETTINGS:
			editEEPROM();
			break;

		case GUI_TO_MAIN_FLASH_SAVE_SETTINGS_AND_DEVICE_ALIAS:
			editEEPROM();
			saveDeviceAlias();
			break;

		case GUI_TO_MAIN_FLASH_ERASE_SIGNATURE:
			eraseSignature();
			break;
		}
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void stateMachineScreens(void)
{
	switch(cuvex.screen)
	{
	case SCREEN_INIT:
	case SCREEN_MAIN_MENU:
	case SCREEN_FLOW_WALLET:
	case SCREEN_FLOW_PSBT:
	case SCREEN_FLOW_SETTINGS:
	default:
		break;

		/*
		 * Flow "Encrypt"
		 */

	case SCREEN_FLOW_ENCRYPT:
		if((cuvex.nfc.flag_enabled == true) && (cuvex.nfc.flag_initialized == true))
		{
			/*** Initialization of NFC reader/writer (if requested) ***/
			if(cuvex.nfc.flag_notify_init == false)
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_INITIALIZED}, 0, 0);
				}
				cuvex.nfc.flag_notify_init = true;
			}

			/*** NFC tag reading (if requested) ***/
			if((cuvex.nfc.tag.action == NFC_TAG_READ_FROM_NFC) && (cuvex.nfc.tag.flag_readed_from_nfc == true))
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_TAG_READED_FROM_NFC}, 0, 0);
				}
				cuvex.nfc.tag.action = NFC_TAG_NONE;
				cuvex.nfc.tag.flag_readed_from_nfc = false;
			}

			/*** NFC tag reading + writing (if requested) ***/
			if((cuvex.nfc.tag.action == NFC_TAG_READ_WRITE_FLOW_ENCRYPT) && (cuvex.nfc.tag.flag_readed_writed == true))
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_ENCRYPT}, 0, 0);
				}
				cuvex.nfc.tag.action = NFC_TAG_NONE;
				cuvex.nfc.tag.flag_readed_writed = false;
			}

			/*** NFC tag reading + writing (if requested) ***/
			if((cuvex.nfc.tag.action == NFC_TAG_READ_WRITE_FLOW_ENCRYPT_T4T_8K) && (cuvex.nfc.tag.flag_readed_writed == true))
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_ENCRYPT_T4T_8K}, 0, 0);
				}
				cuvex.nfc.tag.action = NFC_TAG_NONE;
				cuvex.nfc.tag.flag_readed_writed = false;
			}
		}
		break;

		/*
		 * Flow "Decrypt"
		 */

	case SCREEN_FLOW_DECRYPT:
		if((cuvex.nfc.flag_enabled == true) && (cuvex.nfc.flag_initialized == true))
		{
			/*** Initialization of NFC reader/writer (if requested) ***/
			if(cuvex.nfc.flag_notify_init == false)
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_INITIALIZED}, 0, 0);
				}
				cuvex.nfc.flag_notify_init = true;
			}

			/*** NFC tag reading (if requested) ***/
			if((cuvex.nfc.tag.action == NFC_TAG_READ) && (cuvex.nfc.tag.flag_readed == true))
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_TAG_READED}, 0, 0);
				}
				cuvex.nfc.tag.action = NFC_TAG_NONE;
				cuvex.nfc.tag.flag_readed = false;
			}
		}
		break;


		/*
		 * Flow "Clone"
		 */

	case SCREEN_FLOW_CLONE:
		if((cuvex.nfc.flag_enabled == true) && (cuvex.nfc.flag_initialized == true))
		{
			/*** Initialization of NFC reader/writer (if requested) ***/
			if(cuvex.nfc.flag_notify_init == false)
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_INITIALIZED}, 0, 0);
				}
				cuvex.nfc.flag_notify_init = true;
			}

			/*** NFC tag reading (if requested) ***/
			if((cuvex.nfc.tag.action == NFC_TAG_READ) && (cuvex.nfc.tag.flag_readed == true))
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_TAG_READED}, 0, 0);
				}
				cuvex.nfc.tag.action = NFC_TAG_NONE;
				cuvex.nfc.tag.flag_readed = false;
			}

			/*** NFC tag reading + writing (if requested) ***/
			if((cuvex.nfc.tag.action == NFC_TAG_READ_WRITE_FLOW_CLONE) && (cuvex.nfc.tag.flag_readed_writed == true))
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_CLONE}, 0, 0);
				}
				cuvex.nfc.tag.action = NFC_TAG_NONE;
				cuvex.nfc.tag.flag_readed_writed = false;
			}

			/*** NFC tag reading + writing (if requested) ***/
			if((cuvex.nfc.tag.action == NFC_TAG_READ_WRITE_FLOW_CLONE_T4T_8K) && (cuvex.nfc.tag.flag_readed_writed == true))
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_CLONE_T4T_8K}, 0, 0);
				}
				cuvex.nfc.tag.action = NFC_TAG_NONE;
				cuvex.nfc.tag.flag_readed_writed = false;
			}
		}
		break;
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void clearNfc_all(void)
{
	clearNfc_readerFlags();
	clearNfc_tagFlags();
	clearNfc_tagInfo();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void clearNfc_readerFlags(void)
{
	cuvex.nfc.flag_enabled     = false;
	cuvex.nfc.flag_initialized = false;
	cuvex.nfc.flag_notify_init = false;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void clearNfc_tagFlags(void)
{
	cuvex.nfc.tag.action 	  			= NFC_TAG_NONE;
	cuvex.nfc.tag.type		 			= NFC_TAG_TYPE_NONE;
	cuvex.nfc.tag.flag_readed 			= false;
	cuvex.nfc.tag.flag_readed_writed 	= false;
	cuvex.nfc.tag.flag_readed_from_nfc	= false;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void clearNfc_tagInfo(void)
{
	memset(cuvex.nfc.tag.uid, 0x00, sizeof(cuvex.nfc.tag.uid));
	memset(cuvex.nfc.tag.alias, 0x00, sizeof(cuvex.nfc.tag.alias));
	memset(cuvex.nfc.tag.cryptogram, 0x00, sizeof(cuvex.nfc.tag.cryptogram));
	memset(cuvex.nfc.tag.information, 0x00, sizeof(cuvex.nfc.tag.information));
	memset(cuvex.nfc.tag.multisignature, 0x00, sizeof(cuvex.nfc.tag.multisignature));
	memset(cuvex.nfc.tag.new_uid, 0x00, sizeof(cuvex.nfc.tag.new_uid));
	memset(cuvex.nfc.tag.new_alias, 0x00, sizeof(cuvex.nfc.tag.new_alias));
	memset(cuvex.nfc.tag.new_cryptogram, 0x00, sizeof(cuvex.nfc.tag.new_cryptogram));
	memset(cuvex.nfc.tag.new_information, 0x00, sizeof(cuvex.nfc.tag.new_information));
	memset(cuvex.nfc.tag.new_multisignature, 0x00, sizeof(cuvex.nfc.tag.new_multisignature));
	cuvex.nfc.tag.encripted	  			= 0;
	cuvex.nfc.tag.multisigned_total 	= 0;
	cuvex.nfc.tag.multisigned_mandatory = 0;
	cuvex.nfc.tag.packed	  			= 0;
	cuvex.nfc.tag.cloned	  			= 0;
	/***/
	cuvex.nfc.tag.from_nfc_type	= 0;
	memset(cuvex.nfc.tag.from_nfc_seed, 0x00, sizeof(cuvex.nfc.tag.from_nfc_seed));
	memset(cuvex.nfc.tag.from_nfc_private_key, 0x00, sizeof(cuvex.nfc.tag.from_nfc_private_key));
	memset(cuvex.nfc.tag.from_nfc_public_key, 0x00, sizeof(cuvex.nfc.tag.from_nfc_public_key));
	memset(cuvex.nfc.tag.from_nfc_pass_deriv, 0x00, sizeof(cuvex.nfc.tag.from_nfc_pass_deriv));
	memset(cuvex.nfc.tag.from_nfc_plain_text, 0x00, sizeof(cuvex.nfc.tag.from_nfc_plain_text));
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void clearWallet(void)
{
	cuvex.wallet.flag_new = false;
	memset(cuvex.wallet.dice_selected, 0x00, sizeof(cuvex.wallet.dice_selected));
	memset(cuvex.wallet.coin_dice_values, 0x00, sizeof(cuvex.wallet.coin_dice_values));
	memset(cuvex.wallet.pass_deriv, 0x00, sizeof(cuvex.wallet.pass_deriv));
	memset(cuvex.wallet.zprv_key, 0x00, sizeof(cuvex.wallet.zprv_key));
	memset(cuvex.wallet.zpub_key, 0x00, sizeof(cuvex.wallet.zpub_key));

	for(int i=0; i<24; i++){
		memset(cuvex.wallet.words_to_encrypt[i], 0x00, sizeof(cuvex.wallet.words_to_encrypt));
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void readFlash(uint32_t address, char* data, size_t data_size)
{
	uint32_t i=0;

	for(i = 0; i < data_size; i+=1){
		data[i] = *((char*)address+i);
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void writeFlash(uint32_t address, char* data, size_t data_size)
{
	uint32_t *data_p = (uint32_t*)data;

	HAL_FLASH_Unlock();
	FLASH_WaitForLastOperation(100);

	for(int i=0; i<data_size; i+=16, data_p+=4, address+=16){
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_QUADWORD, address, (uint32_t)data_p) != HAL_OK){
			NVIC_SystemReset();
		}
	}

	FLASH_WaitForLastOperation(100);
	HAL_FLASH_Lock();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void eraseFlash(uint32_t Banks, uint32_t Page, uint32_t NbPages)
{
	FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PageError;

	HAL_FLASH_Unlock();

	FLASH_WaitForLastOperation(100);

	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Banks       = Banks;
	EraseInitStruct.Page        = Page;
	EraseInitStruct.NbPages     = NbPages;

	if(HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK){
		NVIC_SystemReset();
	}

	FLASH_WaitForLastOperation(100);
	HAL_FLASH_Lock();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void initEEPROM(void)
{
	/*** Buffer reset ***/
	memset(cuvex.eeprom_buffer, 0x00, EEPROM_SIZE);

	/*** Header (16 Bytes) ***/
	memcpy(cuvex.eeprom_buffer, ">>>>>Header<<<<<", 16);

	/*** Mapped fields (10 x 16 Bytes) ***/
	memcpy(cuvex.eeprom_buffer + 16, "#B:100", 	 6);	//Brightness  (1-100)
	memcpy(cuvex.eeprom_buffer + 32, "#M:LIGHT", 8);	//Mode (LIGHT, DARK)
	memcpy(cuvex.eeprom_buffer + 48, "#L:GB", 	 5);	//Language (GB, SP)
	memcpy(cuvex.eeprom_buffer + 64, "#E:0", 	 4);	//Errors while decrypting (0-2)

	/*** Footer (11 Bytes) ***/
	memcpy(cuvex.eeprom_buffer + 96, ">>>>>Footer<<<<<", 16);

	/*** Saved to flash memory ***/
	eraseFlash(FLASH_BANK_2, EEPROM_PAGE, 1);
	writeFlash(EEPROM_ADDR, cuvex.eeprom_buffer, EEPROM_SIZE);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void loadEEPROM(void)
{
	char brightness_str[5] = {0};

	/*** Brightness (1-100) ***/
	memcpy(brightness_str, cuvex.eeprom_buffer + 16 + 3, 5);
	cuvex.info.brightness = atoi(brightness_str);
	TIM1->CCR1 = cuvex.info.brightness;

	/*** Mode (LIGHT, DARK) ***/
	if(memcmp(cuvex.eeprom_buffer + 32, "#M:DARK", 7) == 0){
		cuvex.info.mode = DARK;
	}
	else{
		cuvex.info.mode = LIGHT;
	}

	/*** Language (GB, SP) ***/
	if(memcmp(cuvex.eeprom_buffer + 48, "#L:SP", 5) == 0){
		cuvex.info.language = SPANISH;
	}
	else{
		cuvex.info.language = ENGLISH;
	}

	/*** Errors while decrypting (0-2) ***/
	if(memcmp(cuvex.eeprom_buffer + 64, "#E:1", 4) == 0){
		cuvex.info.errors = 1;
	}
	else if(memcmp(cuvex.eeprom_buffer + 64, "#E:2", 4) == 0){
		cuvex.info.errors = 2;
	}
	else{
		cuvex.info.errors = 0;
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void editEEPROM(void)
{
	static uint8_t last_brightness = 0, last_mode = 0, last_language = 0, last_errors = 0;
	char brightness_str[5] = {0};

	if((last_brightness != cuvex.info.brightness) || (last_mode != cuvex.info.mode) || (last_language != cuvex.info.language) || (last_errors != cuvex.info.errors))
	{
		/*** Reset buffer + "header" + "footer" ***/
		memset(cuvex.eeprom_buffer, 0x00, EEPROM_SIZE);
		memcpy(cuvex.eeprom_buffer, ">>>>>Header<<<<<", 16);
		memcpy(cuvex.eeprom_buffer + 96, ">>>>>Footer<<<<<", 16);

		/*** Brightness ***/
		if((cuvex.info.brightness >= 1) && (cuvex.info.brightness <= 100)){
			itoa(cuvex.info.brightness, brightness_str, 10);
			memcpy(cuvex.eeprom_buffer + 16, "#B:", 3);
			memcpy(cuvex.eeprom_buffer + 16 + 3, brightness_str, 5);
		}

		/*** Mode ***/
		if(cuvex.info.mode == DARK){
			memcpy(cuvex.eeprom_buffer + 32, "#M:DARK", 7);
		}
		else{
			memcpy(cuvex.eeprom_buffer + 32, "#M:LIGHT", 8);
		}

		/*** Language ***/
		if(cuvex.info.language == SPANISH){
			memcpy(cuvex.eeprom_buffer + 48, "#L:SP", 5);
		}
		else{
			memcpy(cuvex.eeprom_buffer + 48, "#L:GB", 5);
		}

		/*** Errors while decrypting ***/
		if(cuvex.info.errors == 1){
			memcpy(cuvex.eeprom_buffer + 64, "#E:1", 4);
		}
		else if(cuvex.info.errors == 2){
			memcpy(cuvex.eeprom_buffer + 64, "#E:2", 4);
		}
		else{
			memcpy(cuvex.eeprom_buffer + 64, "#E:0", 4);
		}

		/*** Save in flash memory ***/
		eraseFlash(FLASH_BANK_2, EEPROM_PAGE, 1);
		writeFlash(EEPROM_ADDR, cuvex.eeprom_buffer, EEPROM_SIZE);

		/*** Save last values in RAM memory ***/
		last_brightness = cuvex.info.brightness;
		last_mode 		= cuvex.info.mode;
		last_language 	= cuvex.info.language;
		last_errors 	= cuvex.info.errors;
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void saveDeviceAlias(void)
{
	eraseFlash(FLASH_BANK_2, DEV_ALIAS_PAGE, 1);
	writeFlash(DEV_ALIAS_ADDR, cuvex.device_alias_buffer, DEV_ALIAS_SIZE);
	NVIC_SystemReset();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void eraseSignature(void)
{
	eraseFlash(FLASH_BANK_2, SIGNATURE_PAGE, 1);
	NVIC_SystemReset();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void getCuvexVersions(void)
{
	/*** Get firmware version ***/
	memset(cuvex.info.fw_version, 0x00, sizeof(cuvex.info.fw_version));
	memcpy(cuvex.info.fw_version, FIRMWARE_VERSION, strlen(FIRMWARE_VERSION));

	/*** Get hardware version ***/
	memset(cuvex.info.hw_version, 0x00, sizeof(cuvex.info.hw_version));

	if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_RESET)){
		memcpy(cuvex.info.hw_version, "1", 1);
	}
	else if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_SET)){
		memcpy(cuvex.info.hw_version, "2", 1);
	}
	else if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_RESET)){
		memcpy(cuvex.info.hw_version, "3", 1);
	}
	else if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_SET)){
		memcpy(cuvex.info.hw_version, "4", 1);
	}
	else if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_RESET)){
		memcpy(cuvex.info.hw_version, "5", 1);
	}
	else if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_SET)){
		memcpy(cuvex.info.hw_version, "6", 1);
	}
	else if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_RESET)){
		memcpy(cuvex.info.hw_version, "7", 1);
	}
	else if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_SET)){
		memcpy(cuvex.info.hw_version, "8", 1);
	}
}


