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

#include <gui/screen_flow_4_screen/screen_flow_4View.hpp>
#include <gui/screen_flow_4_screen/screen_flow_4Presenter.hpp>

screen_flow_4Presenter::screen_flow_4Presenter(screen_flow_4View& v)
    : view(v)
{

}

void screen_flow_4Presenter::activate()
{

}

void screen_flow_4Presenter::deactivate()
{

}

/*
 * view -> presenter -> model
 */

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_4Presenter::changeScreen(uint16_t screen)
{
	model->changeScreen(screen);
}

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_4Presenter::changeStateNfc(uint16_t state)
{
	model->changeStateNfc(state);
}

/*
 * model -> presenter -> view
 */

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_4Presenter::updateStateNfc(uint16_t state)
{
	view.updateStateNfc(state);
}

