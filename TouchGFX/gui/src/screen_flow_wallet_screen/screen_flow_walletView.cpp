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

#include <gui/screen_flow_wallet_screen/screen_flow_walletView.hpp>
#include "main.h"

extern struct cuvex cuvex;
extern HASH_HandleTypeDef hhash;

screen_flow_walletView::screen_flow_walletView()
{
}

void screen_flow_walletView::setupScreen()
{
	screen_flow_walletViewBase::setupScreen();
	screen_flow_walletView::setScreenMode();
	screen_flow_walletView::setScreenLanguage();
	screen_flow_walletView::changeScreen(GUI_TO_MAIN_SCREEN_FLOW_WALLET);

	/*** Force clear keyboards buffers ***/
	memset(keyboard2_text_typedBuffer, 0x00, sizeof(keyboard2_text_typedBuffer));
	keyboard1.clearBuffer();
	keyboard2.clearBuffer();

	/*** Force default dices colours ***/
	box_dice_1.setBoxColour(0xFF, 0xFF, 0xFF);
	box_dice_2.setBoxColour(0x00, 0x00, 0x00);
	box_dice_3.setBoxColour(0xE4, 0x21, 0x2B);
	box_dice_4.setBoxColour(0x44, 0x5D, 0xA1);
	box_dice_5.setBoxColour(0xDC, 0x2C, 0x99);
	box_dice_6.setBoxColour(0xE9, 0xC2, 0x25);
	box_dice_7.setBoxColour(0xEE, 0x75, 0x11);
	box_dice_8.setBoxColour(0x54, 0xA3, 0x38);
	box_dice_1.setId(DICE_COLOUR_1);
	box_dice_2.setId(DICE_COLOUR_2);
	box_dice_3.setId(DICE_COLOUR_3);
	box_dice_4.setId(DICE_COLOUR_4);
	box_dice_5.setId(DICE_COLOUR_5);
	box_dice_6.setId(DICE_COLOUR_6);
	box_dice_7.setId(DICE_COLOUR_7);
	box_dice_8.setId(DICE_COLOUR_8);
}

