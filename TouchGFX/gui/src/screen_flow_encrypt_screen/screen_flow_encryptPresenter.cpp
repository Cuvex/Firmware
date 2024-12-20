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

#include <gui/screen_flow_encrypt_screen/screen_flow_encryptView.hpp>
#include <gui/screen_flow_encrypt_screen/screen_flow_encryptPresenter.hpp>

screen_flow_encryptPresenter::screen_flow_encryptPresenter(screen_flow_encryptView& v)
    : view(v)
{

}

void screen_flow_encryptPresenter::activate()
{

}

void screen_flow_encryptPresenter::deactivate()
{

}

/*
 * view -> presenter -> model
 */

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_encryptPresenter::changeScreen(uint16_t screen)
{
	model->changeScreen(screen);
}

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_encryptPresenter::changeStateNfc(uint16_t state)
{
	model->changeStateNfc(state);
}

/*
 * model -> presenter -> view
 */

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_encryptPresenter::updateStateNfc(uint16_t state)
{
	view.updateStateNfc(state);
}

