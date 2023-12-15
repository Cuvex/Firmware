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
 *
 * Comunicación: "view -> presenter -> model"
 *
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
 *
 * Comunicación: "model -> presenter -> view"
 *
 */

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_4Presenter::updateStateNfc(uint16_t state)
{
	view.updateStateNfc(state);
}
