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

#include <gui/screen_flow_3_screen/screen_flow_3View.hpp>
#include "main.h"

extern struct cuvex cuvex;
extern HASH_HandleTypeDef hhash;
extern CRYP_HandleTypeDef hcryp;

screen_flow_3View::screen_flow_3View(): qr_info_type(0), temporal_block(0), text_type(0), total_words(0), index_words(0), num_pwds(1), actual_pwd(0), pwd_ok(false), words_decrypted{0}, words_to_check{0}, buff_passphrase{0}, buff_plain_text{0}, buff_pass_der{0}, buff_derivation1{0}, buff_derivation2{0}, buff_pri_key{0}, buff_pub_key{0}, pwds{0}, pwd_raw{0}, pwd_sha256{0}, pwd_combined_sha256{0}, header_aes_gcm{0}, iv_aes_gcm{0}
{
	add(qr_code);
}

void screen_flow_3View::setupScreen()
{
	screen_flow_3ViewBase::setupScreen();
	screen_flow_3View::checkTemporalBlock();
	screen_flow_3View::setScreenMode();
	screen_flow_3View::setScreenLanguage();
	screen_flow_3View::changeScreen(GUI_TO_MAIN_SCREEN_FLOW_3);

	memset(keyboard_text_typedBuffer, 0x00, sizeof(keyboard_text_typedBuffer));
	keyboard_password.clearBuffer();
}

