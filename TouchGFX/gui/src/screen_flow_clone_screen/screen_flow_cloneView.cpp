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

#include <gui/screen_flow_clone_screen/screen_flow_cloneView.hpp>
#include "main.h"

extern struct cuvex cuvex;

screen_flow_cloneView::screen_flow_cloneView()
{
}

void screen_flow_cloneView::setupScreen()
{
    screen_flow_cloneViewBase::setupScreen();
    screen_flow_cloneView::setScreenMode();
    screen_flow_cloneView::setScreenLanguage();
    screen_flow_cloneView::changeScreen(GUI_TO_MAIN_SCREEN_FLOW_CLONE);
    screen_flow_cloneView::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
    screen_flow_cloneView::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ);
}

void screen_flow_cloneView::tearDownScreen()
{
    screen_flow_cloneViewBase::tearDownScreen();
    screen_flow_cloneView::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
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
void screen_flow_cloneView::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_cloneView::changeStateNfc(uint8_t state)
{
	presenter->changeStateNfc(state);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_cloneView::updateStateNfc(uint16_t state)
{
	switch(state)
	{
	case MAIN_TO_GUI_NFC_ERROR:
	default:
		application().gotoscreen_menuScreenNoTransition();
		break;

	case MAIN_TO_GUI_NFC_INITIALIZED:
		if(s0_initNFC.isVisible() == true)
		{
			s0_initNFC.setVisible(false);
			s1_waitReadNFC.setVisible(true);
		}
		break;

	case MAIN_TO_GUI_NFC_TAG_READED:
		if(s1_waitReadNFC.isVisible() == true)
		{
			s1_waitReadNFC.setVisible(false);
			s2_viewTagInfo.setVisible(true);

			if(cuvex.nfc.tag.alias[0] == 0x00){		//If the 'read' tag doesn't have an alias => Text with the UID (otherwise alias)
				text_uid.setVisible(true);
				text_uid_info.setVisible(true);
				text_alias.setVisible(false);
				text_alias_info.setVisible(false);
				memset(text_uidBuffer, 0x00, TEXT_UID_SIZE);
				Unicode::snprintf(text_uidBuffer, TEXT_UID_SIZE, (const char*) cuvex.nfc.tag.uid);
			}
			else{
				text_uid.setVisible(false);
				text_uid_info.setVisible(false);
				text_alias.setVisible(true);
				text_alias_info.setVisible(true);
				memset(text_aliasBuffer, 0x00, TEXT_ALIAS_SIZE);

				for(int i=0; i<SIZE_ALIAS; i++)
				{
					if(cuvex.nfc.tag.alias[i] == 182){	//If '¶' (182) is converted to the character '€' (8364) for display on screen
						text_aliasBuffer[i] = 8364;
					}
					else{
						text_aliasBuffer[i] = cuvex.nfc.tag.alias[i];
					}
				}
			}
		}
		break;

	case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_CLONE:
	case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_CLONE_T4T_8K:
		if(s4_waitReadWriteNFC.isVisible() == true)
		{
			screen_flow_cloneView::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);

			if((state == MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_CLONE_T4T_8K) && (cuvex.nfc.tag.type != NFC_TAG_TYPE_T4T_8K))	//Error 1, the card being written has not correct format
			{
				text_error_cryptogram.setVisible(false);
				text_error_nfc_type.setVisible(true);
				s4_waitReadWriteNFC.setVisible(false);
				s5_writeError.setVisible(true);
			}
			else if(cuvex.nfc.tag.encripted == true)	//Error 2, the card being written to already has a stored cryptogram
			{
				text_error_cryptogram.setVisible(true);
				text_error_nfc_type.setVisible(false);
				s4_waitReadWriteNFC.setVisible(false);
				s5_writeError.setVisible(true);
			}
			else
			{
				s4_waitReadWriteNFC.setVisible(false);
				s6_writeSuccess.setVisible(true);
			}
		}
		break;
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
void screen_flow_cloneView::clonePressed()
{
	/*** Selecting visible/hidden elements on the screen ***/
	if(cuvex.nfc.tag.encripted == true)
	{
		if(cuvex.nfc.tag.type == NFC_TAG_TYPE_T4T_8K){
			screen_flow_cloneView::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_CLONE_T4T_8K);
		}
		else{
			screen_flow_cloneView::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_CLONE);
		}

		s2_viewTagInfo.setVisible(false);
		s4_waitReadWriteNFC.setVisible(true);
	}
	else
	{
		s2_viewTagInfo.setVisible(false);
		s3_readError.setVisible(true);
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
void screen_flow_cloneView::retryPressed()
{
	application().gotoscreen_menuScreenNoTransition();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_cloneView::exitFailPressed()
{
	application().gotoscreen_menuScreenNoTransition();
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void screen_flow_cloneView::exitSuccessPressed()
{
	application().gotoscreen_menuScreenNoTransition();
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
void screen_flow_cloneView::setScreenMode()
{
	/*** Setting screen elements based on mode (dark/light) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		init_nfc_text1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		init_nfc_text2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_clone.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_clone.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_alias_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_uid_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_alias.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_uid.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_retry.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_retry.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_exit_fail.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_exit_fail.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_error_cryptogram.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_error_nfc_type.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_exit_success.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_exit_success.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text6.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
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
void screen_flow_cloneView::setScreenLanguage()
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




