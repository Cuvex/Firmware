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

#include <gui/containers/keyboardPassphrase_container.hpp>
#include <touchgfx/Color.hpp>
#include <string.h>

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
keyboardPassphrase_container::keyboardPassphrase_container(): keyboard(), modeBtnTextArea(), submodeBtnTextArea(), capslockPressed(this, &keyboardPassphrase_container::capslockPressedHandler), backspacePressed(this, &keyboardPassphrase_container::backspacePressedHandler),
modePressed(this, &keyboardPassphrase_container::modePressedHandler), keyPressed(this, &keyboardPassphrase_container::keyPressedhandler), alphaKeys(true), uppercaseKeys(false), firstCharacterEntry(false)
{
	/*** Buffer Initialization ***/
	memset(buffer, 0, sizeof(buffer));

	/*** Assignment of callback for special keys ***/
	layout_1.callbackAreaArray[0].callback = &capslockPressed;
	layout_1.callbackAreaArray[1].callback = &backspacePressed;
	layout_1.callbackAreaArray[2].callback = &modePressed;

	/*** Initialization of the custom widget "keyboard" ***/
	keyboard.setLayout(&layout_1);
	keyboard.setKeyListener(keyPressed);
	keyboard.setPosition(0, 0, 320, 240);
	keyboard.setTextIndentation();
	keyboard.setBuffer(buffer, BUFFER_SIZE);
	add(keyboard);

	/*** Auxiliary variables ***/
	uppercaseKeys = true;
	firstCharacterEntry = true;

	/*** Key initialization "mode" ***/
	modeBtnTextArea.setPosition(3, 95, 76, 25);
	modeBtnTextArea.setColor(Color::getColorFromRGB(0x00, 0x00, 0x00));
	add(modeBtnTextArea);

	/*** Key initialization "sub-mode" ***/
	submodeBtnTextArea.setPosition(3, 66, 60, 25);
	submodeBtnTextArea.setColor(Color::getColorFromRGB(0x00, 0x00, 0x00));
	add(submodeBtnTextArea);

	/*** Initial mapping ***/
	setKeyMappingList();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboardPassphrase_container::initialize()
{
    keyboardPassphrase_containerBase::initialize();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboardPassphrase_container::setKeyMappingList()
{
	if(alphaKeys == true)
	{
		modeBtnTextArea.setTypedText(TypedText(T_ALPHAMODE));
		submodeBtnTextArea.setVisible(false);

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
		submodeBtnTextArea.setVisible(true);

		if(uppercaseKeys == true){
			submodeBtnTextArea.setTypedText(TypedText(T_SIMB2MODE));
			keyboard.setKeymappingList(&keyMappingListNumUpper);
		}
		else{
			submodeBtnTextArea.setTypedText(TypedText(T_SIMB1MODE));
			keyboard.setKeymappingList(&keyMappingListNumLower);
		}
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboardPassphrase_container::backspacePressedHandler()
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

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboardPassphrase_container::capslockPressedHandler()
{
	uppercaseKeys = !uppercaseKeys;
	setKeyMappingList();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboardPassphrase_container::modePressedHandler()
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

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboardPassphrase_container::keyPressedhandler(Unicode::UnicodeChar keyChar)
{
	/*** After the first keystroke, the keyboard switches to lowercase ***/
	if((firstCharacterEntry == true) && (keyChar != 0))
	{
		firstCharacterEntry = false;
		uppercaseKeys = false;
		setKeyMappingList();
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboardPassphrase_container::setTouchable(bool touch)
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
Unicode:: UnicodeChar* keyboardPassphrase_container::getBuffer()
{
	return keyboard.getBuffer();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboardPassphrase_container::clearBuffer()
{
	memset(buffer, 0, BUFFER_SIZE+1);
	keyboard.setBufferPosition(0);
	firstCharacterEntry = true;
	uppercaseKeys = true;
	setKeyMappingList();
}









