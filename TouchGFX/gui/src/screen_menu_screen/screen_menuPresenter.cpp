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
 *
 *
 *
 */

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_menuPresenter::changeScreen(uint16_t screen)
{
	model->changeScreen(screen);
}

