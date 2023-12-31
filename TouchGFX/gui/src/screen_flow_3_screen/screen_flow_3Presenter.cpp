#include <gui/screen_flow_3_screen/screen_flow_3View.hpp>
#include <gui/screen_flow_3_screen/screen_flow_3Presenter.hpp>

screen_flow_3Presenter::screen_flow_3Presenter(screen_flow_3View& v)
    : view(v)
{

}

void screen_flow_3Presenter::activate()
{

}

void screen_flow_3Presenter::deactivate()
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
void screen_flow_3Presenter::changeScreen(uint16_t screen)
{
	model->changeScreen(screen);
}

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_3Presenter::changeFlash(uint16_t state)
{
	model->changeFlash(state);
}

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_3Presenter::changeStateNfc(uint16_t state)
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
void screen_flow_3Presenter::updateStateNfc(uint16_t state)
{
	view.updateStateNfc(state);
}