void screen_flow_3View::tearDownScreen()
{
	screen_flow_3ViewBase::tearDownScreen();
	screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
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
void screen_flow_3View::tickEventScreen()
{
	static uint8_t tick = 0;
	static uint16_t tick_temporal_block = 0;

	/*** Temporary lock timing within the flow ***/
	if(temporal_block == 1)
	{
		tick_temporal_block++;

		if(tick_temporal_block >= 5*60*5)	//5 minutes in total (approx.)
		{
			temporal_block = 0;
			tick_temporal_block = 0;
			cuvex.info.errors = 0;
			screen_flow_3View::changeFlash(GUI_TO_MAIN_FLASH_SAVE_SETTINGS);
			screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
			screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ);
			s0_temporalBlock.setVisible(false);
			s1_initNFC.setVisible(true);
			close_button.setVisible(true);
			background.invalidate();
		}
	}

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

	/*** Timer management ***/
	if(s8_viewSecret.isVisible() == true)
	{
		if(tick++ > 4)
		{
			if((Unicode::atoi(text_timeoutBuffer) - 1) > 9)
			{
				Unicode::snprintf(text_timeoutBuffer, TEXT_TIMEOUT_SIZE, "%d", Unicode::atoi(text_timeoutBuffer) - 1);
				background.invalidate();
				tick = 0;
			}
			else if(((Unicode::atoi(text_timeoutBuffer) - 1) <= 9) && ((Unicode::atoi(text_timeoutBuffer) - 1) > 0))
			{
				Unicode::snprintf(text_timeoutBuffer, TEXT_TIMEOUT_SIZE, "0%d", Unicode::atoi(text_timeoutBuffer) - 1);
				background.invalidate();
				tick = 0;
			}
			else
			{
				qr_code.setVisible(false);
				btn_back.setVisible(false);
				close_button.setVisible(false);
				s8_viewSecret.setVisible(false);
				s9_timeoutSecret.setVisible(true);
				background.invalidate();
			}
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
void screen_flow_3View::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::changeFlash(uint8_t state)
{
	presenter->changeFlash(state);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::changeStateNfc(uint8_t state)
{
	presenter->changeStateNfc(state);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::updateStateNfc(uint16_t state)
{
	switch(state)
	{
	case MAIN_TO_GUI_NFC_ERROR:
	default:
		application().gotoscreen_menuScreenNoTransition();
		break;

	case MAIN_TO_GUI_NFC_INITIALIZED:
		if(s1_initNFC.isVisible() == true)
		{
			s1_initNFC.setVisible(false);
			s2_waitReadNFC.setVisible(true);
		}
		break;

	case MAIN_TO_GUI_NFC_TAG_READED:
		if(s2_waitReadNFC.isVisible() == true)
		{
			s2_waitReadNFC.setVisible(false);

			if(cuvex.nfc.tag.encripted == true)
			{
				s3_viewTagInfo.setVisible(true);
				screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);

				if(cuvex.nfc.tag.alias[0] == 0x00)	//If the read tag doesn't have an alias => Text with the UID (otherwise alias)
				{
					text_uid.setVisible(true);
					text_uid_info.setVisible(true);
					text_alias.setVisible(false);
					text_alias_info.setVisible(false);
					memset(text_uidBuffer, 0x00, TEXT_UID_SIZE);
					Unicode::snprintf(text_uidBuffer, TEXT_UID_SIZE, (const char*) cuvex.nfc.tag.uid);
				}
				else
				{
					text_uid.setVisible(false);
					text_uid_info.setVisible(false);
					text_alias.setVisible(true);
					text_alias_info.setVisible(true);
					memset(text_aliasBuffer, 0x00, TEXT_ALIAS_SIZE);

					for(int i=0; i<SIZE_ALIAS; i++)
					{
						if(cuvex.nfc.tag.alias[i] == 182){	//If '¶' (182) is converted to the character '€' (8364) for display on screen
							text_aliasBuffer[i] = 8364;
						}
						else{
							text_aliasBuffer[i] = cuvex.nfc.tag.alias[i];
						}
					}
				}
			}
			else
			{
				s4_readError.setVisible(true);
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
void screen_flow_3View::hideKeyboardPressed()
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
void screen_flow_3View::showKeyboardPressed()
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
void screen_flow_3View::enterKeyboardPressed()
{
	uint8_t  decrypted_text[SIZE_CRYPT] = {0};

	if(keyboard_text_typedBuffer[0] != 0x00)
	{
		memset(pwds[actual_pwd], 0x00, KEYBOARD_TEXT_TYPED_SIZE);

		/*** Obtaining the typed text (password) ***/
		for(int i=0; i<KEYBOARD_TEXT_TYPED_SIZE; i++)
		{
			if(keyboard_text_typedBuffer[i] == 8364){	//If '€' (8364) is converted to the character '¶' (182) to only occupy 1 byte
				pwds[actual_pwd][i] = 182;
			}
			else{
				pwds[actual_pwd][i] = (uint8_t) keyboard_text_typedBuffer[i];
			}
		}

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
			/*** Decryption of secret (seeds, plaintext) ***/
			if(cuvex.nfc.tag.multisigned_total != cuvex.nfc.tag.multisigned_mandatory){
				decryptSecretWithCombinations(decrypted_text);
			}
			else{
				decryptSecret(decrypted_text);
			}

			/*** Selecting visible/hidden elements on the screen ***/
			if(pwd_ok == true){
				passwordSuccess(decrypted_text);
			}
			else{
				passwordWrong();
			}
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
void screen_flow_3View::decryptPressed()
{
	num_pwds = cuvex.nfc.tag.multisigned_mandatory;

	/*** Selection of texts to display in the information fields ***/
	Unicode::UnicodeChar degree[] = {0x00B0,0};

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

	/*** Selecting visible/hidden elements on the screen ***/
	s3_viewTagInfo.setVisible(false);
	s5_typePassword.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::retryPressed()
{
	/*** NFC re-initialization ***/
	screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
	screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ);

	/*** Selecting visible/hidden elements on the screen ***/
	s4_readError.setVisible(false);
	s1_initNFC.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::moreTimePressed()
{
	Unicode::snprintf(text_timeoutBuffer, TEXT_TIMEOUT_SIZE, "60");
	text_timeout.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::eyePressed()
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
void screen_flow_3View::resetMicrocontrollerPressed()
{
	NVIC_SystemReset();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::btnUpPressed()
{
	switch(text_type)
	{
	case TEXT_TYPE_NONE:
	default:
		break;

	case TEXT_TYPE_BIP39:
	case TEXT_TYPE_SLIP39:
	case TEXT_TYPE_XMR:
		if(text_secret_check.getY() < 0){
			text_secret_check.setPosition(0, text_secret_check.getY() + 20, 200, (20*(total_words+1)) + (20*7));
		}
		break;

	case TEXT_TYPE_PLAINTEXT:
	case TEXT_TYPE_FROM_NFC_PLAINTEXT:
		if(text_secret_check.getY() < 0){
			text_secret_check.setPosition(0, text_secret_check.getY() + 20, 200, 20*(text_secret_check.getTextWidth()/200));
		}
		break;


	case TEXT_TYPE_FROM_NFC_BIP39:
		if(text_secret_check.getY() < 0){
			text_secret_check.setPosition(0, text_secret_check.getY() + 20, 200, (20*(total_words+1)) + (4*20*7));
		}
		break;
	}

	container_typed_check.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::btnDownPressed()
{
	switch(text_type)
	{
	case TEXT_TYPE_NONE:
	default:
		break;

	case TEXT_TYPE_BIP39:
	case TEXT_TYPE_SLIP39:
	case TEXT_TYPE_XMR:
		if((text_secret_check.getY() + 20*(total_words+1)) > 0){
			text_secret_check.setPosition(0, text_secret_check.getY() - 20, 200, (20*(total_words+1))+(20*7));
		}
		break;

	case TEXT_TYPE_PLAINTEXT:
	case TEXT_TYPE_FROM_NFC_PLAINTEXT:
		if((text_secret_check.getY() + (20*(text_secret_check.getTextWidth()/200))-3*20) > 0){
			text_secret_check.setPosition(0, text_secret_check.getY() - 20, 200, 20*(text_secret_check.getTextWidth()/200)+2*20);
		}
		break;

	case TEXT_TYPE_FROM_NFC_BIP39:
		if((text_secret_check.getY() + (20*(total_words+1))+(4*20*7)) > 0){
			text_secret_check.setPosition(0, text_secret_check.getY() - 20, 200, (20*(total_words+1))+(4*20*7));
		}
		break;
	}

	container_typed_check.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::qrSmallPressed()
{
	if(text_type == TEXT_TYPE_FROM_NFC_BIP39)
	{
		/*** Selecting visible/hidden elements on the screen ***/
		container_qr_to_check_menu.setVisible(true);
		container_caution_msg.setVisible(false);
		container_qr_small_code.setVisible(false);
		container_typed_check.setVisible(false);
		close_button.setVisible(false);
		btn_more_time.setVisible(false);
		text_timeout.setVisible(false);
		btn_back.setVisible(false);
		qr_code.setVisible(false);
	}
	else
	{
		/*** Configuration of text based on the selected language (Spanish/English) ***/
		if(cuvex.info.language == SPANISH){
			text_caution_msg_spanish.setVisible(true);
			text_caution_msg_english.setVisible(false);
		}
		else{
			text_caution_msg_spanish.setVisible(false);
			text_caution_msg_english.setVisible(true);
		}

		/*** Selecting visible/hidden elements on the screen ***/
		container_qr_to_check_menu.setVisible(false);
		container_caution_msg.setVisible(true);
		container_qr_small_code.setVisible(false);
		container_typed_check.setVisible(false);
		close_button.setVisible(false);
		btn_more_time.setVisible(false);
		text_timeout.setVisible(false);
		btn_back.setVisible(false);
		qr_code.setVisible(false);
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
void screen_flow_3View::backPressed()
{
	/*** Move timer ***/
	text_timeout.setPosition(80, 25, 60, 30);

	/*** Selecting visible/hidden elements on the screen ***/
	container_qr_small_code.setVisible(true);
	container_typed_check.setVisible(true);
	close_button.setVisible(true);
	btn_back.setVisible(false);
	qr_code.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::btnError1Pressed()
{
	/*** Deletion of variables linked to password acquisition ***/
	for(int i=0; i<10; i++){
		memset(pwds[i], 0x00, KEYBOARD_TEXT_TYPED_SIZE);
	}

	memset(pwd_raw, 0x00, 10*KEYBOARD_TEXT_TYPED_SIZE);
	memset(pwd_sha256, 0x00, 32);
	num_pwds 	= cuvex.nfc.tag.multisigned_total;
	actual_pwd 	= 0;
	pwd_ok 		= false;

	/*** Call to the function that jumps back to the previous screen to ensure proper loading of elements before the screen to be skipped ***/
	screen_flow_3View::decryptPressed();

	/*** Selecting visible/hidden elements on the screen ***/
	s6_passwordError1.setVisible(false);
	s5_typePassword.setVisible(true);
	close_button.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::btnError2Pressed()
{
	NVIC_SystemReset();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::btnCautionMsgPressed()
{
	uint8_t words_lower_case[55][15] = {0};

	for(int i = 0; i<55; i++){
		for(int j = 0; j<15; j++){
			if((words_to_check[i][j] >= 0x41) && (words_to_check[i][j] <= 0x5A)){
				words_lower_case[i][j] = words_to_check[i][j] + 0x20;
			}
			else if((words_to_check[i][j] >= 0x61) && (words_to_check[i][j] <= 0x7A)){
				words_lower_case[i][j] = words_to_check[i][j];
			}
		}
	}

	/*** QR code generation ***/
	char qr_text[1000] = {0};

	switch(text_type)
	{
	case TEXT_TYPE_NONE:
	default:
		break;

	case TEXT_TYPE_BIP39:
	case TEXT_TYPE_SLIP39:
	case TEXT_TYPE_XMR:
		for(int i=0; i<total_words; i++)
		{
			strcat(qr_text, (char *) words_lower_case[i]);
			strcat(qr_text, (char *) " ");
		}
		break;

	case TEXT_TYPE_PLAINTEXT:
	case TEXT_TYPE_FROM_NFC_PLAINTEXT:
		strcpy(qr_text, (char *) buff_plain_text);
		break;

	case TEXT_TYPE_FROM_NFC_BIP39:
		if(qr_info_type == 1)
		{
			for(int i=0; i<total_words; i++)
			{
				strcat(qr_text, (char *) words_lower_case[i]);
				strcat(qr_text, (char *) " ");
			}
		}
		else if (qr_info_type == 2)
		{
			strcpy(qr_text, (char *) buff_pri_key);
		}
		else if (qr_info_type == 3)
		{
			strcpy(qr_text, (char *) buff_pub_key);
		}
		break;
	}

	code = new QR(qr_text, 15);
	qr_code.setXY(83,45);
	qr_code.setScale(2);
	qr_code.setQRCode(code);

	/*** Move timer ***/
	text_timeout.setPosition(130, 5, 60, 30);

	/*** Selecting visible/hidden elements on the screen ***/
	container_caution_msg.setVisible(false);
	container_qr_small_code.setVisible(false);
	container_typed_check.setVisible(false);
	close_button.setVisible(false);
	btn_more_time.setVisible(true);
	text_timeout.setVisible(true);
	btn_back.setVisible(true);
	qr_code.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::btnQrSeedPressed()
{
	qr_info_type = 1;

	/*** Configuration of text based on the selected language (Spanish/English) ***/
	if(cuvex.info.language == SPANISH){
		text_caution_msg_spanish.setVisible(true);
		text_caution_msg_english.setVisible(false);
	}
	else{
		text_caution_msg_spanish.setVisible(false);
		text_caution_msg_english.setVisible(true);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	container_qr_to_check_menu.setVisible(false);
	container_caution_msg.setVisible(true);
	container_qr_small_code.setVisible(false);
	container_typed_check.setVisible(false);
	close_button.setVisible(false);
	btn_more_time.setVisible(false);
	text_timeout.setVisible(false);
	btn_back.setVisible(false);
	qr_code.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::btnQrPrivateKeyPressed()
{
	qr_info_type = 2;

	/*** Configuration of text based on the selected language (Spanish/English) ***/
	if(cuvex.info.language == SPANISH){
		text_caution_msg_spanish.setVisible(true);
		text_caution_msg_english.setVisible(false);
	}
	else{
		text_caution_msg_spanish.setVisible(false);
		text_caution_msg_english.setVisible(true);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	container_qr_to_check_menu.setVisible(false);
	container_caution_msg.setVisible(true);
	container_qr_small_code.setVisible(false);
	container_typed_check.setVisible(false);
	close_button.setVisible(false);
	btn_more_time.setVisible(false);
	text_timeout.setVisible(false);
	btn_back.setVisible(false);
	qr_code.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::btnQrPublicKeyPressed()
{
	qr_info_type = 3;

	/*** Configuration of text based on the selected language (Spanish/English) ***/
	if(cuvex.info.language == SPANISH){
		text_caution_msg_spanish.setVisible(true);
		text_caution_msg_english.setVisible(false);
	}
	else{
		text_caution_msg_spanish.setVisible(false);
		text_caution_msg_english.setVisible(true);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	container_qr_to_check_menu.setVisible(false);
	container_caution_msg.setVisible(true);
	container_qr_small_code.setVisible(false);
	container_typed_check.setVisible(false);
	close_button.setVisible(false);
	btn_more_time.setVisible(false);
	text_timeout.setVisible(false);
	btn_back.setVisible(false);
	qr_code.setVisible(false);

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
void screen_flow_3View::setScreenMode()
{
	/*** Setting screen elements based on mode (dark/light) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_back.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_back.setIconBitmaps(Bitmap(BITMAP_BACK_DARK_ID), Bitmap(BITMAP_BACK_ID));
		init_nfc_text1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		init_nfc_text2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_wait_read_nfc.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_decrypt.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_decrypt.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_alias_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_alias.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_uid_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_uid.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_retry.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_retry.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_read_error.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_btn_enter.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_typed_hide.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_english_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_english_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_english_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_english_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_english_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_spanish_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_spanish_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_spanish_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_spanish_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_spanish_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_english_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_english_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_english_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_english_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_english_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_spanish_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_spanish_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_spanish_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_spanish_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_spanish_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_more_time.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_more_time.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_secret_check.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_caution_msg.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_caution_msg.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		caution_msg_english_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		caution_msg_english_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		caution_msg_english_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		caution_msg_spanish_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		caution_msg_spanish_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		caution_msg_spanish_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_timeout.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_timeout_secret.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_english_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_english_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_english_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_english_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_english_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_english_6.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_spanish_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_spanish_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_spanish_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_spanish_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_spanish_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_spanish_6.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_spanish_7.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_1_qr_seed.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_1_qr_seed.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_2_qr_private_key.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_2_qr_private_key.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_3_qr_public_key.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_3_qr_public_key.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
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
void screen_flow_3View::setScreenLanguage()
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
void screen_flow_3View::checkTemporalBlock()
{
	/*** Configuration of screen elements based on whether there is an active temporary lock or not ***/
	switch(cuvex.info.errors)
	{
	case 0:
	case 1:
	default:
		screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
		screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ);
		s0_temporalBlock.setVisible(false);
		s1_initNFC.setVisible(true);
		temporal_block = 0;
		break;

	case 2:
		s0_temporalBlock.setVisible(true);
		s1_initNFC.setVisible(false);
		close_button.setVisible(false);

		if(cuvex.info.language == SPANISH){
			text_temporal_block_spanish.setVisible(true);
			text_temporal_block_english.setVisible(false);
		}
		else{
			text_temporal_block_spanish.setVisible(false);
			text_temporal_block_english.setVisible(true);
		}

		temporal_block = 1;
		break;
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
void screen_flow_3View::configAESPeripheral(uint8_t keyAES[], uint8_t ivAES[], uint8_t headerAES[], uint8_t type)
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
void screen_flow_3View::decryptSecret(uint8_t  decrypted_text[SIZE_CRYPT])
{
	uint16_t pwd_raw_length = SIGNATURE_SIZE;
	uint8_t  pwd_lengths[6] = {0};
	uint8_t  iteration_length = 0;

	/*** Obtaining the length and concatenation of the complete password (in raw) ***/
	for(int i=0; i<6; i++){
		pwd_lengths[i] = strlen((const char *) pwds[i]);
		pwd_raw_length = pwd_raw_length + pwd_lengths[i];
	}

	memset(pwd_raw, 0x00, sizeof(pwd_raw));
	strncat((char*) pwd_raw, (const char*) cuvex.signature_buffer, SIGNATURE_SIZE);
	for(int i=0; i<6; i++){
		strcat((char*) pwd_raw, (const char*) pwds[i]);
	}

	if(pwd_lengths[0] != 0)
	{
		/*** Obtaining the encrypted password (SHA-256) ***/
		HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, pwd_raw_length, pwd_sha256, HAL_MAX_DELAY);

		/*** AES-256 peripheral configuration (password + initialization vector + header) + AES-256 Decrypt ***/
		if(strstr((const char *) cuvex.nfc.tag.information, "v1.0.0") != NULL){
			configAESPeripheral(pwd_sha256, iv_aes_gcm, header_aes_gcm, 1);
			HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.cryptogram, SIZE_CRYPT_MSG, (uint32_t *) decrypted_text, HAL_MAX_DELAY);
		}
		else{
			HAL_HASH_MD5_Start(&hhash, cuvex.nfc.tag.alias, strlen((char *) cuvex.nfc.tag.alias), iv_aes_gcm, HAL_MAX_DELAY);
			memset(header_aes_gcm, 0x00, sizeof(header_aes_gcm));
			configAESPeripheral(pwd_sha256, iv_aes_gcm, header_aes_gcm, 0);
			HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.cryptogram, SIZE_CRYPT_MSG, (uint32_t *) decrypted_text, HAL_MAX_DELAY);
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
			if(pwd_ok == true){
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

					/*** Updates 'pwd_raw' by concatenating the signature and the new permutation of passwords in 'pwds' ***/
					memset(pwd_raw, 0x00, sizeof(pwd_raw));
					strncat((char*) pwd_raw, (const char*) cuvex.signature_buffer, SIGNATURE_SIZE);
					for(int i=0; i<6; i++){
						strcat((char*) pwd_raw, (const char*) pwds[i]);
					}

					/*** Obtaining the encrypted password (SHA-256) ***/
					HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, pwd_raw_length, pwd_sha256, HAL_MAX_DELAY);

					/*** AES-256 peripheral configuration (password + initialization vector + header) + AES-256 Decrypt ***/
					if(strstr((const char *) cuvex.nfc.tag.information, "v1.0.0") != NULL){
						configAESPeripheral(pwd_sha256, iv_aes_gcm, header_aes_gcm, 1);
						HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.cryptogram, SIZE_CRYPT_MSG, (uint32_t *) decrypted_text, HAL_MAX_DELAY);
					}
					else{
						HAL_HASH_MD5_Start(&hhash, cuvex.nfc.tag.alias, strlen((char *) cuvex.nfc.tag.alias), iv_aes_gcm, HAL_MAX_DELAY);
						memset(header_aes_gcm, 0x00, sizeof(header_aes_gcm));
						configAESPeripheral(pwd_sha256, iv_aes_gcm, header_aes_gcm, 0);
						HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.cryptogram, SIZE_CRYPT_MSG, (uint32_t *) decrypted_text, HAL_MAX_DELAY);
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
void screen_flow_3View::decryptSecretWithCombinations(uint8_t  decrypted_text[SIZE_CRYPT])
{
	uint8_t block_buffer[32] = {0};
	uint8_t pwd_lengths[6] = {0};
	uint8_t iteration_length = 0;

	/*** Concatenation of the complete password (in raw) ***/
	memset(pwd_raw, 0x00, sizeof(pwd_raw));
	strncat((char*) pwd_raw, (const char*) cuvex.signature_buffer, SIGNATURE_SIZE);
	for(int i=0; i<6; i++){
		strcat((char*) pwd_raw, (const char*) pwds[i]);
		pwd_lengths[i] = strlen((const char *) pwds[i]);
	}

	if(pwd_lengths[0] != 0)
	{
		/*** Obtaining the encrypted password (SHA-256) ***/
		memset(pwd_combined_sha256, 0x00, sizeof(pwd_combined_sha256));
		HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, strlen((char *) pwd_raw) + SIGNATURE_SIZE, pwd_combined_sha256, HAL_MAX_DELAY);

		/*** Check all blocks trying decrypt ***/
		for(int i=0; i<20; i++)
		{
			/*** Select block to decrypt ***/
			memset(block_buffer, 0x00, 32);
			memcpy(block_buffer, cuvex.nfc.tag.multisignature + (i*32) , 32);

			/*** AES-256 peripheral configuration (initialization vector + header) ***/
			HAL_HASH_MD5_Start(&hhash, cuvex.nfc.tag.alias, strlen((char *) cuvex.nfc.tag.alias), iv_aes_gcm, HAL_MAX_DELAY);
			memset(header_aes_gcm, 0x00, sizeof(header_aes_gcm));

			/*** AES-256 peripheral configuration (password 1) + AES-256 Decrypt 1 ***/
			configAESPeripheral(pwd_combined_sha256, iv_aes_gcm, header_aes_gcm, 0);
			HAL_CRYP_Decrypt(&hcryp, (uint32_t *) block_buffer, 32/4, (uint32_t *) pwd_sha256, HAL_MAX_DELAY);

			/*** AES-256 peripheral configuration (password 2) + AES-256 Decrypt 2 ***/
			configAESPeripheral(pwd_sha256, iv_aes_gcm, header_aes_gcm, 0);
			HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.cryptogram, SIZE_CRYPT_MSG, (uint32_t *) decrypted_text, HAL_MAX_DELAY);

			/*** Check if text is decrypted correctly ***/
			pwd_ok = checkDecryptedText(decrypted_text);

			if(pwd_ok == true){
				break;
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
			if(pwd_ok == true){
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
					strncat((char*) pwd_raw, (const char*) cuvex.signature_buffer, SIGNATURE_SIZE);
					for(int i=0; i<6; i++){
						strcat((char*) pwd_raw, (const char*) pwds[i]);
					}

					/*** Obtaining the encrypted password (SHA-256) ***/
					memset(pwd_combined_sha256, 0x00, sizeof(pwd_combined_sha256));
					HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, strlen((char *) pwd_raw) + SIGNATURE_SIZE, pwd_combined_sha256, HAL_MAX_DELAY);

					/*** Check all blocks trying decrypt ***/
					for(int i=0; i<20; i++)
					{
						/*** Select block to decrypt ***/
						memset(block_buffer, 0x00, 32);
						memcpy(block_buffer, cuvex.nfc.tag.multisignature + (i*32) , 32);

						/*** AES-256 peripheral configuration (initialization vector + header) ***/
						HAL_HASH_MD5_Start(&hhash, cuvex.nfc.tag.alias, strlen((char *) cuvex.nfc.tag.alias), iv_aes_gcm, HAL_MAX_DELAY);
						memset(header_aes_gcm, 0x00, sizeof(header_aes_gcm));

						/*** AES-256 peripheral configuration (password 1) + AES-256 Decrypt 1 ***/
						configAESPeripheral(pwd_combined_sha256, iv_aes_gcm, header_aes_gcm, 0);
						HAL_CRYP_Decrypt(&hcryp, (uint32_t *) block_buffer, 32/4, (uint32_t *) pwd_sha256, HAL_MAX_DELAY);

						/*** AES-256 peripheral configuration (password 2) + AES-256 Decrypt 2 ***/
						configAESPeripheral(pwd_sha256, iv_aes_gcm, header_aes_gcm, 0);
						HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.cryptogram, SIZE_CRYPT_MSG, (uint32_t *) decrypted_text, HAL_MAX_DELAY);

						/*** Check if text is decrypted correctly ***/
						pwd_ok = checkDecryptedText(decrypted_text);

						if(pwd_ok == true){
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
bool screen_flow_3View::checkDecryptedText(uint8_t  decrypted_text[SIZE_CRYPT])
{
	if(strstr((const char *) decrypted_text, "[bip39]") != NULL)
	{
		text_type = TEXT_TYPE_BIP39;
		return true;
	}
	else if (strstr((const char *) decrypted_text, "[slip39]") != NULL)
	{
		text_type = TEXT_TYPE_SLIP39;
		return true;
	}
	else if (strstr((const char *) decrypted_text, "[xmr]") != NULL)
	{
		text_type = TEXT_TYPE_XMR;
		return true;
	}
	else if (strstr((const char *) decrypted_text, "[plain-text]") != NULL)
	{
		text_type = TEXT_TYPE_PLAINTEXT;
		return true;
	}
	else if (strstr((const char *) decrypted_text, "{plain-text}") != NULL)
	{
		text_type = TEXT_TYPE_FROM_NFC_PLAINTEXT;
		return true;
	}
	else if (strstr((const char *) decrypted_text, "{bip39}") != NULL)
	{
		text_type = TEXT_TYPE_FROM_NFC_BIP39;
		return true;
	}
	else
	{
		text_type = TEXT_TYPE_NONE;
		return false;
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::passwordSuccess(uint8_t  decrypted_text[SIZE_CRYPT])
{
	char buff1_check_all[TEXT_SECRET_CHECK_SIZE] = {0}, buff2_words_index[10] = {0};
	char *ptr1, *ptr2, *ptr3, *ptr4;
	int decrypted_lenght = 0;

	switch(text_type)
	{
	case TEXT_TYPE_NONE:
	default:
		break;

	case TEXT_TYPE_BIP39:
		/*** Parsing of the bip39 words and passphrase ***/
		ptr1 = strstr((char *) decrypted_text, "[bip39]");
		ptr2 = strstr((char *) decrypted_text, "[passphrase]");

		for(int i=8; i<ptr2-ptr1; i++)
		{
			if(decrypted_text[i] == ','){
				total_words++;
				index_words = 0;
			}
			else{
				words_decrypted[total_words][index_words++] = decrypted_text[i];
			}
		}
		total_words++;

		for(int j=0; j<total_words; j++){
			for(int i=0; i<15; i++){
				words_to_check[j][i] = words_decrypted[j][i];
			}
			getBip39Word((char *) words_to_check[j]);
		}

		decrypted_lenght = strlen((char *) decrypted_text);

		for(int i=0; i<((decrypted_lenght)-(ptr2-ptr1)+(12)); i++){
			buff_passphrase[i] = decrypted_text[i+((ptr2-ptr1)+(12))];
		}

		/*** Array generation for visualization ***/
		for(int i=0; i<total_words; i++)
		{
			snprintf(buff2_words_index, 5, "%d. ", i+1);
			strcat(buff1_check_all, (char *) buff2_words_index);
			strcat(buff1_check_all, (char *) words_to_check[i]);
			strcat(buff1_check_all, (char *) "\n");
		}

		strcat(buff1_check_all, (char*) "\nPassphrase:\n");
		strcat(buff1_check_all, (char*) buff_passphrase);

		/*** Assignment of words+passphrase for visualization in 'scrollable' text (if '¶' (182) converts to the character '€' (8364)) ***/
		Unicode::snprintf(text_secret_checkBuffer, TEXT_SECRET_CHECK_SIZE, buff1_check_all);

		for(int i = 0; i<TEXT_SECRET_CHECK_SIZE; i++){
			if(text_secret_checkBuffer[i] == 182){
				text_secret_checkBuffer[i] = 8364;
			}
		}

		text_secret_check.setPosition(0, 0, 200, (20*(total_words+1))+(20*7));
		text_secret_check.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);
		s5_typePassword.setVisible(false);
		s8_viewSecret.setVisible(true);
		break;

	case TEXT_TYPE_SLIP39:
		/*** Parsing of the slip39 words and passphrase ***/
		ptr1 = strstr((char *) decrypted_text, "[slip39]");
		ptr2 = strstr((char *) decrypted_text, "[passphrase]");

		for(int i=9; i<ptr2-ptr1; i++)
		{
			if(decrypted_text[i] == ','){
				total_words++;
				index_words = 0;
			}
			else{
				words_decrypted[total_words][index_words++] = decrypted_text[i];
			}
		}
		total_words++;

		for(int j=0; j<total_words; j++){
			for(int i=0; i<15; i++){
				words_to_check[j][i] = words_decrypted[j][i];
			}
			getSlip39Word((char *) words_to_check[j]);
		}

		decrypted_lenght = strlen((char *) decrypted_text);

		for(int i=0; i<((decrypted_lenght)-(ptr2-ptr1)+(12)); i++){
			buff_passphrase[i] = decrypted_text[i+((ptr2-ptr1)+(12))];
		}

		/*** Array generation for visualization ***/
		for(int i=0; i<total_words; i++)
		{
			snprintf(buff2_words_index, 5, "%d. ", i+1);
			strcat(buff1_check_all, (char *) buff2_words_index);
			strcat(buff1_check_all, (char *) words_to_check[i]);
			strcat(buff1_check_all, (char *) "\n");
		}

		strcat(buff1_check_all, (char*) "\nPassphrase:\n");
		strcat(buff1_check_all, (char*) buff_passphrase);

		/*** Assignment of words+passphrase for visualization in 'scrollable' text (if '¶' (182) converts to the character '€' (8364)) ***/
		Unicode::snprintf(text_secret_checkBuffer, TEXT_SECRET_CHECK_SIZE, buff1_check_all);

		for(int i = 0; i<TEXT_SECRET_CHECK_SIZE; i++){
			if(text_secret_checkBuffer[i] == 182){
				text_secret_checkBuffer[i] = 8364;
			}
		}

		text_secret_check.setPosition(0, 0, 200, (20*(total_words+1))+(20*7));
		text_secret_check.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);
		s5_typePassword.setVisible(false);
		s8_viewSecret.setVisible(true);
		break;

	case TEXT_TYPE_XMR:
		/*** Parsing of the xmr words and passphrase ***/
		ptr1 = strstr((char *) decrypted_text, "[xmr]");
		ptr2 = strstr((char *) decrypted_text, "[passphrase]");

		for(int i=6; i<ptr2-ptr1; i++)
		{
			if(decrypted_text[i] == ','){
				total_words++;
				index_words = 0;
			}
			else{
				words_decrypted[total_words][index_words++] = decrypted_text[i];
			}
		}
		total_words++;

		for(int j=0; j<total_words; j++){
			for(int i=0; i<15; i++){
				words_to_check[j][i] = words_decrypted[j][i];
			}
			getXmrWord((char *) words_to_check[j]);
		}

		decrypted_lenght = strlen((char *) decrypted_text);

		for(int i=0; i<((decrypted_lenght)-(ptr2-ptr1)+(12)); i++){
			buff_passphrase[i] = decrypted_text[i+((ptr2-ptr1)+(12))];
		}

		/*** Array generation for visualization ***/
		for(int i=0; i<total_words; i++)
		{
			snprintf(buff2_words_index, 5, "%d. ", i+1);
			strcat(buff1_check_all, (char *) buff2_words_index);
			strcat(buff1_check_all, (char *) words_to_check[i]);
			strcat(buff1_check_all, (char *) "\n");
		}

		strcat(buff1_check_all, (char*) "\nPassphrase:\n");
		strcat(buff1_check_all, (char*) buff_passphrase);

		/*** Assignment of words+passphrase for visualization in 'scrollable' text (if '¶' (182) converts to the character '€' (8364)) ***/
		Unicode::snprintf(text_secret_checkBuffer, TEXT_SECRET_CHECK_SIZE, buff1_check_all);

		for(int i = 0; i<TEXT_SECRET_CHECK_SIZE; i++){
			if(text_secret_checkBuffer[i] == 182){
				text_secret_checkBuffer[i] = 8364;
			}
		}

		text_secret_check.setPosition(0, 0, 200, (20*(total_words+1))+(20*7));
		text_secret_check.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);
		s5_typePassword.setVisible(false);
		s8_viewSecret.setVisible(true);
		break;

	case TEXT_TYPE_PLAINTEXT:
	case TEXT_TYPE_FROM_NFC_PLAINTEXT:
		/*** Array generation for visualization ***/
		memset(buff_plain_text, 0x00, sizeof(buff_plain_text));

		decrypted_lenght = strlen((char *) decrypted_text);

		for(int i=0; i<decrypted_lenght; i++){
			buff_plain_text[i] = decrypted_text[i+12];
		}

		/*** Assignment of plain text for visualization in 'scrollable' text (if '¶' (182) converts to the character '€' (8364)) ***/
		Unicode::snprintf(text_secret_checkBuffer, TEXT_SECRET_CHECK_SIZE, (char *) buff_plain_text);

		for(int i = 0; i<TEXT_SECRET_CHECK_SIZE; i++){
			if(text_secret_checkBuffer[i] == 182){
				text_secret_checkBuffer[i] = 8364;
			}
		}

		text_secret_check.setPosition(0, 0, 200, 20*(text_secret_check.getTextWidth()/200)+2*20);
		text_secret_check.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);
		s5_typePassword.setVisible(false);
		s8_viewSecret.setVisible(true);
		break;

	case TEXT_TYPE_FROM_NFC_BIP39:

		int len_bip39 = 0;
		int len_pass_der = 0;
		int len_priv_key = 0;
		int len_pub_key = 0;
		int aux = 0, j = 0;

		/*** Parsing of the bip39 words and passphrase ***/
		ptr1 = strstr((char *) decrypted_text, "{bip39}");
		ptr2 = strstr((char *) decrypted_text, "{passder}");
		ptr3 = strstr((char *) decrypted_text, "{prikey}");
		ptr4 = strstr((char *) decrypted_text, "{pubkey}");

		decrypted_lenght = strlen((char *) decrypted_text);

		len_bip39 		= ptr2 - ptr1;
		len_pass_der 	= ptr3 - ptr2;
		len_priv_key 	= ptr4 - ptr3;
		len_pub_key 	= decrypted_lenght - len_bip39 - len_pass_der - len_priv_key;

		/*** Words ***/
		for(int i=8; i<ptr2-ptr1; i++)
		{
			if(decrypted_text[i] == ','){
				total_words++;
				index_words = 0;
			}
			else{
				words_decrypted[total_words][index_words++] = decrypted_text[i];
			}
		}
		total_words++;

		for(int j=0; j<total_words; j++){
			for(int i=0; i<5; i++){
				words_to_check[j][i] = words_decrypted[j][i];
			}
			getBip39Word((char *) words_to_check[j]);
		}

		/*** Get seed "passphrase" + "derivation path" + "private key" + "public key" in screen format ***/
		for(int i=0; i<len_pass_der-9; i++)
		{
			buff_pass_der[i] = decrypted_text[len_bip39 + i + 9];
		}

		for(int i=1; i<strlen((char *) buff_pass_der); i++)
		{
			if(aux == 0)
			{
				if((buff_pass_der[i] == ',') && (buff_pass_der[i+1] == ' ') && (buff_pass_der[i+17] == ',') && (buff_pass_der[i+18] == ' '))
				{
					aux = 1;
					i = i+18;
					j = 0;
				}
				else{
					buff_passphrase[j++] = buff_pass_der[i];
				}
			}
			else if(aux == 1)
			{
				if((buff_pass_der[i] == ',') && (buff_pass_der[i+1] == ' ')){
					aux = 2;
					i = i+1;
					j = 0;
				}
				else{
					buff_derivation1[j++] = buff_pass_der[i];
				}
			}
			else if(aux == 2)
			{
				if(buff_pass_der[i] != '"'){
					buff_derivation2[j++] = buff_pass_der[i];
				}
			}
		}

		/*** Private key ***/
		for(int i=0; i<len_priv_key-8; i++)
		{
			buff_pri_key[i] = decrypted_text[len_bip39 + len_pass_der + i + 8];
		}

		/*** Public key ***/
		for(int i=0; i<len_pub_key-8; i++)
		{
			buff_pub_key[i] = decrypted_text[len_bip39 + len_pass_der + len_priv_key + i + 8];
		}

		/*** Generating an array for displaying: "words" + "passphrase" + "derivation path" + "private key" + "public key" ***/
		for(int i=0; i<total_words; i++)
		{
			snprintf(buff2_words_index, 15, "%d. ", i+1);
			strcat(buff1_check_all, (char *) buff2_words_index);
			strcat(buff1_check_all, (char *) words_to_check[i]);
			strcat(buff1_check_all, (char *) "\n");
		}

		strcat(buff1_check_all, (char*) "____________________\n\n");
		strcat(buff1_check_all, (char*) "Passphrase:\n");
		strcat(buff1_check_all, (char*) buff_passphrase);

		strcat(buff1_check_all, (char*) "\n____________________\n\n");
		strcat(buff1_check_all, (char*) buff_derivation1);
		strcat(buff1_check_all, (char*) "\n\nDerivation Path:\n");
		strcat(buff1_check_all, (char*) buff_derivation2);

		strcat(buff1_check_all, (char*) "\n____________________\n\n");
		strcat(buff1_check_all, (char*) "Master Private Key:\n");
		strcat(buff1_check_all, (char*) buff_pri_key);

		strcat(buff1_check_all, (char*) "\n____________________\n\n");
		strcat(buff1_check_all, (char*) "Master Public Key:\n");
		strcat(buff1_check_all, (char*) buff_pub_key);

		/*** Assignment of "words" + "passphrase" + "derivation path" + "private key" + "public key" to be displayed in "scrollable" field ***/
		Unicode::snprintf(text_secret_checkBuffer, TEXT_SECRET_CHECK_SIZE, buff1_check_all);
		text_secret_check.setPosition(0, 0, 200, (20*(total_words+1))+(4*20*7));
		text_secret_check.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);

		/*** Selecting visible/hidden elements on the screen ***/
		s5_typePassword.setVisible(false);
		s8_viewSecret.setVisible(true);
		break;
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::passwordWrong()
{
	cuvex.info.errors++;

	if(cuvex.info.errors == 1)	//Warning
	{
		close_button.setVisible(false);
		s5_typePassword.setVisible(false);
		s6_passwordError1.setVisible(true);

		if(cuvex.info.language == SPANISH){
			text_password_error1_spanish.setVisible(true);
			text_password_error1_english.setVisible(false);
		}
		else{
			text_password_error1_spanish.setVisible(false);
			text_password_error1_english.setVisible(true);
		}
	}
	else	//Temporary block
	{
		close_button.setVisible(false);
		s5_typePassword.setVisible(false);
		s7_passwordError2.setVisible(true);

		if(cuvex.info.language == SPANISH){
			text_password_error2_spanish.setVisible(true);
			text_password_error2_english.setVisible(false);
		}
		else{
			text_password_error2_spanish.setVisible(false);
			text_password_error2_english.setVisible(true);
		}

		screen_flow_3View::changeFlash(GUI_TO_MAIN_FLASH_SAVE_SETTINGS);
	}
}


