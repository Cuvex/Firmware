/*
 *****************************************************************************
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

#include <gui/containers/decrypt_tag.hpp>
#include "main.h"

extern struct cuvex cuvex;
extern HASH_HandleTypeDef hhash;
extern CRYP_HandleTypeDef hcryp;
extern RNG_HandleTypeDef hrng;

typedef struct{
	uint8_t ipad[64];
	uint8_t opad[64];
}hmac_sha256_ctx_t;

decrypt_tag::decrypt_tag(): num_pwds(0), actual_pwd(0), pwd_ok(0), pwd_raw{0}, pwd_sha256{0}, pwd_combined_sha256{0}, header_aes_gcm{0}, iv_aes_gcm{0}, pwds{0}, pwds_sha256{0}, pwds_sha256_concat{0}, pwds_key_pbkdf2{0}
{

}

void decrypt_tag::initialize()
{
	decrypt_tagBase::initialize();
	decrypt_tag::setScreenMode();
	decrypt_tag::setScreenLanguage();
	decrypt_tag::defaultValues();
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::tickEvent()
{
	/*** Password - Keyboard (password) ***/
	if(keyboard_password.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard_text_typedBuffer, keyboard_password.getBuffer(), KEYBOARD_TEXT_TYPED_SIZE) != 0)
		{
			Unicode::snprintf(keyboard_text_typedBuffer, KEYBOARD_TEXT_TYPED_SIZE, keyboard_password.getBuffer());
			keyboard_text_typed.setWideTextAction(touchgfx::WIDE_TEXT_NONE);

			if(keyboard_text_typed.getTextWidth() <= 160){
				keyboard_text_typed.setPosition(160-(keyboard_text_typed.getTextWidth()/2), 75, keyboard_text_typed.getTextWidth(), 20);
			}
			else{
				keyboard_text_typed.setPosition(76, 75, 160, 20);
			}

			for(int i=0; i<KEYBOARD_TEXT_TYPED_HIDE_SIZE; i++){
				keyboard_text_typed_hideBuffer[i] = 0x00;
			}
			for(int i=0; i<Unicode::strlen(keyboard_text_typedBuffer); i++){
				keyboard_text_typed_hideBuffer[i] = 8226;	//U+8226 (bullet '•')
			}

			if(keyboard_text_typedBuffer[0] == 0x00){
				keyboard_placeholder.setVisible(true);
			}
			else{
				keyboard_placeholder.setVisible(false);
			}

			keyboard_text_area.invalidate();
		}
	}

	/*** Processing secret ***/
	if(processing.isVisible() == true)
	{
		/*** Proccesing secret logic ***/
		processingSecret();

		/*** Screen update ***/
		processing.setVisible(false);
		background.invalidate();
	}
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::hideKeyboardPressed()
{
	keyboard_text_info.setPosition(0, 90, 320, 20);
	keyboard_text_typed_hide.setPosition(76, 125, 160, 20);
	keyboard_text_area.setXY(45, 120);
	keyboard_pwd_eye.setXY(245, 120);
	keyboard_placeholder.setPosition(62, 125, 180, 20);

	if(keyboard_text_typed.getTextWidth() <= 160){
		keyboard_text_typed.setPosition(160-(keyboard_text_typed.getTextWidth()/2), 125, keyboard_text_typed.getTextWidth(), 20);
	}
	else{
		keyboard_text_typed.setPosition(76, 125, 160, 20);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard_password.setVisible(false);
	keyboard_btn_hide.setVisible(false);
	keyboard_btn_show.setVisible(true);
	keyboard_btn_enter.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::showKeyboardPressed()
{
	keyboard_text_info.setPosition(0, 40, 320, 20);
	keyboard_text_typed_hide.setPosition(76, 75, 160, 20);
	keyboard_text_area.setXY(45, 70);
	keyboard_pwd_eye.setXY(245, 70);
	keyboard_placeholder.setPosition(62, 75, 180, 20);

	if(keyboard_text_typed.getTextWidth() <= 160){
		keyboard_text_typed.setPosition(160-(keyboard_text_typed.getTextWidth()/2), 75, keyboard_text_typed.getTextWidth(), 20);
	}
	else{
		keyboard_text_typed.setPosition(76, 75, 160, 20);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard_password.setVisible(true);
	keyboard_btn_hide.setVisible(true);
	keyboard_btn_show.setVisible(false);
	keyboard_btn_enter.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::enterKeyboardPressed()
{
	memset(cuvex.decrypt.cryptogram_decrypted, 0x00, sizeof(cuvex.decrypt.cryptogram_decrypted));

	if(keyboard_text_typedBuffer[0] != 0x00)
	{
		/*** Obtaining the typed text (raw password) + Obtaining its SHA-256 hash ***/
		memset(pwds[actual_pwd], 0x00, KEYBOARD_TEXT_TYPED_SIZE);
		memset(pwds_sha256[actual_pwd], 0x00, 32);

		for(int i=0; i<KEYBOARD_TEXT_TYPED_SIZE; i++)
		{
			if(keyboard_text_typedBuffer[i] == 8364){	//If '€' (8364) is converted to the character '¶' (182) to only occupy 1 byte
				pwds[actual_pwd][i] = 182;
			}
			else{
				pwds[actual_pwd][i] = (uint8_t) keyboard_text_typedBuffer[i];
			}
		}

		HAL_HASHEx_SHA256_Start(&hhash, pwds[actual_pwd], strlen((char *) pwds[actual_pwd]), pwds_sha256[actual_pwd], HAL_MAX_DELAY);

		actual_pwd++;

		if(actual_pwd < num_pwds)
		{
			/*** Selection of texts to display in the password information field (based on language and number of signers) ***/
			Unicode::UnicodeChar degree[] = {0x00B0,0};

			if(cuvex.info.language == SPANISH){
				if(num_pwds > 1){
					Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Persona N%s%d", degree, actual_pwd+1);
				}
				else{
					Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Introduce tu Password.");
				}

				if(num_pwds != actual_pwd+1){
					Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "CONTINUAR");
				}
				else{
					Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "DESCIFRAR");
				}
			}
			else{
				if(num_pwds > 1){
					Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Person N%s%d", degree, actual_pwd+1);
				}
				else{
					Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Enter your Password.");
				}

				if(num_pwds != actual_pwd+1){
					Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "CONTINUE");
				}
				else{
					Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "DECRYPT");
				}
			}
		}
		else
		{
			/*** Procesing state ***/
			typePassword.setVisible(false);
			passwordError1.setVisible(false);
			passwordError2.setVisible(false);
			processing.setVisible(true);

			//			/*** Decryption of secret (seeds, plaintext) ***/
			//			if(cuvex.nfc.tag.multisigned_total != cuvex.nfc.tag.multisigned_mandatory){
			//				decryptSecretWithCombinations(cuvex.decrypt.cryptogram_decrypted);
			//			}
			//			else{
			//				decryptSecret(cuvex.decrypt.cryptogram_decrypted);
			//			}
			//
			//			/*** Callback with password result ***/
			//			if(passwordResultCallback && passwordResultCallback->isValid())
			//			{
			//				if(pwd_ok == false){
			//					if(cuvex.info.errors == 0){
			//						typePassword.setVisible(false);
			//						passwordError1.setVisible(true);
			//						passwordError2.setVisible(false);
			//					}
			//					else{
			//						typePassword.setVisible(false);
			//						passwordError1.setVisible(false);
			//						passwordError2.setVisible(true);
			//					}
			//				}
			//
			//				passwordResultCallback->execute(pwd_ok);	//Send password result and execute callback
			//			}
		}

		/*** Clearing keyboard and display buffers ***/
		memset(keyboard_text_typedBuffer, 0x00, sizeof(keyboard_text_typedBuffer));
		memset(keyboard_text_typed_hideBuffer, 0x00, sizeof(keyboard_text_typed_hideBuffer));
		keyboard_password.clearBuffer();

		/*** Screen update ***/
		background.invalidate();
	}
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::eyePressed()
{
	if(keyboard_pwd_eye.getCurrentlyDisplayedBitmap() == BITMAP_OJO_ABIERTO_ID){
		keyboard_text_typed.setVisible(true);
		keyboard_text_typed_hide.setVisible(false);
	}
	else{
		keyboard_text_typed.setVisible(false);
		keyboard_text_typed_hide.setVisible(true);
	}

	keyboard_text_area.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::btnError1Pressed()
{
	/*** Restore default values ***/
	defaultValues();

	/*** Selecting visible/hidden elements on the screen ***/
	typePassword.setVisible(true);
	passwordError1.setVisible(false);
	passwordError2.setVisible(false);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::btnError2Pressed()
{
	NVIC_SystemReset();
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::setPasswordResultCallback(touchgfx::GenericCallback<uint8_t>& cb)
{
	passwordResultCallback = &cb;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::setVisible(bool visible)
{
	Container::setVisible(visible);

	if(visible){
		decrypt_tag::defaultValues();
	}
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::setScreenMode()
{
	/*** Setting screen elements based on mode (dark/light) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		keyboard_btn_enter.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_typed_hide.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		processing_text.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		ko_password_1_error_text_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		ko_password_1_error_text_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		ko_password_2_error_text_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		ko_password_2_error_text_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		ko_password_1_btn.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		ko_password_2_btn.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
	}

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::setScreenLanguage()
{
	/*** Text configuration based on selected language (Spanish/English) ***/
	if(cuvex.info.language == SPANISH){
		Texts::setLanguage(SP);
	}
	else{
		Texts::setLanguage(GB);
	}

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::defaultValues()
{
	/*** Default variables value ***/
	num_pwds = 0;
	actual_pwd = 0;
	pwd_ok = 0;
	memset(pwds, 0, sizeof(pwds));
	memset(pwd_raw, 0, sizeof(pwd_raw));
	memset(pwd_sha256, 0, sizeof(pwd_sha256));
	memset(pwd_combined_sha256, 0, sizeof(pwd_combined_sha256));
	memset(header_aes_gcm, 0, sizeof(header_aes_gcm));
	memset(iv_aes_gcm, 0, sizeof(iv_aes_gcm));
	memset(pwds_sha256, 0, sizeof(pwds_sha256));
	memset(pwds_sha256_concat, 0, sizeof(pwds_sha256_concat));
	memset(pwds_key_pbkdf2, 0, sizeof(pwds_key_pbkdf2));

	/*** Default keyboard buffers ***/
	memset(keyboard_text_typedBuffer, 0x00, sizeof(keyboard_text_typedBuffer));
	keyboard_password.clearBuffer();

	/*** Default texts ***/
	Unicode::UnicodeChar degree[] = {0x00B0,0};
	num_pwds = cuvex.nfc.tag.multisigned_mandatory;

	if(cuvex.info.language == SPANISH){
		if(num_pwds > 1){
			Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Persona N%s%d", degree, actual_pwd+1);
			Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "CONTINUAR");
		}
		else{
			Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Introduce tu Password.");
			Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "DESCIFRAR");
		}
	}
	else{
		if(num_pwds > 1){
			Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Person N%s%d", degree, actual_pwd+1);
			Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "CONTINUE");
		}
		else{
			Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Enter your Password.");
			Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "DECRYPT");
		}
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::configAESPeripheral(uint8_t keyAES[], uint8_t ivAES[], uint8_t headerAES[], uint8_t type)
{
	HAL_CRYP_DeInit(&hcryp);

	if(type == 1)
	{
		hcryp.Instance = AES;
		hcryp.Init.DataType = CRYP_NO_SWAP;
		hcryp.Init.KeySize = CRYP_KEYSIZE_256B;
		hcryp.Init.pKey = (uint32_t *) keyAES;
		hcryp.Init.Algorithm = CRYP_AES_ECB;
		hcryp.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
		hcryp.Init.HeaderWidthUnit = CRYP_HEADERWIDTHUNIT_WORD;
		hcryp.Init.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ALWAYS;
		hcryp.Init.KeyMode = CRYP_KEYMODE_NORMAL;
	}
	else
	{
		for(int i = 0; i < 8; i++){
			hcryp.Init.pKey[i] = ((keyAES[i*4] << 24) | (keyAES[i*4+1] << 16) | (keyAES[i*4+2] << 8) | keyAES[i*4+3]);
		}

		for(int i = 0; i < 4; i++){
			hcryp.Init.pInitVect[i] = ((ivAES[i*4] << 24) | (ivAES[i*4+1] << 16) | (ivAES[i*4+2] << 8) | ivAES[i*4+3]);
		}

		for(int i = 0; i < 1; i++){
			hcryp.Init.Header[i] = ((headerAES[i*4] << 24) | (headerAES[i*4+1] << 16) | (headerAES[i*4+2] << 8) | headerAES[i*4+3]);
		}

		hcryp.Instance = AES;
		hcryp.Init.DataType = CRYP_NO_SWAP;
		hcryp.Init.KeySize = CRYP_KEYSIZE_256B;
		hcryp.Init.Algorithm = CRYP_AES_GCM_GMAC;
		hcryp.Init.HeaderSize = 1;
		hcryp.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
		hcryp.Init.HeaderWidthUnit = CRYP_HEADERWIDTHUNIT_WORD;
		hcryp.Init.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ALWAYS;
		hcryp.Init.KeyMode = CRYP_KEYMODE_NORMAL;
	}

	if(HAL_CRYP_Init(&hcryp) != HAL_OK){
		Error_Handler();
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::configAESPeripheral_v2(uint8_t keyAES[], uint8_t ivAES[])
{
	__ALIGN_BEGIN uint32_t HeaderAES_aux[1] __ALIGN_END = {0x00000000};

	for(uint8_t a=0; a<8; a++){
		cuvex.nfc.tag.new_pKeyAES[a] = keyAES[a*4] * 0x1000000 + keyAES[(a*4)+1] * 0x10000 + keyAES[(a*4)+2] * 0x100 + keyAES[(a*4)+3];
	}

	for(uint8_t b=0; b<4; b++){
		cuvex.nfc.tag.new_ivAES[b] = ivAES[b*4] * 0x1000000 + ivAES[(b*4)+1] * 0x10000 + ivAES[(b*4)+2] * 0x100 + ivAES[(b*4)+3];
	}

	HAL_CRYP_DeInit(&hcryp);

	hcryp.Instance = AES;
	hcryp.Init.DataType = CRYP_NO_SWAP;
	hcryp.Init.KeySize = CRYP_KEYSIZE_256B;
	hcryp.Init.pKey = (uint32_t *) cuvex.nfc.tag.new_pKeyAES;
	hcryp.Init.pInitVect = (uint32_t *) cuvex.nfc.tag.new_ivAES;
	hcryp.Init.Algorithm = CRYP_AES_GCM_GMAC;
	hcryp.Init.Header = (uint32_t *) HeaderAES_aux;
	hcryp.Init.HeaderSize = 1;
	hcryp.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
	hcryp.Init.HeaderWidthUnit = CRYP_HEADERWIDTHUNIT_WORD;
	hcryp.Init.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ALWAYS;
	hcryp.Init.KeyMode = CRYP_KEYMODE_NORMAL;

	if (HAL_CRYP_Init(&hcryp) != HAL_OK){
		Error_Handler();
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::decryptSecret(uint8_t  decrypted_text[SIZE_CRYPT])
{
	uint16_t pwd_raw_length_old = SIGNATURE_SIZE;
	uint16_t pwd_raw_length = 0;
	uint8_t  pwd_lengths[6] = {0};
	uint8_t  iteration_length = 0;
	uint8_t  decrypted_text_aux[SIZE_CRYPT] = {0};
	uint16_t pos=0;

	/*** Obtaining the length and concatenation of the complete password (in raw) ***/
	for(int i=0; i<6; i++){
		pwd_lengths[i] = strlen((const char *) pwds[i]);
		pwd_raw_length_old = pwd_raw_length_old + pwd_lengths[i];
		pwd_raw_length = pwd_raw_length + pwd_lengths[i];
	}

	if(pwd_lengths[0] != 0)
	{
		/*** AES-256 peripheral configuration (password + initialization vector + header) + AES-256 Decrypt ***/
		if(strstr((const char *) cuvex.nfc.tag.fw_version, "v1.0.0") != NULL)
		{
			/*** Obtaining the encrypted password (SHA-256) ***/
			memset(pwd_raw, 0x00, sizeof(pwd_raw));
			strncat((char*) pwd_raw, (const char*) cuvex.signature_buffer, SIGNATURE_SIZE);
			for(int i=0; i<6; i++){
				strcat((char*) pwd_raw, (const char*) pwds[i]);
			}

			HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, pwd_raw_length_old, pwd_sha256, HAL_MAX_DELAY);

			configAESPeripheral(pwd_sha256, iv_aes_gcm, header_aes_gcm, 1);
			HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.cryptogram, SIZE_CRYPT_MSG, (uint32_t *) decrypted_text, HAL_MAX_DELAY);
		}
		else if((strstr((const char *) cuvex.nfc.tag.fw_version, "v1.0.1") != NULL) || (strstr((const char *) cuvex.nfc.tag.fw_version, "v1.0.2") != NULL) || (strstr((const char *) cuvex.nfc.tag.fw_version, "v1.0.3") != NULL))
		{
			/*** Obtaining the encrypted password (SHA-256) ***/
			memset(pwd_raw, 0x00, sizeof(pwd_raw));
			strncat((char*) pwd_raw, (const char*) cuvex.signature_buffer, SIGNATURE_SIZE);
			for(int i=0; i<6; i++){
				strcat((char*) pwd_raw, (const char*) pwds[i]);
			}

			HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, pwd_raw_length_old, pwd_sha256, HAL_MAX_DELAY);

			HAL_HASH_MD5_Start(&hhash, cuvex.nfc.tag.alias, strlen((char *) cuvex.nfc.tag.alias), iv_aes_gcm, HAL_MAX_DELAY);
			memset(header_aes_gcm, 0x00, sizeof(header_aes_gcm));
			configAESPeripheral(pwd_sha256, iv_aes_gcm, header_aes_gcm, 0);
			HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.cryptogram, SIZE_CRYPT_MSG, (uint32_t *) decrypted_text, HAL_MAX_DELAY);
		}
		else if((strstr((const char *) cuvex.nfc.tag.fw_version, "v1.1.0") != NULL) || (strstr((const char *) cuvex.nfc.tag.fw_version, "v1.1.1") != NULL) || (strstr((const char *) cuvex.nfc.tag.fw_version, "v1.1.2") != NULL) || (strstr((const char *) cuvex.nfc.tag.fw_version, "v1.1.3") != NULL))
		{
			/*** Obtaining the encrypted password (SHA-256) ***/
			memset(pwd_raw, 0x00, sizeof(pwd_raw));
			for(int i=0; i<6; i++){
				strcat((char*) pwd_raw, (const char*) pwds[i]);
			}

			HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, pwd_raw_length, pwd_sha256, HAL_MAX_DELAY);

			HAL_HASH_MD5_Start(&hhash, cuvex.nfc.tag.alias, strlen((char *) cuvex.nfc.tag.alias), iv_aes_gcm, HAL_MAX_DELAY);

			/*** Init count to 0x02 ***/
			iv_aes_gcm[12]=0x00;
			iv_aes_gcm[13]=0x00;
			iv_aes_gcm[14]=0x00;
			iv_aes_gcm[15]=0x02;

			configAESPeripheral_v2(pwd_sha256, iv_aes_gcm);

			/*** NFC SAVES DATA IN UINT8_T FORMAT ***/
			/*** Create new text to dencrypt under format uint32_t ***/
			for(uint8_t k=0; k<SIZE_CRYPT_MSG; k++){
				cuvex.nfc.tag.new_text_to_decrypt[k] = cuvex.nfc.tag.cryptogram[k*4] * 0x1000000 + cuvex.nfc.tag.cryptogram[(k*4)+1] * 0x10000 + cuvex.nfc.tag.cryptogram[(k*4)+2] * 0x100 + cuvex.nfc.tag.cryptogram[(k*4)+3];
			}

			HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.new_text_to_decrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_text_decrypted, HAL_MAX_DELAY);

			pos=0;
			for(uint8_t z=0; z<SIZE_CRYPT_MSG; z++)
			{
				decrypted_text_aux[pos]   = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z] / 0x1000000);
				decrypted_text_aux[pos+1] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z] / 0x10000);
				decrypted_text_aux[pos+2] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z] / 0x100);
				decrypted_text_aux[pos+3] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z]);
				pos+=4;
			}

			memset(decrypted_text, 0, SIZE_CRYPT);
			memcpy(decrypted_text, decrypted_text_aux, SIZE_CRYPT);
		}
		else
		{
			/*** 1) Sort the keys lexicographically ***/
			sortPasswordsLexicographically(pwds_sha256, num_pwds);

			/*** 2) Concatenate keys ***/
			for(int i=0; i<num_pwds; i++){
				memcpy(&pwds_sha256_concat[i*32], pwds_sha256[i], 32);
			}

			/*** 3) PBKDF2-HMAC-SHA256 ***/
			pbkdf2_sha256(pwds_sha256_concat, 32*num_pwds, cuvex.nfc.tag.salt_pbkdf2, sizeof(cuvex.nfc.tag.salt_pbkdf2), 50000, pwds_key_pbkdf2, sizeof(pwds_key_pbkdf2));

			/*** 4) AES-256 peripheral configuration --> password + initialization vector (12Bytes nonce + 4B counter) ***/
			configAESPeripheral_v2(pwds_key_pbkdf2, cuvex.nfc.tag.iv_aes_gcm);

			/*** 5) Convert text to decrypt under format uint32_t --> Data is packed/unpacked in big-endian order (AES hardware requirement) ***/
			for(uint8_t k=0; k<SIZE_CRYPT_MSG; k++){
				cuvex.nfc.tag.new_text_to_decrypt[k] = ((uint32_t) cuvex.nfc.tag.cryptogram[k*4] << 24) | ((uint32_t) cuvex.nfc.tag.cryptogram[(k*4)+1] << 16) | ((uint32_t) cuvex.nfc.tag.cryptogram[(k*4)+2] << 8) | ((uint32_t) cuvex.nfc.tag.cryptogram[(k*4)+3]);
			}

			/*** 6) Decrypt the text ***/
			HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.new_text_to_decrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_text_decrypted, HAL_MAX_DELAY);

			/*** 7) Convert text decrypted under format uint8_t ***/
			for(uint8_t z=0; z<SIZE_CRYPT_MSG; z++){
				decrypted_text_aux[z*4] 	= (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z] >> 24);
				decrypted_text_aux[(z*4)+1] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z] >> 16);
				decrypted_text_aux[(z*4)+2] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z] >> 8);
				decrypted_text_aux[(z*4)+3] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z]);
			}

			memset(decrypted_text, 0, SIZE_CRYPT);
			memcpy(decrypted_text, decrypted_text_aux, SIZE_CRYPT);
		}

		/*** Check if text is decrypted correctly ***/
		pwd_ok = checkDecryptedText(decrypted_text);

		/*** All possible combinations must be checked ***/
		for(int i=5; i>=0; i--){
			if(pwd_lengths[i] != 0){
				iteration_length = i+1;
				break;
			}
		}

		/*** Heap algorithm ***/
		uint8_t aux[KEYBOARD_TEXT_TYPED_SIZE] = {0};
		uint16_t c[iteration_length] = {0};
		uint16_t z = 0;

		while(z < iteration_length)
		{
			if(pwd_ok == 1){
				break;
			}
			else{
				if(c[z] < z)
				{
					/*** Swaps two elements in 'pwds' according to the index 'z' and the Heap's algorithm ***/
					if(z%2 == 0){
						memset(aux, 0, KEYBOARD_TEXT_TYPED_SIZE);
						memcpy(aux, &pwds[0], strlen((const char *) pwds[0]));
						memset(&pwds[0], 0, KEYBOARD_TEXT_TYPED_SIZE);
						memcpy(&pwds[0], &pwds[z], strlen((const char *) pwds[z]));
						memset(&pwds[z], 0, KEYBOARD_TEXT_TYPED_SIZE);
						memcpy(&pwds[z], aux, strlen((const char *) aux));
					}
					else{
						memset(aux, 0, KEYBOARD_TEXT_TYPED_SIZE);
						memcpy(aux, &pwds[c[z]], strlen((const char *) pwds[c[z]]));
						memset(&pwds[c[z]], 0, KEYBOARD_TEXT_TYPED_SIZE);
						memcpy(&pwds[c[z]], &pwds[z], strlen((const char *) pwds[z]));
						memset(&pwds[z], 0, KEYBOARD_TEXT_TYPED_SIZE);
						memcpy(&pwds[z], aux, strlen((const char *) aux));
					}

					/*** AES-256 peripheral configuration (password + initialization vector + header) + AES-256 Decrypt ***/
					if(strstr((const char *) cuvex.nfc.tag.fw_version, "v1.0.0") != NULL)
					{
						/*** Updates 'pwd_raw' by concatenating the signature and the new permutation of passwords in 'pwds' ***/
						memset(pwd_raw, 0x00, sizeof(pwd_raw));
						strncat((char*) pwd_raw, (const char*) cuvex.signature_buffer, SIGNATURE_SIZE);
						for(int i=0; i<6; i++){
							strcat((char*) pwd_raw, (const char*) pwds[i]);
						}

						/*** Obtaining the encrypted password (SHA-256) ***/
						HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, pwd_raw_length_old, pwd_sha256, HAL_MAX_DELAY);

						configAESPeripheral(pwd_sha256, iv_aes_gcm, header_aes_gcm, 1);
						HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.cryptogram, SIZE_CRYPT_MSG, (uint32_t *) decrypted_text, HAL_MAX_DELAY);
					}
					else if((strstr((const char *) cuvex.nfc.tag.fw_version, "v1.0.1") != NULL) || (strstr((const char *) cuvex.nfc.tag.fw_version, "v1.0.2") != NULL) || (strstr((const char *) cuvex.nfc.tag.fw_version, "v1.0.3") != NULL))
					{
						/*** Updates 'pwd_raw' by concatenating the signature and the new permutation of passwords in 'pwds' ***/
						memset(pwd_raw, 0x00, sizeof(pwd_raw));
						strncat((char*) pwd_raw, (const char*) cuvex.signature_buffer, SIGNATURE_SIZE);
						for(int i=0; i<6; i++){
							strcat((char*) pwd_raw, (const char*) pwds[i]);
						}

						/*** Obtaining the encrypted password (SHA-256) ***/
						HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, pwd_raw_length_old, pwd_sha256, HAL_MAX_DELAY);

						HAL_HASH_MD5_Start(&hhash, cuvex.nfc.tag.alias, strlen((char *) cuvex.nfc.tag.alias), iv_aes_gcm, HAL_MAX_DELAY);
						memset(header_aes_gcm, 0x00, sizeof(header_aes_gcm));
						configAESPeripheral(pwd_sha256, iv_aes_gcm, header_aes_gcm, 0);
						HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.cryptogram, SIZE_CRYPT_MSG, (uint32_t *) decrypted_text, HAL_MAX_DELAY);
					}
					else
					{
						/*** Updates 'pwd_raw' by concatenating the signature and the new permutation of passwords in 'pwds' ***/
						memset(pwd_raw, 0x00, sizeof(pwd_raw));
						for(int i=0; i<6; i++){
							strcat((char*) pwd_raw, (const char*) pwds[i]);
						}

						/*** Obtaining the encrypted password (SHA-256) ***/
						HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, pwd_raw_length, pwd_sha256, HAL_MAX_DELAY);

						HAL_HASH_MD5_Start(&hhash, cuvex.nfc.tag.alias, strlen((char *) cuvex.nfc.tag.alias), iv_aes_gcm, HAL_MAX_DELAY);

						/*** Init count to 0x02 ***/
						iv_aes_gcm[12]=0x00;
						iv_aes_gcm[13]=0x00;
						iv_aes_gcm[14]=0x00;
						iv_aes_gcm[15]=0x02;

						configAESPeripheral_v2(pwd_sha256, iv_aes_gcm);

						/*** NFC SAVES DATA IN UINT8_T FORMAT ***/
						/*** Create new text to dencrypt under format uint32_t ***/
						for(uint8_t k=0; k<SIZE_CRYPT_MSG; k++){
							cuvex.nfc.tag.new_text_to_decrypt[k] = cuvex.nfc.tag.cryptogram[k*4] * 0x1000000 + cuvex.nfc.tag.cryptogram[(k*4)+1] * 0x10000 + cuvex.nfc.tag.cryptogram[(k*4)+2] * 0x100 + cuvex.nfc.tag.cryptogram[(k*4)+3];
						}

						HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.new_text_to_decrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_text_decrypted, HAL_MAX_DELAY);

						pos=0;
						for(uint8_t z=0; z<SIZE_CRYPT_MSG; z++)
						{
							decrypted_text_aux[pos]   = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z] / 0x1000000);
							decrypted_text_aux[pos+1] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z] / 0x10000);
							decrypted_text_aux[pos+2] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z] / 0x100);
							decrypted_text_aux[pos+3] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z]);
							pos+=4;
						}

						memset(decrypted_text, 0, SIZE_CRYPT);
						memcpy(decrypted_text, decrypted_text_aux, SIZE_CRYPT);
					}

					/*** Check if text is decrypted correctly ***/
					pwd_ok = checkDecryptedText(decrypted_text);

					c[z] = c[z] + 1;
					z = 0;
				}
				else{
					c[z] = 0;
					z++;
				}
			}
		}
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::decryptSecretWithCombinations(uint8_t  decrypted_text[SIZE_CRYPT])
{
	uint8_t block_buffer[32] = {0};
	uint32_t block_buffer_st_format[8] = {0};
	uint32_t pwd_sha256_st_format[8] = {0};
	uint8_t pwd_lengths[6] = {0};
	uint8_t iteration_length = 0;
	bool is_old = false;
	uint16_t pos = 0;
	uint8_t decrypted_text_aux[SIZE_CRYPT] = {0};

	if((strstr((const char *) cuvex.nfc.tag.fw_version, "v1.0.0") != NULL) || (strstr((const char *) cuvex.nfc.tag.fw_version, "v1.0.1") != NULL) || (strstr((const char *) cuvex.nfc.tag.fw_version, "v1.0.2") != NULL) || (strstr((const char *) cuvex.nfc.tag.fw_version, "v1.0.3") != NULL)){
		is_old = true;
	}

	/*** Concatenation of the complete password (in raw) ***/
	memset(pwd_raw, 0x00, sizeof(pwd_raw));
	if(is_old){
		strncat((char*) pwd_raw, (const char*) cuvex.signature_buffer, SIGNATURE_SIZE);
	}

	for(int i=0; i<6; i++){
		strcat((char*) pwd_raw, (const char*) pwds[i]);
		pwd_lengths[i] = strlen((const char *) pwds[i]);
	}

	if(pwd_lengths[0] != 0)
	{
		if((is_old == true) || (strstr((const char *) cuvex.nfc.tag.fw_version, "v1.1.0") != NULL) || (strstr((const char *) cuvex.nfc.tag.fw_version, "v1.1.1") != NULL) || (strstr((const char *) cuvex.nfc.tag.fw_version, "v1.1.2") != NULL) || (strstr((const char *) cuvex.nfc.tag.fw_version, "v1.1.3") != NULL))
		{
			/*** Obtaining the encrypted password (SHA-256) ***/
			memset(pwd_combined_sha256, 0x00, sizeof(pwd_combined_sha256));
			if(is_old){
				HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, strlen((char *) pwd_raw) + SIGNATURE_SIZE, pwd_combined_sha256, HAL_MAX_DELAY);
			}
			else{
				HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, strlen((char *) pwd_raw), pwd_combined_sha256, HAL_MAX_DELAY);
			}

			/*** Check all blocks trying decrypt ***/
			for(int i=0; i<20; i++)
			{
				/*** Select block to decrypt ***/
				memset(block_buffer, 0x00, 32);
				memcpy(block_buffer, cuvex.nfc.tag.multisignature + (i*32) , 32);

				/*** AES-256 peripheral configuration (initialization vector + header) ***/
				HAL_HASH_MD5_Start(&hhash, cuvex.nfc.tag.alias, strlen((char *) cuvex.nfc.tag.alias), iv_aes_gcm, HAL_MAX_DELAY);
				if(!is_old)
				{
					/*** Init count to 0x02 ***/
					iv_aes_gcm[12]=0x00;
					iv_aes_gcm[13]=0x00;
					iv_aes_gcm[14]=0x00;
					iv_aes_gcm[15]=0x02;

					configAESPeripheral_v2(pwd_combined_sha256, iv_aes_gcm);

					/*** NFC SAVES DATA IN UINT8_T FORMAT ***/
					/*** Create new text to dencrypt under format uint32_t ***/
					for(uint8_t k=0; k<8; k++){
						block_buffer_st_format[k] = block_buffer[k*4] * 0x1000000 + block_buffer[(k*4)+1] * 0x10000 + block_buffer[(k*4)+2] * 0x100 + block_buffer[(k*4)+3];
					}

					HAL_CRYP_Decrypt(&hcryp, (uint32_t *) block_buffer_st_format, 8, (uint32_t *) pwd_sha256_st_format, HAL_MAX_DELAY);

					pos=0;
					for(uint8_t a=0; a<8; a++)
					{
						pwd_sha256[pos] = (uint8_t) (pwd_sha256_st_format[a] / 0x1000000);
						pwd_sha256[pos+1] = (uint8_t) (pwd_sha256_st_format[a] / 0x10000);
						pwd_sha256[pos+2] = (uint8_t) (pwd_sha256_st_format[a] / 0x100);
						pwd_sha256[pos+3] = (uint8_t) (pwd_sha256_st_format[a]);
						pos+=4;
					}

					/*** AES-256 peripheral configuration (password 2) + AES-256 Decrypt 2 ***/
					configAESPeripheral_v2(pwd_sha256, iv_aes_gcm);

					/*** Create new text to dencrypt under format uint32_t ***/
					for(uint8_t b=0; b<SIZE_CRYPT_MSG; b++){
						cuvex.nfc.tag.new_text_to_decrypt[b] = cuvex.nfc.tag.cryptogram[b*4] * 0x1000000 + cuvex.nfc.tag.cryptogram[(b*4)+1] * 0x10000 + cuvex.nfc.tag.cryptogram[(b*4)+2] * 0x100 + cuvex.nfc.tag.cryptogram[(b*4)+3];
					}

					HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.new_text_to_decrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_text_decrypted, HAL_MAX_DELAY);

					pos=0;
					for(uint8_t c=0; c<SIZE_CRYPT_MSG; c++)
					{
						decrypted_text_aux[pos] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[c] / 0x1000000);
						decrypted_text_aux[pos+1] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[c] / 0x10000);
						decrypted_text_aux[pos+2] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[c] / 0x100);
						decrypted_text_aux[pos+3] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[c]);
						pos+=4;
					}

					memset(decrypted_text, 0, SIZE_CRYPT);
					memcpy(decrypted_text, decrypted_text_aux, SIZE_CRYPT);
				}
				else
				{
					memset(header_aes_gcm, 0x00, sizeof(header_aes_gcm));

					/*** AES-256 peripheral configuration (password 1) + AES-256 Decrypt 1 ***/
					configAESPeripheral(pwd_combined_sha256, iv_aes_gcm, header_aes_gcm, 0);
					HAL_CRYP_Decrypt(&hcryp, (uint32_t *) block_buffer, 32/4, (uint32_t *) pwd_sha256, HAL_MAX_DELAY);

					/*** AES-256 peripheral configuration (password 2) + AES-256 Decrypt 2 ***/
					configAESPeripheral(pwd_sha256, iv_aes_gcm, header_aes_gcm, 0);
					HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.cryptogram, SIZE_CRYPT_MSG, (uint32_t *) decrypted_text, HAL_MAX_DELAY);
				}

				/*** Check if text is decrypted correctly ***/
				pwd_ok = checkDecryptedText(decrypted_text);

				if(pwd_ok == 1){
					break;
				}
			}
		}
		else
		{
			uint8_t aes_crypt[32] = {0};
			uint8_t salt[16] = {0};
			uint8_t iv[16] = {0};
			uint32_t text_to_decrypt_u32[8] = {0}, text_decrypted_u32[8] = {0};
			uint8_t text_decrypted_u8[32] = {0};

			/*** Sort the keys lexicographically ***/
			sortPasswordsLexicographically(pwds_sha256, cuvex.nfc.tag.multisigned_mandatory);

			/*** Concatenate keys ***/
			for(int i=0; i<cuvex.nfc.tag.multisigned_mandatory; i++){
				memcpy(&pwds_sha256_concat[i*32], pwds_sha256[i], 32);
			}

			/*** Worst case (3 of 6) get 20 combinations ***/
			for(int i=0; i<20; i++)
			{
				memset(aes_crypt, 0x00, sizeof(aes_crypt));
				memset(salt, 0x00, sizeof(salt));
				memset(iv, 0x00, sizeof(iv));

				memcpy(aes_crypt, cuvex.nfc.tag.multisignature + (i*64), 32);
				memcpy(salt, cuvex.nfc.tag.multisignature + (i*64) + 32, 16);
				memcpy(iv, cuvex.nfc.tag.multisignature + (i*64) + 48, 16);

				/*** PBKDF2-HMAC-SHA256 ***/
				pbkdf2_sha256(pwds_sha256_concat, 32*cuvex.nfc.tag.multisigned_mandatory, salt, sizeof(salt), 50000, pwds_key_pbkdf2, sizeof(pwds_key_pbkdf2));

				/*** AES-256 peripheral configuration --> password + initialization vector (12Bytes nonce + 4B counter) ***/
				configAESPeripheral_v2(pwds_key_pbkdf2, iv);

				/*** Convert text to decrypt under format uint32_t --> Data is packed/unpacked in big-endian order (AES hardware requirement) ***/
				for(uint8_t k=0; k<32/4; k++){
					text_to_decrypt_u32[k] = ((uint32_t) aes_crypt[k*4] << 24) | ((uint32_t) aes_crypt[(k*4)+1] << 16) | ((uint32_t) aes_crypt[(k*4)+2] << 8) | ((uint32_t) aes_crypt[(k*4)+3]);
				}

				/*** Decrypt the text ***/
				HAL_CRYP_Decrypt(&hcryp, (uint32_t *) text_to_decrypt_u32, 32/4, (uint32_t *) text_decrypted_u32, HAL_MAX_DELAY);

				/*** Convert text decrypted under format uint8_t ***/
				for(uint8_t z=0; z<32/4; z++){
					text_decrypted_u8[z*4] 	= (uint8_t) (text_decrypted_u32[z] >> 24);
					text_decrypted_u8[(z*4)+1] = (uint8_t) (text_decrypted_u32[z] >> 16);
					text_decrypted_u8[(z*4)+2] = (uint8_t) (text_decrypted_u32[z] >> 8);
					text_decrypted_u8[(z*4)+3] = (uint8_t) (text_decrypted_u32[z]);
				}

				/*** AES-256 peripheral configuration --> password + initialization vector (12Bytes nonce + 4B counter) ***/
				configAESPeripheral_v2(text_decrypted_u8, cuvex.nfc.tag.iv_aes_gcm);

				/*** Convert text to decrypt under format uint32_t --> Data is packed/unpacked in big-endian order (AES hardware requirement) ***/
				for(uint8_t k=0; k<SIZE_CRYPT_MSG; k++){
					cuvex.nfc.tag.new_text_to_decrypt[k] = ((uint32_t) cuvex.nfc.tag.cryptogram[k*4] << 24) | ((uint32_t) cuvex.nfc.tag.cryptogram[(k*4)+1] << 16) | ((uint32_t) cuvex.nfc.tag.cryptogram[(k*4)+2] << 8) | ((uint32_t) cuvex.nfc.tag.cryptogram[(k*4)+3]);
				}

				/*** Decrypt the text ***/
				HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.new_text_to_decrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_text_decrypted, HAL_MAX_DELAY);

				/*** Convert text decrypted under format uint8_t ***/
				for(uint8_t z=0; z<SIZE_CRYPT_MSG; z++){
					decrypted_text_aux[z*4] 	= (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z] >> 24);
					decrypted_text_aux[(z*4)+1] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z] >> 16);
					decrypted_text_aux[(z*4)+2] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z] >> 8);
					decrypted_text_aux[(z*4)+3] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[z]);
				}

				memset(decrypted_text, 0, SIZE_CRYPT);
				memcpy(decrypted_text, decrypted_text_aux, SIZE_CRYPT);

				/*** Check if text is decrypted correctly ***/
				pwd_ok = checkDecryptedText(decrypted_text);

