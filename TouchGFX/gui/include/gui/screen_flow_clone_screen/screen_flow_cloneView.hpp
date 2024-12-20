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

#ifndef SCREEN_FLOW_CLONEVIEW_HPP
#define SCREEN_FLOW_CLONEVIEW_HPP

#include <gui_generated/screen_flow_clone_screen/screen_flow_cloneViewBase.hpp>
#include <gui/screen_flow_clone_screen/screen_flow_clonePresenter.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class screen_flow_cloneView : public screen_flow_cloneViewBase
{
public:
    screen_flow_cloneView();
    virtual ~screen_flow_cloneView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

	virtual void changeScreen(uint8_t screen);
	virtual void changeStateNfc(uint8_t state);
	virtual void updateStateNfc(uint16_t state);
	virtual void clonePressed();
	virtual void retryPressed();
	virtual void exitFailPressed();
	virtual void exitSuccessPressed();
    virtual void setScreenMode();
    virtual void setScreenLanguage();
protected:
};

#endif // SCREEN_FLOW_CLONEVIEW_HPP
