#ifndef SCREEN_INITVIEW_HPP
#define SCREEN_INITVIEW_HPP

#include <gui_generated/screen_init_screen/screen_initViewBase.hpp>
#include <gui/screen_init_screen/screen_initPresenter.hpp>

/********** Custom include's ***********/
#include <texts/TextKeysAndLanguages.hpp>
/***************************************/

class screen_initView : public screen_initViewBase
{
public:
    screen_initView();
    virtual ~screen_initView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

	/*********** Custom public *************/
    virtual void changeScreen(uint8_t screen);
    /***/
    virtual void setScreenMode();
    virtual void setScreenLanguage();
	/***************************************/

protected:
};

#endif // SCREEN_INITVIEW_HPP
