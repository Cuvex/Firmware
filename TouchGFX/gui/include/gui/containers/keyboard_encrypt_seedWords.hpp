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

#ifndef KEYBOARD_ENCRYPT_SEEDWORDS_HPP
#define KEYBOARD_ENCRYPT_SEEDWORDS_HPP

#include <gui_generated/containers/keyboard_encrypt_seedWordsBase.hpp>
#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include <gui/common/KeyboardKeyMapping.hpp>
#include <gui/common/KeyboardLayout.hpp>

using namespace touchgfx;

class keyboard_encrypt_seedWords : public keyboard_encrypt_seedWordsBase
{
public:
    keyboard_encrypt_seedWords();
    virtual ~keyboard_encrypt_seedWords() {}

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
    Callback<keyboard_encrypt_seedWords> backspacePressed;

    /*** Callback for when keys are pressed on the keyboard ***/
    Callback<keyboard_encrypt_seedWords, Unicode::UnicodeChar> keyPressed;

    /*** Callback handler for the backspace button ***/
    void backspacePressedHandler();

    /*** Callback handler for key presses ***/
    void keyPressedhandler(Unicode::UnicodeChar keyChar);
};

#endif // KEYBOARD_ENCRYPT_SEEDWORDS_HPP
