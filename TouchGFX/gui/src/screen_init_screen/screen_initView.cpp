#include <gui/screen_init_screen/screen_initView.hpp>
#include <touchgfx/Color.hpp>

/*******************************/
#include "main.h"
extern struct cuvex cuvex;
/*******************************/

screen_initView::screen_initView()
{

}

void screen_initView::setupScreen()
{
    screen_initViewBase::setupScreen();
    screen_initView::setScreenMode();
	screen_initView::setScreenLanguage();
    screen_initView::changeScreen(GUI_TO_MAIN_SCREEN_INIT);

    /*** Versión de firmware ***/
	Unicode::snprintf(fw_versionBuffer, FW_VERSION_SIZE, (char *) cuvex.info.fw_version);
	fw_version.invalidate();
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

/*
 *
 * Comunicación: "view -> presenter -> model"
 *
 */

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_initView::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
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
void screen_initView::setScreenMode()
{
	/*** Configuración de elementos de pantalla en función al modo (oscuro/claro) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		/***/
		fw_version.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	}

	/*** Actualización de la pantalla ***/
	background.invalidate();

	/*** Paleta de colores ***/
	//0xED,0xED,0xED  	--> Blanco principal
	//0x3F,0x3F,0x51  	--> Negro principal
	//0x40,0x5C,0xA0	--> Azul auxiliar (noche)
	//0x6B,0x6B,0x7D  	--> Gris auxiliar (noche)
	//0,0,0  			--> N/A
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_initView::setScreenLanguage()
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



