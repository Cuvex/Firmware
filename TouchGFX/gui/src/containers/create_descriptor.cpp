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

#include <gui/containers/create_descriptor.hpp>
#include "main.h"

extern struct cuvex cuvex;

create_descriptor::create_descriptor()
{

}

void create_descriptor::initialize()
{
	create_descriptorBase::initialize();
	create_descriptor::setScreenMode();
	create_descriptor::setScreenLanguage();
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void create_descriptor::tickEvent()
{
	/*** Password - Keyboard (password) ***/
	if(keyboard.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard_text_typedBuffer, keyboard.getBuffer(), KEYBOARD_TEXT_TYPED_SIZE) != 0)
		{
			Unicode::snprintf(keyboard_text_typedBuffer, KEYBOARD_TEXT_TYPED_SIZE, keyboard.getBuffer());
			keyboard_text_typed.setWideTextAction(touchgfx::WIDE_TEXT_NONE);

			if(keyboard_text_typed.getTextWidth() <= 160){
				keyboard_text_typed.setPosition(160-(keyboard_text_typed.getTextWidth()/2), 83, keyboard_text_typed.getTextWidth(), 20);
			}
			else{
				keyboard_text_typed.setPosition(76, 83, 160, 20);
			}

			if(keyboard_text_typedBuffer[0] == 0x00){
				keyboard_placeholder.setVisible(true);
				keyboard_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));	//Black (default)
			}
			else{
				keyboard_placeholder.setVisible(false);

				if((keyboard_text_typedBuffer[0] == '0') && (keyboard_text_typedBuffer[1] != 0x00)){
					keyboard_text_typed.setColor(touchgfx::Color::getColorFromRGB(0xE7,0x44,0x3E));	//Red (invalid character)
				}
				else{
					keyboard_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));	//Black (default)
				}
			}
			keyboard_text_area.invalidate();
		}
	}
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void create_descriptor::hideKeyboardPressed()
{
	keyboard_text_info_1.setPosition(0, 16, 320, 20);
	keyboard_text_info_2.setPosition(0, 59, 320, 40);
	keyboard_text_info_3.setPosition(0, 104, 320, 20);
	keyboard_text_info_1_multisignature.setPosition(0, 16, 320, 20);
	keyboard_text_info_2_multisignature.setPosition(0, 59, 320, 40);

	keyboard_text_area.setXY(45, 134);
	keyboard_placeholder.setPosition(62, 139, 180, 20);

	if(keyboard_text_typed.getTextWidth() <= 160){
		keyboard_text_typed.setPosition(160-(keyboard_text_typed.getTextWidth()/2), 139, keyboard_text_typed.getTextWidth(), 20);
	}
	else{
		keyboard_text_typed.setPosition(76, 139, 160, 20);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard.setVisible(false);
	keyboard_btn_hide.setVisible(false);
	keyboard_btn_show.setVisible(true);
	keyboard_btn_enter.setVisible(true);

	if(cuvex.decrypt.descriptor_is_multisignature == true){
		keyboard_text_info_1.setVisible(false);
		keyboard_text_info_2.setVisible(false);
		keyboard_text_info_3.setVisible(true);
		keyboard_text_info_1_multisignature.setVisible(true);
		keyboard_text_info_2_multisignature.setVisible(true);
	}
	else{
		keyboard_text_info_1.setVisible(true);
		keyboard_text_info_2.setVisible(true);
		keyboard_text_info_3.setVisible(true);
		keyboard_text_info_1_multisignature.setVisible(false);
		keyboard_text_info_2_multisignature.setVisible(false);
	}

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void create_descriptor::showKeyboardPressed()
{
	keyboard_text_info_1.setPosition(0, 16, 320, 20);
	keyboard_text_info_2.setPosition(0, 59, 320, 40);
	keyboard_text_info_3.setPosition(0, 48, 320, 20);
	keyboard_text_info_1_multisignature.setPosition(0, 16, 320, 20);
	keyboard_text_info_2_multisignature.setPosition(0, 59, 320, 40);

	keyboard_text_area.setXY(45, 78);
	keyboard_placeholder.setPosition(62, 83, 180, 20);

	if(keyboard_text_typed.getTextWidth() <= 160){
		keyboard_text_typed.setPosition(160-(keyboard_text_typed.getTextWidth()/2), 83, keyboard_text_typed.getTextWidth(), 20);
	}
	else{
		keyboard_text_typed.setPosition(76, 83, 160, 20);
	}

	/*** Selecting visible/hidden elements on the screen ***/
	keyboard.setVisible(true);
	keyboard_btn_hide.setVisible(true);
	keyboard_btn_show.setVisible(false);
	keyboard_btn_enter.setVisible(false);

	if(cuvex.decrypt.descriptor_is_multisignature == true){
		keyboard_text_info_1.setVisible(false);
		keyboard_text_info_2.setVisible(false);
		keyboard_text_info_3.setVisible(true);
		keyboard_text_info_1_multisignature.setVisible(true);
		keyboard_text_info_2_multisignature.setVisible(false);
	}
	else{
		keyboard_text_info_1.setVisible(true);
		keyboard_text_info_2.setVisible(false);
		keyboard_text_info_3.setVisible(true);
		keyboard_text_info_1_multisignature.setVisible(false);
		keyboard_text_info_2_multisignature.setVisible(false);
	}

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void create_descriptor::enterKeyboardPressed()
{
	if((keyboard_text_typedBuffer[0] != 0x00) && ((keyboard_text_typedBuffer[0] != '0') || (keyboard_text_typedBuffer[1] == 0x00)))
	{
		memset(cuvex.decrypt.descriptor_acount_number, 0x00, sizeof(cuvex.decrypt.descriptor_acount_number));

		for(int i=0; i<KEYBOARD_TEXT_TYPED_SIZE; i++){
			cuvex.decrypt.descriptor_acount_number[i] = keyboard_text_typedBuffer[i];
		}

		if(createDescriptorCallback && createDescriptorCallback->isValid()){
			createDescriptorCallback->execute(true);
		}

		/*** Screen update ***/
		background.invalidate();
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void create_descriptor::setCreateDescriptorMultisignatureInfo()
{
	/*** Selecting visible/hidden elements on the screen ***/
	keyboard_text_info_1.setVisible(false);
	keyboard_text_info_2.setVisible(false);
	keyboard_text_info_1_multisignature.setVisible(true);
	keyboard_text_info_2_multisignature.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void create_descriptor::setCreateDescriptorCallback(touchgfx::GenericCallback<bool>& cb)
{
	createDescriptorCallback = &cb;
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void create_descriptor::setScreenMode()
{
	/*** Setting screen elements based on mode (dark/light) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		keyboard_btn_enter.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_info_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_text_info_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_text_info_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_text_info_1_multisignature.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_text_info_2_multisignature.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	}

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void create_descriptor::setScreenLanguage()
{
	/*** Text configuration based on selected language (Spanish/English) ***/
	if(cuvex.info.language == SPANISH){
		Texts::setLanguage(SP);
	}
	else{
		Texts::setLanguage(GB);
	}

	/*** Screen update ***/
	background.invalidate();
}





