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

#ifndef KEYBOARD_DECRYPT_VERIFYADDRESS_HPP
#define KEYBOARD_DECRYPT_VERIFYADDRESS_HPP

#include <gui_generated/containers/keyboard_decrypt_verifyAddressBase.hpp>
#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include <gui/common/KeyboardKeyMapping.hpp>
#include <gui/common/KeyboardLayout.hpp>

using namespace touchgfx;

class keyboard_decrypt_verifyAddress : public keyboard_decrypt_verifyAddressBase
{
public:
    keyboard_decrypt_verifyAddress();
    virtual ~keyboard_decrypt_verifyAddress() {}

    virtual void initialize();

    /*** Override setTouchable to also affect the keyboard object inside this CustomKeyboard ***/
    void setTouchable(bool touch);
	Unicode::UnicodeChar *getBuffer();
    virtual void clearBuffer();

protected:
    /*** The size of the buffer that is used by the keyboard ***/
    static const uint8_t BUFFER_SIZE = 21;

    /*** The keyboard which this CustomKeyboard wraps ***/
    Keyboard keyboard;

    /*** The buffer used by the keyboard for text input ***/
    Unicode::UnicodeChar buffer[BUFFER_SIZE];

    /*** Used to display text on top of the button for changing keyboard mode ***/
    TextArea modeBtnTextArea;
    TextArea submodeBtnTextArea;

    /*** Callback for the capslock button ***/
    Callback<keyboard_decrypt_verifyAddress> capslockPressed;

    /*** Callback for the backspace button ***/
    Callback<keyboard_decrypt_verifyAddress> backspacePressed;

    /*** Callback for the keyboard mode button ***/
    Callback<keyboard_decrypt_verifyAddress> modePressed;

    /*** Callback for when keys are pressed on the keyboard ***/
    Callback<keyboard_decrypt_verifyAddress, Unicode::UnicodeChar> keyPressed;

    /*** True if the keyboard should show alpha keys, false for numeric ***/
    bool alphaKeys;

    /*** True if the keyboard should show upper-case keys ***/
    bool uppercaseKeys;

    /*** True if the input position in the text field, and hence the buffer, is at the beginning ***/
    bool firstCharacterEntry;

    /*** Sets the correct key mappings of the keyboard according to alpha/numeric and upper-case/lower-case ***/
    void setKeyMappingList();

    /*** Callback handler for the backspace button ***/
    void backspacePressedHandler();

    /*** Callback handler for the caps-lock button ***/
    void capslockPressedHandler();

    /*** Callback handler for the mode button ***/
    void modePressedHandler();

    /*** Callback handler for key presses ***/
    void keyPressedhandler(Unicode::UnicodeChar keyChar);
};

#endif // KEYBOARD_DECRYPT_VERIFYADDRESS_HPP
