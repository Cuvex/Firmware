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

#ifndef SCREEN_FLOW_SETTINGSVIEW_HPP
#define SCREEN_FLOW_SETTINGSVIEW_HPP

#include <gui_generated/screen_flow_settings_screen/screen_flow_settingsViewBase.hpp>
#include <gui/screen_flow_settings_screen/screen_flow_settingsPresenter.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class screen_flow_settingsView : public screen_flow_settingsViewBase
{
public:
    screen_flow_settingsView();
    virtual ~screen_flow_settingsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void changeScreen(uint8_t screen);
    virtual void changeFlash(uint8_t state);
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
    virtual void setScreenMode();
    virtual void setScreenLanguage();

protected:
    uint8_t btn_update_count;
};

#endif // SCREEN_FLOW_SETTINGSVIEW_HPP
