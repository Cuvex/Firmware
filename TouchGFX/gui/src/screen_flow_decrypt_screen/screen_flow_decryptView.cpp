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

#include <gui/screen_flow_decrypt_screen/screen_flow_decryptView.hpp>
#include "main.h"

extern struct cuvex cuvex;
extern HASH_HandleTypeDef hhash;
extern CRYP_HandleTypeDef hcryp;

screen_flow_decryptView::screen_flow_decryptView(): passwordResultCallback(this, &screen_flow_decryptView::handlePasswordResult), verifyAddressCallback(this, &screen_flow_decryptView::handleVerifyAddressResult), qr_info_type(0), temporal_block(0), text_type(0), total_words(0), index_words(0), num_pwds(1), actual_pwd(0), pwd_ok(false), words_decrypted{0}, words_to_check{0}, buff_passphrase{0}, buff_plain_text{0}, buff_pass_der{0}, buff_derivation1{0}, buff_derivation2{0}, buff_pri_key{0}, buff_pub_key{0}/*, pwds{0}, pwd_raw{0}*/, pwd_sha256{0}, pwd_combined_sha256{0}, header_aes_gcm{0}, iv_aes_gcm{0}
{

}

void screen_flow_decryptView::setupScreen()
{
	screen_flow_decryptViewBase::setupScreen();
	screen_flow_decryptView::checkTemporalBlock();
	screen_flow_decryptView::setScreenMode();
	screen_flow_decryptView::setScreenLanguage();
	screen_flow_decryptView::changeScreen(GUI_TO_MAIN_SCREEN_FLOW_DECRYPT);

	s5_typePassword.setPasswordResultCallback(passwordResultCallback);
	s8_verify_address.setVerifyAddressCallback(verifyAddressCallback);
}

