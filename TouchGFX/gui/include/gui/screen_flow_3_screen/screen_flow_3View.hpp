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

#ifndef SCREEN_FLOW_3VIEW_HPP
#define SCREEN_FLOW_3VIEW_HPP

#include <gui_generated/screen_flow_3_screen/screen_flow_3ViewBase.hpp>
#include <gui/screen_flow_3_screen/screen_flow_3Presenter.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/CustomKeyboard.hpp>
#include <gui/widgets/qrcode/QRCodeWidget.hpp>
#include <gui/widgets/qrcode/QRCode.hpp>

class screen_flow_3View : public screen_flow_3ViewBase
{
public:
    screen_flow_3View();
    virtual ~screen_flow_3View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void tickEventScreen();
    virtual void changeScreen(uint8_t screen);
    virtual void changeFlash(uint8_t state);
    virtual void changeStateNfc(uint8_t state);
    virtual void updateStateNfc(uint16_t state);
    virtual void hideKeyboardPressed();
    virtual void showKeyboardPressed();
    virtual void enterKeyboardPressed();
    virtual void decryptPressed();
    virtual void retryPressed();
    virtual void moreTimePressed();
    virtual void eyePressed();
    virtual void resetMicrocontrollerPressed();
    virtual void btnUpPressed();
    virtual void btnDownPressed();
    virtual void qrSmallPressed();
    virtual void backPressed();
    virtual void btnError1Pressed();
    virtual void btnError2Pressed();
    virtual void btnCautionMsgPressed();
    virtual void btnQrSeedPressed();
    virtual void btnQrPrivateKeyPressed();
    virtual void btnQrPublicKeyPressed();

protected:
    CustomKeyboard keyboard;
    QRCodeWidget qr_code;
    QR *code;
    uint8_t  qr_info_type;
    uint8_t  temporal_block;
    uint8_t  text_type;
    uint16_t total_words;
    uint16_t index_words;
	uint8_t	 num_pwds;
	uint8_t  actual_pwd;
	bool 	 pwd_ok;
    uint8_t  words_decrypted[55][5];	//48 words... 4 characters per word...
    uint8_t  words_to_check[55][15];	//48 words... 8 characters per word...
	uint8_t  buff_passphrase[105];		//100 characters
	uint8_t  buff_plain_text[505];		//500 characters
	uint8_t  buff_pass_der[205];		//200 characters
	uint8_t  buff_derivation1[105];		//100 characters
	uint8_t  buff_derivation2[105];		//100 characters
	uint8_t  buff_pri_key[205];			//200 characters
	uint8_t  buff_pub_key[205];			//200 characters
	uint8_t  pwds[10][KEYBOARD_TEXT_TYPED_SIZE];	//6 passwords... 40 characters per password...
	uint8_t  pwd_raw[10*KEYBOARD_TEXT_TYPED_SIZE];	//6*40 = 240
	uint8_t  pwd_sha256[32];						//32
	uint8_t  pwd_combined_sha256[32];				//32
	uint8_t  header_aes_gcm[4];						//4
	uint8_t  iv_aes_gcm[16];						//16
    virtual void setScreenMode();
    virtual void setScreenLanguage();
    virtual void checkTemporalBlock();
	void configAESPeripheral(uint8_t keyAES[], uint8_t ivAES[], uint8_t headerAES[], uint8_t type);
	void decryptSecret(uint8_t  decrypted_text[SIZE_CRYPT]);
	void decryptSecretWithCombinations(uint8_t  decrypted_text[SIZE_CRYPT]);
	bool checkDecryptedText(uint8_t  decrypted_text[SIZE_CRYPT]);
	void passwordSuccess(uint8_t  decrypted_text[SIZE_CRYPT]);
	void passwordWrong();
};

#endif // SCREEN_FLOW_3VIEW_HPP
