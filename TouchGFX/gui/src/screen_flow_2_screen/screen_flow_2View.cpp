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

#include <gui/screen_flow_2_screen/screen_flow_2View.hpp>
#include "main.h"

extern struct cuvex cuvex;
extern HASH_HandleTypeDef hhash;
extern CRYP_HandleTypeDef hcryp;

screen_flow_2View::screen_flow_2View(): text_type(0), total_words(0), actual_word(0), index_words(0), valid_word(0), actual_pwd(0), total_pwds(1), mandatory_pwds(1), flag_refresh_text_area(0), words_to_encrypt{0}, words_to_check{0}, buff_passphrase{0}, buff_plain_text{0}, pwds{0}, pwd_raw{0}, pwd_sha256{0}, pwd_combined_sha256{0}, header_aes_gcm{0}, iv_aes_gcm{0}
{

}

void screen_flow_2View::setupScreen()
{
	screen_flow_2ViewBase::setupScreen();
	screen_flow_2View::setScreenMode();
	screen_flow_2View::setScreenLanguage();
	screen_flow_2View::changeScreen(GUI_TO_MAIN_SCREEN_FLOW_2);

	memset(keyboard1_text_typed_seedBuffer,   		0x00, sizeof(keyboard1_text_typed_seedBuffer));
	memset(keyboard2_text_typed_seedBuffer,   		0x00, sizeof(keyboard2_text_typed_seedBuffer));
	memset(keyboard3_text_typed_seedBuffer,   		0x00, sizeof(keyboard3_text_typed_seedBuffer));
	memset(keyboard_text_typed_plain_textBuffer,	0x00, sizeof(keyboard_text_typed_plain_textBuffer));
	memset(keyboard1_text_typed_passwordBuffer, 	0x00, sizeof(keyboard1_text_typed_passwordBuffer));
	memset(keyboard2_text_typed_passwordBuffer, 	0x00, sizeof(keyboard2_text_typed_passwordBuffer));
	memset(keyboard_text_typed_aliasBuffer, 	 	0x00, sizeof(keyboard_text_typed_aliasBuffer));
	keyboard1_seed.clearBuffer();
	keyboard2_seed.clearBuffer();
	keyboard3_seed.clearBuffer();
	keyboard_plain_text.clearBuffer();
	keyboard1_password.clearBuffer();
	keyboard2_password.clearBuffer();
	keyboard_alias.clearBuffer();
}

