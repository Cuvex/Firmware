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

#ifndef DECRYPT_TAG_HPP
#define DECRYPT_TAG_HPP

#include <gui_generated/containers/decrypt_tagBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Callback.hpp>

class decrypt_tag : public decrypt_tagBase
{
public:
	decrypt_tag();
	virtual ~decrypt_tag() {}

	virtual void initialize();

	virtual void tickEvent();
	virtual void hideKeyboardPressed();
	virtual void showKeyboardPressed();
	virtual void enterKeyboardPressed();
	virtual void eyePressed();
	virtual void btnError1Pressed();
	virtual void btnError2Pressed();

	void setPasswordResultCallback(touchgfx::GenericCallback<uint8_t>& cb);
	void setVisible(bool visible);

protected:
	touchgfx::GenericCallback<uint8_t>* passwordResultCallback;

	uint8_t	num_pwds;
	uint8_t actual_pwd;
	uint8_t	pwd_ok;
	uint8_t pwd_raw[10*KEYBOARD_TEXT_TYPED_SIZE];	//6*40 = 240
	uint8_t pwd_sha256[32];							//32
	uint8_t pwd_combined_sha256[32];				//32
	uint8_t header_aes_gcm[4];						//4
	uint8_t iv_aes_gcm[16];							//16

	uint8_t pwds[10][KEYBOARD_TEXT_TYPED_SIZE];		//New
	uint8_t pwds_sha256[10][32];					//New
	uint8_t pwds_sha256_concat[320];				//New
	uint8_t pwds_key_pbkdf2[32];					//New

    virtual void setScreenMode();
    virtual void setScreenLanguage();
    virtual void defaultValues();
	void configAESPeripheral(uint8_t keyAES[], uint8_t ivAES[], uint8_t headerAES[], uint8_t type);
	void configAESPeripheral_v2(uint8_t keyAES[], uint8_t ivAES[]);
	void decryptSecret(uint8_t  decrypted_text[SIZE_CRYPT]);
	void decryptSecretWithCombinations(uint8_t  decrypted_text[SIZE_CRYPT]);
	bool checkDecryptedText(uint8_t  decrypted_text[SIZE_CRYPT]);
	void processingSecret(void);
	void sortPasswordsLexicographically(uint8_t pwds[10][32], uint8_t num_pwd);
	uint8_t getRNG16Bytes(uint8_t *buffer);
	uint8_t pbkdf2_sha256(const uint8_t *password, size_t pass_len, const uint8_t *salt, size_t salt_len, uint32_t iterations, uint8_t *derived_key, size_t dk_len);
};

#endif // DECRYPT_TAG_HPP
