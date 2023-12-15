#ifndef SCREEN_FLOW_3PRESENTER_HPP
#define SCREEN_FLOW_3PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_flow_3View;

class screen_flow_3Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_flow_3Presenter(screen_flow_3View& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~screen_flow_3Presenter() {};

	/*********** Custom public *************/
    virtual void changeScreen(uint16_t screen);
    virtual void changeFlash(uint16_t state);
    virtual void changeStateNfc(uint16_t state);
    virtual void updateStateNfc(uint16_t state);
	/***************************************/

private:
    screen_flow_3Presenter();

    screen_flow_3View& view;
};

#endif // SCREEN_FLOW_3PRESENTER_HPP
