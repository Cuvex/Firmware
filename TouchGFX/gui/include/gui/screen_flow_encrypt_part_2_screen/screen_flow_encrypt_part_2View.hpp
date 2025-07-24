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

#ifndef SCREEN_FLOW_ENCRYPT_PART_2VIEW_HPP
#define SCREEN_FLOW_ENCRYPT_PART_2VIEW_HPP

#include <gui_generated/screen_flow_encrypt_part_2_screen/screen_flow_encrypt_part_2ViewBase.hpp>
#include <gui/screen_flow_encrypt_part_2_screen/screen_flow_encrypt_part_2Presenter.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class screen_flow_encrypt_part_2View : public screen_flow_encrypt_part_2ViewBase
{
public:
	screen_flow_encrypt_part_2View();
	virtual ~screen_flow_encrypt_part_2View() {}
	virtual void setupScreen();
	virtual void tearDownScreen();

	virtual void tickEventScreen();
	void changeScreen(uint8_t screen);
	void changeStateNfc(uint8_t state);
	void updateStateNfc(uint16_t state);
	virtual void hideKeyboardPasswordPressed();
	virtual void show1KeyboardPasswordPressed();
	virtual void show2KeyboardPasswordPressed();
	virtual void enterKeyboardPasswordPressed();
	virtual void hideKeyboardAliasPressed();
	virtual void showKeyboardAliasPressed();
	virtual void enterKeyboardAliasPressed();
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

protected:
	uint8_t  actual_pwd;
	uint8_t	 total_pwds;
	uint8_t	 mandatory_pwds;
	uint8_t  pwds[10][KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE];		//6 passwords... 40 characters per password...
	uint8_t  pwd_raw[10*KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE];	//6*40 = 240
	uint8_t  pwd_sha256[32];									//32
	uint8_t  pwd_combined_sha256[32];							//32
	uint8_t  iv_aes_gcm[16];									//16
	void setScreenMode();
	void setScreenLanguage();
	void generateRecordData1_Alias();
	void generateRecordData2_Cryptogram();
	void generateRecordData3_Information();
	void generateRecordData4_Multisignature();
	void configAESPeripheral(uint8_t keyAES[], uint8_t ivAES[]);
	void generateCombinations(int start, int index, char result[][KEYBOARD1_TEXT_TYPED_PASSWORD_SIZE]);
};

#endif // SCREEN_FLOW_ENCRYPT_PART_2VIEW_HPP
