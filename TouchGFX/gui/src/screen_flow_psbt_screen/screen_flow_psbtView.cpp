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

#include <gui/screen_flow_psbt_screen/screen_flow_psbtView.hpp>
#include "main.h"

extern struct cuvex cuvex;
extern HASH_HandleTypeDef hhash;
extern CRYP_HandleTypeDef hcryp;
PSBT psbt;

screen_flow_psbtView::screen_flow_psbtView(): passwordResultCallback(this, &screen_flow_psbtView::handlePasswordResult), temporal_block(0), text_type(0), num_pwds(1), actual_pwd(0), pwd_ok(false), buff_pri_key{0}, buff_pub_key{0}, pwd_sha256{0}, pwd_combined_sha256{0}, header_aes_gcm{0}, iv_aes_gcm{0}, psbt_total_receivers{0}, psbt_actual_receiver{0}, psbt_btn_sign_count{0}, psbt_has_change_address{false}
{

}

void screen_flow_psbtView::setupScreen()
{
	screen_flow_psbtViewBase::setupScreen();
	screen_flow_psbtView::checkTemporalBlock();
	screen_flow_psbtView::setScreenMode();
	screen_flow_psbtView::setScreenLanguage();
	screen_flow_psbtView::changeScreen(GUI_TO_MAIN_SCREEN_FLOW_PSBT);

	s5_typePassword.setPasswordResultCallback(passwordResultCallback);
}

