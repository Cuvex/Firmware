/*
 *****************************************************************************
 * @attention
 *
 * Portion Copyright (C) 2024 Semilla3 OÜ.  All Rights Reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef KEYBOARDSEED_CONTAINER_HPP
#define KEYBOARDSEED_CONTAINER_HPP

#include <gui_generated/containers/keyboardSeed_containerBase.hpp>
#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include <gui/common/KeyboardKeyMapping.hpp>
#include <gui/common/KeyboardLayout.hpp>

using namespace touchgfx;

class keyboardSeed_container : public keyboardSeed_containerBase
{
public:
    keyboardSeed_container();
    virtual ~keyboardSeed_container() {}

    virtual void initialize();

    /*** Override setTouchable to also affect the keyboard object inside this CustomKeyboard ***/
    void setTouchable(bool touch);
	Unicode::UnicodeChar *getBuffer();
    virtual void clearBuffer();

protected:
    /*** The size of the buffer that is used by the keyboard ***/
    static const uint8_t BUFFER_SIZE = 5;

    /*** The keyboard which this CustomKeyboard wraps ***/
    Keyboard keyboard;

    /*** The buffer used by the keyboard for text input ***/
    Unicode::UnicodeChar buffer[BUFFER_SIZE];

    /*** Used to display text on top of the button for changing keyboard mode ***/
    TextArea modeBtnTextArea;

    /*** Callback for the backspace button ***/
    Callback<keyboardSeed_container> backspacePressed;

    /*** Callback for when keys are pressed on the keyboard ***/
    Callback<keyboardSeed_container, Unicode::UnicodeChar> keyPressed;

    /*** Callback handler for the backspace button ***/
    void backspacePressedHandler();

    /*** Callback handler for key presses ***/
    void keyPressedhandler(Unicode::UnicodeChar keyChar);
};

#endif // KEYBOARDSEED_CONTAINER_HPP
