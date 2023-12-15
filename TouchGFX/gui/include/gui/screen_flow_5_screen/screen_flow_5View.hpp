#ifndef SCREEN_FLOW_5VIEW_HPP
#define SCREEN_FLOW_5VIEW_HPP

#include <gui_generated/screen_flow_5_screen/screen_flow_5ViewBase.hpp>
#include <gui/screen_flow_5_screen/screen_flow_5Presenter.hpp>
#include <images/BitmapDatabase.hpp>

/********** Custom include's ***********/
#include <texts/TextKeysAndLanguages.hpp>
/***************************************/

class screen_flow_5View : public screen_flow_5ViewBase
{
public:
    screen_flow_5View();
    virtual ~screen_flow_5View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

	/*********** Custom public *************/
    virtual void changeScreen(uint8_t screen);
    virtual void changeFlash(uint8_t state);
    /***/
    virtual void menuVersionPressed();
    virtual void menuBrightnessPressed();
    virtual void menuLanguagePressed();
    virtual void menuAppearancePressed();
    virtual void versionUpdatePressed();
    virtual void sliderSetDutyCicle(int value);
    virtual void languageEnglishPressed();
    virtual void languageSpanishPressed();
    virtual void appearanceLightPressed();
    virtual void appearanceDarkPressed();
    virtual void backPressed();
    /***/
    virtual void setScreenMode();
    virtual void setScreenLanguage();
	/***************************************/

protected:

    uint8_t btn_update_count;

};

#endif // SCREEN_FLOW_5VIEW_HPP
