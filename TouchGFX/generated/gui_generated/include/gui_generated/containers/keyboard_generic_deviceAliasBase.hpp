/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef KEYBOARD_GENERIC_DEVICEALIASBASE_HPP
#define KEYBOARD_GENERIC_DEVICEALIASBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>

class keyboard_generic_deviceAliasBase : public touchgfx::Container
{
public:
    keyboard_generic_deviceAliasBase();
    virtual ~keyboard_generic_deviceAliasBase();
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box keyboard_background;
    touchgfx::Container alpha_num_layout_1;
    touchgfx::Image layout_1_key_hide;
    touchgfx::Image layout_1_key_space;
    touchgfx::Image layout_1_key_mode;
    touchgfx::Image layout_1_key_delete;
    touchgfx::Image layout_1_key_shift;
    touchgfx::Image layout_1_key_1;
    touchgfx::Image layout_1_key_2;
    touchgfx::Image layout_1_key_3;
    touchgfx::Image layout_1_key_4;
    touchgfx::Image layout_1_key_5;
    touchgfx::Image layout_1_key_6;
    touchgfx::Image layout_1_key_7;
    touchgfx::Image layout_1_key_8;
    touchgfx::Image layout_1_key_9;
    touchgfx::Image layout_1_key_10;
    touchgfx::Image layout_1_key_11;
    touchgfx::Image layout_1_key_12;
    touchgfx::Image layout_1_key_13;
    touchgfx::Image layout_1_key_14;
    touchgfx::Image layout_1_key_15;
    touchgfx::Image layout_1_key_16;
    touchgfx::Image layout_1_key_17;
    touchgfx::Image layout_1_key_18;
    touchgfx::Image layout_1_key_19;
    touchgfx::Image layout_1_key_20;
    touchgfx::Image layout_1_key_21;
    touchgfx::Image layout_1_key_22;
    touchgfx::Image layout_1_key_23;
    touchgfx::Image layout_1_key_24;
    touchgfx::Image layout_1_key_25;
    touchgfx::Image layout_1_key_26;
    touchgfx::Container alpha_num_layout_2;
    touchgfx::Image layout_2_key_hide;
    touchgfx::Image layout_2_key_space;
    touchgfx::Image layout_2_key_mode;
    touchgfx::Image layout_2_key_delete;
    touchgfx::Image layout_2_key_shift;
    touchgfx::Image layout_2_key_1;
    touchgfx::Image layout_2_key_2;
    touchgfx::Image layout_2_key_3;
    touchgfx::Image layout_2_key_4;
    touchgfx::Image layout_2_key_5;
    touchgfx::Image layout_2_key_6;
    touchgfx::Image layout_2_key_7;
    touchgfx::Image layout_2_key_8;
    touchgfx::Image layout_2_key_9;
    touchgfx::Image layout_2_key_10;
    touchgfx::Image layout_2_key_11;
    touchgfx::Image layout_2_key_12;
    touchgfx::Image layout_2_key_13;
    touchgfx::Image layout_2_key_14;
    touchgfx::Image layout_2_key_15;
    touchgfx::Image layout_2_key_16;
    touchgfx::Image layout_2_key_17;
    touchgfx::Image layout_2_key_18;
    touchgfx::Image layout_2_key_19;
    touchgfx::Image layout_2_key_20;
    touchgfx::Image layout_2_key_21;
    touchgfx::Image layout_2_key_22;
    touchgfx::Image layout_2_key_23;
    touchgfx::Image layout_2_key_24;
    touchgfx::Image layout_2_key_25;

private:

};

#endif // KEYBOARD_GENERIC_DEVICEALIASBASE_HPP
