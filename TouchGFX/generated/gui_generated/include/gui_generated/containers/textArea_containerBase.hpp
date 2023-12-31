/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef TEXTAREA_CONTAINERBASE_HPP
#define TEXTAREA_CONTAINERBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/widgets/Box.hpp>

class textArea_containerBase : public touchgfx::Container
{
public:
    textArea_containerBase();
    virtual ~textArea_containerBase();
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Circle circle2;
    touchgfx::PainterRGB888 circle2Painter;
    touchgfx::Circle circle1;
    touchgfx::PainterRGB888 circle1Painter;
    touchgfx::Box box;

private:

};

#endif // TEXTAREA_CONTAINERBASE_HPP
