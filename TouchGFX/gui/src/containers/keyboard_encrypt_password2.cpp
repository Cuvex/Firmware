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

#include <gui/containers/keyboard_encrypt_password2.hpp>
#include <touchgfx/Color.hpp>
#include <string.h>

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
keyboard_encrypt_password2::keyboard_encrypt_password2(): keyboard(), modeBtnTextArea(), submodeBtnTextArea(), capslockPressed(this, &keyboard_encrypt_password2::capslockPressedHandler), backspacePressed(this, &keyboard_encrypt_password2::backspacePressedHandler),
modePressed(this, &keyboard_encrypt_password2::modePressedHandler), keyPressed(this, &keyboard_encrypt_password2::keyPressedhandler), alphaKeys(true), uppercaseKeys(false), firstCharacterEntry(false)
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
void keyboard_encrypt_password2::initialize()
{
    keyboard_encrypt_password2Base::initialize();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboard_encrypt_password2::setKeyMappingList()
{
	if(alphaKeys == true)
	{
		modeBtnTextArea.setTypedText(TypedText(T_ALPHAMODE));
		submodeBtnTextArea.setVisible(false);

		if(uppercaseKeys == true){
			keyboard.setKeymappingList(&keyMappingListLayout1Upper);
		}
		else{
			keyboard.setKeymappingList(&keyMappingListLayout1Lower);
		}
	}
	else
	{
		modeBtnTextArea.setTypedText(TypedText(T_NUMMODE));
		submodeBtnTextArea.setVisible(true);

		if(uppercaseKeys == true){
			submodeBtnTextArea.setTypedText(TypedText(T_SIMB2MODE));
			keyboard.setKeymappingList(&keyMappingListLayout2Upper);
		}
		else{
			submodeBtnTextArea.setTypedText(TypedText(T_SIMB1MODE));
			keyboard.setKeymappingList(&keyMappingListLayout2Lower);
		}
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboard_encrypt_password2::backspacePressedHandler()
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
void keyboard_encrypt_password2::capslockPressedHandler()
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
void keyboard_encrypt_password2::modePressedHandler()
{
	alphaKeys = !alphaKeys;

	if(alphaKeys == true)
	{
		alpha_num_layout_1.setVisible(true);
		alpha_num_layout_2.setVisible(false);

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
		alpha_num_layout_1.setVisible(false);
		alpha_num_layout_2.setVisible(true);

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
void keyboard_encrypt_password2::keyPressedhandler(Unicode::UnicodeChar keyChar)
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
void keyboard_encrypt_password2::setTouchable(bool touch)
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
Unicode:: UnicodeChar* keyboard_encrypt_password2::getBuffer()
{
	return keyboard.getBuffer();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void keyboard_encrypt_password2::clearBuffer()
{
	memset(buffer, 0, BUFFER_SIZE+1);
	keyboard.setBufferPosition(0);
	firstCharacterEntry = true;
	uppercaseKeys = true;
	setKeyMappingList();
}










