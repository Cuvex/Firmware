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

#include <gui/containers/verify_address.hpp>
#include "main.h"

extern struct cuvex cuvex;

verify_address::verify_address()
{

}

void verify_address::initialize()
{
	verify_addressBase::initialize();
	verify_address::setScreenMode();
	verify_address::setScreenLanguage();
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
void verify_address::tickEvent()
{
	const char* valid_characters = "0123456789/";
	uint8_t aux_ascii_buffer[KEYBOARD_TEXT_TYPED_SIZE] = {0};

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

			if(keyboard_text_typedBuffer[0] == 0x00)
			{
				keyboard_placeholder.setVisible(true);
				keyboard_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));	//Black (default)
			}
			else
			{
				keyboard_placeholder.setVisible(false);
				keyboard_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));	//Black (default)

		        for(int i=0; i<KEYBOARD_TEXT_TYPED_SIZE-1; i++){
		            if(keyboard_text_typedBuffer[i] < 128){
		            	aux_ascii_buffer[i] = static_cast<uint8_t>(keyboard_text_typedBuffer[i]);
		            }
		            else{
		            	aux_ascii_buffer[i] = '?';
		            }
		        }

		        for(int i=0; i<strlen((char *) aux_ascii_buffer); i++){
		            if(strchr(valid_characters, aux_ascii_buffer[i]) == 0x00){
		            	keyboard_text_typed.setColor(touchgfx::Color::getColorFromRGB(0xE7,0x44,0x3E));	//Red (invalid character)
		                break;
		            }
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
void verify_address::hideKeyboardPressed()
{
	keyboard_text_info_1.setPosition(0, 16, 320, 20);
	keyboard_text_info_2.setPosition(0, 59, 320, 40);
	keyboard_text_info_3_1.setPosition(0, 104, 172, 20);
	keyboard_text_info_3_2.setPosition(172, 104, 148, 20);
	keyboard_text_info_4_1.setPosition(0, 48, 144, 20);
	keyboard_text_info_4_2.setPosition(144, 48, 176, 20);

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
	keyboard_text_info_1.setVisible(true);
	keyboard_text_info_2.setVisible(true);
	keyboard_text_info_3_1.setVisible(true);
	keyboard_text_info_3_2.setVisible(true);
	keyboard_text_info_4_1.setVisible(false);
	keyboard_text_info_4_2.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void verify_address::showKeyboardPressed()
{
	keyboard_text_info_1.setPosition(0, 16, 320, 20);
	keyboard_text_info_2.setPosition(0, 59, 320, 40);
	keyboard_text_info_3_1.setPosition(0, 48, 172, 20);
	keyboard_text_info_3_2.setPosition(172, 48, 148, 20);
	keyboard_text_info_4_1.setPosition(0, 48, 144, 20);
	keyboard_text_info_4_2.setPosition(144, 48, 176, 20);

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
	keyboard_text_info_1.setVisible(true);
	keyboard_text_info_2.setVisible(false);
	keyboard_text_info_3_1.setVisible(false);
	keyboard_text_info_3_2.setVisible(false);
	keyboard_text_info_4_1.setVisible(true);
	keyboard_text_info_4_2.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void verify_address::enterKeyboardPressed()
{
	uint8_t ascii_buffer[KEYBOARD_TEXT_TYPED_SIZE] = {0};
	int ascii_len = 0;
	bool error = false;

	if(keyboard_text_typedBuffer[0] != 0x00)
	{
		/*** Unicodechar to uint8_t (ascii) ***/
		for(int i=0; i<KEYBOARD_TEXT_TYPED_SIZE; i++)
		{
			if(keyboard_text_typedBuffer[i] < 128){
				ascii_buffer[ascii_len++] = static_cast<uint8_t>(keyboard_text_typedBuffer[i]);
			}
			else{
				error = true;
				break;
			}
		}

		/*** Check derivation path format ***/
		if(error == false)
		{
			if(checkDerivationPathFormat(ascii_buffer, strlen((char *) ascii_buffer)) == ERROR){
				error = true;
			}
		}

		/*** Visualize in base to success or error --> ERROR: red message... SUCCESS: get derivation_path and callback with true ***/
		if(error == false)
		{
			memset(cuvex.decrypt.derivation_path, 0x00, sizeof(cuvex.decrypt.derivation_path));

			cuvex.decrypt.derivation_path[0] = 'm';
			cuvex.decrypt.derivation_path[1] = '/';
			cuvex.decrypt.derivation_path[2] = '8';
			cuvex.decrypt.derivation_path[3] = '4';
			cuvex.decrypt.derivation_path[4] = '/';
			cuvex.decrypt.derivation_path[5] = '0';
			cuvex.decrypt.derivation_path[6] = '/';

			strcat((char *) cuvex.decrypt.derivation_path, (char *) ascii_buffer);

			/*** Callback with password result ***/
			if(verifyAddressCallback && verifyAddressCallback->isValid()){
				verifyAddressCallback->execute(true);
			}
		}
		else{
			keyboard_text_typed.setColor(touchgfx::Color::getColorFromRGB(0xE7,0x44,0x3E));
		}

		/*** Screen update ***/
		background.invalidate();
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
void verify_address::setVerifyAddressCallback(touchgfx::GenericCallback<bool>& cb)
{
	verifyAddressCallback = &cb;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void verify_address::setScreenMode()
{
	/*** Setting screen elements based on mode (dark/light) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		keyboard_btn_enter.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_info_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_text_info_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_text_info_3_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_text_info_3_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_text_info_4_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_text_info_4_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
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
void verify_address::setScreenLanguage()
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
int verify_address::checkDerivationPathFormat(const uint8_t *arr, int len)
{
	bool wait_first_digit = true;
	int number_count = 0;
	int slash_count = 0;

	for(int i=0; i<len; i++)
	{
		if(wait_first_digit == true)
		{
			if(!isdigit(arr[i])){		//Format error --> Digit not expected
				return ERROR;
			}
			else{
				wait_first_digit = false;
				number_count++;
			}
		}
		else
		{
			if(isdigit(arr[i])){		//Format success --> Digit expected
				continue;
			}
			else{
				if(arr[i] == '/'){		//Format success --> Char expected
					wait_first_digit = true;
					slash_count++;
				}
				else{					//Format error --> Char not expected
					return ERROR;
				}
			}
		}
	}

	if((number_count == 3) && (slash_count == 2)){
		return SUCCESS;
	}else{
		return ERROR;
	}
}



