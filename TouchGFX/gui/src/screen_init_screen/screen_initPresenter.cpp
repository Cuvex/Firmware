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
 *
 *
 *
 */

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_initPresenter::changeScreen(uint16_t screen)
{
	model->changeScreen(screen);
}
