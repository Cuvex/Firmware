#include <gui/screen_flow_5_screen/screen_flow_5View.hpp>

/*******************************/
#include "main.h"
extern struct cuvex cuvex;
/*******************************/

screen_flow_5View::screen_flow_5View(): btn_update_count(0)
{

}

void screen_flow_5View::setupScreen()
{
	screen_flow_5ViewBase::setupScreen();
	screen_flow_5View::setScreenMode();
	screen_flow_5View::setScreenLanguage();
	screen_flow_5View::changeScreen(GUI_TO_MAIN_SCREEN_FLOW_5);
}

void screen_flow_5View::tearDownScreen()
{
	screen_flow_5ViewBase::tearDownScreen();
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
void screen_flow_5View::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_5View::changeFlash(uint8_t state)
{
	presenter->changeFlash(state);
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/*
 *
 * Gestión de las pulsaciones del flujo
 *
 */

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_5View::menuVersionPressed()
{
	/*** Inicialización variable auxiliar (update) ***/
	btn_update_count = 0;

	/*** Versiones de firmware y hardware ***/
	Unicode::snprintf(text_versionBuffer1, TEXT_VERSIONBUFFER1_SIZE, (char *) cuvex.info.fw_version);
	Unicode::snprintf(text_versionBuffer2, TEXT_VERSIONBUFFER2_SIZE, (char *) cuvex.info.hw_version);
	text_version.invalidate();

	/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
	s0_menu.setVisible(false);
	s1_version.setVisible(true);
	text_version.setVisible(true);
	logo.setVisible(true);
	text_caution_alert_spanish.setVisible(false);
	text_caution_alert_english.setVisible(false);
	update_click_view.setVisible(false);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_5View::menuBrightnessPressed()
{
	/*** Actualización del valor del slider ***/
	slider_brightness.setValue(cuvex.info.brightness);

	/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
	s0_menu.setVisible(false);
	s2_brightness.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_5View::menuLanguagePressed()
{
	/*** Posición del check (opción actualmente seleccionada) ***/
	if(cuvex.info.language == SPANISH){
		check_language.setPosition(255, 144, 30, 30);
	}
	else{
		check_language.setPosition(255, 94, 30, 30);
	}

	/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
	s0_menu.setVisible(false);
	s3_language.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_5View::menuAppearancePressed()
{
	/*** Posición del check (opción actualmente seleccionada) ***/
	if(cuvex.info.mode == DARK){
		check_appearance.setPosition(255, 144, 30, 30);
	}
	else{
		check_appearance.setPosition(255, 94, 30, 30);
	}

	/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
	s0_menu.setVisible(false);
	s4_appearance.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_5View::versionUpdatePressed()
{
	if(btn_update_count < 3)
	{
		btn_update_count++;

		if(btn_update_count == 1){
			Unicode::snprintf(update_click_viewBuffer, UPDATE_CLICK_VIEW_SIZE, "3");
			update_click_view.setVisible(true);
			text_version.setVisible(false);
			logo.setVisible(false);

			if(cuvex.info.language == SPANISH){
				text_caution_alert_spanish.setVisible(true);
				text_caution_alert_english.setVisible(false);
			}
			else{
				text_caution_alert_spanish.setVisible(false);
				text_caution_alert_english.setVisible(true);
			}
		}
		else if(btn_update_count == 2){
			Unicode::snprintf(update_click_viewBuffer, UPDATE_CLICK_VIEW_SIZE, "2");
		}
		else if(btn_update_count == 3){
			Unicode::snprintf(update_click_viewBuffer, UPDATE_CLICK_VIEW_SIZE, "1");
		}

		background.invalidate();
	}
	else
	{
		screen_flow_5View::changeFlash(GUI_TO_MAIN_FLASH_ERASE_SIGNATURE);
	}
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_5View::sliderSetDutyCicle(int value)
{
	cuvex.info.brightness = value;
	TIM1->CCR1 = value;
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_5View::languageEnglishPressed()
{
	cuvex.info.language = ENGLISH;
	screen_flow_5View::setScreenLanguage();
	check_language.setPosition(255, 94, 30, 30);
	background.invalidate();
}
/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_5View::languageSpanishPressed()
{
	cuvex.info.language = SPANISH;
	screen_flow_5View::setScreenLanguage();
	check_language.setPosition(255, 144, 30, 30);
	background.invalidate();
}
/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_5View::appearanceLightPressed()
{
	cuvex.info.mode = LIGHT;
	screen_flow_5View::setScreenMode();
	check_appearance.setPosition(255, 94, 30, 30);
	background.invalidate();
}
/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_5View::appearanceDarkPressed()
{
	cuvex.info.mode = DARK;
	screen_flow_5View::setScreenMode();
	check_appearance.setPosition(255, 144, 30, 30);
	background.invalidate();
}
/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_5View::backPressed()
{
	if(s0_menu.isVisible() == false)
	{
		/*** Comunicación con task principal (para guardar settings) ***/
		screen_flow_5View::changeFlash(GUI_TO_MAIN_FLASH_SAVE_SETTINGS);

		/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
		s0_menu.setVisible(true);
		s1_version.setVisible(false);
		s2_brightness.setVisible(false);
		s3_language.setVisible(false);
		s4_appearance.setVisible(false);
		update_click_view.setVisible(false);

		/*** Actualización de la pantalla ***/
		background.invalidate();
	}
	else
	{
		application().gotoscreen_menuScreenNoTransition();
	}
}

/*
 *
 *
 *
 *
 *
 *
 *
 *
 */

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_5View::setScreenMode()
{
	/*** Configuración de elementos de pantalla en función al modo (oscuro/claro) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		back_button.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		back_button.setIconBitmaps(Bitmap(BITMAP_BACK_DARK_ID), Bitmap(BITMAP_BACK_ID));
		/***/
		btn_1_version.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_1_version.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_2_brightness.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_2_brightness.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_3_language.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_3_language.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_4_appearance.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F, 0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_4_appearance.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		/***/
		text_version.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_select_update.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_select_update.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		update_click_view.setWildcardTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_english_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_english_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_english_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_english_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_english_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_english_6.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_english_7.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_english_8.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_english_9.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_spanish_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_spanish_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_spanish_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_spanish_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_spanish_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_spanish_6.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_spanish_7.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_spanish_8.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_spanish_9.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		text_brightness.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		text_language.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_select_lan_english.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_select_lan_english.setIconBitmaps(Bitmap(BITMAP_BTN_APPEARANCE_DARK_ID), Bitmap(BITMAP_BTN_APPEARANCE_DARK_ID));
		btn_select_lan_spanish.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_select_lan_spanish.setIconBitmaps(Bitmap(BITMAP_BTN_APPEARANCE_DARK_ID), Bitmap(BITMAP_BTN_APPEARANCE_DARK_ID));
		/***/
		text_appearance.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_select_mode_dark.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_select_mode_dark.setIconBitmaps(Bitmap(BITMAP_BTN_APPEARANCE_DARK_ID), Bitmap(BITMAP_BTN_APPEARANCE_DARK_ID));
		btn_select_mode_light.setTextColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_select_mode_light.setIconBitmaps(Bitmap(BITMAP_BTN_APPEARANCE_LIGHT_ID), Bitmap(BITMAP_BTN_APPEARANCE_LIGHT_ID));
		lightCircle1Painter.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		lightCircle2Painter.setColor(touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0));
		lightCircle3Painter.setColor(touchgfx::Color::getColorFromRGB(0xD8,0xD9,0xDD));
		darkCircle1Painter.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		darkCircle2Painter.setColor(touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0));
		darkCircle3Painter.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
	}
	else
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		back_button.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		back_button.setIconBitmaps(Bitmap(BITMAP_BACK_ID), Bitmap(BITMAP_BACK_DARK_ID));
		/***/
		btn_1_version.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_1_version.setTextColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_2_brightness.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_2_brightness.setTextColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_3_language.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_3_language.setTextColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_4_appearance.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_4_appearance.setTextColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		text_version.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_select_update.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_select_update.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		update_click_view.setWildcardTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_caution_english_1.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_english_2.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_english_3.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_english_4.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_english_5.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_english_6.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_english_7.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_english_8.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_english_9.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_spanish_1.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_spanish_2.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_spanish_3.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_spanish_4.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_spanish_5.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_spanish_6.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_spanish_7.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_spanish_8.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		text_caution_spanish_9.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		/***/
		text_brightness.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		/***/
		text_language.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_select_lan_english.setTextColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_select_lan_english.setIconBitmaps(Bitmap(BITMAP_BTN_APPEARANCE_LIGHT_ID), Bitmap(BITMAP_BTN_APPEARANCE_LIGHT_ID));
		btn_select_lan_spanish.setTextColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_select_lan_spanish.setIconBitmaps(Bitmap(BITMAP_BTN_APPEARANCE_LIGHT_ID), Bitmap(BITMAP_BTN_APPEARANCE_LIGHT_ID));
		/***/
		text_appearance.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_select_mode_dark.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_select_mode_dark.setIconBitmaps(Bitmap(BITMAP_BTN_APPEARANCE_DARK_ID), Bitmap(BITMAP_BTN_APPEARANCE_DARK_ID));
		btn_select_mode_light.setTextColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_select_mode_light.setIconBitmaps(Bitmap(BITMAP_BTN_APPEARANCE_LIGHT_ID), Bitmap(BITMAP_BTN_APPEARANCE_LIGHT_ID));
		lightCircle1Painter.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		lightCircle2Painter.setColor(touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0));
		lightCircle3Painter.setColor(touchgfx::Color::getColorFromRGB(0xD8,0xD9,0xDD));
		darkCircle1Painter.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		darkCircle2Painter.setColor(touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0));
		darkCircle3Painter.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
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
void screen_flow_5View::setScreenLanguage()
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