void screen_flow_walletView::tearDownScreen()
{
	screen_flow_walletViewBase::tearDownScreen();
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
void screen_flow_walletView::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
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
void screen_flow_walletView::tickEventScreen()
{
	uint8_t num_of_lines = 0;

	/*** Keyboard 1 (dice value) ***/
	if((s2_getWords.isVisible() == true) && (dice_roll.isVisible() == true) && (keyboard1.isVisible() == true) && (keyboard1.getBuffer()[0] != 0x00))
	{
		switch(current_dice)
		{
		case DICE_SELECTED_VALUE_1:
			cuvex.wallet.coin_dice_values[1] = keyboard1.getBuffer()[0] - 0x30;
			box_dice_sel_1.setValue(cuvex.wallet.coin_dice_values[1]);
			keyboard1.clearBuffer();
			changeCurrentDice();
			break;

		case DICE_SELECTED_VALUE_2:
			cuvex.wallet.coin_dice_values[2] = keyboard1.getBuffer()[0] - 0x30;
			box_dice_sel_2.setValue(cuvex.wallet.coin_dice_values[2]);
			keyboard1.clearBuffer();
			changeCurrentDice();
			break;

		case DICE_SELECTED_VALUE_3:
			cuvex.wallet.coin_dice_values[3] = keyboard1.getBuffer()[0] - 0x30;
			box_dice_sel_3.setValue(cuvex.wallet.coin_dice_values[3]);
			keyboard1.clearBuffer();
			changeCurrentDice();
			break;

		case DICE_SELECTED_VALUE_4:
			cuvex.wallet.coin_dice_values[4] = keyboard1.getBuffer()[0] - 0x30;
			box_dice_sel_4.setValue(cuvex.wallet.coin_dice_values[4]);
			keyboard1.clearBuffer();
			changeCurrentDice();
			break;

		default:
			break;
		}
	}

	/*** Keyboard 2 (passphrase) ***/
	if(keyboard2.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard2_text_typedBuffer, keyboard2.getBuffer(), KEYBOARD2_TEXT_TYPED_SIZE) != 0)
		{
			Unicode::snprintf(keyboard2_text_typedBuffer, KEYBOARD2_TEXT_TYPED_SIZE, keyboard2.getBuffer());
			keyboard2_text_typed.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);

			num_of_lines = keyboard2_text_typed.getTextWidth()/230;

			if(num_of_lines > 1){
				keyboard2_text_typed.setPosition(60, 50-((num_of_lines-1)*20), 230, 60+((num_of_lines-1)*20));
			}
			else{
				keyboard2_text_typed.setPosition(60, 50, 230, 60);
			}

			Unicode::itoa(Unicode::strlen(keyboard2_text_typedBuffer), keyboard2_char_countBuffer, KEYBOARD2_CHAR_COUNT_SIZE, 10);

			keyboard2_text_area.invalidate();
		}

		if(flag_refresh_text_area == 1)
		{
			num_of_lines = keyboard2_text_typed.getTextWidth()/230;

			if(num_of_lines > 1){
				keyboard2_text_typed.setPosition(60, 50-((num_of_lines-1)*20), 230, 60+((num_of_lines-1)*20));
				keyboard2_text_area.invalidate();
			}

			flag_refresh_text_area = 0;
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
void screen_flow_walletView::btnInfoWalletPressed()
{
	/*** Selecting visible/hidden elements on the screen + initialize coin/dice values ***/
	s0_infoWallet.setVisible(false);
	s1_selectDice.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::btnDiceSelectPressed()
{
	if((cuvex.wallet.dice_selected[0] != 0) && (cuvex.wallet.dice_selected[1] != 0) && (cuvex.wallet.dice_selected[2] != 0) && (cuvex.wallet.dice_selected[3] != 0))
	{
		/*** Dice selected 1 --> Set colour ***/
		if(cuvex.wallet.dice_selected[0] == DICE_COLOUR_1){
			box_dice_sel_1.setBoxColour(0xFF, 0xFF, 0xFF);
		}
		else if(cuvex.wallet.dice_selected[0] == DICE_COLOUR_2){
			box_dice_sel_1.setBoxColour(0x00, 0x00, 0x00);
		}
		else if(cuvex.wallet.dice_selected[0] == DICE_COLOUR_3){
			box_dice_sel_1.setBoxColour(0xE4, 0x21, 0x2B);
		}
		else if(cuvex.wallet.dice_selected[0] == DICE_COLOUR_4){
			box_dice_sel_1.setBoxColour(0x44, 0x5D, 0xA1);
		}
		else if(cuvex.wallet.dice_selected[0] == DICE_COLOUR_5){
			box_dice_sel_1.setBoxColour(0xDC, 0x2C, 0x99);
		}
		else if(cuvex.wallet.dice_selected[0] == DICE_COLOUR_6){
			box_dice_sel_1.setBoxColour(0xE9, 0xC2, 0x25);
		}
		else if(cuvex.wallet.dice_selected[0] == DICE_COLOUR_7){
			box_dice_sel_1.setBoxColour(0xEE, 0x75, 0x11);
		}
		else if(cuvex.wallet.dice_selected[0] == DICE_COLOUR_8){
			box_dice_sel_1.setBoxColour(0x54, 0xA3, 0x38);
		}

		/*** Dice selected 2 --> Set colour ***/
		if(cuvex.wallet.dice_selected[1] == DICE_COLOUR_1){
			box_dice_sel_2.setBoxColour(0xFF, 0xFF, 0xFF);
		}
		else if(cuvex.wallet.dice_selected[1] == DICE_COLOUR_2){
			box_dice_sel_2.setBoxColour(0x00, 0x00, 0x00);
		}
		else if(cuvex.wallet.dice_selected[1] == DICE_COLOUR_3){
			box_dice_sel_2.setBoxColour(0xE4, 0x21, 0x2B);
		}
		else if(cuvex.wallet.dice_selected[1] == DICE_COLOUR_4){
			box_dice_sel_2.setBoxColour(0x44, 0x5D, 0xA1);
		}
		else if(cuvex.wallet.dice_selected[1] == DICE_COLOUR_5){
			box_dice_sel_2.setBoxColour(0xDC, 0x2C, 0x99);
		}
		else if(cuvex.wallet.dice_selected[1] == DICE_COLOUR_6){
			box_dice_sel_2.setBoxColour(0xE9, 0xC2, 0x25);
		}
		else if(cuvex.wallet.dice_selected[1] == DICE_COLOUR_7){
			box_dice_sel_2.setBoxColour(0xEE, 0x75, 0x11);
		}
		else if(cuvex.wallet.dice_selected[1] == DICE_COLOUR_8){
			box_dice_sel_2.setBoxColour(0x54, 0xA3, 0x38);
		}

		/*** Dice selected 3 --> Set colour ***/
		if(cuvex.wallet.dice_selected[2] == DICE_COLOUR_1){
			box_dice_sel_3.setBoxColour(0xFF, 0xFF, 0xFF);
		}
		else if(cuvex.wallet.dice_selected[2] == DICE_COLOUR_2){
			box_dice_sel_3.setBoxColour(0x00, 0x00, 0x00);
		}
		else if(cuvex.wallet.dice_selected[2] == DICE_COLOUR_3){
			box_dice_sel_3.setBoxColour(0xE4, 0x21, 0x2B);
		}
		else if(cuvex.wallet.dice_selected[2] == DICE_COLOUR_4){
			box_dice_sel_3.setBoxColour(0x44, 0x5D, 0xA1);
		}
		else if(cuvex.wallet.dice_selected[2] == DICE_COLOUR_5){
			box_dice_sel_3.setBoxColour(0xDC, 0x2C, 0x99);
		}
		else if(cuvex.wallet.dice_selected[2] == DICE_COLOUR_6){
			box_dice_sel_3.setBoxColour(0xE9, 0xC2, 0x25);
		}
		else if(cuvex.wallet.dice_selected[2] == DICE_COLOUR_7){
			box_dice_sel_3.setBoxColour(0xEE, 0x75, 0x11);
		}
		else if(cuvex.wallet.dice_selected[2] == DICE_COLOUR_8){
			box_dice_sel_3.setBoxColour(0x54, 0xA3, 0x38);
		}

		/*** Dice selected 4 --> Set colour ***/
		if(cuvex.wallet.dice_selected[3] == DICE_COLOUR_1){
			box_dice_sel_4.setBoxColour(0xFF, 0xFF, 0xFF);
		}
		else if(cuvex.wallet.dice_selected[3] == DICE_COLOUR_2){
			box_dice_sel_4.setBoxColour(0x00, 0x00, 0x00);
		}
		else if(cuvex.wallet.dice_selected[3] == DICE_COLOUR_3){
			box_dice_sel_4.setBoxColour(0xE4, 0x21, 0x2B);
		}
		else if(cuvex.wallet.dice_selected[3] == DICE_COLOUR_4){
			box_dice_sel_4.setBoxColour(0x44, 0x5D, 0xA1);
		}
		else if(cuvex.wallet.dice_selected[3] == DICE_COLOUR_5){
			box_dice_sel_4.setBoxColour(0xDC, 0x2C, 0x99);
		}
		else if(cuvex.wallet.dice_selected[3] == DICE_COLOUR_6){
			box_dice_sel_4.setBoxColour(0xE9, 0xC2, 0x25);
		}
		else if(cuvex.wallet.dice_selected[3] == DICE_COLOUR_7){
			box_dice_sel_4.setBoxColour(0xEE, 0x75, 0x11);
		}
		else if(cuvex.wallet.dice_selected[3] == DICE_COLOUR_8){
			box_dice_sel_4.setBoxColour(0x54, 0xA3, 0x38);
		}

		/*** Selecting visible/hidden elements on the screen + initialize coin/dice values ***/
		btn_get_words_selected.setTouchable(false);
		btn_get_words_selected.setAlpha(100);
		s1_selectDice.setVisible(false);
		s2_getWords.setVisible(true);
		resetCoinDiceValues(1,1);

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
void screen_flow_walletView::btnGetWordsPressed()
{
	/*** Update variable + Force keyboard buffer reset ***/
	current_dice = DICE_SELECTED_VALUE_1;
	keyboard1.clearBuffer();

	/*** Default visual assignment ***/
	btn_get_words_selected.setTouchable(false);
	btn_get_words_selected.setAlpha(100);
	keyboard1.setVisible(true);
	keyboard1_btn_hide.setVisible(true);
	text_word.setVisible(false);
	box_dice_sel_1.setHighlight();
	box_dice_sel_2.resetHighlight();
	box_dice_sel_3.resetHighlight();
	box_dice_sel_4.resetHighlight();
	btn_heads.setAlpha(100);
	btn_tails.setAlpha(100);

	/*** Selecting visible/hidden elements on the screen + initialize coin/dice values ***/
	if(heads_or_tails.isVisible() == true)
	{
		heads_or_tails.setVisible(false);
		dice_roll.setVisible(true);
		word24.setVisible(false);
	}
	else if(dice_roll.isVisible() == true)
	{
		if(actual_word < 23){
			Unicode::snprintf(text_get_words_infoBuffer, TEXT_GET_WORDS_INFO_SIZE, "%d", ++actual_word);
			heads_or_tails.setVisible(true);
			dice_roll.setVisible(false);
			word24.setVisible(false);
		}
		else{
			getWord24();
			Unicode::snprintf(text_get_words_infoBuffer, TEXT_GET_WORDS_INFO_SIZE, "%d", ++actual_word);
			Unicode::snprintf(text_word_24Buffer, TEXT_WORD_24_SIZE, (const char *) words[23]);
			btn_get_words_selected.setTouchable(true);
			btn_get_words_selected.setAlpha(255);
			heads_or_tails.setVisible(false);
			dice_roll.setVisible(false);
			word24.setVisible(true);
		}

		resetCoinDiceValues(1,1);
	}
	else if(word24.isVisible() == true)
	{
		s2_getWords.setVisible(false);
		s3_typePassprhase.setVisible(true);
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
void screen_flow_walletView::btnHeadsPressed()
{
	/*** Get and save coin value ***/
	cuvex.wallet.coin_dice_values[0] = 0;

	/*** Selecting visible/hidden elements on the screen ***/
	btn_get_words_selected.setTouchable(true);
	btn_get_words_selected.setAlpha(255);
	btn_heads.setAlpha(255);
	btn_tails.setAlpha(100);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::btnTailsPressed()
{
	/*** Get and save coin value ***/
	cuvex.wallet.coin_dice_values[0] = 1;

	/*** Selecting visible/hidden elements on the screen ***/
	btn_get_words_selected.setTouchable(true);
	btn_get_words_selected.setAlpha(255);
	btn_heads.setAlpha(100);
	btn_tails.setAlpha(255);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::hideKeyboard1Pressed()
{
	/*** Update variable + Force keyboard buffer reset ***/
	current_dice = 0;
	keyboard1.clearBuffer();

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard1.setVisible(false);
	keyboard1_btn_hide.setVisible(false);
	box_dice_sel_1.resetHighlight();
	box_dice_sel_2.resetHighlight();
	box_dice_sel_3.resetHighlight();
	box_dice_sel_4.resetHighlight();

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::showKeyboard1Dice1Pressed()
{
	/*** Update variable + Force keyboard buffer reset ***/
	current_dice = DICE_SELECTED_VALUE_1;
	keyboard1.clearBuffer();

	/*** Word error exception ***/
	if(text_word_error.isVisible() == true){
		text_word_error.setVisible(false);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard1.setVisible(true);
	keyboard1_btn_hide.setVisible(true);
	box_dice_sel_1.setHighlight();
	box_dice_sel_2.resetHighlight();
	box_dice_sel_3.resetHighlight();
	box_dice_sel_4.resetHighlight();

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::showKeyboard1Dice2Pressed()
{
	/*** Update variable + Force keyboard buffer reset ***/
	current_dice = DICE_SELECTED_VALUE_2;
	keyboard1.clearBuffer();

	/*** Word error exception ***/
	if(text_word_error.isVisible() == true){
		text_word_error.setVisible(false);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard1.setVisible(true);
	keyboard1_btn_hide.setVisible(true);
	box_dice_sel_1.resetHighlight();
	box_dice_sel_2.setHighlight();
	box_dice_sel_3.resetHighlight();
	box_dice_sel_4.resetHighlight();

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::showKeyboard1Dice3Pressed()
{
	/*** Update variable + Force keyboard buffer reset ***/
	current_dice = DICE_SELECTED_VALUE_3;
	keyboard1.clearBuffer();

	/*** Word error exception ***/
	if(text_word_error.isVisible() == true){
		text_word_error.setVisible(false);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard1.setVisible(true);
	keyboard1_btn_hide.setVisible(true);
	box_dice_sel_1.resetHighlight();
	box_dice_sel_2.resetHighlight();
	box_dice_sel_3.setHighlight();
	box_dice_sel_4.resetHighlight();

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::showKeyboard1Dice4Pressed()
{
	/*** Update variable + Force keyboard buffer reset ***/
	current_dice = DICE_SELECTED_VALUE_4;
	keyboard1.clearBuffer();

	/*** Word error exception ***/
	if(text_word_error.isVisible() == true){
		text_word_error.setVisible(false);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard1.setVisible(true);
	keyboard1_btn_hide.setVisible(true);
	box_dice_sel_1.resetHighlight();
	box_dice_sel_2.resetHighlight();
	box_dice_sel_3.resetHighlight();
	box_dice_sel_4.setHighlight();

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
void screen_flow_walletView::hideKeyboard2Pressed()
{
	keyboard2_text_area.setPosition(20, 40, 280, 160);
	keyboard2_text_typed.setPosition(60, 50, 230, 140);
	keyboard2_btn_up.setPosition(30, 50, 20, 20);
	keyboard2_btn_down.setPosition(30, 170, 20, 20);
	keyboard2_char_count.setPosition(250, 188, 50, 12);

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard2.setVisible(false);
	keyboard2_btn_hide.setVisible(false);
	keyboard2_btn_show.setVisible(true);
	keyboard2_btn_enter.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::showKeyboard2Pressed()
{
	keyboard2_text_area.setPosition(20, 40, 280, 70);
	keyboard2_text_typed.setPosition(60, 50, 230, 60);
	keyboard2_btn_up.setPosition(30, 50, 20, 20);
	keyboard2_btn_down.setPosition(30, 80, 20, 20);
	keyboard2_char_count.setPosition(250, 98, 50, 12);

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard2.setVisible(true);
	keyboard2_btn_hide.setVisible(true);
	keyboard2_btn_show.setVisible(false);
	keyboard2_btn_enter.setVisible(false);

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
void screen_flow_walletView::enterKeyboard2Pressed()
{
	char buff_aux1[TYPED_CHECK_INFO_SIZE] = {0}, buff_aux2[15] = {0};

	memset(passphrase, 0x00, KEYBOARD2_TEXT_TYPED_SIZE);
	memset(typed_check_infoBuffer, 0x00, TYPED_CHECK_INFO_SIZE);

	/*** Obtaining the typed text (passphrase) ***/
	for(int i=0; i<KEYBOARD2_TEXT_TYPED_SIZE; i++)
	{
		if(keyboard2_text_typedBuffer[i] == 8364){	//If '€' (8364) is converted to the character '¶' (182) to only occupy 1 byte
			passphrase[i] = 182;
		}
		else{
			passphrase[i] = (uint8_t) keyboard2_text_typedBuffer[i];
		}
	}

	/*** Get BIP39 seed + get master private key + get master public key ***/
	if((getSeedBIP39() == SUCCESS) && (getPrivateKey() == SUCCESS) && (getPublicKey() == SUCCESS))
	{
		/*** Get private and public key in "zprv" and "zpub" format ***/
		getZprvKey();
		getZpubKey();

		/*** Generating an array for displaying words + passphrase ***/
		for(int i=0; i<24; i++)
		{
			snprintf(buff_aux2, 15, "%d. ", i+1);
			strcat(buff_aux1, (char *) buff_aux2);
			strcat(buff_aux1, (char *) words[i]);
			strcat(buff_aux1, (char *) "\n");
		}

		strcat(buff_aux1, (char*) "____________________\n\n");
		strcat(buff_aux1, (char*) "Passphrase:\n");
		strcat(buff_aux1, (char*) passphrase);

		strcat(buff_aux1, (char*) "\n____________________\n\n");
		strcat(buff_aux1, (char*) "Native Segwit Bech32 P2WPKH\nAddress");
		strcat(buff_aux1, (char*) "\n\nDerivation Path:\n");
		strcat(buff_aux1, (char*) "m/84'/0'/0'");

		strcat(buff_aux1, (char*) "\n____________________\n\n");
		strcat(buff_aux1, (char*) "Master Private Key:\n");
		strcat(buff_aux1, (char*) zprv_key);

		strcat(buff_aux1, (char*) "\n____________________\n\n");
		strcat(buff_aux1, (char*) "Master Public Key:\n");
		strcat(buff_aux1, (char*) zpub_key);

		/*** Assignment of words + passphrase to be displayed in "scrollable" field ***/
		for(int i=0; i<TYPED_CHECK_INFO_SIZE; i++)
		{
			if(buff_aux1[i] == 182){	//If '¶' (182) is converted to the character '€' (8364) for display on screen
				typed_check_infoBuffer[i] = 8364;
			}
			else{
				typed_check_infoBuffer[i] = buff_aux1[i];
			}
		}

		typed_check_info.setPosition(0, 0, 210, 1060);
		typed_check_info.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);

		/*** Clearing keyboard and display buffers ***/
		memset(keyboard2_text_typedBuffer, 0x00, sizeof(keyboard2_text_typedBuffer));
		keyboard2.clearBuffer();

		/*** Selecting visible/hidden elements on the screen ***/
		s3_typePassprhase.setVisible(false);
		s4_walletSuccess.setVisible(true);
	}
	else
	{
		/*** Selecting visible/hidden elements on the screen ***/
		s3_typePassprhase.setVisible(false);
		s5_walletError.setVisible(true);
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
void screen_flow_walletView::btnUpPassphrasePressed()
{
	uint8_t num_of_lines = 0;

	num_of_lines = keyboard2_text_typed.getTextWidth()/230;

	if(num_of_lines != 0)	//Multi-line
	{
		if(keyboard2_text_area.getHeight() == 70)		//Small box
		{
			if(keyboard2_text_typed.getHeight() > 60){
				keyboard2_text_typed.setPosition(60, keyboard2_text_typed.getY() + 20, 230, keyboard2_text_typed.getHeight() - 20);
			}
		}
		else if(keyboard2_text_area.getHeight() == 160)	//Big box
		{
			if(keyboard2_text_typed.getHeight() > 140){
				keyboard2_text_typed.setPosition(60, keyboard2_text_typed.getY() + 20, 230, keyboard2_text_typed.getHeight() - 20);
			}
		}
		keyboard2_text_area.invalidate();
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::btnDownPassphrasePressed()
{
	uint8_t num_of_lines = 0;

	num_of_lines = keyboard2_text_typed.getTextWidth()/230;

	if(num_of_lines != 0)	//Multi-line
	{
		if(keyboard2_text_area.getHeight() == 70)		//Small box
		{
			if(keyboard2_text_typed.getHeight() < 60+(20*num_of_lines)){
				keyboard2_text_typed.setPosition(60, keyboard2_text_typed.getY() - 20, 230, keyboard2_text_typed.getHeight() + 20);
			}
		}
		else if(keyboard2_text_area.getHeight() == 160)	//Big box
		{
			if(keyboard2_text_typed.getHeight() < 140+(20*num_of_lines)){
				keyboard2_text_typed.setPosition(60, keyboard2_text_typed.getY() - 20, 230, keyboard2_text_typed.getHeight() + 20);
			}
		}
		keyboard2_text_area.invalidate();
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
void screen_flow_walletView::btnScrollUpPressed()
{
	if(typed_check_info.getY() < 0){
		typed_check_info.setPosition(0, typed_check_info.getY() + 20, 210, 1060);
	}
	scrollable_container_typed_check_info.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::btnScrollDownPressed()
{
	if((typed_check_info.getY() + 1060) > 0){
		typed_check_info.setPosition(0, typed_check_info.getY() - 20, 210, 1060);
	}
	scrollable_container_typed_check_info.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::btnEncryptPressed()
{
	/*** Copy buffers in flow 2 expected format ***/
	cuvex.wallet.flag_new = true;

	for(int i=0; i<24; i++){
		memset(cuvex.wallet.words_to_encrypt[i], 0x00, sizeof(cuvex.wallet.words_to_encrypt));
		memcpy(cuvex.wallet.words_to_encrypt[i], words[i], 4);
	}

	strcat((char *) cuvex.wallet.pass_deriv, (char *) "\"");
	strcat((char *) cuvex.wallet.pass_deriv, (char *) passphrase);
	strcat((char *) cuvex.wallet.pass_deriv, (char *) ", Derivation Path, Native Segwit Bech32 P2WPKH Address, m/84'/0'/0'\"");

	strcat((char *) cuvex.wallet.zprv_key, (char *) zprv_key);
	strcat((char *) cuvex.wallet.zpub_key, (char *) zpub_key);

	/*** Jump to flow 2 ***/
	application().gotoscreen_flow_encryptScreenNoTransition();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::btnRestartPressed()
{
	application().gotoscreen_menuScreenNoTransition();
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
void screen_flow_walletView::setScreenMode()
{
	/*** Setting screen elements based on mode (dark/light) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		/***/
		btn_info_wallet.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_info_wallet.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_info_wallet_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_info_wallet_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		btn_dice_selected.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_dice_selected.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_dice_select_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_dice_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_dice_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_dice_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_dice_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_dice_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_dice_6.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_dice_7.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_dice_8.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		btn_heads.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_tails.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		btn_get_words_selected.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_get_words_selected.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_get_words_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_heads_or_tails_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_word.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_word_24.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		keyboard2_btn_enter.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard2_btn_enter.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard2_text_info_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard2_text_info_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		btn_encrypt_info.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_encrypt_info.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		typed_check_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		btn_restart.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_restart.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_error.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
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
void screen_flow_walletView::setScreenLanguage()
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
void screen_flow_walletView::changeCurrentDice()
{
	if(cuvex.wallet.coin_dice_values[1] == 0){
		showKeyboard1Dice1Pressed();
	}
	else if(cuvex.wallet.coin_dice_values[2] == 0){
		showKeyboard1Dice2Pressed();
	}
	else if(cuvex.wallet.coin_dice_values[3] == 0){
		showKeyboard1Dice3Pressed();
	}
	else if(cuvex.wallet.coin_dice_values[4] == 0){
		showKeyboard1Dice4Pressed();
	}
	else{
		getCurrentWord();
		hideKeyboard1Pressed();
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::getCurrentWord()
{
	if((cuvex.wallet.coin_dice_values[1] != 0) && (cuvex.wallet.coin_dice_values[2] != 0) && (cuvex.wallet.coin_dice_values[3] != 0) && (cuvex.wallet.coin_dice_values[4] != 0))
	{
		int base = 6, index = 0;
		uint8_t str_word[10] = {0};

		/*** Get index from dice roll value ***/
		for(int i=1; i<5; i++){
			index = index * base + (cuvex.wallet.coin_dice_values[i] - 1);
		}

		/*** Get index from head or tail value (if tail add offset 6^4) ***/
		if(cuvex.wallet.coin_dice_values[0] == 1){
			index = index + (base*base*base*base);
		}

		/*** Get bip39 word ***/
		if(getBip39WordFromGlobalIndex(index, (char *) str_word) == true)
		{
			words_index[actual_word-1] = index;
			memcpy(words[actual_word-1], str_word, 10);
			text_word.setVisible(true);
			text_word_error.setVisible(false);
			btn_get_words_selected.setTouchable(true);
			btn_get_words_selected.setAlpha(255);
			Unicode::snprintf(text_wordBuffer, TEXT_WORD_SIZE, (const char *) str_word);
		}
		else
		{
			words_index[actual_word-1] = 0;
			memset(words[actual_word-1], 0x00, 10);
			text_word.setVisible(false);
			text_word_error.setVisible(true);
			btn_get_words_selected.setTouchable(false);
			btn_get_words_selected.setAlpha(100);
			Unicode::snprintf(text_wordBuffer, TEXT_WORD_SIZE, "---");
			resetCoinDiceValues(0,1);
		}
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::resetCoinDiceValues(uint8_t reset_coin, uint8_t reset_dice)
{
	if(reset_coin == 1){
		cuvex.wallet.coin_dice_values[0] = 0;
	}

	if(reset_dice == 1){
		cuvex.wallet.coin_dice_values[1] = 0;
		cuvex.wallet.coin_dice_values[2] = 0;
		cuvex.wallet.coin_dice_values[3] = 0;
		cuvex.wallet.coin_dice_values[4] = 0;
		box_dice_sel_1.setValue(0);
		box_dice_sel_2.setValue(0);
		box_dice_sel_3.setValue(0);
		box_dice_sel_4.setValue(0);
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::getWord24()
{
	uint8_t str_word[10] = {0};

	/*** Get 24 words binary sequence ***/
	getBinarySequence();

	/*** Get word 24 string and index values ***/
	words_index[23] = ((sequence_3_264b[31] << 8) | sequence_3_264b[32]) & 0x7FF;

	if(getBip39WordFromGlobalIndex((int) words_index[23], (char *) str_word) == true){
		memcpy(words[23], str_word, 10);
	}

	/*** Generate mnemonic sentence ***/
	for(int i=0; i<24; i++){
		strcat((char *) mnemonic, (char *) words[i]);
		if(i<23){
			strcat((char *) mnemonic, (char *) " ");
		}
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::getBinarySequence()
{
	uint16_t bit_index = 0, current_word = 0, byte_index = 0, bit_offset = 0;
	uint8_t first_three_bits_sha256 = 0;

	/*** Step 1 --> Get 253 bit array with the 23 words (11 bit/word) ***/
	for(uint16_t i=0; i<23; i++){
		current_word = words_index[i];
		for(int j=10; j>=0; j--){
			byte_index = bit_index / 8;	//Get Byte index
			bit_offset = bit_index % 8;	//Get bit offset (inside Byte)

			if((current_word >> j) & 1){
				sequence_1_253b[byte_index] |= (1 << (7 - bit_offset));
			}
			bit_index++;
		}
	}

	/*** Step 2 --> Hash 1, to get the word 24 first 3 bits ***/
	HAL_HASHEx_SHA256_Start(&hhash, sequence_1_253b, 32, sha256_1, HAL_MAX_DELAY);

	/*** Step 3 --> Get 256 bit array with the 23 words (11 bit/word) + 3 bits from hash 1 ***/
	for(int i=0; i<31; i++){
		sequence_2_256b[i] = sequence_1_253b[i];
	}
	sequence_2_256b[31] = sequence_1_253b[31] & 0xF8;

	first_three_bits_sha256 = sha256_1[0] >> 5;
	sequence_2_256b[31] = sequence_2_256b[31] | (first_three_bits_sha256 & 0x07);

	/*** Step 4 --> Hash 2, to get the word 24 last 8 bits ***/
	HAL_HASHEx_SHA256_Start(&hhash, sequence_2_256b, 32, sha256_2, HAL_MAX_DELAY);

	/*** Step 5 --> Get 264 bit array with the 24 words (11 bit/word) + 3 bits from hash 1 + 8 bit from hash 2 ***/
	for(int i=0; i<32; i++){
		sequence_3_264b[i] = sequence_2_256b[i];
	}
	sequence_3_264b[32] = sha256_2[0];
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int screen_flow_walletView::getSeedBIP39()
{
	char password[250] = {0}, salt[125] = {0};
	int iterations = 0, key_length = 0;

	const mbedtls_md_info_t *md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA512);

	if(md_info != NULL)
	{
		/*** Init HMAC context ***/
		mbedtls_md_context_t ctx;
		mbedtls_md_init(&ctx);
		mbedtls_md_setup(&ctx, md_info, 1);

		/*** PBKDF2-HMAC inputs value ***/
		strcat((char *) password, (char *) mnemonic);
		strcat((char *) salt, (char *) "mnemonic");
		strcat((char *) salt, (char *) passphrase);
		iterations = 2048;
		key_length = 64;

		/*** PBKDF2-HMAC key derivation + Clear HMAC context ***/
		if(mbedtls_pkcs5_pbkdf2_hmac(&ctx, (const unsigned char *) password, strlen(password), (const unsigned char *) salt, strlen(salt), iterations, key_length, (unsigned char *) seed) == 0){
			mbedtls_md_free(&ctx);
			return SUCCESS;
		}

		mbedtls_md_free(&ctx);
	}

	return ERROR;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int screen_flow_walletView::getPrivateKey()
{
	const unsigned char *key = (const unsigned char *) "Bitcoin seed";
	uint8_t buffer[64] = {0};

	const mbedtls_md_info_t *md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA512);

	if(md_info != NULL)
	{
		/*** Init HMAC context ***/
		mbedtls_md_context_t ctx;
		mbedtls_md_init(&ctx);
		mbedtls_md_setup(&ctx, md_info, 1);

		/*** PBKDF2-HMAC key derivation + Clear HMAC context ***/
		if(mbedtls_md_hmac_starts(&ctx, key, strlen((const char *) key)) == 0){
			if(mbedtls_md_hmac_update(&ctx, seed, sizeof(seed)) == 0){
				if(mbedtls_md_hmac_finish(&ctx, buffer) == 0){
					memcpy(private_key, buffer, 32);		//Private key (first 32 bytes)
					memcpy(chain_code, buffer + 32, 32);	//Chain code (last 32 bytes)
					mbedtls_md_free(&ctx);
					return SUCCESS;
				}
			}
		}

		mbedtls_md_free(&ctx);
	}

	return ERROR;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int screen_flow_walletView::getPublicKey()
{
	size_t public_key_len = 0;
	mbedtls_ecp_group group;
	mbedtls_ecp_point Q;
	mbedtls_mpi d;

	/*** Init elliptic ***/
	mbedtls_ecp_group_init(&group);
	mbedtls_ecp_point_init(&Q);
	mbedtls_mpi_init(&d);

	/*** Set up the secp256k1 elliptic curve group ***/
	if(mbedtls_ecp_group_load(&group, MBEDTLS_ECP_DP_SECP256K1) != 0){
		return ERROR;
	}

	/*** Load the private key into the MPI structure ***/
	if(mbedtls_mpi_read_binary(&d, private_key, sizeof(private_key)) != 0){
		return ERROR;
	}

	/*** Compute the public key Q = d * G (d is the private key and G is the generator point) ***/
	if(mbedtls_ecp_mul(&group, &Q, &d, &group.G, NULL, NULL) != 0){
		return ERROR;
	}

	/*** Export the public key in compressed format (33 bytes) ***/
	if(mbedtls_ecp_point_write_binary(&group, &Q, MBEDTLS_ECP_PF_COMPRESSED, &public_key_len, public_key, sizeof(public_key)) != 0){
		return ERROR;
	}

	/*** Free the resources ***/
	mbedtls_ecp_group_free(&group);
	mbedtls_ecp_point_free(&Q);
	mbedtls_mpi_free(&d);

	return SUCCESS;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::getZprvKey()
{
	uint8_t buffer[78] = {0};

	/*** Clear buffers ***/
	memset(buffer, 0x00, sizeof(buffer));

	/*** Version for zprv (BIP84) ***/
	buffer[0]  = 0x04;
	buffer[1]  = 0xB2;
	buffer[2]  = 0x43;
	buffer[3]  = 0x0C;

	/*** Depth (root level) ***/
	buffer[4]  = 0x00;

	/*** Parent fingerprint (root level) ***/
	buffer[5]  = 0x00;
	buffer[6]  = 0x00;
	buffer[7]  = 0x00;
	buffer[8]  = 0x00;

	/*** Child number (root level) ***/
	buffer[9]  = 0x00;
	buffer[10] = 0x00;
	buffer[11] = 0x00;
	buffer[12] = 0x00;

	/*** Chain code (last 32 bytes of "master extended private key") ***/
	memcpy(buffer + 13, chain_code, 32);

	/*** Private key (0x00 + first 32 bytes of "master extended private key") ***/
	buffer[45] = 0x00;
	memcpy(buffer + 46, private_key, 32);

	/*** Apply Base58Check encoding ***/
	base58check_encode(buffer, 78, zprv_key);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::getZpubKey()
{
	uint8_t buffer[78] = {0};

	/*** Clear buffers ***/
	memset(buffer, 0x00, sizeof(buffer));

	/*** Version for zpub (BIP84) ***/
	buffer[0]  = 0x04;
	buffer[1]  = 0xB2;
	buffer[2]  = 0x47;
	buffer[3]  = 0x46;

	/*** Depth (root level) ***/
	buffer[4]  = 0x00;

	/*** Parent fingerprint (root level) ***/
	buffer[5]  = 0x00;
	buffer[6]  = 0x00;
	buffer[7]  = 0x00;
	buffer[8]  = 0x00;

	/*** Child number (root level) ***/
	buffer[9]  = 0x00;
	buffer[10] = 0x00;
	buffer[11] = 0x00;
	buffer[12] = 0x00;

	/*** Chain code (last 32 bytes of "master extended private key") ***/
	memcpy(buffer + 13, chain_code, 32);

	/*** Public key (compressed format, 33 bytes) ***/
	memcpy(buffer + 45, public_key, 33);

	/*** Apply Base58Check encoding ***/
	base58check_encode(buffer, 78, zpub_key);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_walletView::base58check_encode(uint8_t *input, int input_len, uint8_t *output)
{
	static const char base58_alphabet[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
	uint8_t hash_1[32] = {0}, hash_2[32] = {0};
	uint8_t extended_input[input_len + 4] = {0};
	uint8_t buffer[128] = {0};
	int output_idx = 0, carry = 0;

	/*** Clear the extended buffer and copy the original input data into it ***/
	memset(extended_input, 0x00, sizeof(extended_input));
	memcpy(extended_input, input, input_len);

	/*** Calculate the double SHA-256 of the input data ***/
	HAL_HASHEx_SHA256_Start(&hhash, input, input_len, hash_1, HAL_MAX_DELAY);
	HAL_HASHEx_SHA256_Start(&hhash, hash_1, 32, hash_2, HAL_MAX_DELAY);

	/*** Add checksum to extended buffer (first 4 Byte of hash_2) ***/
	memcpy(extended_input + input_len, hash_2, 4);

	/*** Perform Base58 encoding on the extended data ***/
	memset(buffer, 0x00, sizeof(buffer));

	for(int i=0; i<input_len + 4; ++i)
	{
		carry = extended_input[i];

		for(int j=0; j<output_idx || carry; ++j)
		{
			carry += 256 * buffer[j];
			buffer[j] = carry % 58;
			carry /= 58;

			if(j >= output_idx){
				output_idx++;
			}
		}
	}

	/*** Map o the Base58 alphabet and add null character ***/
	for(int i=0; i<output_idx; ++i){
		output[i] = base58_alphabet[buffer[output_idx - 1 - i]];
	}
	output[output_idx] = '\0';
}








