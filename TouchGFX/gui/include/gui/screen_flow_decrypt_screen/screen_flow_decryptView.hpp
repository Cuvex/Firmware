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

#ifndef SCREEN_FLOW_DECRYPTVIEW_HPP
#define SCREEN_FLOW_DECRYPTVIEW_HPP

#include <gui_generated/screen_flow_decrypt_screen/screen_flow_decryptViewBase.hpp>
#include <gui/screen_flow_decrypt_screen/screen_flow_decryptPresenter.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Callback.hpp>
#include "Bitcoin.h"

class screen_flow_decryptView : public screen_flow_decryptViewBase
{
public:
	screen_flow_decryptView();
	virtual ~screen_flow_decryptView() {}
	virtual void setupScreen();
	virtual void tearDownScreen();
	/***/
	virtual void tickEventScreen();
	/***/
	virtual void changeScreen(uint8_t screen);
	virtual void changeFlash(uint8_t state);
	virtual void changeStateNfc(uint8_t state);
	virtual void updateStateNfc(uint16_t state);
	/***/
	virtual void decryptPressed();
	virtual void btnConfirmViewSecretPressed();
	virtual void retryPressed();
	virtual void moreTimePressed();
    virtual void moreTimeChatKeyPressed();
	virtual void resetMicrocontrollerPressed();
	virtual void btnUpPressed();
	virtual void btnDownPressed();
	virtual void qrSmallPressed();
	virtual void backPressed();
	virtual void btnCautionMsgPressed();
	virtual void btnClosePressed();
	/***/
	virtual void btnWatchOnlyWalletPressed();
	virtual void btnQrSeedPressed();
	virtual void btnQrPrivateKeyPressed();
	virtual void btnQrPublicKeyPressed();
	virtual void btnReuseSeedPhrasePressed();
	/***/
	virtual void btnCreateDescriptorPressed();
	virtual void btnCreateDescriptorMultisignPressed();
	virtual void btnVerifyAddressPressed();
	virtual void btnCreateChatKeyPressed();
	/***/
	virtual void btnToggleHardenedAddress();
	virtual void btnToggleNotHardenedAddress();
	virtual void btnCautionChatKeyPressed();
	/***/
	void handlePasswordResult(uint8_t result);
	void handleVerifyAddressResult(bool result);
	void handleCreateDescriptorResult(bool result);

protected:
	touchgfx::Callback<screen_flow_decryptView, uint8_t> passwordResultCallback;
	touchgfx::Callback<screen_flow_decryptView, bool> verifyAddressCallback;
	touchgfx::Callback<screen_flow_decryptView, bool> createDescriptorCallback;

	uint8_t  qr_info_type = 0;
	uint8_t  temporal_block = 0;
    uint8_t  text_type = 0;
    uint16_t total_words = 0;
    uint16_t index_words = 0;
	uint8_t	 num_pwds = 1;
	uint8_t  actual_pwd = 0;
	bool 	 pwd_ok = false;
    uint8_t  words_decrypted[55][5] = {0};		//48 words... 4 characters per word...
    uint8_t  words_to_check[55][15] = {0};		//48 words... 8 characters per word...
	uint8_t  buff_passphrase[105] = {0};		//100 characters
	uint8_t  buff_plain_text[505] = {0};		//500 characters
	uint8_t  buff_pass_der[205] = {0};			//200 characters
	uint8_t  buff_derivation1[105] = {0};		//100 characters
	uint8_t  buff_derivation2[105] = {0};		//100 characters
	uint8_t  buff_pri_key[205] = {0};			//200 characters
	uint8_t  buff_pub_key[205] = {0};			//200 characters
	uint8_t  pwd_sha256[32] = {0};				//32
	uint8_t  pwd_combined_sha256[32] = {0};		//32
	uint8_t  header_aes_gcm[4] = {0};			//4
	uint8_t  iv_aes_gcm[16] = {0};				//16

	virtual void setScreenMode();
	virtual void setScreenLanguage();
	virtual void checkTemporalBlock();
	void passwordSuccess(uint8_t  decrypted_text[SIZE_CRYPT]);
	void passwordWrong();
};

#endif // SCREEN_FLOW_DECRYPTVIEW_HPP
