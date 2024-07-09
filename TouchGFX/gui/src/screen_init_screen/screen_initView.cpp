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

#include <gui/screen_init_screen/screen_initView.hpp>
#include <touchgfx/Color.hpp>
#include "main.h"

extern struct cuvex cuvex;

screen_initView::screen_initView()
{

}

void screen_initView::setupScreen()
{
    screen_initViewBase::setupScreen();
    screen_initView::setScreenMode();
	screen_initView::setScreenLanguage();
    screen_initView::changeScreen(GUI_TO_MAIN_SCREEN_INIT);

    /*** Firmware version ***/
	Unicode::snprintf(fw_versionBuffer, FW_VERSION_SIZE, (char *) cuvex.info.fw_version);

	/*** Device alias ***/
	if((cuvex.device_alias_buffer[0] == 0xFF) && (cuvex.device_alias_buffer[1] == 0xFF) && (cuvex.device_alias_buffer[2] == 0xFF))
	{
		btn_menu.setVisible(false);
		btn_settings.setVisible(true);
		Unicode::snprintf(device_aliasBuffer, DEV_ALIAS_SIZE, (char *) "");
	}
	else
	{
		btn_menu.setVisible(true);
		btn_settings.setVisible(false);
		Unicode::snprintf(device_aliasBuffer, DEV_ALIAS_SIZE, (char *) cuvex.device_alias_buffer);
	}

	/*** Screen update ***/
	background.invalidate();
}

void screen_initView::tearDownScreen()
{
    screen_initViewBase::tearDownScreen();
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
void screen_initView::tickEventScreen()
{
	/*** Device Alias - Keyboard ***/
	if(keyboard_device_alias.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard_text_typedBuffer, keyboard_device_alias.getBuffer(), KEYBOARD_TEXT_TYPED_SIZE) != 0)
		{
			Unicode::snprintf(keyboard_text_typedBuffer, KEYBOARD_TEXT_TYPED_SIZE, keyboard_device_alias.getBuffer());
			keyboard_text_typed.setWideTextAction(touchgfx::WIDE_TEXT_NONE);

			if(keyboard_text_typed.getTextWidth() <= 160){
				keyboard_text_typed.setPosition(160-(keyboard_text_typed.getTextWidth()/2), 75, keyboard_text_typed.getTextWidth(), 20);
			}
			else{
				keyboard_text_typed.setPosition(76, 75, 160, 20);
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
void screen_initView::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_initView::changeFlash(uint8_t state)
{
	presenter->changeFlash(state);
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
void screen_initView::settingsPressed()
{
	/*** Re-config elements on the screen ***/
	s0_logo.setVisible(false);
	s1_settings.setVisible(true);
	s1_1_language.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_initView::languageEnglishPressed()
{
	/*** Re-config elements on the screen ***/
	cuvex.info.language = ENGLISH;
	screen_initView::setScreenLanguage();
	check_language.setPosition(255, 94, 30, 30);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_initView::languageSpanishPressed()
{
	/*** Re-config elements on the screen ***/
	cuvex.info.language = SPANISH;
	screen_initView::setScreenLanguage();
	check_language.setPosition(255, 144, 30, 30);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_initView::languageConfirmPressed()
{
	/*** Re-config elements on the screen ***/
	s1_1_language.setVisible(false);
	s1_2_typeDeviceAlias.setVisible(true);

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
void screen_initView::hideKeyboardPressed()
{
	/*** Re-config elements on the screen ***/
	keyboard_text_info_1.setPosition(0, 70, 320, 20);
	keyboard_text_info_2.setPosition(0, 90, 320, 20);
	keyboard_text_area.setXY(45, 120);
	keyboard_btn_enter.setPosition(245, 120, 30, 30);

	if(keyboard_text_typed.getTextWidth() <= 160){
		keyboard_text_typed.setPosition(160-(keyboard_text_typed.getTextWidth()/2), 125, keyboard_text_typed.getTextWidth(), 20);
	}
	else{
		keyboard_text_typed.setPosition(76, 125, 160, 20);
	}

	keyboard_device_alias.setVisible(false);
	keyboard_btn_hide.setVisible(false);
	keyboard_btn_show.setVisible(true);
	keyboard_btn_enter.setVisible(true);
	btn_confirm_dev_alias.setVisible(true);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_initView::showKeyboardPressed()
{
	/*** Re-config elements on the screen ***/
	keyboard_text_info_1.setPosition(0, 20, 320, 20);
	keyboard_text_info_2.setPosition(0, 40, 320, 20);
	keyboard_text_area.setXY(45, 70);
	keyboard_btn_enter.setPosition(245, 70, 30, 30);

	if(keyboard_text_typed.getTextWidth() <= 160){
		keyboard_text_typed.setPosition(160-(keyboard_text_typed.getTextWidth()/2), 75, keyboard_text_typed.getTextWidth(), 20);
	}
	else{
		keyboard_text_typed.setPosition(76, 75, 160, 20);
	}

	keyboard_device_alias.setVisible(true);
	keyboard_btn_hide.setVisible(true);
	keyboard_btn_show.setVisible(false);
	keyboard_btn_enter.setVisible(true);
	btn_confirm_dev_alias.setVisible(false);

	/*** Screen update ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_initView::enterKeyboardPressed()
{
	/*** Obtaining the typed text (device alias) ***/
	memset(cuvex.device_alias_buffer, 0x00, DEV_ALIAS_SIZE);

	for(int i=0; i<DEV_ALIAS_SIZE; i++)
	{
		if(keyboard_text_typedBuffer[i] == 8364){	//If '€' (8364) is converted to the character '¶' (182) to only occupy 1 byte
			cuvex.device_alias_buffer[i] = 182;
		}
		else{
			cuvex.device_alias_buffer[i] = (uint8_t) keyboard_text_typedBuffer[i];
		}
	}

	/*** Clearing keyboard and display buffers ***/
	memset(keyboard_text_typedBuffer, 0x00, sizeof(keyboard_text_typedBuffer));
	keyboard_device_alias.clearBuffer();

	/*** Save in flash (settings + device alias) ***/
	screen_initView::changeFlash(GUI_TO_MAIN_FLASH_SAVE_SETTINGS_AND_DEVICE_ALIAS);

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
void screen_initView::setScreenMode()
{
	/*** Setting screen elements based on mode (dark/light) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		fw_version.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		device_alias.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
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
void screen_initView::setScreenLanguage()
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