void screen_flow_2View::tearDownScreen()
{
	screen_flow_2ViewBase::tearDownScreen();
	screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
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
void screen_flow_2View::tickEventScreen()
{
	uint8_t num_of_lines = 0;
	uint8_t str_prediction[KEYBOARD2_TEXT_PREDICTED_SEED_SIZE] = {0};

	/*** Seed's - Keyboard 1 (numeric) ***/
	if(keyboard1_seed.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard1_text_typed_seedBuffer, keyboard1_seed.getBuffer(), KEYBOARD1_TEXT_TYPED_SEED_SIZE) != 0)
		{
			if(Unicode::atoi(keyboard1_seed.getBuffer()) == 0){
				memset(keyboard1_text_typed_seedBuffer, 0x00, sizeof(keyboard1_text_typed_seedBuffer));
				keyboard1_seed.clearBuffer();
			}
			else if(Unicode::atoi(keyboard1_seed.getBuffer()) > 54){
				keyboard1_text_typed_seed.setColor(touchgfx::Color::getColorFromRGB(0xE7,0x44,0x3E));
			}
			else{
				keyboard1_text_typed_seed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
			}

			Unicode::snprintf(keyboard1_text_typed_seedBuffer, KEYBOARD1_TEXT_TYPED_SEED_SIZE, keyboard1_seed.getBuffer());
			keyboard1_text_area_seed.invalidate();
		}
	}

	/*** Seed's - Keyboard 2 (words) ***/
	if(keyboard2_seed.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard2_text_typed_seedBuffer, keyboard2_seed.getBuffer(), KEYBOARD2_TEXT_TYPED_SEED_SIZE) != 0)
		{
			Unicode::snprintf(keyboard2_text_typed_seedBuffer, KEYBOARD2_TEXT_TYPED_SEED_SIZE, keyboard2_seed.getBuffer());
			Unicode::snprintf(keyboard2_text_predicted_seedBuffer, KEYBOARD2_TEXT_PREDICTED_SEED_SIZE, keyboard2_seed.getBuffer());

			if(Unicode::strlen(keyboard2_text_typed_seedBuffer) >= 3){
				Unicode::toUTF8(keyboard2_text_predicted_seedBuffer, str_prediction, KEYBOARD2_TEXT_PREDICTED_SEED_SIZE);

				switch(text_type)
				{
				case TEXT_TYPE_NONE:
				default:
					valid_word = false;
					break;

				case TEXT_TYPE_BIP39:
					valid_word = getBip39Word((char *) str_prediction);
					break;

				case TEXT_TYPE_SLIP39:
					valid_word = getSlip39Word((char *) str_prediction);
					break;

				case TEXT_TYPE_XMR:
					valid_word = getXmrWord((char *) str_prediction);
					break;
				}

				Unicode::snprintf(keyboard2_text_predicted_seedBuffer, KEYBOARD2_TEXT_PREDICTED_SEED_SIZE, (char *) str_prediction);
				keyboard2_text_predicted_seed.setVisible(true);
				keyboard2_text_typed_seed.setVisible(false);
			}
			else{
				keyboard2_text_predicted_seed.setVisible(false);
				keyboard2_text_typed_seed.setVisible(true);
				valid_word = false;
			}

			if(valid_word == true){
				keyboard2_text_predicted_seed.setColor(touchgfx::Color::getColorFromRGB(0x14,0x8E,0x53));
			}
			else{
				keyboard2_text_predicted_seed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
			}

			keyboard2_text_area_seed.invalidate();
		}
	}

	/*** Seed's - Keyboard 3 (passphrase) ***/
	if(keyboard3_seed.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard3_text_typed_seedBuffer, keyboard3_seed.getBuffer(), KEYBOARD3_TEXT_TYPED_SEED_SIZE) != 0)
		{
			Unicode::snprintf(keyboard3_text_typed_seedBuffer, KEYBOARD3_TEXT_TYPED_SEED_SIZE, keyboard3_seed.getBuffer());
			keyboard3_text_typed_seed.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);

			num_of_lines = keyboard3_text_typed_seed.getTextWidth()/230;

			if(num_of_lines > 1){
				keyboard3_text_typed_seed.setPosition(60, 50-((num_of_lines-1)*20), 230, 60+((num_of_lines-1)*20));
			}
			else{
				keyboard3_text_typed_seed.setPosition(60, 50, 230, 60);
			}

			Unicode::itoa(Unicode::strlen(keyboard3_text_typed_seedBuffer), keyboard3_char_count_seedBuffer, KEYBOARD3_CHAR_COUNT_SEED_SIZE, 10);

			keyboard3_text_area_seed.invalidate();
		}

		if(flag_refresh_text_area == 1)
		{
			num_of_lines = keyboard3_text_typed_seed.getTextWidth()/230;

			if(num_of_lines > 1){
				keyboard3_text_typed_seed.setPosition(60, 50-((num_of_lines-1)*20), 230, 60+((num_of_lines-1)*20));
				keyboard3_text_area_seed.invalidate();
			}

			flag_refresh_text_area = 0;
		}
	}

	/*** PlainText - Keyboard (plain text) ***/
	if(keyboard_plain_text.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard_text_typed_plain_textBuffer, keyboard_plain_text.getBuffer(), KEYBOARD_TEXT_TYPED_PLAIN_TEXT_SIZE) != 0)
		{
			Unicode::snprintf(keyboard_text_typed_plain_textBuffer, KEYBOARD_TEXT_TYPED_PLAIN_TEXT_SIZE, keyboard_plain_text.getBuffer());
			keyboard_text_typed_plain_text.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);

			num_of_lines = keyboard_text_typed_plain_text.getTextWidth()/230;

			if(num_of_lines > 1){
				keyboard_text_typed_plain_text.setPosition(60, 50-((num_of_lines-1)*20), 230, 60+((num_of_lines-1)*20));
			}
			else{
				keyboard_text_typed_plain_text.setPosition(60, 50, 230, 60);
			}

			Unicode::itoa(Unicode::strlen(keyboard_text_typed_plain_textBuffer), keyboard_char_count_plain_textBuffer, KEYBOARD_CHAR_COUNT_PLAIN_TEXT_SIZE, 10);

			keyboard_text_area_plain_text.invalidate();
		}

		if(flag_refresh_text_area == 1)
		{
			num_of_lines = keyboard_text_typed_plain_text.getTextWidth()/230;

			if(num_of_lines > 1){
				keyboard_text_typed_plain_text.setPosition(60, 50-((num_of_lines-1)*20), 230, 60+((num_of_lines-1)*20));
				keyboard_text_area_plain_text.invalidate();
			}

			flag_refresh_text_area = 0;
		}
	}

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
void screen_flow_2View::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::changeStateNfc(uint8_t state)
{
	presenter->changeStateNfc(state);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::updateStateNfc(uint16_t state)
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

			if(text_type == TEXT_TYPE_FROM_NFC_BIP39){
				wait_read_write_nfc_text.setTypedText(touchgfx::TypedText(T_SF2_S6_WAIT_READ_NFC_FROMNFC_TEXT));
			}

			if(total_pwds != mandatory_pwds){
				screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_2_T4T_8K);
			}
			else{
				screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_2);
			}
		}
		else if(s1_fromNFC_1_initNFC.isVisible())
		{
			s1_fromNFC_1_initNFC.setVisible(false);
			s1_fromNFC_2_waitReadNFC.setVisible(true);
			s1_fromNFC_3_error.setVisible(false);
			screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_FROM_NFC);
		}
		break;

	case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_2:
	case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_2_T4T_8K:
		if(s6_waitReadWriteNFC.isVisible())
		{
			if((state == MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_2_T4T_8K) && (cuvex.nfc.tag.type != NFC_TAG_TYPE_T4T_8K))	//Error 1, the card being written has not correct format
			{
				s6_waitReadWriteNFC.setVisible(false);
				s7_writeError.setVisible(true);
				text_error_cryptogram.setVisible(false);
				text_error_tag_format.setVisible(true);
				image_error.setVisible(true);
				screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
			}
			else if(cuvex.nfc.tag.encripted == true)		//Error 2, the card being written to already has a stored cryptogram
			{
				s6_waitReadWriteNFC.setVisible(false);
				s7_writeError.setVisible(true);
				text_error_cryptogram.setVisible(true);
				text_error_tag_format.setVisible(false);
				image_error.setVisible(false);
				screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
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
				screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
			}
		}
		break;

	case MAIN_TO_GUI_NFC_TAG_READED_FROM_NFC:
		if(s1_fromNFC_2_waitReadNFC.isVisible())
		{
			screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
			checkDataFromNFC();
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
void screen_flow_2View::hideKeyboard1SeedPressed()
{
	keyboard1_text_info_seed.setPosition(0, 90, 320, 20);
	keyboard1_text_typed_seed.setPosition(76, 125, 169, 20);
	keyboard1_text_area_seed.setXY(45, 120);
	keyboard1_btn_enter_seed.setPosition(245, 120, 30, 30);

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard1_seed.setVisible(false);
	keyboard1_btn_hide_seed.setVisible(false);
	keyboard1_btn_show_seed.setVisible(true);
	keyboard1_btn_enter_seed.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::showKeyboard1SeedPressed()
{
	keyboard1_text_info_seed.setPosition(0, 40, 320, 20);
	keyboard1_text_typed_seed.setPosition(76, 75, 169, 20);
	keyboard1_text_area_seed.setXY(45, 70);
	keyboard1_btn_enter_seed.setPosition(245, 70, 30, 30);

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard1_seed.setVisible(true);
	keyboard1_btn_hide_seed.setVisible(true);
	keyboard1_btn_show_seed.setVisible(false);
	keyboard1_btn_enter_seed.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::enterKeyboard1SeedPressed()
{
	total_words = Unicode::atoi(keyboard1_text_typed_seedBuffer);
	actual_word = 1;

	if((total_words > 0) && (total_words <= 54))
	{
		/*** Editing information in the next sub-screen ***/
		Unicode::snprintf(keyboard2_text_info_seedBuffer1, KEYBOARD2_TEXT_INFO_SEEDBUFFER1_SIZE, "%d", actual_word);
		Unicode::snprintf(keyboard2_text_info_seedBuffer2, KEYBOARD2_TEXT_INFO_SEEDBUFFER2_SIZE, "%d", total_words);

		/*** Clearing keyboard and display buffers ***/
		memset(keyboard1_text_typed_seedBuffer, 0x00, sizeof(keyboard1_text_typed_seedBuffer));
		keyboard1_seed.clearBuffer();

		/*** Selecting visible/hidden elements on the screen ***/
		s1_seed_1_typeNumWords.setVisible(false);
		s1_seed_2_typeWords.setVisible(true);

		/*** Screen update ***/
		background.invalidate();
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
void screen_flow_2View::hideKeyboard2SeedPressed()
{
	keyboard2_text_info_seed.setPosition(0, 90, 320, 20);
	keyboard2_text_typed_seed.setPosition(76, 125, 169, 20);
	keyboard2_text_predicted_seed.setPosition(76, 125, 169, 20);
	keyboard2_text_area_seed.setXY(45, 120);
	keyboard2_btn_enter_seed.setPosition(245, 120, 30, 30);

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard2_seed.setVisible(false);
	keyboard2_btn_hide_seed.setVisible(false);
	keyboard2_btn_show_seed.setVisible(true);
	keyboard2_btn_enter_seed.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::showKeyboard2SeedPressed()
{
	keyboard2_text_info_seed.setPosition(0, 40, 320, 20);
	keyboard2_text_typed_seed.setPosition(76, 75, 169, 20);
	keyboard2_text_predicted_seed.setPosition(76, 75, 169, 20);
	keyboard2_text_area_seed.setXY(45, 70);
	keyboard2_btn_enter_seed.setPosition(245, 70, 30, 30);

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard2_seed.setVisible(true);
	keyboard2_btn_hide_seed.setVisible(true);
	keyboard2_btn_show_seed.setVisible(false);
	keyboard2_btn_enter_seed.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::enterKeyboard2SeedPressed()
{
	if((keyboard2_text_typed_seedBuffer[0] != 0x00) && (valid_word == true))
	{
		/*** Obtaining the typed text (seed words.. UTF-8 format...) ***/
		Unicode::toUTF8(keyboard2_text_typed_seedBuffer, words_to_encrypt[actual_word-1], KEYBOARD2_TEXT_TYPED_SEED_SIZE);
		Unicode::toUTF8(keyboard2_text_predicted_seedBuffer, words_to_check[actual_word-1], KEYBOARD2_TEXT_PREDICTED_SEED_SIZE);

		/*** Clearing keyboard and display buffers ***/
		memset(keyboard2_text_typed_seedBuffer, 0x00, sizeof(keyboard2_text_typed_seedBuffer));
		memset(keyboard2_text_predicted_seedBuffer, 0x00, sizeof(keyboard2_text_predicted_seedBuffer));
		keyboard2_seed.clearBuffer();

		/*** Selecting visible/hidden elements on the screen ***/
		if(actual_word == total_words){
			s1_seed_2_typeWords.setVisible(false);
			s1_seed_3_typePassphrase.setVisible(true);
		}
		else{
			Unicode::snprintf(keyboard2_text_info_seedBuffer1, KEYBOARD2_TEXT_INFO_SEEDBUFFER1_SIZE, "%d", ++actual_word);
			Unicode::snprintf(keyboard2_text_info_seedBuffer2, KEYBOARD2_TEXT_INFO_SEEDBUFFER2_SIZE, "%d", total_words);
		}

		/*** Screen update ***/
		background.invalidate();
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
void screen_flow_2View::hideKeyboard3SeedPressed()
{
	keyboard3_text_area_seed.setPosition(20, 40, 280, 160);
	keyboard3_text_typed_seed.setPosition(60, 50, 230, 140);
	keyboard3_btn_up_seed.setPosition(30, 50, 20, 20);
	keyboard3_btn_down_seed.setPosition(30, 170, 20, 20);
	keyboard3_char_count_seed.setPosition(250, 188, 50, 12);

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard3_seed.setVisible(false);
	keyboard3_btn_hide_seed.setVisible(false);
	keyboard3_btn_show_seed.setVisible(true);
	keyboard3_btn_enter_seed.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::showKeyboard3SeedPressed()
{
	keyboard3_text_area_seed.setPosition(20, 40, 280, 70);
	keyboard3_text_typed_seed.setPosition(60, 50, 230, 60);
	keyboard3_btn_up_seed.setPosition(30, 50, 20, 20);
	keyboard3_btn_down_seed.setPosition(30, 80, 20, 20);
	keyboard3_char_count_seed.setPosition(250, 98, 50, 12);

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard3_seed.setVisible(true);
	keyboard3_btn_hide_seed.setVisible(true);
	keyboard3_btn_show_seed.setVisible(false);
	keyboard3_btn_enter_seed.setVisible(false);

	/*** Screen update ***/
	background.invalidate();

	/*** Auxiliar flag ***/
	flag_refresh_text_area = 1;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::enterKeyboard3SeedPressed()
{
	char buff_aux1[TYPED_CHECK_SEED_SIZE] = {0}, buff_aux2[15] = {0};

	memset(buff_passphrase, 0x00, KEYBOARD3_TEXT_TYPED_SEED_SIZE);
	memset(typed_check_seedBuffer, 0x00, TYPED_CHECK_SEED_SIZE);

	/*** Obtaining the typed text (passphrase) ***/
	for(int i=0; i<KEYBOARD3_TEXT_TYPED_SEED_SIZE; i++)
	{
		if(keyboard3_text_typed_seedBuffer[i] == 8364){	//If '€' (8364) is converted to the character '¶' (182) to only occupy 1 byte
			buff_passphrase[i] = 182;
		}
		else{
			buff_passphrase[i] = (uint8_t) keyboard3_text_typed_seedBuffer[i];
		}
	}

	/*** Generating an array for displaying words + passphrase ***/
	for(int i=0; i<total_words; i++)
	{
		snprintf(buff_aux2, 15, "%d. ", i+1);
		strcat(buff_aux1, (char *) buff_aux2);
		strcat(buff_aux1, (char *) words_to_check[i]);
		strcat(buff_aux1, (char *) "\n");
	}

	strcat(buff_aux1, (char*) "\nPassphrase:\n");
	strcat(buff_aux1, (char*) buff_passphrase);

	/*** Assignment of words + passphrase to be displayed in "scrollable" field ***/
	for(int i=0; i<TYPED_CHECK_SEED_SIZE; i++)
	{
		if(buff_aux1[i] == 182){	//If '¶' (182) is converted to the character '€' (8364) for display on screen
			typed_check_seedBuffer[i] = 8364;
		}
		else{
			typed_check_seedBuffer[i] = buff_aux1[i];
		}
	}

	typed_check_seed.setPosition(0, 0, 210, (20*(total_words+1))+(20*7));
	typed_check_seed.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);

	/*** Clearing keyboard and display buffers ***/
	memset(keyboard3_text_typed_seedBuffer, 0x00, sizeof(keyboard3_text_typed_seedBuffer));
	keyboard3_seed.clearBuffer();

	/*** Selecting visible/hidden elements on the screen ***/
	s1_seed_3_typePassphrase.setVisible(false);
	s1_checkInfo.setVisible(true);
	s1_checkInfo_Seed.setVisible(true);

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
void screen_flow_2View::hideKeyboardPlainTextPressed()
{
	keyboard_text_area_plain_text.setPosition(20, 40, 280, 160);
	keyboard_text_typed_plain_text.setPosition(60, 50, 230, 140);
	keyboard_btn_up_plain_text.setPosition(30, 50, 20, 20);
	keyboard_btn_down_plain_text.setPosition(30, 170, 20, 20);
	keyboard_char_count_plain_text.setPosition(250, 188, 50, 12);

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard_plain_text.setVisible(false);
	keyboard_btn_hide_plain_text.setVisible(false);
	keyboard_btn_show_plain_text.setVisible(true);
	keyboard_btn_enter_plain_text.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::showKeyboardPlainTextPressed()
{
	keyboard_text_area_plain_text.setPosition(20, 40, 280, 70);
	keyboard_text_typed_plain_text.setPosition(60, 50, 230, 60);
	keyboard_btn_up_plain_text.setPosition(30, 50, 20, 20);
	keyboard_btn_down_plain_text.setPosition(30, 80, 20, 20);
	keyboard_char_count_plain_text.setPosition(250, 98, 50, 12);

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard_plain_text.setVisible(true);
	keyboard_btn_hide_plain_text.setVisible(true);
	keyboard_btn_show_plain_text.setVisible(false);
	keyboard_btn_enter_plain_text.setVisible(false);

	/*** Screen update ***/
	background.invalidate();

	/*** Auxiliar flag ***/
	flag_refresh_text_area = 1;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::enterKeyboardPlainTextPressed()
{
	if(keyboard_text_typed_plain_textBuffer[0] != 0x00)
	{
		memset(buff_plain_text, 0x00, KEYBOARD_TEXT_TYPED_PLAIN_TEXT_SIZE);
		memset(typed_check_plain_textBuffer, 0x00, TYPED_CHECK_PLAIN_TEXT_SIZE);

		/*** Obtaining the typed text (plain text) ***/
		for(int i=0; i<KEYBOARD_TEXT_TYPED_PLAIN_TEXT_SIZE; i++)
		{
			if(keyboard_text_typed_plain_textBuffer[i] == 8364){	//If '€' (8364) is converted to the character '¶' (182) to only occupy 1 byte
				buff_plain_text[i] = 182;
			}
			else{
				buff_plain_text[i] = (uint8_t) keyboard_text_typed_plain_textBuffer[i];
			}
		}

		/*** Assignment of plain text to be displayed in "scrollable" field ***/
		for(int i=0; i<KEYBOARD_TEXT_TYPED_PLAIN_TEXT_SIZE; i++)
		{
			if(buff_plain_text[i] == 182){	//If '¶' (182) is converted to the character '€' (8364) for display on screen
				typed_check_plain_textBuffer[i] = 8364;
			}
			else{
				typed_check_plain_textBuffer[i] = buff_plain_text[i];
			}
		}

		typed_check_plain_text.setPosition(0, 0, 220, 20*(typed_check_plain_text.getTextWidth()/220)+2*20);
		typed_check_plain_text.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);

		/*** Clearing keyboard and display buffers ***/
		memset(keyboard_text_typed_plain_textBuffer, 0x00, sizeof(keyboard_text_typed_plain_textBuffer));
		keyboard_plain_text.clearBuffer();

		/*** Selecting visible/hidden elements on the screen ***/
		s1_plainText_1_typePlainText.setVisible(false);
		s1_checkInfo.setVisible(true);
		s1_checkInfo_PlainText.setVisible(true);

		/*** Screen update ***/
		background.invalidate();
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
void screen_flow_2View::hideKeyboardPasswordPressed()
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
void screen_flow_2View::show1KeyboardPasswordPressed()
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
void screen_flow_2View::show2KeyboardPasswordPressed()
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
void screen_flow_2View::enterKeyboardPasswordPressed()
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
void screen_flow_2View::hideKeyboardAliasPressed()
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
void screen_flow_2View::showKeyboardAliasPressed()
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
void screen_flow_2View::enterKeyboardAliasPressed()
{
	if(keyboard_text_typed_aliasBuffer[0] != 0x00)
	{
		/*** Generation of the records data ***/
		screen_flow_2View::generateRecordData1_Alias();
		screen_flow_2View::generateRecordData2_Cryptogram();
		screen_flow_2View::generateRecordData3_Information();

		if(total_pwds != mandatory_pwds){
			screen_flow_2View::generateRecordData4_Multisignature();
		}

		/*** Clearing keyboard and display buffers ***/
		memset(keyboard_text_typed_aliasBuffer, 0x00, sizeof(keyboard_text_typed_aliasBuffer));
		keyboard_alias.clearBuffer();

		/*** Enabling NFC to allow reading/writing ***/
		screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);

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
void screen_flow_2View::menuBip39Pressed()
{
	/*** Update variable of type of text to encrypt ***/
	text_type = TEXT_TYPE_BIP39;

	/*** Selecting visible/hidden elements on the screen ***/
	s0_menuSelection.setVisible(false);
	s1_menuContent.setVisible(true);
	s1_seed.setVisible(true);
	s1_plainText.setVisible(false);
	s1_fromNFC.setVisible(false);
	s1_checkInfo.setVisible(false);
	s1_seed_1_typeNumWords.setVisible(true);
	s1_seed_2_typeWords.setVisible(false);
	s1_seed_3_typePassphrase.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::menuSlip39Pressed()
{
	/*** Update variable of type of text to encrypt ***/
	text_type = TEXT_TYPE_SLIP39;

	/*** Selecting visible/hidden elements on the screen ***/
	s0_menuSelection.setVisible(false);
	s1_menuContent.setVisible(true);
	s1_seed.setVisible(true);
	s1_plainText.setVisible(false);
	s1_fromNFC.setVisible(false);
	s1_checkInfo.setVisible(false);
	s1_seed_1_typeNumWords.setVisible(true);
	s1_seed_2_typeWords.setVisible(false);
	s1_seed_3_typePassphrase.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::menuXmrPressed()
{
	/*** Update variable of type of text to encrypt ***/
	text_type = TEXT_TYPE_XMR;

	/*** Selecting visible/hidden elements on the screen ***/
	s0_menuSelection.setVisible(false);
	s1_menuContent.setVisible(true);
	s1_seed.setVisible(true);
	s1_plainText.setVisible(false);
	s1_fromNFC.setVisible(false);
	s1_checkInfo.setVisible(false);
	s1_seed_1_typeNumWords.setVisible(true);
	s1_seed_2_typeWords.setVisible(false);
	s1_seed_3_typePassphrase.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::menuPlainTextPressed()
{
	/*** Update variable of type of text to encrypt ***/
	text_type = TEXT_TYPE_PLAINTEXT;

	/*** Selecting visible/hidden elements on the screen ***/
	s0_menuSelection.setVisible(false);
	s1_menuContent.setVisible(true);
	s1_seed.setVisible(false);
	s1_plainText.setVisible(true);
	s1_fromNFC.setVisible(false);
	s1_checkInfo.setVisible(false);
	s1_plainText_1_typePlainText.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::menuTextFromNfcPressed()
{
	/*** Enabling NFC to allow reading/writing ***/
	screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);

	/*** Selecting visible/hidden elements on the screen ***/
	s0_menuSelection.setVisible(false);
	s1_menuContent.setVisible(true);
	s1_seed.setVisible(false);
	s1_plainText.setVisible(false);
	s1_fromNFC.setVisible(true);
	s1_checkInfo.setVisible(false);
	s1_fromNFC_1_initNFC.setVisible(true);
	s1_fromNFC_2_waitReadNFC.setVisible(false);
	s1_fromNFC_3_error.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::encryptPressed()
{
	/*** Selecting visible/hidden elements on the screen ***/
	s1_menuContent.setVisible(false);
	s2_multiSignature.setVisible(true);
	s2_1_askMultiSignature.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::successPressed()
{
	NVIC_SystemReset();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::eye1Pressed()
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
void screen_flow_2View::eye2Pressed()
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

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::retryPressed()
{
	/*** Enabling NFC to allow reading/writing ***/
	screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);

	/*** Selecting visible/hidden elements on the screen ***/
	s7_writeError.setVisible(false);
	s5_initNFC.setVisible(true);

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
void screen_flow_2View::passwordSuccessPressed()
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
void screen_flow_2View::multisignedYesPressed()
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
void screen_flow_2View::multisignedNoPressed()
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
void screen_flow_2View::multisignedPlusPressed()
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
void screen_flow_2View::multisignedMinusPressed()
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
void screen_flow_2View::multisignedSelectPressed()
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
void screen_flow_2View::btnUpPressed()
{
	uint8_t aux = 0;

	if(s1_seed.isVisible() == true)
	{
		aux = keyboard3_text_typed_seed.getTextWidth()/230;

		if(aux != 0)	//Multi-line
		{
			if(keyboard3_text_area_seed.getHeight() == 70)		//Small box
			{
				if(keyboard3_text_typed_seed.getHeight() > 60){
					keyboard3_text_typed_seed.setPosition(60, keyboard3_text_typed_seed.getY() + 20, 230, keyboard3_text_typed_seed.getHeight() - 20);
				}
			}
			else if(keyboard3_text_area_seed.getHeight() == 160)	//Big box
			{
				if(keyboard3_text_typed_seed.getHeight() > 140){
					keyboard3_text_typed_seed.setPosition(60, keyboard3_text_typed_seed.getY() + 20, 230, keyboard3_text_typed_seed.getHeight() - 20);
				}
			}

			keyboard3_text_area_seed.invalidate();
		}
	}
	else if(s1_plainText.isVisible() == true)
	{
		aux = keyboard_text_typed_plain_text.getTextWidth()/230;

		if(aux != 0)	//Multi-line
		{
			if(keyboard_text_area_plain_text.getHeight() == 70)		//Small box
			{
				if(keyboard_text_typed_plain_text.getHeight() > 60){
					keyboard_text_typed_plain_text.setPosition(60, keyboard_text_typed_plain_text.getY() + 20, 230, keyboard_text_typed_plain_text.getHeight() - 20);
				}
			}
			else if(keyboard_text_area_plain_text.getHeight() == 160)	//Big box
			{
				if(keyboard_text_typed_plain_text.getHeight() > 140){
					keyboard_text_typed_plain_text.setPosition(60, keyboard_text_typed_plain_text.getY() + 20, 230, keyboard_text_typed_plain_text.getHeight() - 20);
				}
			}

			keyboard_text_area_plain_text.invalidate();
		}
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::btnDownPressed()
{
	uint8_t num_of_lines = 0;

	if(s1_seed.isVisible() == true)
	{
		num_of_lines = keyboard3_text_typed_seed.getTextWidth()/230;

		if(num_of_lines)
		{
			if(keyboard3_text_area_seed.getHeight() == 70)		//Small box
			{
				if(keyboard3_text_typed_seed.getHeight() < 60+(20*num_of_lines)){
					keyboard3_text_typed_seed.setPosition(60, keyboard3_text_typed_seed.getY() - 20, 230, keyboard3_text_typed_seed.getHeight() + 20);
				}
			}
			else if(keyboard3_text_area_seed.getHeight() == 160)	//Big box
			{
				if(keyboard3_text_typed_seed.getHeight() < 140+(20*num_of_lines)){
					keyboard3_text_typed_seed.setPosition(60, keyboard3_text_typed_seed.getY() - 20, 230, keyboard3_text_typed_seed.getHeight() + 20);
				}
			}
			keyboard3_text_area_seed.invalidate();
		}
	}
	else if(s1_plainText.isVisible() == true)
	{
		num_of_lines = keyboard_text_typed_plain_text.getTextWidth()/230;

		if(num_of_lines != 0)
		{
			if(keyboard_text_area_plain_text.getHeight() == 70)		//Small box
			{
				if(keyboard_text_typed_plain_text.getHeight() < 60+(20*num_of_lines)){
					keyboard_text_typed_plain_text.setPosition(60, keyboard_text_typed_plain_text.getY() - 20, 230, keyboard_text_typed_plain_text.getHeight() + 20);
				}
			}
			else if(keyboard_text_area_plain_text.getHeight() == 160)	//Big box
			{
				if(keyboard_text_typed_plain_text.getHeight() < 140+(20*num_of_lines)){
					keyboard_text_typed_plain_text.setPosition(60, keyboard_text_typed_plain_text.getY() - 20, 230, keyboard_text_typed_plain_text.getHeight() + 20);
				}
			}
			keyboard_text_area_plain_text.invalidate();
		}
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::btnScrollUpPressed()
{
	switch(text_type)
	{
	case TEXT_TYPE_NONE:
	default:
		break;

	case TEXT_TYPE_BIP39:
	case TEXT_TYPE_SLIP39:
	case TEXT_TYPE_XMR:
		if(typed_check_seed.getY() < 0){
			typed_check_seed.setPosition(0, typed_check_seed.getY() + 20, 210, (20*(total_words+1))+(20*7));
		}
		scrollable_container_typed_check_seed.invalidate();
		break;

	case TEXT_TYPE_PLAINTEXT:
	case TEXT_TYPE_FROM_NFC_PLAINTEXT:
		if(typed_check_plain_text.getY() < 0){
			typed_check_plain_text.setPosition(0, typed_check_plain_text.getY() + 20, 220, 20*(typed_check_plain_text.getTextWidth()/220)+2*20);
		}
		scrollable_container_typed_check_plain_text.invalidate();
		break;

	case TEXT_TYPE_FROM_NFC_BIP39:
		if(typed_check_seed.getY() < 0){
			typed_check_seed.setPosition(0, typed_check_seed.getY() + 20, 210, (20*(total_words+1))+(4*20*7));
		}
		scrollable_container_typed_check_seed.invalidate();
		break;
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::btnScrollDownPressed()
{
	switch(text_type)
	{
	case TEXT_TYPE_NONE:
	default:
		break;

	case TEXT_TYPE_BIP39:
	case TEXT_TYPE_SLIP39:
	case TEXT_TYPE_XMR:
		if((typed_check_seed.getY() + 20*(total_words+1)+(20*7)) > 0){
			typed_check_seed.setPosition(0, typed_check_seed.getY() - 20, 210, (20*(total_words+1))+(20*7));
		}
		scrollable_container_typed_check_seed.invalidate();
		break;

	case TEXT_TYPE_PLAINTEXT:
	case TEXT_TYPE_FROM_NFC_PLAINTEXT:
		if((typed_check_plain_text.getY() + (20*(typed_check_plain_text.getTextWidth()/220))-1*20) > 0){
			typed_check_plain_text.setPosition(0, typed_check_plain_text.getY() - 20, 220, 20*(typed_check_plain_text.getTextWidth()/220)+2*20);
		}
		scrollable_container_typed_check_plain_text.invalidate();
		break;

	case TEXT_TYPE_FROM_NFC_BIP39:
		if((typed_check_seed.getY() + 20*(total_words+1))+(4*20*7) > 0){
			typed_check_seed.setPosition(0, typed_check_seed.getY() - 20, 210, (20*(total_words+1))+(4*20*7));
		}
		scrollable_container_typed_check_seed.invalidate();
		break;
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
void screen_flow_2View::btnFromNfcErrorPressed()
{
	/*** Enabling NFC to allow reading/writing ***/
	screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);

	/*** Selecting visible/hidden elements on the screen ***/
	s1_fromNFC_1_initNFC.setVisible(true);
	s1_fromNFC_2_waitReadNFC.setVisible(false);
	s1_fromNFC_3_error.setVisible(false);

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
void screen_flow_2View::setScreenMode()
{
	/*** Setting screen elements based on mode (dark/light) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_seed_bip39.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_seed_bip39.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_seed_slip39.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_seed_slip39.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_seed_xmr.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_seed_xmr.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_plain_text.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_plain_text.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_text_from_nfc.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_text_from_nfc.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		keyboard1_text_typed_seed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard1_text_info_seed.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard2_text_typed_seed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard2_text_predicted_seed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard2_text_info_seed.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard3_text_area_seed.setColor(touchgfx::Color::getColorFromRGB(0xFF,0xFF,0xFF));
		keyboard3_btn_enter_seed.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard3_btn_enter_seed.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard3_text_typed_seed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		typed_check_seed.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard3_text_info_1_seed.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard3_text_info_2_seed.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_text_area_plain_text.setColor(touchgfx::Color::getColorFromRGB(0xFF,0xFF,0xFF));
		keyboard_btn_enter_plain_text.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_btn_enter_plain_text.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_text_typed_plain_text.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_info_plain_text.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		typed_check_plain_text.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_encrypt.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_encrypt.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
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
		s1_fromNFC_1_init_nfc_text1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		s1_fromNFC_1_init_nfc_text2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		s1_fromNFC_wait_read_nfc_text.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		s1_fromNFC_error_text.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		s1_fromNFC_error_btn.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		s1_fromNFC_error_btn.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
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
void screen_flow_2View::setScreenLanguage()
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
void screen_flow_2View::generateRecordData1_Alias()
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
void screen_flow_2View::generateRecordData2_Cryptogram()
{
	uint8_t text_to_encrypt[SIZE_CRYPT] = {0};
	uint16_t pwd_raw_length = SIGNATURE_SIZE;
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
	pwd_raw_length = pwd_raw_length + pwd0_length + pwd1_length + pwd2_length + pwd3_length + pwd4_length + pwd5_length;

	strncat((char*) pwd_raw, (const char*) cuvex.signature_buffer, SIGNATURE_SIZE);
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
	memset(header_aes_gcm, 0x00, sizeof(header_aes_gcm));
	configAESPeripheral(pwd_sha256, iv_aes_gcm, header_aes_gcm);

	/*** Generating text to encrypt (BIP39 seed, plaintext) + AES-256 Encryption ***/
	switch(text_type)
	{
	case TEXT_TYPE_NONE:
	default:
		break;

	case TEXT_TYPE_BIP39:
		strcat((char*) text_to_encrypt, (const char*) "[bip39]");

		for(int i=0; i<total_words; i++){
			strcat((char*) text_to_encrypt, (const char*) ",");
			strcat((char*) text_to_encrypt, (const char*) words_to_encrypt[i]);
		}

		strcat((char*) text_to_encrypt, (const char*) "[passphrase]");
		strcat((char*) text_to_encrypt, (char*) buff_passphrase);

		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_cryptogram, HAL_MAX_DELAY);
		break;

	case TEXT_TYPE_SLIP39:
		strcat((char*) text_to_encrypt, (const char*) "[slip39]");

		for(int i=0; i<total_words; i++){
			strcat((char*) text_to_encrypt, (const char*) ",");
			strcat((char*) text_to_encrypt, (const char*) words_to_encrypt[i]);
		}

		strcat((char*) text_to_encrypt, (const char*) "[passphrase]");
		strcat((char*) text_to_encrypt, (char*) buff_passphrase);

		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_cryptogram, HAL_MAX_DELAY);
		break;

	case TEXT_TYPE_XMR:
		strcat((char*) text_to_encrypt, (const char*) "[xmr]");

		for(int i=0; i<total_words; i++){
			strcat((char*) text_to_encrypt, (const char*) ",");
			strcat((char*) text_to_encrypt, (const char*) words_to_encrypt[i]);
		}

		strcat((char*) text_to_encrypt, (const char*) "[passphrase]");
		strcat((char*) text_to_encrypt, (char*) buff_passphrase);

		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_cryptogram, HAL_MAX_DELAY);
		break;

	case TEXT_TYPE_PLAINTEXT:
		strcat((char*) text_to_encrypt, (char*) "[plain-text]");
		strcat((char*) text_to_encrypt, (char*) buff_plain_text);

		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_cryptogram, HAL_MAX_DELAY);
		break;

	case TEXT_TYPE_FROM_NFC_PLAINTEXT:
		strcat((char*) text_to_encrypt, (char*) "{plain-text}");
		strcat((char*) text_to_encrypt, (char*) buff_plain_text);

		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_cryptogram, HAL_MAX_DELAY);
		break;

	case TEXT_TYPE_FROM_NFC_BIP39:
		strcat((char*) text_to_encrypt, (const char*) "{bip39}");

		for(int i=0; i<total_words; i++){
			strcat((char*) text_to_encrypt, (const char*) ",");
			strcat((char*) text_to_encrypt, (const char*) words_to_encrypt[i]);
		}

		strcat((char*) text_to_encrypt, (const char*) "{passder}");
		strcat((char*) text_to_encrypt, (char*) cuvex.nfc.tag.from_nfc_pass_deriv);
		strcat((char*) text_to_encrypt, (const char*) "{prikey}");
		strcat((char*) text_to_encrypt, (char*) cuvex.nfc.tag.from_nfc_private_key);
		strcat((char*) text_to_encrypt, (const char*) "{pubkey}");
		strcat((char*) text_to_encrypt, (char*) cuvex.nfc.tag.from_nfc_public_key);

		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_cryptogram, HAL_MAX_DELAY);
		break;
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::generateRecordData3_Information()
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
void screen_flow_2View::generateRecordData4_Multisignature()
{
	char comb_buffer[10][KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE] = {0};

	memset(cuvex.nfc.tag.new_multisignature, 0x00, SIZE_MULTISIGN);
	generateCombinations(0, 0, comb_buffer);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::configAESPeripheral(uint8_t keyAES[], uint8_t ivAES[], uint8_t headerAES[])
{
	HAL_CRYP_DeInit(&hcryp);

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
void screen_flow_2View::checkDataFromNFC()
{
	char buff1_check_all[TYPED_CHECK_SEED_SIZE] = {0};
	char buff2_words_index[15] = {0};
	char buff3_passphrase[100] = {0};
	char buff4_derivation1[100] = {0};
	char buff5_derivation2[100] = {0};
	int aux = 0, j = 0;

	switch(cuvex.nfc.tag.from_nfc_type)
	{
	default: //bad format
	case 0:
		/*** Selecting visible/hidden elements on the screen ***/
		s1_fromNFC_2_waitReadNFC.setVisible(false);
		s1_fromNFC_3_error.setVisible(true);
		break;

	case 1:	//seed bip-39
		text_type = TEXT_TYPE_FROM_NFC_BIP39;

		/*** Get seed "words" in screen format ***/
		for(int i=0; i<strlen((char *) cuvex.nfc.tag.from_nfc_seed); i++)
		{
			if(cuvex.nfc.tag.from_nfc_seed[i] == ','){
				total_words++;
				index_words = 0;
			}
			else{
				words_to_encrypt[total_words][index_words++] = cuvex.nfc.tag.from_nfc_seed[i];
			}
		}

		total_words++;

		for(int j=0; j<total_words; j++){
			for(int i=0; i<5; i++){
				words_to_check[j][i] = words_to_encrypt[j][i];
			}
			getBip39Word((char *) words_to_check[j]);
		}

		/*** Get seed "passphrase" + "derivation path" + "private key" + "public key" in screen format ***/
		for(int i=1; i<strlen((char *) cuvex.nfc.tag.from_nfc_pass_deriv); i++)
		{
			if(aux == 0)
			{
				if((cuvex.nfc.tag.from_nfc_pass_deriv[i] == ',') && (cuvex.nfc.tag.from_nfc_pass_deriv[i+1] == ' ') && (cuvex.nfc.tag.from_nfc_pass_deriv[i+17] == ',') && (cuvex.nfc.tag.from_nfc_pass_deriv[i+18] == ' '))
				{
					aux = 1;
					i = i+18;
					j = 0;
				}
				else{
					buff3_passphrase[j++] = cuvex.nfc.tag.from_nfc_pass_deriv[i];
				}
			}
			else if(aux == 1)
			{
				if((cuvex.nfc.tag.from_nfc_pass_deriv[i] == ',') && (cuvex.nfc.tag.from_nfc_pass_deriv[i+1] == ' ')){
					aux = 2;
					i = i+1;
					j = 0;
				}
				else{
					buff4_derivation1[j++] = cuvex.nfc.tag.from_nfc_pass_deriv[i];
				}
			}
			else if(aux == 2)
			{
				if(cuvex.nfc.tag.from_nfc_pass_deriv[i] != '"'){
					buff5_derivation2[j++] = cuvex.nfc.tag.from_nfc_pass_deriv[i];
				}
			}
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
		strcat(buff1_check_all, (char*) buff3_passphrase);

		strcat(buff1_check_all, (char*) "\n____________________\n\n");
		strcat(buff1_check_all, (char*) buff4_derivation1);
		strcat(buff1_check_all, (char*) "\n\nDerivation Path:\n");
		strcat(buff1_check_all, (char*) buff5_derivation2);

		strcat(buff1_check_all, (char*) "\n____________________\n\n");
		strcat(buff1_check_all, (char*) "Master Private Key:\n");
		strcat(buff1_check_all, (char*) cuvex.nfc.tag.from_nfc_private_key);

		strcat(buff1_check_all, (char*) "\n____________________\n\n");
		strcat(buff1_check_all, (char*) "Master Public Key:\n");
		strcat(buff1_check_all, (char*) cuvex.nfc.tag.from_nfc_public_key);

		/*** Assignment of "words" + "passphrase" + "derivation path" + "private key" + "public key" to be displayed in "scrollable" field ***/
		Unicode::snprintf(typed_check_seedBuffer, TYPED_CHECK_SEED_SIZE, buff1_check_all);
		typed_check_seed.setPosition(0, 0, 210, (20*(total_words+1))+(4*20*7));
		typed_check_seed.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);

		/*** Selecting visible/hidden elements on the screen ***/
		s1_fromNFC_2_waitReadNFC.setVisible(false);
		s1_checkInfo.setVisible(true);
		s1_checkInfo_Seed.setVisible(true);

		break;

	case 2:	//plain-text

		text_type = TEXT_TYPE_FROM_NFC_PLAINTEXT;

		/*** Obtaining the plain text and assignment to be displayed in "scrollable" field ***/
		memset(buff_plain_text, 0x00, KEYBOARD_TEXT_TYPED_PLAIN_TEXT_SIZE);
		memset(typed_check_plain_textBuffer, 0x00, TYPED_CHECK_PLAIN_TEXT_SIZE);

		for(int i=0; i<FROM_NFC_PLAIN_TEXT; i++){
			buff_plain_text[i] = (uint8_t) cuvex.nfc.tag.from_nfc_plain_text[i];
		}

		for(int i=0; i<FROM_NFC_PLAIN_TEXT; i++){
			typed_check_plain_textBuffer[i] = buff_plain_text[i];
		}

		typed_check_plain_text.setPosition(0, 0, 220, 20*(typed_check_plain_text.getTextWidth()/220)+2*20);
		typed_check_plain_text.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);

		/*** Selecting visible/hidden elements on the screen ***/
		s1_fromNFC_2_waitReadNFC.setVisible(false);
		s1_checkInfo.setVisible(true);
		s1_checkInfo_PlainText.setVisible(true);

		break;
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
void screen_flow_2View::generateCombinations(int start, int index, char comb_buffer[][KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE])
{
	uint8_t pwd_combined_raw[10*KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE] = {0};
	uint8_t aux_criptogram[32] = {0};
	static int count_bytes = 0;

	if(index == mandatory_pwds)
	{
		/*** Obtaining the raw password combination ***/
		strncat((char*) pwd_combined_raw, (const char*) cuvex.signature_buffer, SIGNATURE_SIZE);
		for(int i=0; i<mandatory_pwds; i++){
			strcat((char *) pwd_combined_raw, (char *) comb_buffer[i]);
		}

		/*** Obtaining the encrypted password combination (SHA-256) ***/
		HAL_HASHEx_SHA256_Start(&hhash, pwd_combined_raw, strlen((char *) pwd_combined_raw) + SIGNATURE_SIZE, pwd_combined_sha256, HAL_MAX_DELAY);

		/*** AES-256 peripheral configuration (password + initialization vector + header) ***/
		HAL_HASH_MD5_Start(&hhash, cuvex.nfc.tag.new_alias, strlen((char *) cuvex.nfc.tag.new_alias), iv_aes_gcm, HAL_MAX_DELAY);
		memset(header_aes_gcm, 0x00, sizeof(header_aes_gcm));
		configAESPeripheral(pwd_combined_sha256, iv_aes_gcm, header_aes_gcm);

		/*** Generating text to encrypt (BIP39 seed, plaintext) + AES-256 Encryption ***/
		HAL_CRYP_Encrypt(&hcryp, (uint32_t *) pwd_sha256, 32, (uint32_t *) aux_criptogram, HAL_MAX_DELAY);

		/*** Concatenate combination in buffer ***/
		memcpy(cuvex.nfc.tag.new_multisignature + count_bytes, aux_criptogram, 32);
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

