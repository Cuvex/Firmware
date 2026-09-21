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

#include <gui/screen_flow_encrypt_part_2_screen/screen_flow_encrypt_part_2View.hpp>
#include "main.h"

extern struct cuvex cuvex;
extern HASH_HandleTypeDef hhash;
extern CRYP_HandleTypeDef hcryp;

screen_flow_encrypt_part_2View::screen_flow_encrypt_part_2View(): actual_pwd(0), total_pwds(1), mandatory_pwds(1), pwds{0}, pwd_raw{0}, pwd_sha256{0}, pwd_combined_sha256{0}, iv_aes_gcm{0}
{

}

void screen_flow_encrypt_part_2View::setupScreen()
{
	screen_flow_encrypt_part_2ViewBase::setupScreen();
	screen_flow_encrypt_part_2View::setScreenMode();
	screen_flow_encrypt_part_2View::setScreenLanguage();
	screen_flow_encrypt_part_2View::changeScreen(GUI_TO_MAIN_SCREEN_FLOW_ENCRYPT);

	memset(keyboard1_text_typed_passwordBuffer, 	0x00, sizeof(keyboard1_text_typed_passwordBuffer));
	memset(keyboard2_text_typed_passwordBuffer, 	0x00, sizeof(keyboard2_text_typed_passwordBuffer));
	memset(keyboard_text_typed_aliasBuffer, 	 	0x00, sizeof(keyboard_text_typed_aliasBuffer));
	keyboard1_password.clearBuffer();
	keyboard2_password.clearBuffer();
	keyboard_alias.clearBuffer();

	if(cuvex.wallet.flag_new == true){
		cuvex.encrypt.text_type = TEXT_TYPE_FROM_WALLET_BIP39;
	}
}

