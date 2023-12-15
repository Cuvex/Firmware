#ifndef SCREEN_FLOW_2VIEW_HPP
#define SCREEN_FLOW_2VIEW_HPP

#include <gui_generated/screen_flow_2_screen/screen_flow_2ViewBase.hpp>
#include <gui/screen_flow_2_screen/screen_flow_2Presenter.hpp>

/********** Custom includes ************/
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/CustomKeyboard.hpp>
/***************************************/

class screen_flow_2View : public screen_flow_2ViewBase
{
public:
	screen_flow_2View();
	virtual ~screen_flow_2View() {}
	virtual void setupScreen();
	virtual void tearDownScreen();

	/*********** Custom public *************/
    virtual void tickEventScreen();
    /***/
	virtual void changeScreen(uint8_t screen);
    virtual void changeStateNfc(uint8_t state);
    virtual void updateStateNfc(uint16_t state);
	/***/
    virtual void hideKeyboard1Pressed();
    virtual void showKeyboard1Pressed();
    virtual void enterKeyboard1Pressed();
    virtual void hideKeyboard2Pressed();
    virtual void showKeyboard2Pressed();
    virtual void enterKeyboard2Pressed();
    virtual void hideKeyboard3Pressed();
    virtual void showKeyboard3Pressed();
    virtual void enterKeyboard3Pressed();
    virtual void hideKeyboard4Pressed();
    virtual void showKeyboard4Pressed();
    virtual void enterKeyboard4Pressed();
    virtual void hideKeyboard5Pressed();
    virtual void show1Keyboard5Pressed();
    virtual void show2Keyboard5Pressed();
    virtual void enterKeyboard5Pressed();
    virtual void hideKeyboard6Pressed();
    virtual void showKeyboard6Pressed();
    virtual void enterKeyboard6Pressed();
    /***/
	virtual void seedButtonPressed();
	virtual void plainTextButtonPressed();
    virtual void encryptPressed();
    virtual void multisignedYesPressed();
    virtual void multisignedNoPressed();
    virtual void multisignedPlusPressed();
    virtual void multisignedMinusPressed();
    virtual void multisignedSelectPressed();
    virtual void storeCriptogramPressed();
    virtual void successPressed();
    /***/
    virtual void btnUpPressed();
    virtual void btnDownPressed();
    virtual void btnScrollUpPressed();
    virtual void btnScrollDownPressed();
    /***/
    virtual void eye1Pressed();
    virtual void eye2Pressed();
    /***/
    virtual void retryPressed();
    virtual void assignAliasPressed();
    /***/
    virtual void setScreenMode();
    virtual void setScreenLanguage();
	/***************************************/

protected:

	/*********** Custom protected *************/
    CustomKeyboard keyboard;
    uint8_t  text_type;
	uint16_t total_words;
	uint16_t actual_word;
	uint8_t  valid_word;
	uint8_t	 num_pwds;
	uint8_t  actual_pwd;
	uint8_t  flag_refresh_text_area;
    /***/
    uint8_t  words_to_encrypt[50][5];	//48 palabras... 4 char por palabra...
    uint8_t  words_to_check[50][15];	//48 palabras... 8 char por palabra...
	uint8_t  buff_passphrase[105];		//100 caracteres
	uint8_t  buff_plain_text[505];		//500 caracteres
	/***/
	uint8_t  pwds[10][KEYBOARD5_TEXT_TYPED_1_SIZE];		//6 contraseñas... 40 char por contraseña...
	uint8_t  pwd_raw[10*KEYBOARD5_TEXT_TYPED_1_SIZE];	//6*40 = 240
	uint8_t  pwd_sha256[32];							//32
	/***/
	void changeAESPassword(uint8_t keyAES[]);
	/******************************************/
};

#endif // SCREEN_FLOW_2VIEW_HPP
