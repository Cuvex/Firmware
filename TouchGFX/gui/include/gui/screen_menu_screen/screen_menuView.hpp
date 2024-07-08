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

#ifndef SCREEN_MENUVIEW_HPP
#define SCREEN_MENUVIEW_HPP

#include <gui_generated/screen_menu_screen/screen_menuViewBase.hpp>
#include <gui/screen_menu_screen/screen_menuPresenter.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class screen_menuView : public screen_menuViewBase
{
public:
    screen_menuView();
    virtual ~screen_menuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void changeScreen(uint8_t screen);
    virtual void setScreenMode();
    virtual void setScreenLanguage();

protected:
};

#endif // SCREEN_MENUVIEW_HPP
