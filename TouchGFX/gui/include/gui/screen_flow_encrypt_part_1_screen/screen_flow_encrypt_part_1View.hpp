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

#ifndef SCREEN_FLOW_ENCRYPT_PART_1VIEW_HPP
#define SCREEN_FLOW_ENCRYPT_PART_1VIEW_HPP

#include <gui_generated/screen_flow_encrypt_part_1_screen/screen_flow_encrypt_part_1ViewBase.hpp>
#include <gui/screen_flow_encrypt_part_1_screen/screen_flow_encrypt_part_1Presenter.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class screen_flow_encrypt_part_1View : public screen_flow_encrypt_part_1ViewBase
{
public:
	screen_flow_encrypt_part_1View();
	virtual ~screen_flow_encrypt_part_1View() {}
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
	virtual void menuBip39Pressed();
	virtual void menuSlip39Pressed();
	virtual void menuXmrPressed();
	virtual void menuPlainTextPressed();
	virtual void menuTextFromNfcPressed();
	virtual void encryptPressed();
	virtual void btnUpPressed();
	virtual void btnDownPressed();
	virtual void btnScrollUpPressed();
	virtual void btnScrollDownPressed();
	virtual void btnFromNfcErrorPressed();
protected:
	uint16_t actual_word;
	uint16_t index_words;
	uint8_t  valid_word;
	uint8_t  flag_refresh_text_area;
	uint8_t  words_to_check[55][15];	//54 words... 8 characters per word...
	void setScreenMode();
	void setScreenLanguage();
	void checkDataFromNFC();
};

#endif // SCREEN_FLOW_ENCRYPT_PART_1VIEW_HPP
