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

#ifndef SCREEN_FLOW_WALLETVIEW_HPP
#define SCREEN_FLOW_WALLETVIEW_HPP

#include <gui_generated/screen_flow_wallet_screen/screen_flow_walletViewBase.hpp>
#include <gui/screen_flow_wallet_screen/screen_flow_walletPresenter.hpp>
#include "mbedtls/pkcs5.h"
#include "mbedtls/md.h"
#include "mbedtls/error.h"
#include "mbedtls/sha512.h"
#include "mbedtls/sha256.h"
#include "mbedtls/ecp.h"
#include "mbedtls/platform.h"
#include "mbedtls/bignum.h"

class screen_flow_walletView : public screen_flow_walletViewBase
{
public:
	screen_flow_walletView();
	virtual ~screen_flow_walletView() {}
	virtual void setupScreen();
	virtual void tearDownScreen();

    virtual void changeScreen(uint8_t screen);
	virtual void tickEventScreen();
	virtual void btnInfoWalletPressed();
	virtual void btnDiceSelectPressed();
	virtual void btnGetWordsPressed();
	virtual void btnHeadsPressed();
	virtual void btnTailsPressed();
	virtual void hideKeyboard1Pressed();
	virtual void showKeyboard1Dice1Pressed();
	virtual void showKeyboard1Dice2Pressed();
	virtual void showKeyboard1Dice3Pressed();
	virtual void showKeyboard1Dice4Pressed();
	virtual void hideKeyboard2Pressed();
	virtual void showKeyboard2Pressed();
	virtual void enterKeyboard2Pressed();
	virtual void btnUpPassphrasePressed();
	virtual void btnDownPassphrasePressed();
	virtual void btnScrollUpPressed();
	virtual void btnScrollDownPressed();
	virtual void btnEncryptPressed();
	virtual void btnRestartPressed();

protected:
	uint8_t current_dice = 0;
	uint8_t actual_word = 1;
	uint8_t words[25][10] = {0};
	uint8_t passphrase[105] = {0};
	uint16_t words_index[25] = {0};
	uint8_t sequence_1_253b[32] = {0};	//23 words * 11 bits/word
	uint8_t sequence_2_256b[32] = {0};	//23 words * 11 bits/word + 3 bits (sha256_1)
	uint8_t sequence_3_264b[33] = {0};	//23 words * 11 bits/word + 3 bits (sha256_1) + 8 bits (sha256_2)
	uint8_t sha256_1[32] = {0};			//from "sequence_1_253b"
	uint8_t sha256_2[32] = {0};			//from "sequence_2_256b"
	uint8_t mnemonic[250] = {0};
	uint8_t seed[64] = {0};
	uint8_t private_key[32] = {0};
	uint8_t public_key[33] = {0};
	uint8_t chain_code[32] = {0};
	uint8_t zprv_key[125] = {0};
	uint8_t zpub_key[125] = {0};
	uint8_t flag_refresh_text_area = 0;
	void setScreenMode();
	void setScreenLanguage();
	void changeCurrentDice();
	void getCurrentWord();
	void resetCoinDiceValues(uint8_t reset_coin, uint8_t reset_dice);
	void getWord24();
	void getBinarySequence();
	int getSeedBIP39();
	int getPrivateKey();
	int getPublicKey();
	void getZprvKey();
	void getZpubKey();
	void base58check_encode(uint8_t *input, int input_len, uint8_t *output);
};

#endif // SCREEN_FLOW_WALLETVIEW_HPP
