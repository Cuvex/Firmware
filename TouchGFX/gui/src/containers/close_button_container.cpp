#include <gui/containers/close_button_container.hpp>
#include <touchgfx/Color.hpp>

/*******************************/
#include "main.h"
extern struct cuvex cuvex;
/*******************************/

close_button_container::close_button_container()
{

}

void close_button_container::initialize()
{
	close_button_containerBase::initialize();
	close_button_container::checkScreenMode();
}

/*
 *
 *
 *
 */

/***************************************************************************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ***************************************************************************************************************************************************************************************************/
void close_button_container::crossButtonClicked()
{
	confirm_close_window.setVisible(true);
	confirm_close_window.invalidate();
}

/***************************************************************************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ***************************************************************************************************************************************************************************************************/
void close_button_container::cancelButtonClicked()
{
	confirm_close_window.setVisible(false);
	confirm_close_window.invalidate();
}

/***************************************************************************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ***************************************************************************************************************************************************************************************************/
void close_button_container::confirmButtonClicked()
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
void close_button_container::checkScreenMode()
{
	/*** Configuración de elementos de pantalla en función al modo (oscuro/claro) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F, 0x3F, 0x51));
		/***/
	    cross_button.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
	    cross_button.setIconBitmaps(Bitmap(BITMAP_CERRAR_DARK_ID), Bitmap(BITMAP_CERRAR_ID));
	    textArea.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    cancel_button.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
	    cancel_button.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    confirm_button.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
	    confirm_button.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	}

	/*** Actualización de la pantalla ***/
	background.invalidate();
}
