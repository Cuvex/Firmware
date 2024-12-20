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

#include <gui/screen_menu_screen/screen_menuView.hpp>
#include <touchgfx/Color.hpp>
#include "main.h"

extern struct cuvex cuvex;

screen_menuView::screen_menuView()
{

}

void screen_menuView::setupScreen()
{
    screen_menuViewBase::setupScreen();
    screen_menuView::setScreenMode();
    screen_menuView::setScreenLanguage();
    screen_menuView::changeScreen(GUI_TO_MAIN_SCREEN_MAIN_MENU);
}

void screen_menuView::tearDownScreen()
{
    screen_menuViewBase::tearDownScreen();
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
void screen_menuView::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
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
void screen_menuView::setScreenMode()
{
	/*** Setting screen elements based on mode (dark/light) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F, 0x3F, 0x51));
		btn_encrypt.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_encrypt.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_decrypt.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_decrypt.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_clone.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_clone.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_wallet.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_wallet.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_settings.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_settings.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
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
void screen_menuView::setScreenLanguage()
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


