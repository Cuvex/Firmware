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

#include <gui/screen_menu_screen/screen_menuView.hpp>
#include <gui/screen_menu_screen/screen_menuPresenter.hpp>

screen_menuPresenter::screen_menuPresenter(screen_menuView& v)
    : view(v)
{

}

void screen_menuPresenter::activate()
{

}

void screen_menuPresenter::deactivate()
{

}

/*
 * view -> presenter -> model
 */

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_menuPresenter::changeScreen(uint16_t screen)
{
	model->changeScreen(screen);
}

