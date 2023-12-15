#ifndef KEYBOARDPASSWORD_CONTAINER_HPP
#define KEYBOARDPASSWORD_CONTAINER_HPP

#include <gui_generated/containers/keyboardPassword_containerBase.hpp>
#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include <gui/common/KeyboardKeyMapping.hpp>
#include <gui/common/KeyboardLayout.hpp>

using namespace touchgfx;

/*
 * An alphanumeric keyboard with backspace, space-bar and delete functionality.
 * Keyboard mappings for the keyboard are defined in gui/include/gui/common/KeyboardKeyMapping.hpp.
 * Keyboard layout for the keyboard is defined in gui/include/gui/common/KeyboardLayout.hpp.
 * Please note that the ApplicationFontProvider is initialized and set with the FontManager in main.cpp
 * The fonts and the characters used by the keyboard have to be defined in the assets/texts/texts.xlsx file.
 */

class keyboardPassword_container : public keyboardPassword_containerBase
{
public:
    keyboardPassword_container();
    virtual ~keyboardPassword_container() {}

    virtual void initialize();

    /*** Override setTouchable to also affect the keyboard object inside this CustomKeyboard ***/
    void setTouchable(bool touch);
	Unicode::UnicodeChar *getBuffer();
    virtual void clearBuffer();

protected:
    /*** The size of the buffer that is used by the keyboard ***/
    static const uint8_t BUFFER_SIZE = 41;

    /*** The keyboard which this CustomKeyboard wraps ***/
    Keyboard keyboard;

    /*** The buffer used by the keyboard for text input ***/
    Unicode::UnicodeChar buffer[BUFFER_SIZE];

    /*** Used to display text on top of the button for changing keyboard mode ***/
    TextArea modeBtnTextArea;
    TextArea submodeBtnTextArea;

    /*** Callback for the capslock button ***/
    Callback<keyboardPassword_container> capslockPressed;

    /*** Callback for the backspace button ***/
    Callback<keyboardPassword_container> backspacePressed;

    /*** Callback for the keyboard mode button ***/
    Callback<keyboardPassword_container> modePressed;

    /*** Callback for when keys are pressed on the keyboard ***/
    Callback<keyboardPassword_container, Unicode::UnicodeChar> keyPressed;

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

#endif // KEYBOARDPASSWORD_CONTAINER_HPP
