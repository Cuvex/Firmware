#ifndef SCREEN_FLOW_PSBTVIEW_HPP
#define SCREEN_FLOW_PSBTVIEW_HPP

#include <gui_generated/screen_flow_psbt_screen/screen_flow_psbtViewBase.hpp>
#include <gui/screen_flow_psbt_screen/screen_flow_psbtPresenter.hpp>

class screen_flow_psbtView : public screen_flow_psbtViewBase
{
public:
    screen_flow_psbtView();
    virtual ~screen_flow_psbtView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREEN_FLOW_PSBTVIEW_HPP