void screen_flow_encrypt_part_2View::tearDownScreen()
{
	screen_flow_encrypt_part_2ViewBase::tearDownScreen();
	screen_flow_encrypt_part_2View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
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
void screen_flow_encrypt_part_2View::tickEventScreen()
{
	/*** Password - Keyboard 1 (password field 1) ***/
	if(keyboard1_password.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard1_text_typed_passwordBuffer, keyboard1_password.getBuffer(), KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE) != 0)
		{
			/*** Obtaining typed text in widget ***/
			Unicode::snprintf(keyboard1_text_typed_passwordBuffer, KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE, keyboard1_password.getBuffer());
			keyboard1_text_typed_password.setWideTextAction(touchgfx::WIDE_TEXT_NONE);

			/*** Text alignment within area ***/
			if(keyboard1_text_typed_password.getTextWidth() <= 160){
				keyboard1_text_typed_password.setPosition(160-(keyboard1_text_typed_password.getTextWidth()/2), 40, keyboard1_text_typed_password.getTextWidth(), 20);
			}
			else{
				keyboard1_text_typed_password.setPosition(76, 40, 160, 20);
			}

			/*** Reset and filling of buffer with hidden password ***/
			for(int i=0; i<KEYBOARD1_TEXT_TYPED_HIDE_PASSWORD_SIZE; i++){
				keyboard1_text_typed_hide_passwordBuffer[i] = 0x00;
			}
			for(int i=0; i<Unicode::strlen(keyboard1_text_typed_passwordBuffer); i++){
				keyboard1_text_typed_hide_passwordBuffer[i] = 8226;	//U+8226 (bullet '•')
			}

			/*** Placeholder status (visible or hidden) ***/
			if(keyboard1_text_typed_passwordBuffer[0] == 0x00){
				placeholder_1_password.setVisible(true);
			}
			else{
				placeholder_1_password.setVisible(false);
			}

			/*** Color of text with password instruction information ***/
			if(cuvex.info.mode == DARK){
				text_info_2_password.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
			}
			else{
				text_info_2_password.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
			}

			/*** Area update ***/
			keyboard1_text_area_password.invalidate();
			text_info_2_password.invalidate();
		}
	}

	/*** Password - Keyboard 2 (password field 2) ***/
	if(keyboard2_password.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard2_text_typed_passwordBuffer, keyboard2_password.getBuffer(), KEYBOARD2_TEXT_TYPED_PASSWORD_SIZE) != 0)
		{
			/*** Obtaining typed text in widget ***/
			Unicode::snprintf(keyboard2_text_typed_passwordBuffer, KEYBOARD2_TEXT_TYPED_PASSWORD_SIZE, keyboard2_password.getBuffer());
			keyboard2_text_typed_password.setWideTextAction(touchgfx::WIDE_TEXT_NONE);

			/*** Text alignment within area ***/
			if(keyboard2_text_typed_password.getTextWidth() <= 160){
				keyboard2_text_typed_password.setPosition(160-(keyboard2_text_typed_password.getTextWidth()/2), 75, keyboard2_text_typed_password.getTextWidth(), 20);
			}
			else{
				keyboard2_text_typed_password.setPosition(76, 75, 160, 20);
			}

			/*** Reset and filling of buffer with hidden password ***/
			for(int i=0; i<KEYBOARD2_TEXT_TYPED_HIDE_PASSWORD_SIZE; i++){
				keyboard2_text_typed_hide_passwordBuffer[i] = 0x00;
			}
			for(int i=0; i<Unicode::strlen(keyboard2_text_typed_passwordBuffer); i++){
				keyboard2_text_typed_hide_passwordBuffer[i] = 8226;	//U+8226 (bullet '•')
			}

			/*** Placeholder status (visible or hidden) ***/
			if(keyboard2_text_typed_passwordBuffer[0] == 0x00){
				placeholder_2_password.setVisible(true);
			}
			else{
				placeholder_2_password.setVisible(false);
			}

			/*** Color of text with password instruction information ***/
			if(cuvex.info.mode == DARK){
				text_info_2_password.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
			}
			else{
				text_info_2_password.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
			}

			/*** Area update ***/
			keyboard2_text_area_password.invalidate();
			text_info_2_password.invalidate();
		}
	}

	/*** Alias - Keyboard (card alias) ***/
	if(keyboard_alias.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard_text_typed_aliasBuffer, keyboard_alias.getBuffer(), KEYBOARD_TEXT_TYPED_ALIAS_SIZE) != 0)
		{
			Unicode::snprintf(keyboard_text_typed_aliasBuffer, KEYBOARD_TEXT_TYPED_ALIAS_SIZE, keyboard_alias.getBuffer());
			keyboard_text_typed_alias.setWideTextAction(touchgfx::WIDE_TEXT_NONE);

			if(keyboard_text_typed_alias.getTextWidth() <= 160){
				keyboard_text_typed_alias.setPosition(160-(keyboard_text_typed_alias.getTextWidth()/2), 75, keyboard_text_typed_alias.getTextWidth(), 20);
			}
			else{
				keyboard_text_typed_alias.setPosition(76, 75, 160, 20);
			}

			keyboard_text_area_alias.invalidate();
		}
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
void screen_flow_encrypt_part_2View::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::changeStateNfc(uint8_t state)
{
	presenter->changeStateNfc(state);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::updateStateNfc(uint16_t state)
{
	switch(state)
	{
	case MAIN_TO_GUI_NFC_ERROR:
	default:
		application().gotoscreen_menuScreenNoTransition();
		break;

	case MAIN_TO_GUI_NFC_INITIALIZED:
		if(s5_initNFC.isVisible())
		{
			s5_initNFC.setVisible(false);
			s6_waitReadWriteNFC.setVisible(true);

			if(cuvex.encrypt.text_type == TEXT_TYPE_FROM_NFC_BIP39){
				wait_read_write_nfc_text.setTypedText(touchgfx::TypedText(T_SE_S6_WAIT_READ_NFC_FROMNFC_TEXT));
			}

			if(total_pwds != mandatory_pwds){
				screen_flow_encrypt_part_2View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_ENCRYPT_T4T_8K);
			}
			else{
				screen_flow_encrypt_part_2View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_ENCRYPT);
			}
		}
		break;

	case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_ENCRYPT:
	case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_ENCRYPT_T4T_8K:
		if(s6_waitReadWriteNFC.isVisible())
		{
			if((state == MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_ENCRYPT_T4T_8K) && (cuvex.nfc.tag.type != NFC_TAG_TYPE_T4T_8K))	//Error 1, the card being written has not correct format
			{
				s6_waitReadWriteNFC.setVisible(false);
				s7_writeError.setVisible(true);
				text_error_cryptogram.setVisible(false);
				text_error_tag_format.setVisible(true);
				image_error.setVisible(true);
				screen_flow_encrypt_part_2View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
			}
			else if(cuvex.nfc.tag.encripted == true)		//Error 2, the card being written to already has a stored cryptogram
			{
				s6_waitReadWriteNFC.setVisible(false);
				s7_writeError.setVisible(true);
				text_error_cryptogram.setVisible(true);
				text_error_tag_format.setVisible(false);
				image_error.setVisible(false);
				screen_flow_encrypt_part_2View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
			}
			else	//Success, card successfully written
			{
				for(int i=0; i<TEXT_CRYPTOGRAM_SUCCESS_ENGLISH_6_SIZE; i++)
				{
					if(cuvex.nfc.tag.alias[i] == 182){	//If '¶' (182) is converted to the character '€' (8364) for display on screen
						text_cryptogram_success_english_6Buffer[i] = 8364;
						text_cryptogram_success_spanish_5Buffer[i] = 8364;
					}
					else{
						text_cryptogram_success_english_6Buffer[i] = cuvex.nfc.tag.alias[i];
						text_cryptogram_success_spanish_5Buffer[i] = cuvex.nfc.tag.alias[i];
					}
				}

				if(cuvex.info.language == SPANISH){
					text_cryptogram_success_spanish.setVisible(true);
					text_cryptogram_success_english.setVisible(false);
				}
				else{
					text_cryptogram_success_spanish.setVisible(false);
					text_cryptogram_success_english.setVisible(true);
				}

				close_button.setVisible(false);
				s6_waitReadWriteNFC.setVisible(false);
				s8_writeSuccess.setVisible(true);
				screen_flow_encrypt_part_2View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
			}
		}
		break;
	}

	/*** Screen update ***/
	background.invalidate();
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
void screen_flow_encrypt_part_2View::hideKeyboardPasswordPressed()
{
	text_info_1_password.setPosition(0, 60, 320, 20);
	text_info_2_password.setPosition(0, 152, 320, 13);
	keyboard1_text_typed_hide_password.setPosition(76, 90, 160, 20);
	keyboard2_text_typed_hide_password.setPosition(76, 125, 160, 20);
	keyboard1_text_area_password.setXY(45, 85);
	keyboard2_text_area_password.setXY(45, 120);
	keyboard1_text_area_selected_password.setXY(45, 85);
	keyboard2_text_area_selected_password.setXY(45, 120);
	keyboard1_pwd_eye_password.setXY(245, 85);
	keyboard2_pwd_eye_password.setXY(245, 120);
	keyboard1_btn_show_password.setPosition(76, 85, 169, 30);
	keyboard2_btn_show_password.setPosition(76, 120, 169, 30);
	placeholder_1_password.setPosition(62, 90, 180, 20);
	placeholder_2_password.setPosition(62, 125, 180, 20);

	if(keyboard1_text_typed_password.getTextWidth() <= 160){
		keyboard1_text_typed_password.setPosition(160-(keyboard1_text_typed_password.getTextWidth()/2), 90, keyboard1_text_typed_password.getTextWidth(), 20);
	}
	else{
		keyboard1_text_typed_password.setPosition(76, 90, 160, 20);
	}

	if(keyboard2_text_typed_password.getTextWidth() <= 160){
		keyboard2_text_typed_password.setPosition(160-(keyboard2_text_typed_password.getTextWidth()/2), 125, keyboard2_text_typed_password.getTextWidth(), 20);
	}
	else{
		keyboard2_text_typed_password.setPosition(76, 125, 160, 20);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard1_password.setVisible(false);
	keyboard1_btn_show_password.setVisible(true);
	keyboard1_text_area_selected_password.setVisible(false);
	keyboard2_password.setVisible(false);
	keyboard2_btn_show_password.setVisible(true);
	keyboard2_text_area_selected_password.setVisible(false);
	keyboard_btn_hide_password.setVisible(false);
	keyboard_btn_enter_password.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::show1KeyboardPasswordPressed()
{
	text_info_1_password.setPosition(0, 10, 320, 20);
	text_info_2_password.setPosition(0, 102, 320, 13);
	keyboard1_text_typed_hide_password.setPosition(76, 40, 160, 20);
	keyboard2_text_typed_hide_password.setPosition(76, 75, 160, 20);
	keyboard1_text_area_password.setXY(45, 35);
	keyboard2_text_area_password.setXY(45, 70);
	keyboard1_text_area_selected_password.setXY(45, 35);
	keyboard2_text_area_selected_password.setXY(45, 70);
	keyboard1_pwd_eye_password.setXY(245, 35);
	keyboard2_pwd_eye_password.setXY(245, 70);
	keyboard1_btn_show_password.setPosition(76, 35, 169, 30);
	keyboard2_btn_show_password.setPosition(76, 70, 169, 30);
	placeholder_1_password.setPosition(62, 40, 180, 20);
	placeholder_2_password.setPosition(62, 75, 180, 20);

	if(keyboard1_text_typed_password.getTextWidth() <= 160){
		keyboard1_text_typed_password.setPosition(160-(keyboard1_text_typed_password.getTextWidth()/2), 40, keyboard1_text_typed_password.getTextWidth(), 20);
	}
	else{
		keyboard1_text_typed_password.setPosition(76, 40, 160, 20);
	}

	if(keyboard2_text_typed_password.getTextWidth() <= 160){
		keyboard2_text_typed_password.setPosition(160-(keyboard2_text_typed_password.getTextWidth()/2), 75, keyboard2_text_typed_password.getTextWidth(), 20);
	}
	else{
		keyboard2_text_typed_password.setPosition(76, 75, 160, 20);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard1_password.setVisible(true);
	keyboard1_btn_show_password.setVisible(false);
	keyboard1_text_area_selected_password.setVisible(true);
	keyboard2_password.setVisible(false);
	keyboard2_btn_show_password.setVisible(true);
	keyboard2_text_area_selected_password.setVisible(false);
	keyboard_btn_hide_password.setVisible(true);
	keyboard_btn_enter_password.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::show2KeyboardPasswordPressed()
{
	text_info_1_password.setPosition(0, 10, 320, 20);
	text_info_2_password.setPosition(0, 102, 320, 13);
	keyboard1_text_typed_hide_password.setPosition(76, 40, 160, 20);
	keyboard2_text_typed_hide_password.setPosition(76, 75, 160, 20);
	keyboard1_text_area_password.setXY(45, 35);
	keyboard2_text_area_password.setXY(45, 70);
	keyboard1_text_area_selected_password.setXY(45, 35);
	keyboard2_text_area_selected_password.setXY(45, 70);
	keyboard1_pwd_eye_password.setXY(245, 35);
	keyboard2_pwd_eye_password.setXY(245, 70);
	keyboard1_btn_show_password.setPosition(76, 35, 169, 30);
	keyboard2_btn_show_password.setPosition(76, 70, 169, 30);
	placeholder_1_password.setPosition(62, 40, 180, 20);
	placeholder_2_password.setPosition(62, 75, 180, 20);

	if(keyboard1_text_typed_password.getTextWidth() <= 160){
		keyboard1_text_typed_password.setPosition(160-(keyboard1_text_typed_password.getTextWidth()/2), 40, keyboard1_text_typed_password.getTextWidth(), 20);
	}
	else{
		keyboard1_text_typed_password.setPosition(76, 40, 160, 20);
	}

	if(keyboard2_text_typed_password.getTextWidth() <= 160){
		keyboard2_text_typed_password.setPosition(160-(keyboard2_text_typed_password.getTextWidth()/2), 75, keyboard2_text_typed_password.getTextWidth(), 20);
	}
	else{
		keyboard2_text_typed_password.setPosition(76, 75, 160, 20);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard1_password.setVisible(false);
	keyboard1_btn_show_password.setVisible(true);
	keyboard1_text_area_selected_password.setVisible(false);
	keyboard2_password.setVisible(true);
	keyboard2_btn_show_password.setVisible(false);
	keyboard2_text_area_selected_password.setVisible(true);
	keyboard_btn_hide_password.setVisible(true);
	keyboard_btn_enter_password.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::enterKeyboardPasswordPressed()
{
	bool flag_upercase = false, flag_lowercase = false, flag_simbol = false, flag_number = false;
	bool flag_passwords_ok = false;

	/*** Checking that typed texts meet the conditions (minimum 12 characters, uppercase, lowercase, numbers, and symbols) ***/
	if((Unicode::strlen(keyboard1_text_typed_passwordBuffer) >= 12) && (Unicode::strlen(keyboard2_text_typed_passwordBuffer) >= 12))
	{
		if(Unicode::strncmp(keyboard1_text_typed_passwordBuffer, keyboard2_text_typed_passwordBuffer, KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE) == 0)
		{
			for(int i=0; i<KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE; i++)
			{
				if((keyboard1_text_typed_passwordBuffer[i] >= 32) && (keyboard1_text_typed_passwordBuffer[i] <= 47)){			//Symbol (Unicode: 32-47)
					flag_simbol = true;
				}
				else if((keyboard1_text_typed_passwordBuffer[i] >= 48) && (keyboard1_text_typed_passwordBuffer[i] <= 57)){		//Number (Unicode: 48-57)
					flag_number = true;
				}
				else if((keyboard1_text_typed_passwordBuffer[i] >= 58) && (keyboard1_text_typed_passwordBuffer[i] <= 64)){		//Symbol (Unicode: 58-64)
					flag_simbol = true;
				}
				else if((keyboard1_text_typed_passwordBuffer[i] >= 65) && (keyboard1_text_typed_passwordBuffer[i] <= 90)){		//Uppercase (Unicode: 65-90)
					flag_upercase = true;
				}
				else if((keyboard1_text_typed_passwordBuffer[i] >= 91) && (keyboard1_text_typed_passwordBuffer[i] <= 96)){		//Symbol (Unicode: 91-96)
					flag_simbol = true;
				}
				else if((keyboard1_text_typed_passwordBuffer[i] >= 97) && (keyboard1_text_typed_passwordBuffer[i] <= 122)){		//Lowercase (Unicode: 97-122)
					flag_lowercase = true;
				}
				else if((keyboard1_text_typed_passwordBuffer[i] >= 123) && (keyboard1_text_typed_passwordBuffer[i] <= 126)){	//Symbol (Unicode: 123-126)
					flag_simbol = true;
				}
				else if((keyboard1_text_typed_passwordBuffer[i] >= 160) && (keyboard1_text_typed_passwordBuffer[i] <= 191)){	//Symbol (Unicode: 160-191)
					flag_simbol = true;
				}
				else if(keyboard1_text_typed_passwordBuffer[i] == 8364){	//Symbol '€' (Unicode: 8364)
					flag_simbol = true;
				}
			}

			if((flag_upercase == true) && (flag_lowercase == true) && (flag_number == true) && (flag_simbol == true))	//Passwords contain "uppercase", "lowercase", "numbers", and "symbols"
			{
				flag_passwords_ok = true;
			}
		}
	}

	/*** If both passwords meet the conditions ***/
	if(flag_passwords_ok == true)
	{
		/*** Obtaining the typed text (password) ***/
		memset(pwds[actual_pwd], 0x00, KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE);

		for(int i=0; i<KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE; i++)
		{
			if(keyboard1_text_typed_passwordBuffer[i] == 8364){	//If '€' (8364) is converted to the character '¶' (182) to only occupy 1 byte
				pwds[actual_pwd][i] = 182;
			}
			else{
				pwds[actual_pwd][i] = (uint8_t) keyboard1_text_typed_passwordBuffer[i];
			}
		}

		/*** Selection of texts to display in the field of correct password information (based on language and number of signers) ***/
		if(cuvex.info.language == SPANISH)
		{
			if(total_pwds > 1)
			{
				Unicode::snprintf(text_pwd_success_infoBuffer, TEXT_PWD_SUCCESS_INFO_SIZE, " %d", actual_pwd+1);

				if(total_pwds != actual_pwd+1){
					Unicode::snprintf(btn_pwd_successBuffer, BTN_PWD_SUCCESS_SIZE, "CONTINUAR");
				}
				else{
					Unicode::snprintf(btn_pwd_successBuffer, BTN_PWD_SUCCESS_SIZE, "GRABAR CRIPTOGRAMA");
				}
			}
		}
		else
		{
			if(total_pwds > 1)
			{
				Unicode::snprintf(text_pwd_success_infoBuffer, TEXT_PWD_SUCCESS_INFO_SIZE, " %d", actual_pwd+1);

				if(total_pwds != actual_pwd+1){
					Unicode::snprintf(btn_pwd_successBuffer, BTN_PWD_SUCCESS_SIZE, "CONTINUE");
				}
				else{
					Unicode::snprintf(btn_pwd_successBuffer, BTN_PWD_SUCCESS_SIZE, "RECORD CRYPTOGRAM");
				}
			}
		}

		/*** Clearing keyboard and display buffers ***/
		memset(keyboard1_text_typed_passwordBuffer, 0x00, sizeof(keyboard1_text_typed_passwordBuffer));
		memset(keyboard2_text_typed_passwordBuffer, 0x00, sizeof(keyboard2_text_typed_passwordBuffer));
		memset(keyboard1_text_typed_hide_passwordBuffer, 0x00, sizeof(keyboard1_text_typed_hide_passwordBuffer));
		memset(keyboard2_text_typed_hide_passwordBuffer, 0x00, sizeof(keyboard2_text_typed_hide_passwordBuffer));
		keyboard1_password.clearBuffer();
		keyboard2_password.clearBuffer();

		/*** Selecting visible/hidden elements on the screen ***/
		s3_1_typePasword.setVisible(false);
		s3_2_successPassword.setVisible(true);

		if(cuvex.info.mode == DARK){
			text_info_2_password.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		}
		else{
			text_info_2_password.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		}
	}
	else
	{
		text_info_2_password.setColor(touchgfx::Color::getColorFromRGB(0xE7,0x44,0x3E));
	}

	/*** Screen update ***/
	background.invalidate();
}

/*
 *
 *
 *
 */

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::hideKeyboardAliasPressed()
{
	keyboard_text_info_1_alias.setPosition(0, 70, 320, 20);
	keyboard_text_info_2_alias.setPosition(0, 90, 320, 20);
	keyboard_text_area_alias.setXY(45, 120);
	keyboard_btn_enter_alias.setPosition(245, 120, 30, 30);

	if(keyboard_text_typed_alias.getTextWidth() <= 160){
		keyboard_text_typed_alias.setPosition(160-(keyboard_text_typed_alias.getTextWidth()/2), 125, keyboard_text_typed_alias.getTextWidth(), 20);
	}
	else{
		keyboard_text_typed_alias.setPosition(76, 125, 160, 20);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard_alias.setVisible(false);
	keyboard_btn_hide_alias.setVisible(false);
	keyboard_btn_show_alias.setVisible(true);
	keyboard_btn_enter_alias.setVisible(true);
	btn_assign_alias.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::showKeyboardAliasPressed()
{
	keyboard_text_info_1_alias.setPosition(0, 20, 320, 20);
	keyboard_text_info_2_alias.setPosition(0, 40, 320, 20);
	keyboard_text_area_alias.setXY(45, 70);
	keyboard_btn_enter_alias.setPosition(245, 70, 30, 30);

	if(keyboard_text_typed_alias.getTextWidth() <= 160){
		keyboard_text_typed_alias.setPosition(160-(keyboard_text_typed_alias.getTextWidth()/2), 75, keyboard_text_typed_alias.getTextWidth(), 20);
	}
	else{
		keyboard_text_typed_alias.setPosition(76, 75, 160, 20);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard_alias.setVisible(true);
	keyboard_btn_hide_alias.setVisible(true);
	keyboard_btn_show_alias.setVisible(false);
	keyboard_btn_enter_alias.setVisible(true);
	btn_assign_alias.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::enterKeyboardAliasPressed()
{
	if(keyboard_text_typed_aliasBuffer[0] != 0x00)
	{
		/*** Generation of the records data ***/
		screen_flow_encrypt_part_2View::generateRecordData1_Alias();
		screen_flow_encrypt_part_2View::generateRecordData2_Cryptogram();
		screen_flow_encrypt_part_2View::generateRecordData3_Information();

		if(total_pwds != mandatory_pwds){
			screen_flow_encrypt_part_2View::generateRecordData4_Multisignature();
		}

		/*** Clearing keyboard and display buffers ***/
		memset(keyboard_text_typed_aliasBuffer, 0x00, sizeof(keyboard_text_typed_aliasBuffer));
		keyboard_alias.clearBuffer();

		/*** Enabling NFC to allow reading/writing ***/
		screen_flow_encrypt_part_2View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);

		/*** Selecting visible/hidden elements on the screen ***/
		s4_alias.setVisible(false);
		s5_initNFC.setVisible(true);

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
void screen_flow_encrypt_part_2View::successPressed()
{
	NVIC_SystemReset();
}

/*
 *
 *
 *
 */

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::eye1Pressed()
{
	if(keyboard1_pwd_eye_password.getCurrentlyDisplayedBitmap() == BITMAP_OJO_ABIERTO_ID){
		keyboard1_text_typed_password.setVisible(true);
		keyboard1_text_typed_hide_password.setVisible(false);
	}
	else{
		keyboard1_text_typed_password.setVisible(false);
		keyboard1_text_typed_hide_password.setVisible(true);
	}

	keyboard1_text_area_password.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::eye2Pressed()
{
	if(keyboard2_pwd_eye_password.getCurrentlyDisplayedBitmap() == BITMAP_OJO_ABIERTO_ID){
		keyboard2_text_typed_password.setVisible(true);
		keyboard2_text_typed_hide_password.setVisible(false);
	}
	else{
		keyboard2_text_typed_password.setVisible(false);
		keyboard2_text_typed_hide_password.setVisible(true);
	}

	keyboard2_text_area_password.invalidate();
}

/*
 *
 *
 *
 */

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::retryPressed()
{
	/*** Enabling NFC to allow reading/writing ***/
	screen_flow_encrypt_part_2View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);

	/*** Selecting visible/hidden elements on the screen ***/
	s7_writeError.setVisible(false);
	s5_initNFC.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/*
 *
 *
 *
 */

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::passwordSuccessPressed()
{
	actual_pwd++;

	if(actual_pwd != total_pwds)
	{
		/*** Selection of texts to display in the information fields ***/
		Unicode::UnicodeChar degree[] = {0x00B0,0};

		if(cuvex.info.language == SPANISH){
			if(total_pwds > 1){
				Unicode::snprintf(text_info_1_passwordBuffer, TEXT_INFO_1_PASSWORD_SIZE, "Persona N%s%d", degree, actual_pwd+1);
			}
			else{
				Unicode::snprintf(text_info_1_passwordBuffer, TEXT_INFO_1_PASSWORD_SIZE, "Password para cifrar.");
			}
		}
		else{
			if(total_pwds > 1){
				Unicode::snprintf(text_info_1_passwordBuffer, TEXT_INFO_1_PASSWORD_SIZE, "Person N%s%d", degree, actual_pwd+1);
			}
			else{
				Unicode::snprintf(text_info_1_passwordBuffer, TEXT_INFO_1_PASSWORD_SIZE, "Password to encrypt.");
			}
		}

		/*** Selecting visible/hidden elements on the screen ***/
		s3_1_typePasword.setVisible(true);
		s3_2_successPassword.setVisible(false);
		placeholder_1_password.setVisible(true);
		placeholder_2_password.setVisible(true);
	}
	else
	{
		/*** Selecting visible/hidden elements on the screen ***/
		s3_password.setVisible(false);
		s4_alias.setVisible(true);
	}

	/*** Screen update ***/
	background.invalidate();
}

/*
 *
 *
 *
 */

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::multisignedYesPressed()
{
	/*** Selecting visible/hidden elements on the screen ***/
	s2_1_askMultiSignature.setVisible(false);
	s2_2_numMultiSignature.setVisible(true);
	text_info_multi_2.setVisible(true);
	text_info_multi_3.setVisible(false);
	text_info_multi_4.setVisible(false);
	text_info_multi_5.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::multisignedNoPressed()
{
	/*** Selecting visible/hidden elements on the screen ***/
	s2_multiSignature.setVisible(false);
	s3_password.setVisible(true);
	s3_1_typePasword.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::multisignedPlusPressed()
{
	Unicode::UnicodeChar aux_str[5] = {0};

	/*** Update of the number of passwords ***/
	if((text_info_multi_2.isVisible() == true) && (text_info_multi_3.isVisible() == false))
	{
		if(total_pwds < 6){
			Unicode::itoa(++total_pwds, aux_str, 5, 10);
			Unicode::snprintf(text_multi_numBuffer, TEXT_MULTI_NUM_SIZE, aux_str);
		}
	}
	else
	{
		if(mandatory_pwds < total_pwds){
			Unicode::itoa(++mandatory_pwds, aux_str, 5, 10);
			Unicode::snprintf(text_multi_numBuffer, TEXT_MULTI_NUM_SIZE, aux_str);
		}

		if(mandatory_pwds == total_pwds){
			text_info_multi_4.setVisible(false);
			text_info_multi_5.setVisible(false);
		}
		else{
			text_info_multi_4.setVisible(true);
			text_info_multi_5.setVisible(true);
		}
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
void screen_flow_encrypt_part_2View::multisignedMinusPressed()
{
	Unicode::UnicodeChar aux_str[5] = {0};

	/*** Update of the number of passwords ***/
	if((text_info_multi_2.isVisible() == true) && (text_info_multi_3.isVisible() == false))
	{
		if(total_pwds > 1){
			Unicode::itoa(--total_pwds, aux_str, 5, 10);
			Unicode::snprintf(text_multi_numBuffer, TEXT_MULTI_NUM_SIZE, aux_str);
		}
	}
	else
	{
		if(mandatory_pwds > 1){
			Unicode::itoa(--mandatory_pwds, aux_str, 5, 10);
			Unicode::snprintf(text_multi_numBuffer, TEXT_MULTI_NUM_SIZE, aux_str);
		}

		if(mandatory_pwds == total_pwds){
			text_info_multi_4.setVisible(false);
			text_info_multi_5.setVisible(false);
		}
		else{
			text_info_multi_4.setVisible(true);
			text_info_multi_5.setVisible(true);
		}
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
void screen_flow_encrypt_part_2View::multisignedSelectPressed()
{
	Unicode::UnicodeChar degree[] = {0x00B0,0};

	/*** Selecting visible/hidden elements on the screen ***/
	if((total_pwds > 1) && (text_info_multi_2.isVisible() == true) && (text_info_multi_3.isVisible() == false))
	{
		mandatory_pwds = total_pwds;

		text_info_multi_2.setVisible(false);
		text_info_multi_3.setVisible(true);
		text_info_multi_4.setVisible(false);
		text_info_multi_5.setVisible(false);
	}
	else
	{
		if(cuvex.info.language == SPANISH){
			if(total_pwds > 1){
				Unicode::snprintf(text_info_1_passwordBuffer, TEXT_INFO_1_PASSWORD_SIZE, "Persona N%s%d", degree, actual_pwd+1);
			}
			else{
				Unicode::snprintf(text_info_1_passwordBuffer, TEXT_INFO_1_PASSWORD_SIZE, "Password para cifrar.");
			}
		}
		else{
			if(total_pwds > 1){
				Unicode::snprintf(text_info_1_passwordBuffer, TEXT_INFO_1_PASSWORD_SIZE, "Person N%s%d", degree, actual_pwd+1);
			}
			else{
				Unicode::snprintf(text_info_1_passwordBuffer, TEXT_INFO_1_PASSWORD_SIZE, "Password to encrypt.");
			}
		}

		s2_multiSignature.setVisible(false);
		s3_password.setVisible(true);
		s3_1_typePasword.setVisible(true);
	}

	/*** Screen update ***/
	background.invalidate();
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
void screen_flow_encrypt_part_2View::setScreenMode()
{
	/*** Setting screen elements based on mode (dark/light) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_multi_yes.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_multi_yes.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_multi_no.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_multi_no.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_multi_select.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_multi_select.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_info_multi_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_info_multi_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_info_multi_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_info_multi_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_info_multi_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_multi_num.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_multi_plus.setIconBitmaps(Bitmap(BITMAP_PLUS_DARK_ID), Bitmap(BITMAP_PLUS_DARK_ID));
		btn_multi_minus.setIconBitmaps(Bitmap(BITMAP_MINUS_DARK_ID), Bitmap(BITMAP_MINUS_DARK_ID));
		keyboard_btn_enter_password.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_btn_enter_password.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard1_text_typed_password.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard2_text_typed_password.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard1_text_typed_hide_password.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard2_text_typed_hide_password.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		text_info_1_password.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_info_2_password.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_pwd_success.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		text_pwd_success_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		init_nfc_text1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		init_nfc_text2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		wait_read_write_nfc_text.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_retry.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_retry.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_error_cryptogram.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_error_tag_format.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_assign_alias.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_assign_alias.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_text_info_1_alias.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_text_info_2_alias.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_success.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_success.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_spanish_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_spanish_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_spanish_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_spanish_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_spanish_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_english_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_english_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_english_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_english_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_english_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_english_6.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
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
void screen_flow_encrypt_part_2View::setScreenLanguage()
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

/*
 *
 *
 *
 */

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::generateRecordData1_Alias()
{
	memset(cuvex.nfc.tag.new_alias, 0x00, SIZE_ALIAS);

	for(int i=0; i<SIZE_ALIAS; i++)
	{
		if(keyboard_text_typed_aliasBuffer[i] == 8364){	//If '€' (8364) is converted to the character '¶' (182) to only occupy 1 byte
			cuvex.nfc.tag.new_alias[i] = 182;
		}
		else{
			cuvex.nfc.tag.new_alias[i] = (uint8_t) keyboard_text_typed_aliasBuffer[i];
		}
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::generateRecordData2_Cryptogram()
{
	uint8_t text_to_encrypt[SIZE_CRYPT] = {0};
	uint16_t pwd_raw_length = 0, pos = 0;
	uint8_t pwd0_length = 0, pwd1_length = 0, pwd2_length = 0, pwd3_length = 0, pwd4_length = 0, pwd5_length = 0;

	memset(cuvex.nfc.tag.new_cryptogram, 0x00, SIZE_CRYPT);
	memset(pwd_raw, 0x00, sizeof(pwd_raw));

	/*** Obtaining the length and concatenation of the complete password (in raw) ***/
	pwd0_length = strlen((const char *) pwds[0]);
	pwd1_length = strlen((const char *) pwds[1]);
	pwd2_length = strlen((const char *) pwds[2]);
	pwd3_length = strlen((const char *) pwds[3]);
	pwd4_length = strlen((const char *) pwds[4]);
	pwd5_length = strlen((const char *) pwds[5]);
	pwd_raw_length = pwd0_length + pwd1_length + pwd2_length + pwd3_length + pwd4_length + pwd5_length;

	strcat((char*) pwd_raw, (const char*) pwds[0]);
	strcat((char*) pwd_raw, (const char*) pwds[1]);
	strcat((char*) pwd_raw, (const char*) pwds[2]);
	strcat((char*) pwd_raw, (const char*) pwds[3]);
	strcat((char*) pwd_raw, (const char*) pwds[4]);
	strcat((char*) pwd_raw, (const char*) pwds[5]);

	/*** Obtaining the encrypted password (SHA-256) ***/
	HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, pwd_raw_length, pwd_sha256, HAL_MAX_DELAY);

	/*** AES-256 peripheral configuration (password + initialization vector + header) ***/
	HAL_HASH_MD5_Start(&hhash, cuvex.nfc.tag.new_alias, strlen((char *) cuvex.nfc.tag.new_alias), iv_aes_gcm, HAL_MAX_DELAY);

	/*** Init count to 0x02 ***/
	iv_aes_gcm[12]=0x00;
	iv_aes_gcm[13]=0x00;
	iv_aes_gcm[14]=0x00;
	iv_aes_gcm[15]=0x02;

	configAESPeripheral(pwd_sha256, iv_aes_gcm);

	/*** Generating text to encrypt (BIP39 seed, plaintext) + AES-256 Encryption ***/
	switch(cuvex.encrypt.text_type)
	{
	case TEXT_TYPE_NONE:
	default:
		break;

	case TEXT_TYPE_BIP39:
		strcat((char*) text_to_encrypt, (const char*) "[bip39]");

		for(int i=0; i<cuvex.encrypt.total_words; i++){
			strcat((char*) text_to_encrypt, (const char*) ",");
			strcat((char*) text_to_encrypt, (const char*) cuvex.encrypt.words_to_encrypt[i]);
		}

		strcat((char*) text_to_encrypt, (const char*) "[passphrase]");
		strcat((char*) text_to_encrypt, (char*) cuvex.encrypt.buff_passphrase);

		/*** Create new text to encrypt under format uint32_t ***/
		for(uint8_t k=0; k<SIZE_CRYPT_MSG; k++){
			cuvex.nfc.tag.new_text_to_encrypt[k] = text_to_encrypt[k*4] * 0x1000000 + text_to_encrypt[(k*4)+1] * 0x10000 + text_to_encrypt[(k*4)+2] * 0x100 + text_to_encrypt[(k*4)+3];
		}

		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.new_text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_text_encrypted, HAL_MAX_DELAY);

		/*** NFC SAVES DATA IN UINT8_T FORMAT ***/
		pos=0;
		for(uint8_t z=0; z<SIZE_CRYPT_MSG; z++)
		{
			cuvex.nfc.tag.new_cryptogram[pos] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x1000000);
			cuvex.nfc.tag.new_cryptogram[pos+1] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x10000);
			cuvex.nfc.tag.new_cryptogram[pos+2] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x100);
			cuvex.nfc.tag.new_cryptogram[pos+3] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z]);
			pos+=4;
		}

		break;

	case TEXT_TYPE_SLIP39:
		strcat((char*) text_to_encrypt, (const char*) "[slip39]");

		for(int i=0; i<cuvex.encrypt.total_words; i++){
			strcat((char*) text_to_encrypt, (const char*) ",");
			strcat((char*) text_to_encrypt, (const char*) cuvex.encrypt.words_to_encrypt[i]);
		}

		strcat((char*) text_to_encrypt, (const char*) "[passphrase]");
		strcat((char*) text_to_encrypt, (char*) cuvex.encrypt.buff_passphrase);

		/*** Create new text to encrypt under format uint32_t ***/
		for(uint8_t k=0; k<(SIZE_CRYPT_MSG); k++){
			cuvex.nfc.tag.new_text_to_encrypt[k] = text_to_encrypt[k*4] * 0x1000000 + text_to_encrypt[(k*4)+1] * 0x10000 + text_to_encrypt[(k*4)+2] * 0x100 + text_to_encrypt[(k*4)+3];
		}

		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.new_text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_text_encrypted, HAL_MAX_DELAY);

		/*** NFC SAVES DATA IN UINT8_T FORMAT ***/
		pos=0;
		for(uint8_t z=0; z<(SIZE_CRYPT_MSG); z++)
		{
			cuvex.nfc.tag.new_cryptogram[pos] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x1000000);
			cuvex.nfc.tag.new_cryptogram[pos+1] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x10000);
			cuvex.nfc.tag.new_cryptogram[pos+2] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x100);
			cuvex.nfc.tag.new_cryptogram[pos+3] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z]);
			pos+=4;
		}

		break;

	case TEXT_TYPE_XMR:
		strcat((char*) text_to_encrypt, (const char*) "[xmr]");

		for(int i=0; i<cuvex.encrypt.total_words; i++){
			strcat((char*) text_to_encrypt, (const char*) ",");
			strcat((char*) text_to_encrypt, (const char*) cuvex.encrypt.words_to_encrypt[i]);
		}

		strcat((char*) text_to_encrypt, (const char*) "[passphrase]");
		strcat((char*) text_to_encrypt, (char*) cuvex.encrypt.buff_passphrase);


		/*** Create new text to encrypt under format uint32_t ***/
		for(uint8_t k=0; k<(SIZE_CRYPT_MSG); k++){
			cuvex.nfc.tag.new_text_to_encrypt[k] = text_to_encrypt[k*4] * 0x1000000 + text_to_encrypt[(k*4)+1] * 0x10000 + text_to_encrypt[(k*4)+2] * 0x100 + text_to_encrypt[(k*4)+3];
		}

		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.new_text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_text_encrypted, HAL_MAX_DELAY);

		/*** NFC SAVES DATA IN UINT8_T FORMAT ***/
		pos=0;
		for(uint8_t z=0; z<(SIZE_CRYPT_MSG); z++)
		{
			cuvex.nfc.tag.new_cryptogram[pos] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x1000000);
			cuvex.nfc.tag.new_cryptogram[pos+1] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x10000);
			cuvex.nfc.tag.new_cryptogram[pos+2] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x100);
			cuvex.nfc.tag.new_cryptogram[pos+3] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z]);
			pos+=4;
		}

		break;

	case TEXT_TYPE_PLAINTEXT:
		strcat((char*) text_to_encrypt, (char*) "[plain-text]");
		strcat((char*) text_to_encrypt, (char*) cuvex.encrypt.buff_plain_text);

		/*** Create new text to encrypt under format uint32_t ***/
		for(uint8_t k=0; k<(SIZE_CRYPT_MSG); k++){
			cuvex.nfc.tag.new_text_to_encrypt[k] = text_to_encrypt[k*4] * 0x1000000 + text_to_encrypt[(k*4)+1] * 0x10000 + text_to_encrypt[(k*4)+2] * 0x100 + text_to_encrypt[(k*4)+3];
		}

		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.new_text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_text_encrypted, HAL_MAX_DELAY);

		/*** NFC SAVES DATA IN UINT8_T FORMAT ***/
		pos=0;
		for(uint8_t z=0; z<(SIZE_CRYPT_MSG); z++)
		{
			cuvex.nfc.tag.new_cryptogram[pos] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x1000000);
			cuvex.nfc.tag.new_cryptogram[pos+1] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x10000);
			cuvex.nfc.tag.new_cryptogram[pos+2] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x100);
			cuvex.nfc.tag.new_cryptogram[pos+3] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z]);
			pos+=4;
		}

		break;

	case TEXT_TYPE_FROM_NFC_PLAINTEXT:
		strcat((char*) text_to_encrypt, (char*) "{plain-text}");
		strcat((char*) text_to_encrypt, (char*) cuvex.encrypt.buff_plain_text);

		/*** Create new text to encrypt under format uint32_t ***/
		for(uint8_t k=0; k<(SIZE_CRYPT_MSG); k++){
			cuvex.nfc.tag.new_text_to_encrypt[k] = text_to_encrypt[k*4] * 0x1000000 + text_to_encrypt[(k*4)+1] * 0x10000 + text_to_encrypt[(k*4)+2] * 0x100 + text_to_encrypt[(k*4)+3];
		}

		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.new_text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_text_encrypted, HAL_MAX_DELAY);

		/*** NFC SAVES DATA IN UINT8_T FORMAT ***/
		pos=0;
		for(uint8_t z=0; z<(SIZE_CRYPT_MSG); z++)
		{
			cuvex.nfc.tag.new_cryptogram[pos] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x1000000);
			cuvex.nfc.tag.new_cryptogram[pos+1] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x10000);
			cuvex.nfc.tag.new_cryptogram[pos+2] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x100);
			cuvex.nfc.tag.new_cryptogram[pos+3] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z]);
			pos+=4;
		}

		break;

	case TEXT_TYPE_FROM_NFC_BIP39:
		strcat((char*) text_to_encrypt, (const char*) "{bip39}");

		for(int i=0; i<cuvex.encrypt.total_words; i++){
			strcat((char*) text_to_encrypt, (const char*) ",");
			strcat((char*) text_to_encrypt, (const char*) cuvex.encrypt.words_to_encrypt[i]);
		}

		strcat((char*) text_to_encrypt, (const char*) "{passder}");
		strcat((char*) text_to_encrypt, (char*) cuvex.nfc.tag.from_nfc_pass_deriv);
		strcat((char*) text_to_encrypt, (const char*) "{prikey}");
		strcat((char*) text_to_encrypt, (char*) cuvex.nfc.tag.from_nfc_private_key);
		strcat((char*) text_to_encrypt, (const char*) "{pubkey}");
		strcat((char*) text_to_encrypt, (char*) cuvex.nfc.tag.from_nfc_public_key);

		/*** Create new text to encrypt under format uint32_t ***/
		for(uint8_t k=0; k<SIZE_CRYPT_MSG; k++){
			cuvex.nfc.tag.new_text_to_encrypt[k] = text_to_encrypt[k*4] * 0x1000000 + text_to_encrypt[(k*4)+1] * 0x10000 + text_to_encrypt[(k*4)+2] * 0x100 + text_to_encrypt[(k*4)+3];
		}

		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.new_text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_text_encrypted, HAL_MAX_DELAY);

		/*** NFC SAVES DATA IN UINT8_T FORMAT ***/
		pos=0;
		for(uint8_t z=0; z<SIZE_CRYPT_MSG; z++)
		{
			cuvex.nfc.tag.new_cryptogram[pos] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x1000000);
			cuvex.nfc.tag.new_cryptogram[pos+1] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x10000);
			cuvex.nfc.tag.new_cryptogram[pos+2] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x100);
			cuvex.nfc.tag.new_cryptogram[pos+3] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z]);
			pos+=4;
		}
		break;

	case TEXT_TYPE_FROM_WALLET_BIP39:
		strcat((char*) text_to_encrypt, (const char*) "{bip39}");

		for(int i=0; i<24; i++){
			strcat((char*) text_to_encrypt, (const char*) ",");
			strcat((char*) text_to_encrypt, (const char*) cuvex.wallet.words_to_encrypt[i]);
		}

		strcat((char*) text_to_encrypt, (const char*) "{passder}");
		strcat((char*) text_to_encrypt, (char*) cuvex.wallet.pass_deriv);
		strcat((char*) text_to_encrypt, (const char*) "{prikey}");
		strcat((char*) text_to_encrypt, (char*) cuvex.wallet.zprv_key);
		strcat((char*) text_to_encrypt, (const char*) "{pubkey}");
		strcat((char*) text_to_encrypt, (char*) cuvex.wallet.zpub_key);

		/*** Create new text to encrypt under format uint32_t ***/
		for(uint8_t k=0; k<SIZE_CRYPT_MSG; k++){
			cuvex.nfc.tag.new_text_to_encrypt[k] = text_to_encrypt[k*4] * 0x1000000 + text_to_encrypt[(k*4)+1] * 0x10000 + text_to_encrypt[(k*4)+2] * 0x100 + text_to_encrypt[(k*4)+3];
		}

		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.new_text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_text_encrypted, HAL_MAX_DELAY);

		/*** NFC SAVES DATA IN UINT8_T FORMAT ***/
		pos=0;
		for(uint8_t z=0; z<SIZE_CRYPT_MSG; z++)
		{
			cuvex.nfc.tag.new_cryptogram[pos] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x1000000);
			cuvex.nfc.tag.new_cryptogram[pos+1] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x10000);
			cuvex.nfc.tag.new_cryptogram[pos+2] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z] / 0x100);
			cuvex.nfc.tag.new_cryptogram[pos+3] = (uint8_t) (cuvex.nfc.tag.new_text_encrypted[z]);
			pos+=4;
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
void screen_flow_encrypt_part_2View::generateRecordData3_Information()
{
	char str_total_pwds[5] = {0}, str_mandatory_pwds[5] = {0};

	memset(cuvex.nfc.tag.new_information, 0x00, SIZE_INFORMATION);
	itoa(total_pwds, str_total_pwds, 10);
	itoa(mandatory_pwds, str_mandatory_pwds, 10);

	/*** Record info format: "ENC,vXX.XX.XX(Y),M-X:X,P-X,C-X" ***/
	strcat((char *) cuvex.nfc.tag.new_information, (char *) "ENC,v");
	strcat((char *) cuvex.nfc.tag.new_information, (char *) cuvex.info.fw_version);
	strcat((char *) cuvex.nfc.tag.new_information, (char *) "(");
	strcat((char *) cuvex.nfc.tag.new_information, (char *) cuvex.info.hw_version);
	strcat((char *) cuvex.nfc.tag.new_information, (char *) "),M-");
	strcat((char *) cuvex.nfc.tag.new_information, (char *) str_total_pwds);
	strcat((char *) cuvex.nfc.tag.new_information, (char *) ":");
	strcat((char *) cuvex.nfc.tag.new_information, (char *) str_mandatory_pwds);
	strcat((char *) cuvex.nfc.tag.new_information, (char *) ",P-0,C-0");
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::generateRecordData4_Multisignature()
{
	char comb_buffer[10][KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE] = {0};

	memset(cuvex.nfc.tag.new_multisignature, 0x00, SIZE_MULTISIGN);
	generateCombinations(0, 0, comb_buffer);
}

/*
 *
 *
 *
 */

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::configAESPeripheral(uint8_t keyAES[], uint8_t ivAES[])
{
	__ALIGN_BEGIN uint32_t HeaderAES_aux[1] __ALIGN_END = {0x00000000};

	for(uint8_t a=0; a<8; a++){
		cuvex.nfc.tag.new_pKeyAES[a] = keyAES[a*4] * 0x1000000 + keyAES[(a*4)+1] * 0x10000 + keyAES[(a*4)+2] * 0x100 + keyAES[(a*4)+3];
	}

	for(uint8_t b=0; b<4; b++){
		cuvex.nfc.tag.new_pInitVectAES[b] = ivAES[b*4] * 0x1000000 + ivAES[(b*4)+1] * 0x10000 + ivAES[(b*4)+2] * 0x100 + ivAES[(b*4)+3];
	}

	HAL_CRYP_DeInit(&hcryp);

	hcryp.Init.DataType = CRYP_NO_SWAP;
	hcryp.Init.KeySize = CRYP_KEYSIZE_256B;
	hcryp.Init.pKey = (uint32_t *) cuvex.nfc.tag.new_pKeyAES;
	hcryp.Init.pInitVect = (uint32_t *) cuvex.nfc.tag.new_pInitVectAES;
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

/*
 *
 *
 *
 */

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_encrypt_part_2View::generateCombinations(int start, int index, char comb_buffer[][KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE])
{
	uint8_t pwd_combined_raw[10*KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE] = {0};
	uint32_t pwd_sha256_st_format[8] = {0};
	uint32_t aux_cryptogram_st_format[8] = {0};
	uint8_t aux_cryptogram[32] = {0};
	static int count_bytes = 0;

	if(index == mandatory_pwds)
	{
		/*** Obtaining the raw password combination ***/
		for(int i=0; i<mandatory_pwds; i++){
			strcat((char *) pwd_combined_raw, (char *) comb_buffer[i]);
		}

		/*** Obtaining the encrypted password combination (SHA-256) ***/
		HAL_HASHEx_SHA256_Start(&hhash, pwd_combined_raw, strlen((char *) pwd_combined_raw), pwd_combined_sha256, HAL_MAX_DELAY);

		/*** AES-256 peripheral configuration (password + initialization vector + header) ***/
		HAL_HASH_MD5_Start(&hhash, cuvex.nfc.tag.new_alias, strlen((char *) cuvex.nfc.tag.new_alias), iv_aes_gcm, HAL_MAX_DELAY);

		/*** Init count to 0x02 ***/
		iv_aes_gcm[12]=0x00;
		iv_aes_gcm[13]=0x00;
		iv_aes_gcm[14]=0x00;
		iv_aes_gcm[15]=0x02;

		configAESPeripheral(pwd_combined_sha256, iv_aes_gcm);

		/*** Generating text to encrypt (BIP39 seed, plaintext) + AES-256 Encryption ***/
		/*** Create new text to encrypt under format uint32_t ***/
		for(uint8_t k=0; k<8; k++){
			pwd_sha256_st_format[k] = pwd_sha256[k*4] * 0x1000000 + pwd_sha256[(k*4)+1] * 0x10000 + pwd_sha256[(k*4)+2] * 0x100 + pwd_sha256[(k*4)+3];
		}

		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) pwd_sha256_st_format, 8, (uint32_t *) aux_cryptogram_st_format, HAL_MAX_DELAY);

		/*** Concatenate combination in buffer ***/
		/*** NFC SAVES DATA IN UINT8_T FORMAT ***/
		uint16_t pos=0;
		for(uint8_t z=0; z<8; z++)
		{
			aux_cryptogram[pos] = (uint8_t) (aux_cryptogram_st_format[z] / 0x1000000);
			aux_cryptogram[pos+1] = (uint8_t) (aux_cryptogram_st_format[z] / 0x10000);
			aux_cryptogram[pos+2] = (uint8_t) (aux_cryptogram_st_format[z] / 0x100);
			aux_cryptogram[pos+3] = (uint8_t) (aux_cryptogram_st_format[z]);
			pos+=4;
		}

		/*** Concatenate combination in buffer ***/
		memcpy(cuvex.nfc.tag.new_multisignature + count_bytes, aux_cryptogram, 32);
		count_bytes = count_bytes + 32;

		/*** Function return ***/
		return;
	}

	for(int i=start; i<=total_pwds-(mandatory_pwds-index); i++)
	{
		strcpy(comb_buffer[index], (char *) pwds[i]);
		generateCombinations(i+1, index+1, comb_buffer);
	}
}