void screen_flow_psbtView::tearDownScreen()
{
	screen_flow_psbtViewBase::tearDownScreen();
	screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
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
void screen_flow_psbtView::tickEventScreen()
{
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
			screen_flow_psbtView::changeFlash(GUI_TO_MAIN_FLASH_SAVE_SETTINGS);
			screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
			screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_FROM_PSBT);
			s99_error_warning_alert.setVisible(false);
			error_temporalBlock.setVisible(false);
			s0_initNFC_psbt.setVisible(true);
			close_button.setVisible(true);
			background.invalidate();
		}
	}

	/*** Processing ***/
	if(s8_processing.isVisible() == true)	//Sign transaction + Screen update
	{
		signPsbtTransaction();

		s8_processing.setVisible(false);
		s9_checkSignedQR.setVisible(true);
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
void screen_flow_psbtView::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_psbtView::changeFlash(uint8_t state)
{
	presenter->changeFlash(state);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_psbtView::changeStateNfc(uint8_t state)
{
	presenter->changeStateNfc(state);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_psbtView::updateStateNfc(uint16_t state)
{
	switch(state)
	{
	case MAIN_TO_GUI_NFC_ERROR:
	default:
		application().gotoscreen_menuScreenNoTransition();
		break;

	case MAIN_TO_GUI_NFC_INITIALIZED:
		if(s0_initNFC_psbt.isVisible() == true)
		{
			s0_initNFC_psbt.setVisible(false);
			s1_waitReadNFC_psbt.setVisible(true);
		}
		else if(s3_initNFC_crypto.isVisible() == true)
		{
			s3_initNFC_crypto.setVisible(false);
			s4_waitReadNFC_crypto.setVisible(true);
		}
		else if(s10_initNFC_save_psbt.isVisible() == true)
		{
			s10_initNFC_save_psbt.setVisible(false);
			s11_waitReadNFC_save_psbt.setVisible(true);
		}
		break;

	case MAIN_TO_GUI_NFC_TAG_READED_FROM_PSBT:
		if(s1_waitReadNFC_psbt.isVisible() == true)
		{
			/*** NFC reader disable ***/
			screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);

			/*** Selecting visible/hidden elements on the screen ***/
			if((cuvex.nfc.tag.from_psbt_type == PSBT_TYPE_V0_NOT_SIGNED) && (getCheckPsbtInfo1() == SUCCESS)){
				s1_waitReadNFC_psbt.setVisible(false);
				s2_transactionInfo1.setVisible(true);
			}
			else{
				s99_error_warning_alert.setVisible(true);
				error_cardFormat.setVisible(true);
			}
		}
		break;

	case MAIN_TO_GUI_NFC_TAG_READED:
		if(s4_waitReadNFC_crypto.isVisible() == true)
		{
			/*** NFC reader disable ***/
			screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);

			/*** Selecting visible/hidden elements on the screen ***/
			if(cuvex.nfc.tag.encripted == true)
			{
				num_pwds = cuvex.nfc.tag.multisigned_mandatory;

				s4_waitReadNFC_crypto.setVisible(false);
				s5_typePassword.setVisible(true);
			}
			else{
				s99_error_warning_alert.setVisible(true);
				error_noCryptogram.setVisible(true);
			}
		}
		break;

	case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FROM_PSBT:
	case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FROM_PSBT_T4T_8K:
		if(s11_waitReadNFC_save_psbt.isVisible() == true)
		{
			/*** NFC reader disable ***/
			screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);

			/*** Selecting visible/hidden elements on the screen ***/
			if(cuvex.nfc.tag.from_psbt_type == PSBT_TYPE_V0_SIGNED){
				s11_waitReadNFC_save_psbt.setVisible(false);
				s12_psbtSigned_Success.setVisible(true);
			}
			else{
				if(cuvex.nfc.tag.flag_readed_writed_from_psbt_size_warning == true){
					cuvex.nfc.tag.flag_readed_writed_from_psbt_size_warning = false;
					s99_error_warning_alert.setVisible(true);
					error_cardSize.setVisible(true);
				}
				else{
					s99_error_warning_alert.setVisible(true);
					error_cardFormat.setVisible(true);
				}
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
void screen_flow_psbtView::btnVerifyTransactionPressed()
{
	/*** NFC reader config ***/
	screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
	screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ);

	/*** Selecting visible/hidden elements on the screen ***/
	s2_transactionInfo1.setVisible(false);
	s3_initNFC_crypto.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_psbtView::retryCardFormatErrorPressed()
{
	if(s1_waitReadNFC_psbt.isVisible() == true)
	{
		/*** Selecting visible/hidden elements on the screen ***/
		s0_initNFC_psbt.setVisible(false);
		s1_waitReadNFC_psbt.setVisible(false);
		s2_transactionInfo1.setVisible(false);
		s99_error_warning_alert.setVisible(false);
		error_cardFormat.setVisible(false);

		/*** Restart screens checking temporal block ***/
		checkTemporalBlock();
	}
	else if(s11_waitReadNFC_save_psbt.isVisible() == true)
	{
		/*** NFC reader config ***/
		screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);

		if(strlen((const char *) cuvex.nfc.tag.from_psbt_base64_signed) < FROM_PSBT_T2T_MAX_SIZE){
			screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_WRITE_FROM_PSBT);
		}
		else{
			screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_WRITE_FROM_PSBT_T4T_8K);
		}

		/*** Selecting visible/hidden elements on the screen ***/
		s10_initNFC_save_psbt.setVisible(true);
		s11_waitReadNFC_save_psbt.setVisible(false);
		s99_error_warning_alert.setVisible(false);
		error_cardFormat.setVisible(false);

		/*** Screen update ***/
		background.invalidate();
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_psbtView::retryCardSizeErrorPressed()
{
	/*** Selecting visible/hidden elements on the screen ***/
	s9_checkSignedQR.setVisible(true);
	s10_initNFC_save_psbt.setVisible(false);
	s11_waitReadNFC_save_psbt.setVisible(false);
	s99_error_warning_alert.setVisible(false);
	error_cardSize.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_psbtView::retryNoCryptogramErrorPressed()
{
	if(s4_waitReadNFC_crypto.isVisible() == true)
	{
		/*** Selecting visible/hidden elements on the screen ***/
		s4_waitReadNFC_crypto.setVisible(false);
		s2_transactionInfo1.setVisible(true);
		s99_error_warning_alert.setVisible(false);
		error_noCryptogram.setVisible(false);

		/*** Screen update ***/
		background.invalidate();
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_psbtView::koPrivatePasswordBtnPressed()
{
	NVIC_SystemReset();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_psbtView::checkReceiverPressed()
{
	Unicode::UnicodeChar address_part_1[20] = {0}, address_part_2[80] = {0}, address_part_3[20] = {0};
	int adress_len = 0;
	const char* address_cstr;
	char array_amount[50] = {0};

	/*** Get and check receiver info ***/
	psbt_actual_receiver = 0;
	psbt_btn_sign_count = 0;

	if(cuvex.info.language == SPANISH){
		Unicode::snprintf(check_receiver_infoBuffer, CHECK_RECEIVER_INFO_SIZE, "Receptor %d/%d", psbt_actual_receiver + 1, psbt_total_receivers);
	}
	else{
		Unicode::snprintf(check_receiver_infoBuffer, CHECK_RECEIVER_INFO_SIZE, "Recipient %d/%d", psbt_actual_receiver + 1, psbt_total_receivers);
	}

	/*** Get and check receiver amount ***/
	sprintf(array_amount, "%.8f", (double) psbt.tx.txOuts[psbt_actual_receiver].btcAmount());
	Unicode::strncpy(bitcoin_amountBuffer, array_amount, BITCOIN_AMOUNT_SIZE);

	/*** Get and check receiver address ***/
	address_cstr = psbt.tx.txOuts[psbt_actual_receiver].scriptPubkey.address(&DEFAULT_NETWORK).c_str();
	adress_len = Unicode::strlen(address_cstr);
	Unicode::strncpy(address_part_1, address_cstr, 10);
	Unicode::strncpy(address_part_2, address_cstr + 10 , adress_len - 20);
	Unicode::strncpy(address_part_3, address_cstr + adress_len - 10, 10);

	Unicode::snprintf(check_receiver_address_1Buffer, CHECK_RECEIVER_ADDRESS_1_SIZE, "%s", address_part_1);
	Unicode::snprintf(check_receiver_address_2Buffer, CHECK_RECEIVER_ADDRESS_2_SIZE, "%s", address_part_2);
	Unicode::snprintf(check_receiver_address_3Buffer, CHECK_RECEIVER_ADDRESS_3_SIZE, "%s", address_part_3);

	/*** Increment actual receiver ***/
	psbt_actual_receiver++;

	/*** Selecting visible/hidden elements on the screen ***/
	if(psbt_has_change_address == false){
		s99_error_warning_alert.setVisible(true);
		warning_noChangeAddress.setVisible(true);
	}

	if(psbt_actual_receiver < psbt_total_receivers){
		btn_sign_psbt_click_confirm.setVisible(false);
	}
	else{
		btn_sign_psbt_click_confirm.setVisible(true);
		if(cuvex.info.language == SPANISH){
			Unicode::snprintf(btn_sign_psbtBuffer, BTN_SIGN_PSBT_SIZE, "FIRMAR PSBT");
		}
		else{
			Unicode::snprintf(btn_sign_psbtBuffer, BTN_SIGN_PSBT_SIZE, "SIGN PSBT");
		}
	}

	s6_transactionInfo2.setVisible(false);
	s7_checkReceiver.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_psbtView::btnSignPsbtPressed()
{
	Unicode::UnicodeChar address_part_1[20] = {0}, address_part_2[80] = {0}, address_part_3[20] = {0};
	int adress_len = 0;
	const char* address_cstr;
	char array_amount[50] = {0};

	if(psbt_actual_receiver < psbt_total_receivers)
	{
		/*** Get and check receiver info ***/
		if(cuvex.info.language == SPANISH){
			Unicode::snprintf(check_receiver_infoBuffer, CHECK_RECEIVER_INFO_SIZE, "Receptor %d/%d", psbt_actual_receiver + 1, psbt_total_receivers);
		}
		else{
			Unicode::snprintf(check_receiver_infoBuffer, CHECK_RECEIVER_INFO_SIZE, "Recipient %d/%d", psbt_actual_receiver + 1, psbt_total_receivers);
		}

		/*** Get and check receiver amount ***/
		sprintf(array_amount, "%.8f", (double) psbt.tx.txOuts[psbt_actual_receiver].btcAmount());
		Unicode::strncpy(bitcoin_amountBuffer, array_amount, BITCOIN_AMOUNT_SIZE);

		/*** Get and check receiver address ***/
		address_cstr = psbt.tx.txOuts[psbt_actual_receiver].scriptPubkey.address(&DEFAULT_NETWORK).c_str();
		adress_len = Unicode::strlen(address_cstr);
		Unicode::strncpy(address_part_1, address_cstr, 10);
		Unicode::strncpy(address_part_2, address_cstr + 10 , adress_len - 20);
		Unicode::strncpy(address_part_3, address_cstr + adress_len - 10, 10);

		Unicode::snprintf(check_receiver_address_1Buffer, CHECK_RECEIVER_ADDRESS_1_SIZE, "%s", address_part_1);
		Unicode::snprintf(check_receiver_address_2Buffer, CHECK_RECEIVER_ADDRESS_2_SIZE, "%s", address_part_2);
		Unicode::snprintf(check_receiver_address_3Buffer, CHECK_RECEIVER_ADDRESS_3_SIZE, "%s", address_part_3);

		/*** Increment actual receiver ***/
		psbt_actual_receiver++;

		/*** Selecting visible/hidden elements on the screen ***/
		if(psbt_actual_receiver < psbt_total_receivers){
			btn_sign_psbt_click_confirm.setVisible(false);
		}
		else{
			if(cuvex.info.language == SPANISH){
				Unicode::snprintf(btn_sign_psbtBuffer, BTN_SIGN_PSBT_SIZE, "FIRMAR PSBT");
			}
			else{
				Unicode::snprintf(btn_sign_psbtBuffer, BTN_SIGN_PSBT_SIZE, "SIGN PSBT");
			}
			Unicode::snprintf(btn_sign_psbt_click_confirmBuffer, BTN_SIGN_PSBT_CLICK_CONFIRM_SIZE, "3");
			btn_sign_psbt_click_confirm.setVisible(true);
		}
	}
	else
	{
		/*** Selecting visible/hidden elements on the screen ***/
		if(psbt_btn_sign_count < 3)
		{
			psbt_btn_sign_count++;

			if(psbt_btn_sign_count == 1){
				Unicode::snprintf(btn_sign_psbt_click_confirmBuffer, BTN_SIGN_PSBT_CLICK_CONFIRM_SIZE, "2");
			}
			else if(psbt_btn_sign_count == 2){
				Unicode::snprintf(btn_sign_psbt_click_confirmBuffer, BTN_SIGN_PSBT_CLICK_CONFIRM_SIZE, "1");
			}
			else{
				s7_checkReceiver.setVisible(false);
				s8_processing.setVisible(true);
			}
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
void screen_flow_psbtView::btnWarningNoChangeAddressPressed()
{
	/*** Selecting visible/hidden elements on the screen ***/
	s99_error_warning_alert.setVisible(false);
	warning_noChangeAddress.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_psbtView::btnWritePsbtViaNfcPressed()
{
	/*** NFC reader config ***/
	screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);

	if(strlen((const char *) cuvex.nfc.tag.from_psbt_base64_signed) < FROM_PSBT_T2T_MAX_SIZE){
		screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_WRITE_FROM_PSBT);
	}
	else{
		screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_WRITE_FROM_PSBT_T4T_8K);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	s9_checkSignedQR.setVisible(false);
	s10_initNFC_save_psbt.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_psbtView::btnClosePressed()
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
void screen_flow_psbtView::setScreenMode()
{
	/*** Setting screen elements based on mode (dark/light) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		/***/
		init_nfc_text1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		init_nfc_text2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_wait_read_nfc1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		text_transaction_info_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_transactions_info_1_inputs.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_transactions_info_1_outputs.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_transactions_info_1_fee.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_transactions_info_1_inputs_num.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_transactions_info_1_outputs_num.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_transactions_info_1_fee_num.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_verify_transaction_info_1.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_verify_transaction_info_1.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		init_nfc_text1_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		init_nfc_text2_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_wait_read_nfc2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		text_transaction_info_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_transactions_info_2_inputs.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_transactions_info_2_outputs.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_transactions_info_2_fee.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_transactions_info_2_rbf.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_transactions_info_2_inputs_num.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_transactions_info_2_outputs_num.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_transactions_info_2_fee_num.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_transactions_info_2_rbf_num.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_check_receiver.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_check_receiver.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		processing_text.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		check_receiver_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		check_receiver_address_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_sign_psbt.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		/***/
		btn_write_psbt_via_nfc.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_write_psbt_via_nfc.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		psbt_signed_success_text.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		psbt_save_success_text.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		init_nfc_text1_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		init_nfc_text2_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_wait_read_nfc3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_close.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_close.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		background_error.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
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
		card_format_error_text.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		card_format_error_btn.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		card_format_error_btn.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		card_size_error_text.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		card_size_error_btn.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		card_size_error_btn.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		no_cryptogram_error_text.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		no_cryptogram_error_btn.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		no_cryptogram_error_btn.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		ko_private_password_error_text_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		ko_private_password_error_text_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		no_change_address_warning_text_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		no_change_address_warning_text_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		no_change_address_warning_text_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		no_change_address_warning_btn.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		no_change_address_warning_btn.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
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
void screen_flow_psbtView::setScreenLanguage()
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
void screen_flow_psbtView::checkTemporalBlock()
{
	/*** Configuration of screen elements based on whether there is an active temporary lock or not ***/
	switch(cuvex.info.errors)
	{
	case 0:
	case 1:
	default:
		screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
		screen_flow_psbtView::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_FROM_PSBT);
		s99_error_warning_alert.setVisible(false);
		error_temporalBlock.setVisible(false);
		s0_initNFC_psbt.setVisible(true);
		temporal_block = 0;
		break;

	case 2:
		s99_error_warning_alert.setVisible(true);
		error_temporalBlock.setVisible(true);
		s0_initNFC_psbt.setVisible(false);
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
int screen_flow_psbtView::getCheckPsbtInfo1()
{
	char array_total_btc[50] = {0};
	double total_btc = 0;

	if((psbt.parseBase64((const char *) cuvex.nfc.tag.from_psbt_base64) != 0) && (psbt.tx.isValid() == true))
	{
		/*** Check all inputs ***/
		for(int i=0; i<psbt.tx.inputsNumber; i++){
			if(psbt.tx.txIns[i].isValid() != true){
				return ERROR;
			}
			else{
				total_btc += psbt.txInsMeta[i].txOut.btcAmount();
			}
		}

		/*** Check all outputs ***/
		for(int i = 0; i < psbt.tx.outputsNumber; i++){
			if(psbt.tx.txOuts[i].isValid() != true){
				return ERROR;
			}
		}

		/*** Print info in screen ***/
		sprintf(array_total_btc, "%.8f", (double) total_btc);
		Unicode::strncpy(bitcoin_amount_info_1Buffer, array_total_btc, BITCOIN_AMOUNT_INFO_1_SIZE);
		Unicode::snprintf(text_transactions_info_1_inputs_numBuffer, TEXT_TRANSACTIONS_INFO_1_INPUTS_NUM_SIZE, "%u", psbt.tx.inputsNumber);
		Unicode::snprintf(text_transactions_info_1_outputs_numBuffer, TEXT_TRANSACTIONS_INFO_1_OUTPUTS_NUM_SIZE, "%u", psbt.tx.outputsNumber);
		Unicode::snprintf(text_transactions_info_1_fee_numBuffer, TEXT_TRANSACTIONS_INFO_1_FEE_NUM_SIZE, "%u", 1);

#ifdef DEBUG_PSBT_PRINTF
		printf("\r\n###########################################################################\r\n");
		printf("######################### getCheckPsbtInfo1() #############################\r\n");
		printf("###########################################################################\r\n");
		printf("psbt_base64: \"%s\"\r\n\r\n", cuvex.nfc.tag.from_psbt_base64);
		printf("*** SUCCESS => PSBT decoded correctly... inputs and outputs are fine ***\r\n\r\n");
		printf("  - TX_Input........ %u\r\n", psbt.tx.inputsNumber);
		printf("  - TX_Outputs...... %u\r\n", psbt.tx.outputsNumber);
		printf("  - Amount (btc).... %.8f\r\n", total_btc);
		printf("###########################################################################\r\n");
		printf("###########################################################################\r\n");
		printf("###########################################################################\r\n\r\n");
#endif
		return SUCCESS;
	}
	else{
		return ERROR;
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int screen_flow_psbtView::getCheckPsbtInfo2()
{
#ifdef DEBUG_PSBT_PRINTF
	HDPrivateKey myPriKey_print((char *) buff_pri_key);
	HDPublicKey myPubKey_print((char *) buff_pub_key);

	printf("\r\n###########################################################################\r\n");
	printf("######################### getCheckPsbtInfo2() #############################\r\n");
	printf("###########################################################################\r\n");
	printf("Public_key: \"%s\"\r\n", buff_pub_key);
	printf("Private_key: \"%s\"\r\n", buff_pri_key);

	/*** Inputs (metadata) ***/
	printfPsbtInputsMetadata();

	/*** Outputs (isMine) ***/
	for(int i=0; i<psbt.tx.outputsNumber; i++)
	{
		printf("\r\n*** OUTPUT #%d ***\r\n", i);
		printf("isMine priKey?... %u ... isMine pubKey?... %u ...\r\n", psbt.isMine(i, myPriKey_print), psbt.isMine(i, myPubKey_print));
	}

	printf("###########################################################################\r\n");
	printf("###########################################################################\r\n");
	printf("###########################################################################\r\n\r\n");
#endif

	/*
	 * 1) Verify transaction
	 */
	HDPublicKey myPubKey((char *) buff_pub_key);
	HDPrivateKey myPrivKey((char *) buff_pri_key);

	for(int i=0; i<psbt.tx.inputsNumber; i++)
	{
		if(psbt.txInsMeta[i].derivationsLen == 1)
		{
			/*** Fingerprint --> Get and compare ***/
			uint8_t fp_input[4] = {0};
			myPubKey.fingerprint(fp_input);

			if(memcmp(fp_input, psbt.txInsMeta[i].derivations[0].fingerprint, sizeof(fp_input)) != 0x00){
				return ERROR;
			}

			/*** Derived Address --> Get and compare ***/
			char derivedAddress_input[100] = {0}, derivationPath_input[100] = "m";

			for(int k=0; k<psbt.txInsMeta[i].derivations[0].derivationLen; k++)
			{
				char temp[20] = {0};
				uint32_t index = psbt.txInsMeta[i].derivations[0].derivation[k];

				if((index & 0x80000000) == 0x80000000){		//Hardened
					snprintf(temp, sizeof(temp), "/%u'", (unsigned) (index & 0x7FFFFFFF));
				}
				else{	//Not hardened
					snprintf(temp, sizeof(temp), "/%u", (unsigned) (index & 0x7FFFFFFF));
				}

				strcat(derivationPath_input, temp);
			}

			HDPrivateKey derivedPrivKey_input = myPrivKey.derive(derivationPath_input);
			HDPublicKey derivedPubKey_input = derivedPrivKey_input.xpub();
			derivedPubKey_input.address(derivedAddress_input, sizeof(derivedAddress_input));

#ifdef DEBUG_PSBT_PRINTF
			printf("\r\n-----------------------------\r\n");
			printf("INPUT -> #%d:\r\n", i);
			printf("Path used is: %s\r\n", derivationPath_input);
			printf("PSBT address: %s\r\n", psbt.txInsMeta[i].txOut.scriptPubkey.address(&DEFAULT_NETWORK).c_str());
			printf("Der. address: %s\r\n", derivedAddress_input);
			printf("\r\n-----------------------------\r\n");
#endif

			if(memcmp(derivedAddress_input, psbt.txInsMeta[i].txOut.scriptPubkey.address(&DEFAULT_NETWORK).c_str(), strlen(derivedAddress_input)) != 0x00){
				return ERROR;
			}
		}
		else{
			return ERROR;
		}
	}

	for(int i=0; i<psbt.tx.outputsNumber; i++)
	{
		if((psbt.txOutsMeta[i].derivationsLen == 1) && (psbt.isMine(i, myPrivKey) == 1))
		{
			/*** Fingerprint --> Get and compare ***/
			uint8_t fp_output[4] = {0};
			myPubKey.fingerprint(fp_output);

			if(memcmp(fp_output, psbt.txOutsMeta[i].derivations[0].fingerprint, sizeof(fp_output)) != 0x00){
				return ERROR;
			}

			/*** Derived Address --> Get and compare ***/
			char derivedAddress_output[100] = {0}, derivationPath_output[100] = "m";

			for(int k=0; k<psbt.txOutsMeta[i].derivations[0].derivationLen; k++)
			{
				char temp[20] = {0};
				uint32_t index = psbt.txOutsMeta[i].derivations[0].derivation[k];

				if((index & 0x80000000) == 0x80000000){		//Hardened
					snprintf(temp, sizeof(temp), "/%u'", (unsigned) (index & 0x7FFFFFFF));
				}
				else{	//Not hardened
					snprintf(temp, sizeof(temp), "/%u", (unsigned) (index & 0x7FFFFFFF));
				}

				strcat(derivationPath_output, temp);
			}

			HDPrivateKey derivedPrivKey_output = myPrivKey.derive(derivationPath_output);
			HDPublicKey derivedPubKey_output = derivedPrivKey_output.xpub();
			derivedPubKey_output.address(derivedAddress_output, sizeof(derivedAddress_output));

#ifdef DEBUG_PSBT_PRINTF
			printf("\r\n-----------------------------\r\n");
			printf("OUTPUT-> #%d:\r\n", i);
			printf("Path used is: %s\r\n", derivationPath_output);
			printf("PSBT address: %s\r\n", psbt.tx.txOuts[i].scriptPubkey.address(&DEFAULT_NETWORK).c_str());
			printf("Der. address: %s\r\n", derivedAddress_output);
			printf("\r\n-----------------------------\r\n");
#endif

			if(memcmp(derivedAddress_output, psbt.tx.txOuts[i].scriptPubkey.address(&DEFAULT_NETWORK).c_str(), strlen(derivedAddress_output)) != 0x00){
				return ERROR;
			}
		}
	}

	/*
	 * 2) Visualize info (total_change = total_input - total_outputs - total_fee - rbf)
	 */
	double total_input_btc = 0, total_output_btc = 0;
	char array_total_input[50] = {0}, array_total_output[50] = {0}, array_total_fee[50] = {0}, array_total_change[50] = {0};
	bool is_rbf = false;

	for(int i=0; i<psbt.tx.inputsNumber; i++){
		total_input_btc += psbt.txInsMeta[i].txOut.btcAmount();

		if(psbt.tx.txIns[i].sequence < 0xFFFFFFFE){
			is_rbf = true;
		}
	}

	for(int i=0; i<psbt.tx.outputsNumber; i++){
		if(psbt.isMine(i, myPrivKey) == 0){
			total_output_btc += psbt.tx.txOuts[i].btcAmount();
			psbt_total_receivers++;
		}
		else{
			psbt_has_change_address = true;
		}
	}

	sprintf(array_total_input, 	"%.8f", (double) total_input_btc);
	sprintf(array_total_output, "-%.8f", (double) total_output_btc);
	sprintf(array_total_fee, 	"-%.8f", (double) psbt.fee()/1e8);
	sprintf(array_total_change, "%.8f", (double) total_input_btc - total_output_btc - (psbt.fee()/1e8));

	Unicode::strncpy(text_transactions_info_2_inputs_numBuffer, array_total_input, TEXT_TRANSACTIONS_INFO_2_INPUTS_NUM_SIZE);
	Unicode::strncpy(text_transactions_info_2_outputs_numBuffer, array_total_output, TEXT_TRANSACTIONS_INFO_2_OUTPUTS_NUM_SIZE);
	Unicode::strncpy(text_transactions_info_2_fee_numBuffer, array_total_fee, TEXT_TRANSACTIONS_INFO_2_FEE_NUM_SIZE);
	Unicode::strncpy(bitcoin_amount_info_2Buffer, array_total_change, BITCOIN_AMOUNT_INFO_2_SIZE);

	if(is_rbf == true){
		if(cuvex.info.language == SPANISH){
			Unicode::snprintf(text_transactions_info_2_rbf_numBuffer, TEXT_TRANSACTIONS_INFO_2_RBF_NUM_SIZE, "Si");
		}
		else{
			Unicode::snprintf(text_transactions_info_2_rbf_numBuffer, TEXT_TRANSACTIONS_INFO_2_RBF_NUM_SIZE, "Yes");
		}
	}
	else{
		Unicode::snprintf(text_transactions_info_2_rbf_numBuffer, TEXT_TRANSACTIONS_INFO_2_RBF_NUM_SIZE, "No");
	}

	return SUCCESS;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_psbtView::signPsbtTransaction()
{
	/*** Sign PSBT ***/
	HDPrivateKey myPrivKey((char *) buff_pri_key);
	int counter = 0;

	counter = psbt.sign(myPrivKey);

	/*** Export PSBT result ***/
	std::string psbtString = psbt.toString();
	std::string psbtBase64 = psbt.toBase64();

	if(counter > 0){
		strcpy((char*) cuvex.nfc.tag.from_psbt_base64_signed, psbtBase64.c_str());
	}
	else{
		strcpy((char*) cuvex.nfc.tag.from_psbt_base64_signed, "PSBT Sign Error");
	}

	/*** QR code generation ***/
	if(strlen(psbtBase64.c_str()) < FROM_PSBT_T2T_MAX_SIZE)
	{
		if(qr_code.convertStringToQRCode((char *) cuvex.nfc.tag.from_psbt_base64_signed) == true){
			psbt_signed_success.setVisible(false);
			qr_code.setVisible(true);
		}
		else{
			psbt_signed_success.setVisible(true);
			qr_code.setVisible(false);
		}
	}
	else{
		psbt_signed_success.setVisible(true);
		qr_code.setVisible(false);
	}

#ifdef DEBUG_PSBT_PRINTF
	printf("\r\n###########################################################################\r\n");
	printf("######################## signPsbtTransaction() ############################\r\n");
	printf("###########################################################################\r\n");
	printf("[PSBT] %d inputs signed correctly...\r\n\r\n", counter);
	printf("[PSBT] - Sign in String format(%d):\r\n%s\r\n\r\n", strlen(psbtString.c_str()), psbtString.c_str());
	printf("[PSBT] - Sign in Base64 format(%d):\r\n%s\r\n\r\n", strlen(psbtBase64.c_str()), psbtBase64.c_str());
	printf("###########################################################################\r\n");
	printf("###########################################################################\r\n");
	printf("###########################################################################\r\n\r\n");
#endif
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
void screen_flow_psbtView::passwordSuccess(uint8_t  decrypted_text[SIZE_CRYPT])
{
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

	case TEXT_TYPE_FROM_NFC_BIP39:

		int len_bip39 = 0;
		int len_pass_der = 0;
		int len_priv_key = 0;
		int len_pub_key = 0;

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

		/*** Get private key and public key ***/
		for(int i=0; i<len_priv_key-8; i++){
			buff_pri_key[i] = decrypted_text[len_bip39 + len_pass_der + i + 8];
		}

		for(int i=0; i<len_pub_key-8; i++){
			buff_pub_key[i] = decrypted_text[len_bip39 + len_pass_der + len_priv_key + i + 8];
		}

		/*** Get and check PSBT info part 2 - Selecting visible/hidden elements on the screen ***/
		if(getCheckPsbtInfo2() == SUCCESS){
			s5_typePassword.setVisible(false);
			s6_transactionInfo2.setVisible(true);
		}
		else{
			s5_typePassword.setVisible(false);
			s99_error_warning_alert.setVisible(true);
			error_koPrivatePassword.setVisible(true);
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
void screen_flow_psbtView::passwordWrong()
{
	if(cuvex.info.errors < 2){
		cuvex.info.errors++;
	}

	if(cuvex.info.errors >= 2){
		screen_flow_psbtView::changeFlash(GUI_TO_MAIN_FLASH_SAVE_SETTINGS);
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
void screen_flow_psbtView::handlePasswordResult(uint8_t result)
{
	if(result == true){
		passwordSuccess(cuvex.decrypt.cryptogram_decrypted);
	}
	else{
		passwordWrong();
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
void screen_flow_psbtView::printfPsbtInputsMetadata()
{
#ifdef DEBUG_PSBT_PRINTF
	char descriptor_print[150] = {0}, checksum_print[9] = {0};
	uint8_t pubkeyBytes_print[65] = {0};

	/*
	 * Inputs
	 */
	for(int i=0; i<psbt.tx.inputsNumber; i++)
	{
		printf("\r\n*** INPUT #%d ***\r\n", i);

		/*
		 * Witness_utxo
		 */
		printf("[Witness UTXO]\r\n");
		printf("- amount... %.8f (BTC)\r\n", psbt.txInsMeta[i].txOut.btcAmount());
		printf("- ScriptPubKey:\r\n");
		/***/
		printf(" - asm..... ");
		if((psbt.txInsMeta[i].txOut.scriptPubkey.scriptLen == 22) && (psbt.txInsMeta[i].txOut.scriptPubkey.scriptArray[0] == 0x00) && (psbt.txInsMeta[i].txOut.scriptPubkey.scriptArray[1] == 0x14))
		{
			printf("0 ");
			for(size_t j=2; j<22; j++){
				printf("%02x", psbt.txInsMeta[i].txOut.scriptPubkey.scriptArray[j]);
			}
			printf("\r\n");
		}
		else{
			printf("Not compatible with P2WPKH\r\n");
		}
		/***/
		printf(" - desc.... ");
		snprintf(descriptor_print, sizeof(descriptor_print), "addr(%s)", psbt.txInsMeta[i].txOut.scriptPubkey.address(&DEFAULT_NETWORK).c_str());
		if(descriptorChecksum(descriptor_print, strlen(descriptor_print), checksum_print, sizeof(checksum_print))){
			printf("%s#%s\r\n", descriptor_print, checksum_print);
		}
		else{
			printf("%s (Failed to calculate checksum)\r\n", descriptor_print);
		}
		/***/
		printf(" - Hex..... ");
		for (size_t j=0; j<psbt.txInsMeta[i].txOut.scriptPubkey.scriptLen; j++) {
			printf("%02x", psbt.txInsMeta[i].txOut.scriptPubkey.scriptArray[j]);
		}
		printf("\r\n");
		/***/
		printf(" - Addr.... %s\r\n", psbt.txInsMeta[i].txOut.scriptPubkey.address(&DEFAULT_NETWORK).c_str());
		/***/
		printf(" - Type.... %d\r\n", psbt.txInsMeta[i].txOut.scriptPubkey.type());

		/*
		 * BIP32 derivations
		 */
		printf("[BIP32 derivations]\r\n");

		for(int j=0; j<psbt.txInsMeta[i].derivationsLen; j++)
		{
			/***/
			printf(" - Pubkey.. ");
			if(psbt.txInsMeta[i].derivations[j].pubkey.compressed)	//Compressed (33Bytes)
			{
				pubkeyBytes_print[0] = (psbt.txInsMeta[i].derivations[j].pubkey.point[63] % 2 == 0) ? 0x02 : 0x03;
				memcpy(pubkeyBytes_print + 1, psbt.txInsMeta[i].derivations[j].pubkey.point, 32);

				for(int k=0; k<33; k++){
					printf("%02x", pubkeyBytes_print[k]);
				}
				printf("\r\n");
			}
			else	//Not compressed (65Bytes)
			{
				pubkeyBytes_print[0] = 0x04;
				memcpy(pubkeyBytes_print + 1, psbt.txInsMeta[i].derivations[j].pubkey.point, 64);

				for(int k=0; k<65; k++){
					printf("%02x", pubkeyBytes_print[k]);
				}
				printf("\r\n");
			}

			/***/
			printf(" - Fing.... ");
			for (int k=0; k<4; k++){
				printf("%02x", psbt.txInsMeta[i].derivations[j].fingerprint[k]);
			}
			printf("\r\n");

			/***/
			printf(" - Path.... m");
			for(int k=0; k<psbt.txInsMeta[i].derivations[j].derivationLen; k++)
			{
				uint32_t index = psbt.txInsMeta[i].derivations[j].derivation[k];

				if((index & 0x80000000) == 0x80000000){		//Hardened
					printf("/%u'", (unsigned int) (index & 0x7FFFFFFF));
				}
				else{	//Not hardened
					printf("/%u", (unsigned int) (index & 0x7FFFFFFF));
				}
			}
			printf("\r\n");
		}
	}
#endif
}