#ifdef DEBUG_PRINTF_DECRYPT
				printf("[%d]...%d...\r\n", i, pwd_ok);
#endif
				if(pwd_ok == 1){
					break;
				}
			}
		}

		/*** All possible combinations must be checked ***/
		for(int i=5; i>=0; i--){
			if(pwd_lengths[i] != 0){
				iteration_length = i+1;
				break;
			}
		}

		/*** Heap algorithm ***/
		uint8_t aux[KEYBOARD_TEXT_TYPED_SIZE] = {0};
		uint16_t c[iteration_length] = {0};
		uint16_t z = 0;

		while(z < iteration_length)
		{
			if(pwd_ok == 1){
				break;
			}
			else{
				if(c[z] < z)
				{
					/*** Swaps two elements in 'pwds' according to the index 'z' and the Heap's algorithm ***/
					if(z%2 == 0){
						memset(aux, 0, KEYBOARD_TEXT_TYPED_SIZE);
						memcpy(aux, &pwds[0], strlen((const char *) pwds[0]));
						memset(&pwds[0], 0, KEYBOARD_TEXT_TYPED_SIZE);
						memcpy(&pwds[0], &pwds[z], strlen((const char *) pwds[z]));
						memset(&pwds[z], 0, KEYBOARD_TEXT_TYPED_SIZE);
						memcpy(&pwds[z], aux, strlen((const char *) aux));
					}
					else{
						memset(aux, 0, KEYBOARD_TEXT_TYPED_SIZE);
						memcpy(aux, &pwds[c[z]], strlen((const char *) pwds[c[z]]));
						memset(&pwds[c[z]], 0, KEYBOARD_TEXT_TYPED_SIZE);
						memcpy(&pwds[c[z]], &pwds[z], strlen((const char *) pwds[z]));
						memset(&pwds[z], 0, KEYBOARD_TEXT_TYPED_SIZE);
						memcpy(&pwds[z], aux, strlen((const char *) aux));
					}

					/*** Concatenation of the complete password with the new permutation (in raw) ***/
					memset(pwd_raw, 0x00, sizeof(pwd_raw));
					if(is_old){
						strncat((char*) pwd_raw, (const char*) cuvex.signature_buffer, SIGNATURE_SIZE);
					}

					for(int i=0; i<6; i++){
						strcat((char*) pwd_raw, (const char*) pwds[i]);
					}

					/*** Obtaining the encrypted password (SHA-256) ***/
					memset(pwd_combined_sha256, 0x00, sizeof(pwd_combined_sha256));
					if(is_old){
						HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, strlen((char *) pwd_raw) + SIGNATURE_SIZE, pwd_combined_sha256, HAL_MAX_DELAY);
					}
					else{
						HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, strlen((char *) pwd_raw), pwd_combined_sha256, HAL_MAX_DELAY);
					}

					/*** Check all blocks trying decrypt ***/
					for(int i=0; i<20; i++)
					{
						/*** Select block to decrypt ***/
						memset(block_buffer, 0x00, 32);
						memcpy(block_buffer, cuvex.nfc.tag.multisignature + (i*32) , 32);
						HAL_HASH_MD5_Start(&hhash, cuvex.nfc.tag.alias, strlen((char *) cuvex.nfc.tag.alias), iv_aes_gcm, HAL_MAX_DELAY);

						if(!is_old)
						{
							/*Init count to 0x02*/
							iv_aes_gcm[12]=0x00;
							iv_aes_gcm[13]=0x00;
							iv_aes_gcm[14]=0x00;
							iv_aes_gcm[15]=0x02;

							configAESPeripheral_v2(pwd_combined_sha256, iv_aes_gcm);

							/*** NFC SAVES DATA IN UINT8_T FORMAT ***/
							/*** Create new text to dencrypt under format uint32_t ***/
							for(uint8_t l=0; l<8; l++){
								block_buffer_st_format[l] = block_buffer[l*4] * 0x1000000 + block_buffer[(l*4)+1] * 0x10000 + block_buffer[(l*4)+2] * 0x100 + block_buffer[(l*4)+3];
							}

							HAL_CRYP_Decrypt(&hcryp, (uint32_t *) block_buffer_st_format, 8, (uint32_t *) pwd_sha256_st_format, HAL_MAX_DELAY);

							pos=0;
							for(uint8_t d=0; d<8; d++)
							{
								pwd_sha256[pos] = (uint8_t) (pwd_sha256_st_format[d] / 0x1000000);
								pwd_sha256[pos+1] = (uint8_t) (pwd_sha256_st_format[d] / 0x10000);
								pwd_sha256[pos+2] = (uint8_t) (pwd_sha256_st_format[d] / 0x100);
								pwd_sha256[pos+3] = (uint8_t) (pwd_sha256_st_format[d]);
								pos+=4;
							}

							/*** AES-256 peripheral configuration (password 2) + AES-256 Decrypt 2 ***/
							configAESPeripheral_v2(pwd_sha256, iv_aes_gcm);

							/*** Create new text to dencrypt under format uint32_t ***/
							for(uint8_t e=0; e<SIZE_CRYPT_MSG; e++){
								cuvex.nfc.tag.new_text_to_decrypt[e] = cuvex.nfc.tag.cryptogram[e*4] * 0x1000000 + cuvex.nfc.tag.cryptogram[(e*4)+1] * 0x10000 + cuvex.nfc.tag.cryptogram[(e*4)+2] * 0x100 + cuvex.nfc.tag.cryptogram[(e*4)+3];
							}

							HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.new_text_to_decrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_text_decrypted, HAL_MAX_DELAY);

							pos=0;
							for(uint8_t f=0; f<SIZE_CRYPT_MSG; f++)
							{
								decrypted_text_aux[pos]   = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[f] / 0x1000000);
								decrypted_text_aux[pos+1] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[f] / 0x10000);
								decrypted_text_aux[pos+2] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[f] / 0x100);
								decrypted_text_aux[pos+3] = (uint8_t) (cuvex.nfc.tag.new_text_decrypted[f]);
								pos+=4;
							}

							memset(decrypted_text, 0, SIZE_CRYPT);
							memcpy(decrypted_text, decrypted_text_aux, SIZE_CRYPT);
						}
						else
						{
							/*** AES-256 peripheral configuration (initialization vector + header) ***/
							memset(header_aes_gcm, 0x00, sizeof(header_aes_gcm));

							/*** AES-256 peripheral configuration (password 1) + AES-256 Decrypt 1 ***/
							configAESPeripheral(pwd_combined_sha256, iv_aes_gcm, header_aes_gcm, 0);
							HAL_CRYP_Decrypt(&hcryp, (uint32_t *) block_buffer, 32/4, (uint32_t *) pwd_sha256, HAL_MAX_DELAY);

							/*** AES-256 peripheral configuration (password 2) + AES-256 Decrypt 2 ***/
							configAESPeripheral(pwd_sha256, iv_aes_gcm, header_aes_gcm, 0);
							HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.cryptogram, SIZE_CRYPT_MSG, (uint32_t *) decrypted_text, HAL_MAX_DELAY);
						}

						/*** Check if text is decrypted correctly ***/
						pwd_ok = checkDecryptedText(decrypted_text);

						if(pwd_ok == 1){
							break;
						}
					}

					c[z] = c[z] + 1;
					z = 0;
				}
				else{
					c[z] = 0;
					z++;
				}
			}
		}
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
bool decrypt_tag::checkDecryptedText(uint8_t  decrypted_text[SIZE_CRYPT])
{
	if(strstr((const char *) decrypted_text, "[bip39]") != NULL){
		return true;
	}
	else if (strstr((const char *) decrypted_text, "[slip39]") != NULL){
		return true;
	}
	else if (strstr((const char *) decrypted_text, "[xmr]") != NULL){
		return true;
	}
	else if (strstr((const char *) decrypted_text, "[plain-text]") != NULL){
		return true;
	}
	else if (strstr((const char *) decrypted_text, "{plain-text}") != NULL){
		return true;
	}
	else if (strstr((const char *) decrypted_text, "{bip39}") != NULL){
		return true;
	}
	else{
		return false;
	}
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::processingSecret(void)
{
	/*** Decryption of secret (seeds, plaintext) ***/
	if(cuvex.nfc.tag.multisigned_total != cuvex.nfc.tag.multisigned_mandatory){
		decryptSecretWithCombinations(cuvex.decrypt.cryptogram_decrypted);
	}
	else{
		decryptSecret(cuvex.decrypt.cryptogram_decrypted);
	}

	/*** Callback with password result ***/
	if(passwordResultCallback && passwordResultCallback->isValid())
	{
		if(pwd_ok == false){
			if(cuvex.info.errors == 0){
				typePassword.setVisible(false);
				passwordError1.setVisible(true);
				passwordError2.setVisible(false);
			}
			else{
				typePassword.setVisible(false);
				passwordError1.setVisible(false);
				passwordError2.setVisible(true);
			}
		}

		passwordResultCallback->execute(pwd_ok);	//Send password result and execute callback
	}
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void decrypt_tag::sortPasswordsLexicographically(uint8_t pwds[10][32], uint8_t num_pwd)
{
	uint8_t tmp[32] = {0};

	for(int i=0; i<num_pwd-1; i++)
	{
		for(int j=i+1; j<num_pwd; j++)
		{
			if(memcmp(pwds[i], pwds[j], 32) > 0)
			{
				memcpy(tmp, pwds[i], 32);
				memcpy(pwds[i], pwds[j], 32);
				memcpy(pwds[j], tmp, 32);
			}
		}
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
uint8_t decrypt_tag::getRNG16Bytes(uint8_t *buffer)
{
	uint32_t random32 = 0x00;

	for(int i=0; i<4; i++)
	{
		if(HAL_RNG_GenerateRandomNumber(&hrng, &random32) != HAL_OK){
			return ERROR;
		}

		buffer[i*4 + 0] = (uint8_t) (random32 >> 24);
		buffer[i*4 + 1] = (uint8_t) (random32 >> 16);
		buffer[i*4 + 2] = (uint8_t) (random32 >> 8);
		buffer[i*4 + 3] = (uint8_t) (random32);
	}

	return SUCCESS;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
static uint8_t sha256_hw(const uint8_t *data, size_t len, uint8_t out[32])
{
	if(HAL_HASHEx_SHA256_Start(&hhash, (uint8_t *) data, len, out, HAL_MAX_DELAY) != HAL_OK){
		return ERROR;
	}

	return SUCCESS;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
static uint8_t hmac_sha256_init(hmac_sha256_ctx_t *ctx, const uint8_t *key, size_t key_len)
{
	uint8_t key_block[64] = {0};

	/*** Key normalization ***/
	if(key_len > 64){
		if(sha256_hw(key, key_len, key_block) != SUCCESS){
			return ERROR;
		}
	}
	else{
		memcpy(key_block, key, key_len);
	}

	/*** Precompute ipad/opad ***/
	for(int i=0; i<64; i++){
		ctx->ipad[i] = key_block[i] ^ 0x36;
		ctx->opad[i] = key_block[i] ^ 0x5C;
	}

	return SUCCESS;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
static uint8_t hmac_sha256_fast(const hmac_sha256_ctx_t *ctx, const uint8_t *data, size_t data_len, uint8_t out[32])
{
	uint8_t inner_hash[32];
	uint8_t inner_buf[64 + data_len];
	uint8_t outer_buf[64 + 32];

	/*** inner = SHA256(ipad || data) ***/
	memcpy(inner_buf, ctx->ipad, 64);
	memcpy(inner_buf + 64, data, data_len);

	if(sha256_hw(inner_buf, sizeof(inner_buf), inner_hash) != SUCCESS){
		return ERROR;
	}

	/*** outer = SHA256(opad || inner_hash) ***/
	memcpy(outer_buf, ctx->opad, 64);
	memcpy(outer_buf + 64, inner_hash, 32);

	return sha256_hw(outer_buf, sizeof(outer_buf), out);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
uint8_t decrypt_tag::pbkdf2_sha256(const uint8_t *password, size_t pass_len, const uint8_t *salt, size_t salt_len, uint32_t iterations, uint8_t *derived_key, size_t dk_len)
{
	hmac_sha256_ctx_t hmac_ctx;
	uint8_t U[32], T[32];
	uint8_t salt_block[salt_len + 4];
	uint32_t block_index = 1;

	/*** Init HMAC context ***/
	if(hmac_sha256_init(&hmac_ctx, password, pass_len) != SUCCESS){
		return ERROR;
	}

	memcpy(salt_block, salt, salt_len);

	while(dk_len > 0)
	{
		/***salt || INT(block_index) (big-endian) ***/
		salt_block[salt_len + 0] = (block_index >> 24) & 0xFF;
		salt_block[salt_len + 1] = (block_index >> 16) & 0xFF;
		salt_block[salt_len + 2] = (block_index >> 8) & 0xFF;
		salt_block[salt_len + 3] = block_index & 0xFF;

		/*** U1 ***/
		if(hmac_sha256_fast(&hmac_ctx, salt_block, sizeof(salt_block), U) != SUCCESS){
			return ERROR;
		}

		memcpy(T, U, 32);

		/*** U2 .. Uc ***/
		for(uint32_t i=1; i<iterations; i++){
			if(hmac_sha256_fast(&hmac_ctx, U, 32, U) != SUCCESS){
				return ERROR;
			}

			for(int j=0; j<32; j++){
				T[j] ^= U[j];
			}
		}

		/*** Copy block to output ***/
		size_t copy_len = (dk_len > 32) ? 32 : dk_len;

		memcpy(derived_key, T, copy_len);

		derived_key += copy_len;
		dk_len -= copy_len;
		block_index++;
	}

	return SUCCESS;
}




