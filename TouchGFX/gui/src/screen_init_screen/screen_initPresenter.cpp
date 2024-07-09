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

#include <gui/screen_init_screen/screen_initView.hpp>
#include <gui/screen_init_screen/screen_initPresenter.hpp>

screen_initPresenter::screen_initPresenter(screen_initView& v)
    : view(v)
{

}

void screen_initPresenter::activate()
{

}

void screen_initPresenter::deactivate()
{

}

/*
 * view -> presenter -> model
 */

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_initPresenter::changeScreen(uint16_t screen)
{
	model->changeScreen(screen);
}

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_initPresenter::changeFlash(uint16_t state)
{
	model->changeFlash(state);
}
