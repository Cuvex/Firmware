/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen_flow_psbt_screen/screen_flow_psbtViewBase.hpp>
#include <touchgfx/Color.hpp>

screen_flow_psbtViewBase::screen_flow_psbtViewBase() :
    interaction1Counter(0)
{
    __background.setPosition(0, 0, 320, 240);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setPosition(0, 0, 320, 240);
    background.setColor(touchgfx::Color::getColorFromRGB(237, 237, 237));
    add(background);
}

screen_flow_psbtViewBase::~screen_flow_psbtViewBase()
{

}

void screen_flow_psbtViewBase::setupScreen()
{

}

void screen_flow_psbtViewBase::afterTransition()
{
    //Interaction1
    //When screen transition ends delay
    //Delay for 1000 ms (60 Ticks)
    interaction1Counter = INTERACTION1_DURATION;
}

void screen_flow_psbtViewBase::handleTickEvent()
{
    if (interaction1Counter > 0)
    {
        interaction1Counter--;
        if (interaction1Counter == 0)
        {

            //Interaction2
            //When Interaction1 completed change screen to screen_menu
            //Go to screen_menu with no screen transition
            application().gotoscreen_menuScreenNoTransition();
        }
    }

}
