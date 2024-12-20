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

#include <gui/containers/keyboard_encrypt_seedWords.hpp>
#include <touchgfx/Color.hpp>
#include <string.h>

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
keyboard_encrypt_seedWords::keyboard_encrypt_seedWords(): keyboard(), modeBtnTextArea(), backspacePressed(this, &keyboard_encrypt_seedWords::backspacePressedHandler),
keyPressed(this, &keyboard_encrypt_seedWords::keyPressedhandler)
{
	/*** Buffer Initialization ***/
	memset(buffer, 0, sizeof(buffer));

	/*** Assignment of callback for special keys ***/
	layout_3.callbackAreaArray[0].callback = &backspacePressed;

	/*** Initialization of the custom widget "keyboard" ***/
	keyboard.setLayout(&layout_3);
	keyboard.setKeyListener(keyPressed);
	keyboard.setPosition(0, 0, 320, 240);
	keyboard.setTextIndentation();
	keyboard.setKeymappingList(&keyMappingListLayout3);
	keyboard.setBuffer(buffer, BUFFER_SIZE);
	add(keyboard);

	/*** Key initialization "mode" ***/
	modeBtnTextArea.setPosition(3, 95, 76, 25);
	modeBtnTextArea.setColor(Color::getColorFromRGB(0x00, 0x00, 0x00));
	modeBtnTextArea.setTypedText(TypedText(T_ALPHAMODE));
	add(modeBtnTextArea);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboard_encrypt_seedWords::initialize()
{
    keyboard_encrypt_seedWordsBase::initialize();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboard_encrypt_seedWords::backspacePressedHandler()
{
	uint16_t pos = keyboard.getBufferPosition();

	if(pos > 0)
	{
		/*** Clearing the previous input in the buffer and decrementing the position ***/
		buffer[pos - 1] = 0;
		keyboard.setBufferPosition(pos - 1);
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboard_encrypt_seedWords::keyPressedhandler(Unicode::UnicodeChar keyChar)
{

}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboard_encrypt_seedWords::setTouchable(bool touch)
{
	Container::setTouchable(touch);
	keyboard.setTouchable(touch);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
Unicode:: UnicodeChar* keyboard_encrypt_seedWords::getBuffer()
{
	return keyboard.getBuffer();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboard_encrypt_seedWords::clearBuffer()
{
	memset(buffer, 0, BUFFER_SIZE+1);
	keyboard.setBufferPosition(0);
}







