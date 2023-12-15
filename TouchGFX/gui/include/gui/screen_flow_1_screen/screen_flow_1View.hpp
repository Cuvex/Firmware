#ifndef SCREEN_FLOW_1VIEW_HPP
#define SCREEN_FLOW_1VIEW_HPP

#include <gui_generated/screen_flow_1_screen/screen_flow_1ViewBase.hpp>
#include <gui/screen_flow_1_screen/screen_flow_1Presenter.hpp>

/********** Custom includes ************/
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/CustomKeyboard.hpp>
#include <gui/widgets/qrcode/QRCodeWidget.hpp>
#include <gui/widgets/qrcode/QRCode.hpp>
/***************************************/

class screen_flow_1View : public screen_flow_1ViewBase
{
public:
    screen_flow_1View();
    virtual ~screen_flow_1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

	/*********** Custom public *************/
    virtual void tickEventScreen();
    /***/
    virtual void changeScreen(uint8_t screen);
    virtual void changeStateNfc(uint8_t state);
    virtual void updateStateNfc(uint16_t state);
    /***/
    virtual void hideKeyboardPressed();
    virtual void showKeyboardPressed();
    virtual void enterKeyboardPressed();
    /***/
    virtual void assignAliasPressed();
    virtual void acceptSuccessPressed();
    virtual void qrSmallPressed();
    virtual void qrBackPressed();
    /***/
    virtual void setScreenMode();
    virtual void setScreenLanguage();
	/***************************************/

protected:

	/*********** Custom protected *************/
    CustomKeyboard keyboard;
    QRCodeWidget qr_code;
    QR *code;
	/******************************************/

};

#endif // SCREEN_FLOW_1VIEW_HPP
