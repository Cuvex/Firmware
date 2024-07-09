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

#ifndef KEYBOARDNUMERIC_CONTAINER_HPP
#define KEYBOARDNUMERIC_CONTAINER_HPP

#include <gui_generated/containers/keyboardNumeric_containerBase.hpp>
#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include <gui/common/KeyboardKeyMapping.hpp>
#include <gui/common/KeyboardLayout.hpp>

using namespace touchgfx;

class keyboardNumeric_container : public keyboardNumeric_containerBase
{
public:
    keyboardNumeric_container();
    virtual ~keyboardNumeric_container() {}

    virtual void initialize();

    /*** Override setTouchable to also affect the keyboard object inside this CustomKeyboard ***/
    void setTouchable(bool touch);
	Unicode::UnicodeChar *getBuffer();
    virtual void clearBuffer();

protected:
    /*** The size of the buffer that is used by the keyboard ***/
    static const uint8_t BUFFER_SIZE = 3;

    /*** The keyboard which this CustomKeyboard wraps ***/
    Keyboard keyboard;

    /*** The buffer used by the keyboard for text input ***/
    Unicode::UnicodeChar buffer[BUFFER_SIZE];

    /*** Callback for the backspace button ***/
    Callback<keyboardNumeric_container> backspacePressed;

    /*** Callback for when keys are pressed on the keyboard ***/
    Callback<keyboardNumeric_container, Unicode::UnicodeChar> keyPressed;

    /*** Callback handler for the backspace button ***/
    void backspacePressedHandler();

    /*** Callback handler for the caps-lock button ***/
    void capslockPressedHandler();

    /*** Callback handler for the mode button ***/
    void modePressedHandler();

    /*** Callback handler for key presses ***/
    void keyPressedhandler(Unicode::UnicodeChar keyChar);
};

#endif // KEYBOARDNUMERIC_CONTAINER_HPP
