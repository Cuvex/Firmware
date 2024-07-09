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

#ifndef SCREEN_INITVIEW_HPP
#define SCREEN_INITVIEW_HPP

#include <gui_generated/screen_init_screen/screen_initViewBase.hpp>
#include <gui/screen_init_screen/screen_initPresenter.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class screen_initView : public screen_initViewBase
{
public:
    screen_initView();
    virtual ~screen_initView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void tickEventScreen();
    virtual void changeScreen(uint8_t screen);
    virtual void changeFlash(uint8_t state);
    virtual void settingsPressed();
    virtual void languageEnglishPressed();
    virtual void languageSpanishPressed();
    virtual void languageConfirmPressed();
    virtual void hideKeyboardPressed();
    virtual void showKeyboardPressed();
    virtual void enterKeyboardPressed();
    virtual void setScreenMode();
    virtual void setScreenLanguage();

protected:
};

#endif // SCREEN_INITVIEW_HPP
