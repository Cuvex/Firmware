#ifndef SCREEN_FLOW_3VIEW_HPP
#define SCREEN_FLOW_3VIEW_HPP

#include <gui_generated/screen_flow_3_screen/screen_flow_3ViewBase.hpp>
#include <gui/screen_flow_3_screen/screen_flow_3Presenter.hpp>

/********** Custom includes ************/
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/CustomKeyboard.hpp>
#include <gui/widgets/qrcode/QRCodeWidget.hpp>
#include <gui/widgets/qrcode/QRCode.hpp>
/***************************************/

class screen_flow_3View : public screen_flow_3ViewBase
{
public:
    screen_flow_3View();
    virtual ~screen_flow_3View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

	/*********** Custom public *************/
    virtual void tickEventScreen();
    /***/
    virtual void changeScreen(uint8_t screen);
    virtual void changeFlash(uint8_t state);
    virtual void changeStateNfc(uint8_t state);
    virtual void updateStateNfc(uint16_t state);
    /***/
    virtual void hideKeyboardPressed();
    virtual void showKeyboardPressed();
    virtual void enterKeyboardPressed();
    /***/
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
    /***/
    virtual void checkTemporalBlock();
    virtual void setScreenMode();
    virtual void setScreenLanguage();

	/***************************************/

protected:

	/*********** Custom protected *************/
    CustomKeyboard keyboard;
    QRCodeWidget qr_code;
    QR *code;
    /***/
    uint8_t  temporal_block;
    /***/
    uint8_t  text_type;
    uint16_t total_words;
    uint16_t index_words;
	uint8_t	 num_pwds;
	uint8_t  actual_pwd;
	bool 	 pwd_ok;
    /***/
	uint8_t decrypted_text[SIZE_CRYPT] = {0};
	int 	decrypted_lenght = 0;
	/***/
    uint8_t words_decrypted[50][15];				//48 palabras... 4 char por palabra...
    uint8_t words_to_check[50][15];					//48 palabras... 8 char por palabra...
	uint8_t buff_passphrase[105];					//100 caracteres
	uint8_t buff_plain_text[505];					//500 caracteres
	/***/
	uint8_t pwds[10][KEYBOARD_TEXT_TYPED_SIZE];		//6 contraseñas... 40 char por contraseña...
	uint8_t pwd_raw[10*KEYBOARD_TEXT_TYPED_SIZE];	//6*40 = 240
	uint8_t pwd_sha256[32];							//32
	/***/
	void changeAESPassword(uint8_t keyAES[]);
	/******************************************/
};

#endif // SCREEN_FLOW_3VIEW_HPP
