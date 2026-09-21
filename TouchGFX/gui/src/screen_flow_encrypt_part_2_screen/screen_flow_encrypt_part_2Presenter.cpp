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

#include <gui/screen_flow_encrypt_part_2_screen/screen_flow_encrypt_part_2View.hpp>
#include <gui/screen_flow_encrypt_part_2_screen/screen_flow_encrypt_part_2Presenter.hpp>

screen_flow_encrypt_part_2Presenter::screen_flow_encrypt_part_2Presenter(screen_flow_encrypt_part_2View& v)
: view(v)
{

}

void screen_flow_encrypt_part_2Presenter::activate()
{

}

void screen_flow_encrypt_part_2Presenter::deactivate()
{

}

/*
 * view -> presenter -> model
 */

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_encrypt_part_2Presenter::changeScreen(uint16_t screen)
{
	model->changeScreen(screen);
}

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_encrypt_part_2Presenter::changeStateNfc(uint16_t state)
{
	model->changeStateNfc(state);
}

/*
 * model -> presenter -> view
 */

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_encrypt_part_2Presenter::updateStateNfc(uint16_t state)
{
	view.updateStateNfc(state);
}
