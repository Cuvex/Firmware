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

#ifndef SCREEN_FLOW_2VIEW_HPP
#define SCREEN_FLOW_2VIEW_HPP

#include <gui_generated/screen_flow_2_screen/screen_flow_2ViewBase.hpp>
#include <gui/screen_flow_2_screen/screen_flow_2Presenter.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/CustomKeyboard.hpp>

class screen_flow_2View : public screen_flow_2ViewBase
{
public:
	screen_flow_2View();
	virtual ~screen_flow_2View() {}
	virtual void setupScreen();
	virtual void tearDownScreen();

	virtual void tickEventScreen();
	void changeScreen(uint8_t screen);
	void changeStateNfc(uint8_t state);
	void updateStateNfc(uint16_t state);
	virtual void hideKeyboard1SeedPressed();
	virtual void showKeyboard1SeedPressed();
	virtual void enterKeyboard1SeedPressed();
	virtual void hideKeyboard2SeedPressed();
	virtual void showKeyboard2SeedPressed();
	virtual void enterKeyboard2SeedPressed();
	virtual void hideKeyboard3SeedPressed();
	virtual void showKeyboard3SeedPressed();
	virtual void enterKeyboard3SeedPressed();
	virtual void hideKeyboardPlainTextPressed();
	virtual void showKeyboardPlainTextPressed();
	virtual void enterKeyboardPlainTextPressed();
	virtual void hideKeyboardPasswordPressed();
	virtual void show1KeyboardPasswordPressed();
	virtual void show2KeyboardPasswordPressed();
	virtual void enterKeyboardPasswordPressed();
	virtual void hideKeyboardAliasPressed();
	virtual void showKeyboardAliasPressed();
	virtual void enterKeyboardAliasPressed();
	virtual void menuBip39Pressed();
	virtual void menuSlip39Pressed();
	virtual void menuXmrPressed();
	virtual void menuPlainTextPressed();
	virtual void menuTextFromNfcPressed();
	virtual void encryptPressed();
	virtual void successPressed();
	virtual void eye1Pressed();
	virtual void eye2Pressed();
	virtual void retryPressed();
	virtual void passwordSuccessPressed();
	virtual void multisignedYesPressed();
	virtual void multisignedNoPressed();
	virtual void multisignedPlusPressed();
	virtual void multisignedMinusPressed();
	virtual void multisignedSelectPressed();
	virtual void btnUpPressed();
	virtual void btnDownPressed();
	virtual void btnScrollUpPressed();
	virtual void btnScrollDownPressed();
	virtual void btnFromNfcErrorPressed();

protected:
	CustomKeyboard keyboard;
	uint8_t  text_type;
	uint16_t total_words;
	uint16_t actual_word;
    uint16_t index_words;
	uint8_t  valid_word;
	uint8_t  actual_pwd;
	uint8_t	 total_pwds;
	uint8_t	 mandatory_pwds;
	uint8_t  flag_refresh_text_area;
	uint8_t  words_to_encrypt[55][5];	//54 words... 4 characters per word...
	uint8_t  words_to_check[55][15];	//54 words... 8 characters per word...
	uint8_t  buff_passphrase[105];		//100 characters
	uint8_t  buff_plain_text[505];		//500 characters
	uint8_t  pwds[10][KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE];		//6 passwords... 40 characters per password...
	uint8_t  pwd_raw[10*KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE];	//6*40 = 240
	uint8_t  pwd_sha256[32];									//32
	uint8_t  pwd_combined_sha256[32];							//32
	uint8_t  header_aes_gcm[4];									//4
	uint8_t  iv_aes_gcm[16];									//16
	void setScreenMode();
	void setScreenLanguage();
	void generateRecordData1_Alias();
	void generateRecordData2_Cryptogram();
	void generateRecordData3_Information();
	void generateRecordData4_Multisignature();
	void configAESPeripheral(uint8_t keyAES[], uint8_t ivAES[], uint8_t headerAES[]);
	void checkDataFromNFC();
	void generateCombinations(int start, int index, char result[][KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE]);
};

#endif // SCREEN_FLOW_2VIEW_HPP
