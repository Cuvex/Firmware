#ifndef SCREEN_FLOW_PSBTPRESENTER_HPP
#define SCREEN_FLOW_PSBTPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_flow_psbtView;

class screen_flow_psbtPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_flow_psbtPresenter(screen_flow_psbtView& v);

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

    virtual ~screen_flow_psbtPresenter() {}

private:
    screen_flow_psbtPresenter();

    screen_flow_psbtView& view;
};

#endif // SCREEN_FLOW_PSBTPRESENTER_HPP
