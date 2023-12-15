#ifndef SCREEN_MENUVIEW_HPP
#define SCREEN_MENUVIEW_HPP

#include <gui_generated/screen_menu_screen/screen_menuViewBase.hpp>
#include <gui/screen_menu_screen/screen_menuPresenter.hpp>

/********** Custom include's ***********/
#include <texts/TextKeysAndLanguages.hpp>
/***************************************/

class screen_menuView : public screen_menuViewBase
{
public:
    screen_menuView();
    virtual ~screen_menuView() {}
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

#endif // SCREEN_MENUVIEW_HPP
