#include <gui/screen_flow_4_screen/screen_flow_4View.hpp>

/*******************************/
#include "main.h"
extern struct cuvex cuvex;
/*******************************/

screen_flow_4View::screen_flow_4View()
{

}

void screen_flow_4View::setupScreen()
{
	screen_flow_4ViewBase::setupScreen();
	screen_flow_4View::setScreenMode();
	screen_flow_4View::setScreenLanguage();
	screen_flow_4View::changeScreen(GUI_TO_MAIN_SCREEN_FLOW_4);
	screen_flow_4View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
	screen_flow_4View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ);
}

void screen_flow_4View::tearDownScreen()
{
	screen_flow_4ViewBase::tearDownScreen();
	screen_flow_4View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/*
 *
 * Comunicación: "view -> presenter -> model"
 *
 */

/***************************************************************************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ***************************************************************************************************************************************************************************************************/
void screen_flow_4View::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_4View::changeStateNfc(uint8_t state)
{
	presenter->changeStateNfc(state);
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/*
 *
 * Comunicación: "model -> presenter -> view"
 *
 */

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_4View::updateStateNfc(uint16_t state)
{
	/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
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

			if(cuvex.nfc.tag.alias[0] == 0x00){		//Si tag leido no tiene alias => Texto con el uid (sino alias)
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
					if(cuvex.nfc.tag.alias[i] == 182){	//Si '¶' (182) se convierte al caracter '€' (8364) para visualización en pantalla
						text_aliasBuffer[i] = 8364;
					}
					else{
						text_aliasBuffer[i] = cuvex.nfc.tag.alias[i];
					}
				}
			}
		}
		break;

	case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_4:
		if(s4_waitReadWriteNFC.isVisible() == true)
		{
			screen_flow_4View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);

			if(cuvex.nfc.tag.encripted == true){
				s4_waitReadWriteNFC.setVisible(false);
				s5_writeError.setVisible(true);
			}
			else{
				s4_waitReadWriteNFC.setVisible(false);
				s6_writeSuccess.setVisible(true);
			}
		}
		break;
	}

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/*
 *
 * Gestión de las pulsaciones táctiles
 *
 */

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_4View::clonePressed()
{
	/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
	if(cuvex.nfc.tag.encripted == true)
	{
		screen_flow_4View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_4);
		s2_viewTagInfo.setVisible(false);
		s4_waitReadWriteNFC.setVisible(true);
	}
	else
	{
		s2_viewTagInfo.setVisible(false);	//Si tarjeta sin criptograma
		s3_readError.setVisible(true);
	}

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_4View::retryPressed()
{
	/*** Re-inicialización del NFC ***/
	screen_flow_4View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
	screen_flow_4View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ);

	/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
	s3_readError.setVisible(false);
	s0_initNFC.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_4View::exitFailPressed()
{
	application().gotoscreen_menuScreenNoTransition();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_4View::exitSuccessPressed()
{
	application().gotoscreen_menuScreenNoTransition();
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/*
 *
 * Funciones auxiliares
 *
 */

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_4View::setScreenMode()
{
	/*** Configuración de elementos de pantalla en función al modo (oscuro/claro) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		/***/
	    init_nfc_text1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    init_nfc_text2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    /***/
	    text1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    /***/
	    btn_clone.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
	    btn_clone.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    text_alias_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    text_uid_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    text_alias.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    text_uid.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    /***/
	    btn_retry.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
	    btn_retry.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    text3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    /***/
	    text4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    /***/
	    btn_exit_fail.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
	    btn_exit_fail.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    text5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    /***/
	    btn_exit_success.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
	    btn_exit_success.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    text6.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	}

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_4View::setScreenLanguage()
{
	/*** Configuración del texto en base al idioma seleccionado (español/ingles) ***/
	if(cuvex.info.language == SPANISH){
		Texts::setLanguage(SP);
	}
	else{
		Texts::setLanguage(GB);
	}

	/*** Actualización de la pantalla ***/
	background.invalidate();
}




