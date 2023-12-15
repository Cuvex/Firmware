#include <gui/screen_flow_1_screen/screen_flow_1View.hpp>

/*******************************/
#include "main.h"
extern struct cuvex cuvex;
/*******************************/

screen_flow_1View::screen_flow_1View()
{
	add(qr_code);
}

void screen_flow_1View::setupScreen()
{
	screen_flow_1ViewBase::setupScreen();
	screen_flow_1View::setScreenMode();
	screen_flow_1View::setScreenLanguage();
	screen_flow_1View::changeScreen(GUI_TO_MAIN_SCREEN_FLOW_1);
	screen_flow_1View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
	screen_flow_1View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ);

	/*** Borrado de buffer's ***/
	memset(keyboard_text_typedBuffer, 0x00, sizeof(keyboard_text_typedBuffer));
	keyboard_alias.clearBuffer();
}

void screen_flow_1View::tearDownScreen()
{
	screen_flow_1ViewBase::tearDownScreen();
	screen_flow_1View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/*
 *
 * Función que se llama periódicamente desde evento de tick (cada 10 ticks)
 *
 */

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_1View::tickEventScreen()
{
	/*** Gestión del teclado (alias) ***/
	if(keyboard_alias.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard_text_typedBuffer, keyboard_alias.getBuffer(), KEYBOARD_TEXT_TYPED_SIZE) != 0)
		{
			Unicode::snprintf(keyboard_text_typedBuffer, KEYBOARD_TEXT_TYPED_SIZE, keyboard_alias.getBuffer());
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
void screen_flow_1View::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_1View::changeStateNfc(uint8_t state)
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
void screen_flow_1View::updateStateNfc(uint16_t state)
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

			if(cuvex.nfc.tag.encripted == true){	//Si tag leído tiene criptograma => Se oculta botón de asignar alias (sino visible)
				btn_assign_alias.setTouchable(false);
				btn_assign_alias.setAlpha(0);
			}
			else{
				btn_assign_alias.setTouchable(true);
				btn_assign_alias.setAlpha(255);
			}

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

	case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_1:
		if(s4_waitReadWriteNFC.isVisible() == true)
		{
			s4_waitReadWriteNFC.setVisible(false);
			s5_writeSuccess.setVisible(true);
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
 * Gestión de pulsaciones del teclado
 *
 */

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_1View::hideKeyboardPressed()
{
	/*** Se bajan los elementos de la pantalla***/
	keyboard_text_info.setPosition(0, 90, 320, 20);
	keyboard_text_area.setXY(45, 120);
	keyboard_btn_enter.setPosition(245, 120, 30, 30);

	if(keyboard_text_typed.getTextWidth() <= 160){
		keyboard_text_typed.setPosition(160-(keyboard_text_typed.getTextWidth()/2), 125, keyboard_text_typed.getTextWidth(), 20);
	}
	else{
		keyboard_text_typed.setPosition(76, 125, 160, 20);
	}

	/*** Actualización pulsadores y teclado ***/
	keyboard_alias.setVisible(false);
	keyboard_btn_hide.setVisible(false);
	keyboard_btn_show.setVisible(true);
	keyboard_btn_enter.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_1View::showKeyboardPressed()
{
	/*** Se suben los elementos de la pantalla***/
	keyboard_text_info.setPosition(0, 40, 320, 20);
	keyboard_text_area.setXY(45, 70);
	keyboard_btn_enter.setPosition(245, 70, 30, 30);

	if(keyboard_text_typed.getTextWidth() <= 160){
		keyboard_text_typed.setPosition(160-(keyboard_text_typed.getTextWidth()/2), 75, keyboard_text_typed.getTextWidth(), 20);
	}
	else{
		keyboard_text_typed.setPosition(76, 75, 160, 20);
	}

	/*** Actualización pulsadores y teclado ***/
	keyboard_alias.setVisible(true);
	keyboard_btn_hide.setVisible(true);
	keyboard_btn_show.setVisible(false);
	keyboard_btn_enter.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_1View::enterKeyboardPressed()
{
	/*** Obtención del texto tecleado ***/
	memset(cuvex.nfc.tag.new_alias, 0x00, SIZE_ALIAS);

	for(int i=0; i<SIZE_ALIAS; i++)
	{
		if(keyboard_text_typedBuffer[i] == 8364){	//Si '€' (8364) se convierte al caracter '¶' (182) para sólo ocupar 1 byte
			cuvex.nfc.tag.new_alias[i] = 182;
		}
		else{
			cuvex.nfc.tag.new_alias[i] = (uint8_t) keyboard_text_typedBuffer[i];
		}
	}

	/*** Notificación a mainTask de que se espera lectura + escritura ***/
	screen_flow_1View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_1);

	/*** Selección de los elementos visibles/ocultos en la pantalla ***/
	s3_typeAlias.setVisible(false);
	s4_waitReadWriteNFC.setVisible(true);

	/*** Borrado de los buffers del teclado y de visualización ***/
	memset(keyboard_text_typedBuffer, 0x00, sizeof(keyboard_text_typedBuffer));
	keyboard_alias.clearBuffer();

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
 * Gestión de otras pulsaciones
 *
 */

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_1View::assignAliasPressed()
{
	/*** Selección de los elementos visibles/ocultos en la pantalla ***/
	s2_viewTagInfo.setVisible(false);
	s3_typeAlias.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_1View::acceptSuccessPressed()
{
	application().gotoscreen_menuScreenNoTransition();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_1View::qrSmallPressed()
{
	/*** Generación código QR ***/
	char qr_text[100] = {0};

	strcat(qr_text, (char *) "UID:\"");
	strcat(qr_text, (char *) cuvex.nfc.tag.uid);
	strcat(qr_text, (char *) "\"+Alias:\"");
	strcat(qr_text, (char *) cuvex.nfc.tag.alias);
	strcat(qr_text, (char *) "\"+Info:\"");
	strcat(qr_text, (char *) cuvex.nfc.tag.information);
	strcat(qr_text, (char *) "\"");

	code = new QR(qr_text, 5);
	qr_code.setXY(67,27);
	qr_code.setScale(5);
	qr_code.setQRCode(code);

	/*** Selección de los elementos visibles/ocultos en la pantalla ***/
	container_qr_small_code.setVisible(false);
	btn_assign_alias.setVisible(false);
	close_button.setVisible(false);
	btn_back.setVisible(true);
	qr_code.setVisible(true);
	text_alias_info.setVisible(false);
	text_alias.setVisible(false);
	text_uid_info.setVisible(false);
	text_uid.setVisible(false);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_1View::qrBackPressed()
{
	/*** Selección de los elementos visibles/ocultos en la pantalla ***/
	container_qr_small_code.setVisible(true);
	btn_assign_alias.setVisible(true);
	close_button.setVisible(true);
	btn_back.setVisible(false);
	qr_code.setVisible(false);

	if(cuvex.nfc.tag.alias[0] == 0x00){
		text_uid_info.setVisible(true);
		text_uid.setVisible(true);
		text_alias_info.setVisible(false);
		text_alias.setVisible(false);
	}
	else{
		text_uid_info.setVisible(false);
		text_uid.setVisible(false);
		text_alias_info.setVisible(true);
		text_alias.setVisible(true);
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
 * Funciones auxiliares
 *
 */

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_1View::setScreenMode()
{
	/*** Configuración de elementos de pantalla en función al modo (oscuro/claro) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		/***/
		init_nfc_text1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		init_nfc_text2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		wait_read_nfc_text1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		wait_read_nfc_text2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		text_uid.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_alias.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_uid_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_alias_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_assign_alias.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_assign_alias.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		circle_qr_smallPainter.setColor(touchgfx::Color::getColorFromRGB(0xFF,0xFF,0xFF));
		text_qr_small.setColor(touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0));
		btn_back.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_back.setIconBitmaps(Bitmap(BITMAP_BACK_DARK_ID), Bitmap(BITMAP_BACK_ID));
		/***/
		keyboard_text_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard_btn_show.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		/***/
		wait_read_write_nfc_text1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		wait_read_write_nfc_text2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		btn_accept_success.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_accept_success.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		write_success_text.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
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
void screen_flow_1View::setScreenLanguage()
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





