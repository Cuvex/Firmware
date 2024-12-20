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

#include <gui/screen_flow_settings_screen/screen_flow_settingsView.hpp>
#include <gui/screen_flow_settings_screen/screen_flow_settingsPresenter.hpp>

screen_flow_settingsPresenter::screen_flow_settingsPresenter(screen_flow_settingsView& v)
    : view(v)
{

}

void screen_flow_settingsPresenter::activate()
{

}

void screen_flow_settingsPresenter::deactivate()
{

}

/*
 * view -> presenter -> model
 */

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_settingsPresenter::changeScreen(uint16_t screen)
{
	model->changeScreen(screen);
}

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_settingsPresenter::changeFlash(uint16_t state)
{
	model->changeFlash(state);
}


