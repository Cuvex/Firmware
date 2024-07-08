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

#include <gui/common/CustomKeyboard.hpp>
#include <string.h>
#include <touchgfx/Color.hpp>

/************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/
CustomKeyboard::CustomKeyboard() : keyboard(), modeBtnTextArea(), capslockPressed(this, &CustomKeyboard::capslockPressedHandler), backspacePressed(this, &CustomKeyboard::backspacePressedHandler),
modePressed(this, &CustomKeyboard::modePressedHandler), keyPressed(this, &CustomKeyboard::keyPressedhandler), alphaKeys(true), uppercaseKeys(false), firstCharacterEntry(false)
{
	/*** Assignment of callbacks in the zones of the keyboard that require them, and layout assignment ***/
	layout_1.callbackAreaArray[0].callback = &capslockPressed;
	layout_1.callbackAreaArray[1].callback = &backspacePressed;
	layout_1.callbackAreaArray[2].callback = &modePressed;
	keyboard.setLayout(&layout_1);
	keyboard.setKeyListener(keyPressed);
	keyboard.setPosition(0, 0, 320, 240);
	keyboard.setTextIndentation();

	/*** Assignment of the buffer associated with the keyboard ***/
	memset(buffer, 0, sizeof(buffer));
	keyboard.setBuffer(buffer, BUFFER_SIZE);

	uppercaseKeys = true;
	firstCharacterEntry = true;

	modeBtnTextArea.setPosition(3, 93, 76, 25);
	modeBtnTextArea.setColor(Color::getColorFromRGB(0x00, 0x00, 0x00));

	setKeyMappingList();

	add(keyboard);
	add(modeBtnTextArea);
}

/************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/
void CustomKeyboard::setKeyMappingList()
{
	if(alphaKeys == true)
	{
		modeBtnTextArea.setTypedText(TypedText(T_ALPHAMODE));

		if(uppercaseKeys == true){
			keyboard.setKeymappingList(&keyMappingListAlphaUpper);
		}
		else{
			keyboard.setKeymappingList(&keyMappingListAlphaLower);
		}
	}
	else
	{
		modeBtnTextArea.setTypedText(TypedText(T_NUMMODE));

		if(uppercaseKeys == true){
			keyboard.setKeymappingList(&keyMappingListNumUpper);
		}
		else{
			keyboard.setKeymappingList(&keyMappingListNumLower);
		}
	}
}

/************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/
void CustomKeyboard::backspacePressedHandler()
{
	uint16_t pos = keyboard.getBufferPosition();

	if(pos > 0)
	{
		/*** Clearing the previous input in the buffer and decrementing the position ***/
		buffer[pos - 1] = 0;
		keyboard.setBufferPosition(pos - 1);

		/*** Changing the key mapping if the first character has been entered ***/
		if(pos == 1)
		{
			firstCharacterEntry = true;
			uppercaseKeys = true;
			setKeyMappingList();
		}
	}
}

/************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/
void CustomKeyboard::capslockPressedHandler()
{
	uppercaseKeys = !uppercaseKeys;
	setKeyMappingList();
}

/************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/
void CustomKeyboard::modePressedHandler()
{
	alphaKeys = !alphaKeys;

	if(alphaKeys == true)
	{
		layout_1.callbackAreaArray[0].callback = &capslockPressed;
		layout_1.callbackAreaArray[1].callback = &backspacePressed;
		layout_1.callbackAreaArray[2].callback = &modePressed;
		keyboard.setLayout(&layout_1);

		if(firstCharacterEntry == true){
			uppercaseKeys = true;
		}
		else{
			uppercaseKeys = false;
		}
	}
	else
	{
		layout_2.callbackAreaArray[0].callback = &capslockPressed;
		layout_2.callbackAreaArray[1].callback = &backspacePressed;
		layout_2.callbackAreaArray[2].callback = &modePressed;
		keyboard.setLayout(&layout_2);

		uppercaseKeys = false;
	}

	setKeyMappingList();
}

/************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/
void CustomKeyboard::keyPressedhandler(Unicode::UnicodeChar keyChar)
{
	/*** After the first keystroke, the keyboard switches to lowercase ***/
	if((firstCharacterEntry == true) && (keyChar != 0))
	{
		firstCharacterEntry = false;
		uppercaseKeys = false;
		setKeyMappingList();
	}
}

/************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/
void CustomKeyboard::setTouchable(bool touch)
{
	Container::setTouchable(touch);
	keyboard.setTouchable(touch);
}

/************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/
Unicode:: UnicodeChar* CustomKeyboard::getBuffer()
{
	return keyboard.getBuffer();
}

/************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/
void CustomKeyboard::clearBuffer()
{
	memset(buffer, 0, BUFFER_SIZE+1);
	keyboard.setBufferPosition(0);
	firstCharacterEntry = true;
	uppercaseKeys = true;
	setKeyMappingList();
}
