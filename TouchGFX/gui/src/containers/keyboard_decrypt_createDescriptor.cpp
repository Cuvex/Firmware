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

#include <gui/containers/keyboard_decrypt_createDescriptor.hpp>
#include <touchgfx/Color.hpp>
#include <string.h>

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
keyboard_decrypt_createDescriptor::keyboard_decrypt_createDescriptor(): keyboard(), backspacePressed(this, &keyboard_decrypt_createDescriptor::backspacePressedHandler),
keyPressed(this, &keyboard_decrypt_createDescriptor::keyPressedhandler)
{
	/*** Buffer Initialization ***/
	memset(buffer, 0x00, BUFFER_SIZE+1);

	/*** Assignment of callback for special keys ***/
	layout_4.callbackAreaArray[0].callback = &backspacePressed;

	/*** Initialization of the custom widget "keyboard" ***/
	keyboard.setLayout(&layout_4);
	keyboard.setKeyListener(keyPressed);
	keyboard.setPosition(0, 0, 320, 240);
	keyboard.setTextIndentation();
	keyboard.setKeymappingList(&keyMappingListLayout4);
	keyboard.setBuffer(buffer, BUFFER_SIZE);
	add(keyboard);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboard_decrypt_createDescriptor::initialize()
{
    keyboard_decrypt_createDescriptorBase::initialize();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboard_decrypt_createDescriptor::backspacePressedHandler()
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
void keyboard_decrypt_createDescriptor::keyPressedhandler(Unicode::UnicodeChar keyChar)
{

}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboard_decrypt_createDescriptor::setTouchable(bool touch)
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
Unicode:: UnicodeChar* keyboard_decrypt_createDescriptor::getBuffer()
{
	return keyboard.getBuffer();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboard_decrypt_createDescriptor::clearBuffer()
{
	memset(buffer, 0x00, BUFFER_SIZE+1);
	keyboard.setBufferPosition(0);
}