void screen_flow_decryptView::tearDownScreen()
{
	screen_flow_decryptViewBase::tearDownScreen();
	screen_flow_decryptView::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
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
void screen_flow_decryptView::tickEventScreen()
{
	static uint8_t tick = 0;
	static uint16_t tick_temporal_block = 0;

	/*** Temporary lock timing within the flow ***/
	if(temporal_block == 1)
	{
		tick_temporal_block++;

		if(tick_temporal_block >= 6*300)	//5 minutes (6 ticks/second * 300 seconds)
		{
			temporal_block = 0;
			tick_temporal_block = 0;
			cuvex.info.errors = 0;
			screen_flow_decryptView::changeFlash(GUI_TO_MAIN_FLASH_SAVE_SETTINGS);
			screen_flow_decryptView::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
			screen_flow_decryptView::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ);
			s0_temporalBlock.setVisible(false);
			s1_initNFC.setVisible(true);
			close_button.setVisible(true);
			background.invalidate();
		}
	}

	/*** Timer management ***/
	if(s6_viewSecret.isVisible() == true)
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
				s6_viewSecret.setVisible(false);
				s7_timeoutSecret.setVisible(true);
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
void screen_flow_decryptView::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_decryptView::changeFlash(uint8_t state)
{
	presenter->changeFlash(state);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_decryptView::changeStateNfc(uint8_t state)
{
	presenter->changeStateNfc(state);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_decryptView::updateStateNfc(uint16_t state)
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
				screen_flow_decryptView::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);

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
void screen_flow_decryptView::decryptPressed()
{
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
void screen_flow_decryptView::retryPressed()
{
	/*** NFC re-initialization ***/
	screen_flow_decryptView::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
	screen_flow_decryptView::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ);

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
void screen_flow_decryptView::moreTimePressed()
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
void screen_flow_decryptView::resetMicrocontrollerPressed()
{
	NVIC_SystemReset();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_decryptView::btnUpPressed()
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
void screen_flow_decryptView::btnDownPressed()
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
void screen_flow_decryptView::qrSmallPressed()
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
void screen_flow_decryptView::backPressed()
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
void screen_flow_decryptView::btnCautionMsgPressed()
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

	qr_code.convertStringToQRCode(qr_text);

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
void screen_flow_decryptView::btnQrSeedPressed()
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
void screen_flow_decryptView::btnQrPrivateKeyPressed()
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
void screen_flow_decryptView::btnQrPublicKeyPressed()
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

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_decryptView::btnVerifyAddressPressed()
{
	/*** Selecting visible/hidden elements on the screen ***/
	s6_viewSecret.setVisible(false);
	s7_timeoutSecret.setVisible(false);
	s8_verify_address.setVisible(true);
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
void screen_flow_decryptView::btnClosePressed()
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
void screen_flow_decryptView::setScreenMode()
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
		/***/
		btn_1_qr_seed.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_1_qr_seed.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_2_qr_private_key.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_2_qr_private_key.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_3_qr_public_key.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_3_qr_public_key.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_4_verify_address.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_4_verify_address.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		/***/
		btn_close.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_close.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		check_receiver_address_1.setColor(touchgfx::Color::getColorFromRGB(0xFF,0x8C,0x00));
		check_receiver_address_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		check_receiver_address_3.setColor(touchgfx::Color::getColorFromRGB(0xFF,0x8C,0x00));
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
void screen_flow_decryptView::setScreenLanguage()
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
void screen_flow_decryptView::checkTemporalBlock()
{
	/*** Configuration of screen elements based on whether there is an active temporary lock or not ***/
	switch(cuvex.info.errors)
	{
	case 0:
	case 1:
	default:
		screen_flow_decryptView::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
		screen_flow_decryptView::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ);
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
void screen_flow_decryptView::passwordSuccess(uint8_t  decrypted_text[SIZE_CRYPT])
{
	char buff1_check_all[TEXT_SECRET_CHECK_SIZE] = {0}, buff2_words_index[10] = {0};
	char *ptr1, *ptr2, *ptr3, *ptr4;
	int decrypted_lenght = 0;

	/*** Check decryted text type ***/
	if(strstr((const char *) decrypted_text, "[bip39]") != NULL){
		text_type = TEXT_TYPE_BIP39;
	}
	else if (strstr((const char *) decrypted_text, "[slip39]") != NULL){
		text_type = TEXT_TYPE_SLIP39;
	}
	else if (strstr((const char *) decrypted_text, "[xmr]") != NULL){
		text_type = TEXT_TYPE_XMR;
	}
	else if (strstr((const char *) decrypted_text, "[plain-text]") != NULL){
		text_type = TEXT_TYPE_PLAINTEXT;
	}
	else if (strstr((const char *) decrypted_text, "{plain-text}") != NULL){
		text_type = TEXT_TYPE_FROM_NFC_PLAINTEXT;
	}
	else if (strstr((const char *) decrypted_text, "{bip39}") != NULL){
		text_type = TEXT_TYPE_FROM_NFC_BIP39;
	}
	else{
		text_type = TEXT_TYPE_NONE;
	}

	/*** Parsing and visualization in base to text type ***/
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
		s6_viewSecret.setVisible(true);
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
		s6_viewSecret.setVisible(true);
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
		s6_viewSecret.setVisible(true);
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
		s6_viewSecret.setVisible(true);
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
		s6_viewSecret.setVisible(true);
		break;
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_decryptView::passwordWrong()
{
	if(cuvex.info.errors < 2){
		cuvex.info.errors++;
	}

	if(cuvex.info.errors >= 2){
		screen_flow_decryptView::changeFlash(GUI_TO_MAIN_FLASH_SAVE_SETTINGS);
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
void screen_flow_decryptView::handlePasswordResult(uint8_t result)
{
	if(result == true){
		passwordSuccess(cuvex.decrypt.cryptogram_decrypted);
	}
	else{
		passwordWrong();
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_decryptView::handleVerifyAddressResult(bool result)
{
	Unicode::UnicodeChar address_part_1[20] = {0}, address_part_2[80] = {0}, address_part_3[20] = {0};

	if(result == true)
	{
		HDPublicKey myPubKey((char *) buff_pub_key);

		HDPublicKey derivedPubKey = myPubKey.derive((char *) cuvex.decrypt.derivation_path);
		derivedPubKey.address((char *) cuvex.decrypt.derived_address, sizeof(cuvex.decrypt.derived_address));

		Unicode::strncpy(address_part_1, (char *) cuvex.decrypt.derived_address, 10);
		Unicode::strncpy(address_part_2, (char *) cuvex.decrypt.derived_address + 10 , strlen((char *) cuvex.decrypt.derived_address) - 20);
		Unicode::strncpy(address_part_3, (char *) cuvex.decrypt.derived_address + strlen((char *) cuvex.decrypt.derived_address) - 10, 10);

		Unicode::snprintf(check_receiver_address_1Buffer, CHECK_RECEIVER_ADDRESS_1_SIZE, "%s", address_part_1);
		Unicode::snprintf(check_receiver_address_2Buffer, CHECK_RECEIVER_ADDRESS_2_SIZE, "%s", address_part_2);
		Unicode::snprintf(check_receiver_address_3Buffer, CHECK_RECEIVER_ADDRESS_3_SIZE, "%s", address_part_3);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	s8_verify_address.setVisible(false);
	s9_check_address.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}


