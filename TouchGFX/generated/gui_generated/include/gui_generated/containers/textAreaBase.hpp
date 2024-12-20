/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef TEXTAREABASE_HPP
#define TEXTAREABASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/widgets/Box.hpp>

class textAreaBase : public touchgfx::Container
{
public:
    textAreaBase();
    virtual ~textAreaBase();
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

#endif // TEXTAREABASE_HPP