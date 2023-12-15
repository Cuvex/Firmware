#include <gui/screen_flow_2_screen/screen_flow_2View.hpp>

/*******************************/
#include "main.h"
extern struct cuvex cuvex;
extern HASH_HandleTypeDef hhash;
extern CRYP_HandleTypeDef hcryp;
/*******************************/

screen_flow_2View::screen_flow_2View(): text_type(0), total_words(0), actual_word(0), valid_word(0), num_pwds(1), actual_pwd(0), flag_refresh_text_area(0), words_to_encrypt{0}, words_to_check{0}, buff_passphrase{0}, buff_plain_text{0}, pwds{0}, pwd_raw{0}, pwd_sha256{0}
{

}

void screen_flow_2View::setupScreen()
{
	screen_flow_2ViewBase::setupScreen();
	screen_flow_2View::setScreenMode();
	screen_flow_2View::setScreenLanguage();
	screen_flow_2View::changeScreen(GUI_TO_MAIN_SCREEN_FLOW_2);

	/*** Borrado de buffer's ***/
	memset(keyboard1_text_typedBuffer,   0x00, sizeof(keyboard1_text_typedBuffer));
	memset(keyboard2_text_typedBuffer,   0x00, sizeof(keyboard2_text_typedBuffer));
	memset(keyboard3_text_typedBuffer,   0x00, sizeof(keyboard3_text_typedBuffer));
	memset(keyboard4_text_typedBuffer,   0x00, sizeof(keyboard4_text_typedBuffer));
	memset(keyboard5_text_typed_1Buffer, 0x00, sizeof(keyboard5_text_typed_1Buffer));
	memset(keyboard5_text_typed_2Buffer, 0x00, sizeof(keyboard5_text_typed_2Buffer));
	memset(keyboard6_text_typedBuffer, 	 0x00, sizeof(keyboard6_text_typedBuffer));
	keyboard1_numeric.clearBuffer();
	keyboard2_BIP39.clearBuffer();
	keyboard3_passphrase.clearBuffer();
	keyboard4_plain_text.clearBuffer();
	keyboard5_password_1.clearBuffer();
	keyboard5_password_2.clearBuffer();
	keyboard6_alias.clearBuffer();
}

void screen_flow_2View::tearDownScreen()
{
	screen_flow_2ViewBase::tearDownScreen();
	screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
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
void screen_flow_2View::tickEventScreen()
{
	uint8_t num_of_lines = 0;
	uint8_t str_prediction[KEYBOARD2_TEXT_PREDICTED_SIZE] = {0};

	/*** Gestión del teclado 1 (númerico) ***/
	if(keyboard1_numeric.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard1_text_typedBuffer, keyboard1_numeric.getBuffer(), KEYBOARD1_TEXT_TYPED_SIZE) != 0)
		{
			if(Unicode::atoi(keyboard1_numeric.getBuffer()) == 0){
				memset(keyboard1_text_typedBuffer, 0x00, sizeof(keyboard1_text_typedBuffer));
				keyboard1_numeric.clearBuffer();
			}
			else if(Unicode::atoi(keyboard1_numeric.getBuffer()) > 48){
				keyboard1_text_typed.setColor(touchgfx::Color::getColorFromRGB(0xE7,0x44,0x3E));	//#e7443e
			}
			else{
				keyboard1_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
			}

			Unicode::snprintf(keyboard1_text_typedBuffer, KEYBOARD1_TEXT_TYPED_SIZE, keyboard1_numeric.getBuffer());
			keyboard1_text_area.invalidate();
		}
	}

	/*** Gestión del teclado 2 (semilla BIP39) ***/
	if(keyboard2_BIP39.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard2_text_typedBuffer, keyboard2_BIP39.getBuffer(), KEYBOARD2_TEXT_TYPED_SIZE) != 0)
		{
			Unicode::snprintf(keyboard2_text_typedBuffer, KEYBOARD2_TEXT_TYPED_SIZE, keyboard2_BIP39.getBuffer());
			Unicode::snprintf(keyboard2_text_predictedBuffer, KEYBOARD2_TEXT_PREDICTED_SIZE, keyboard2_BIP39.getBuffer());

			if(Unicode::strlen(keyboard2_text_typedBuffer) >= 3){
				Unicode::toUTF8(keyboard2_text_predictedBuffer, str_prediction, KEYBOARD2_TEXT_PREDICTED_SIZE);
				valid_word = getBip39Word((char *) str_prediction);
				Unicode::snprintf(keyboard2_text_predictedBuffer, KEYBOARD2_TEXT_PREDICTED_SIZE, (char *) str_prediction);
				keyboard2_text_predicted.setVisible(true);
				keyboard2_text_typed.setVisible(false);
			}
			else{
				keyboard2_text_predicted.setVisible(false);
				keyboard2_text_typed.setVisible(true);
				valid_word = false;
			}

			if(valid_word == true){
				keyboard2_text_predicted.setColor(touchgfx::Color::getColorFromRGB(0x14,0x8E,0x53));
			}
			else{
				keyboard2_text_predicted.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
			}

			keyboard2_text_area.invalidate();
		}
	}

	/*** Gestión del teclado 3 (passphrase) ***/
	if(keyboard3_passphrase.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard3_text_typedBuffer, keyboard3_passphrase.getBuffer(), KEYBOARD3_TEXT_TYPED_SIZE) != 0)
		{
			Unicode::snprintf(keyboard3_text_typedBuffer, KEYBOARD3_TEXT_TYPED_SIZE, keyboard3_passphrase.getBuffer());
			keyboard3_text_typed.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);

			num_of_lines = keyboard3_text_typed.getTextWidth()/230;

			if(num_of_lines > 1){
				keyboard3_text_typed.setPosition(60, 50-((num_of_lines-1)*20), 230, 60+((num_of_lines-1)*20));
			}
			else{
				keyboard3_text_typed.setPosition(60, 50, 230, 60);
			}

			Unicode::itoa(Unicode::strlen(keyboard3_text_typedBuffer), keyboard3_char_countBuffer, KEYBOARD3_CHAR_COUNT_SIZE, 10);

			keyboard3_text_area.invalidate();
		}

		if(flag_refresh_text_area == 1)
		{
			num_of_lines = keyboard3_text_typed.getTextWidth()/230;

			if(num_of_lines > 1){
				keyboard3_text_typed.setPosition(60, 50-((num_of_lines-1)*20), 230, 60+((num_of_lines-1)*20));
				keyboard3_text_area.invalidate();
			}

			flag_refresh_text_area = 0;
		}
	}

	/*** Gestión del teclado 4 (plain text) ***/
	if(keyboard4_plain_text.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard4_text_typedBuffer, keyboard4_plain_text.getBuffer(), KEYBOARD4_TEXT_TYPED_SIZE) != 0)
		{
			Unicode::snprintf(keyboard4_text_typedBuffer, KEYBOARD4_TEXT_TYPED_SIZE, keyboard4_plain_text.getBuffer());
			keyboard4_text_typed.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);

			num_of_lines = keyboard4_text_typed.getTextWidth()/230;

			if(num_of_lines > 1){
				keyboard4_text_typed.setPosition(60, 50-((num_of_lines-1)*20), 230, 60+((num_of_lines-1)*20));
			}
			else{
				keyboard4_text_typed.setPosition(60, 50, 230, 60);
			}

			Unicode::itoa(Unicode::strlen(keyboard4_text_typedBuffer), keyboard4_char_countBuffer, KEYBOARD4_CHAR_COUNT_SIZE, 10);

			keyboard4_text_area.invalidate();
		}

		if(flag_refresh_text_area == 1)
		{
			num_of_lines = keyboard4_text_typed.getTextWidth()/230;

			if(num_of_lines > 1){
				keyboard4_text_typed.setPosition(60, 50-((num_of_lines-1)*20), 230, 60+((num_of_lines-1)*20));
				keyboard4_text_area.invalidate();
			}

			flag_refresh_text_area = 0;
		}
	}

	/*** Gestión del teclado 5 - password 1 ***/
	if(keyboard5_password_1.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard5_text_typed_1Buffer, keyboard5_password_1.getBuffer(), KEYBOARD5_TEXT_TYPED_1_SIZE) != 0)
		{
			/*** Obtención de texto tecleado en widget ***/
			Unicode::snprintf(keyboard5_text_typed_1Buffer, KEYBOARD5_TEXT_TYPED_1_SIZE, keyboard5_password_1.getBuffer());
			keyboard5_text_typed_1.setWideTextAction(touchgfx::WIDE_TEXT_NONE);

			/*** Alineamiento de texto dentro de área ***/
			if(keyboard5_text_typed_1.getTextWidth() <= 160){
				keyboard5_text_typed_1.setPosition(160-(keyboard5_text_typed_1.getTextWidth()/2), 40, keyboard5_text_typed_1.getTextWidth(), 20);
			}
			else{
				keyboard5_text_typed_1.setPosition(76, 40, 160, 20);
			}

			/*** Reseteo y relleno de buffer con contraseña oculta ***/
			for(int i=0; i<KEYBOARD5_TEXT_TYPED_HIDE_1_SIZE; i++){
				keyboard5_text_typed_hide_1Buffer[i] = 0x00;
			}
			for(int i=0; i<Unicode::strlen(keyboard5_text_typed_1Buffer); i++){
				keyboard5_text_typed_hide_1Buffer[i] = 8226;	//U+8226 (bullet '•')
			}

			/*** Estado del placeholder (visible o no visible) ***/
			if(keyboard5_text_typed_1Buffer[0] == 0x00){
				keyboard5_placeholder_1.setVisible(true);
			}
			else{
				keyboard5_placeholder_1.setVisible(false);
			}

			/*** Color del texto con información de instrucciones de contraseña ***/
			if(cuvex.info.mode == DARK){
				keyboard5_text_info_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
			}
			else{
				keyboard5_text_info_2.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
			}

			/*** Actualización del área ***/
			keyboard5_text_area_1.invalidate();
			keyboard5_text_info_2.invalidate();
		}
	}

	/*** Gestión del teclado 5 - password 2 ***/
	if(keyboard5_password_2.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard5_text_typed_2Buffer, keyboard5_password_2.getBuffer(), KEYBOARD5_TEXT_TYPED_2_SIZE) != 0)
		{
			/*** Obtención de texto tecleado en widget ***/
			Unicode::snprintf(keyboard5_text_typed_2Buffer, KEYBOARD5_TEXT_TYPED_2_SIZE, keyboard5_password_2.getBuffer());
			keyboard5_text_typed_2.setWideTextAction(touchgfx::WIDE_TEXT_NONE);

			/*** Alineamiento de texto dentro de área ***/
			if(keyboard5_text_typed_2.getTextWidth() <= 160){
				keyboard5_text_typed_2.setPosition(160-(keyboard5_text_typed_2.getTextWidth()/2), 75, keyboard5_text_typed_2.getTextWidth(), 20);
			}
			else{
				keyboard5_text_typed_2.setPosition(76, 75, 160, 20);
			}

			/*** Reseteo y relleno de buffer con contraseña oculta ***/
			for(int i=0; i<KEYBOARD5_TEXT_TYPED_HIDE_2_SIZE; i++){
				keyboard5_text_typed_hide_2Buffer[i] = 0x00;
			}
			for(int i=0; i<Unicode::strlen(keyboard5_text_typed_2Buffer); i++){
				keyboard5_text_typed_hide_2Buffer[i] = 8226;	//U+8226 (bullet '•')
			}

			/*** Estado del placeholder (visible o no visible) ***/
			if(keyboard5_text_typed_2Buffer[0] == 0x00){
				keyboard5_placeholder_2.setVisible(true);
			}
			else{
				keyboard5_placeholder_2.setVisible(false);
			}

			/*** Color del texto con información de instrucciones de contraseña ***/
			if(cuvex.info.mode == DARK){
				keyboard5_text_info_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
			}
			else{
				keyboard5_text_info_2.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
			}

			/*** Actualización del área ***/
			keyboard5_text_area_2.invalidate();
			keyboard5_text_info_2.invalidate();
		}
	}

	/*** Gestión del teclado 6 (alias) ***/
	if(keyboard6_alias.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard6_text_typedBuffer, keyboard6_alias.getBuffer(), KEYBOARD6_TEXT_TYPED_SIZE) != 0)
		{
			Unicode::snprintf(keyboard6_text_typedBuffer, KEYBOARD6_TEXT_TYPED_SIZE, keyboard6_alias.getBuffer());
			keyboard6_text_typed.setWideTextAction(touchgfx::WIDE_TEXT_NONE);

			if(keyboard6_text_typed.getTextWidth() <= 160){
				keyboard6_text_typed.setPosition(160-(keyboard6_text_typed.getTextWidth()/2), 75, keyboard6_text_typed.getTextWidth(), 20);
			}
			else{
				keyboard6_text_typed.setPosition(76, 75, 160, 20);
			}

			keyboard6_text_area.invalidate();
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
void screen_flow_2View::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::changeStateNfc(uint8_t state)
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
void screen_flow_2View::updateStateNfc(uint16_t state)
{
	/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
	switch(state)
	{
	case MAIN_TO_GUI_NFC_ERROR:
	default:
		application().gotoscreen_menuScreenNoTransition();
		break;

	case MAIN_TO_GUI_NFC_INITIALIZED:
		if(s5_initNFC.isVisible())
		{
			s5_initNFC.setVisible(false);
			s6_waitReadWriteNFC.setVisible(true);
			screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_2);
		}
		break;

	case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_2:
		if(s6_waitReadWriteNFC.isVisible())
		{
			if(cuvex.nfc.tag.encripted == true)						//Error 1, la tarjeta que se intentó grabar ya tiene un criptograma almacenado
			{
				s6_waitReadWriteNFC.setVisible(false);
				s7_writeError1.setVisible(true);
				screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
			}
			else
			{
				if(cuvex.nfc.tag.alias[0] == 0x00)					//Error 2, la tarjeta que se intentó grabar no tiene ningún alias asignado
				{
					s6_waitReadWriteNFC.setVisible(false);
					s8_writeError2.setVisible(true);
					s8_1_viewTagInfo.setVisible(true);
					s8_2_typeAlias.setVisible(false);
					memset(text_uidBuffer, 0x00, TEXT_UID_SIZE);
					Unicode::snprintf(text_uidBuffer, TEXT_UID_SIZE, (const char*) cuvex.nfc.tag.uid);
					screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
				}
				else												//Success, tarjeta grabada correctamente
				{

					if(cuvex.nfc.tag.alias[0] == 0x00){
						memset(text_cryptogram_success_english_5Buffer, 0x00, TEXT_CRYPTOGRAM_SUCCESS_ENGLISH_5_SIZE);
						memset(text_cryptogram_success_english_6Buffer, 0x00, TEXT_CRYPTOGRAM_SUCCESS_ENGLISH_6_SIZE);
						memset(text_cryptogram_success_spanish_4Buffer, 0x00, TEXT_CRYPTOGRAM_SUCCESS_SPANISH_4_SIZE);
						memset(text_cryptogram_success_spanish_5Buffer, 0x00, TEXT_CRYPTOGRAM_SUCCESS_SPANISH_5_SIZE);

						Unicode::snprintf(text_cryptogram_success_english_5Buffer, TEXT_CRYPTOGRAM_SUCCESS_ENGLISH_5_SIZE, (const char*) "UIDI ");
						Unicode::snprintf(text_cryptogram_success_english_6Buffer, TEXT_CRYPTOGRAM_SUCCESS_ENGLISH_6_SIZE, (const char*) cuvex.nfc.tag.uid);
						Unicode::snprintf(text_cryptogram_success_spanish_4Buffer, TEXT_CRYPTOGRAM_SUCCESS_SPANISH_4_SIZE, (const char*) "UIDI ");
						Unicode::snprintf(text_cryptogram_success_spanish_5Buffer, TEXT_CRYPTOGRAM_SUCCESS_SPANISH_5_SIZE, (const char*) cuvex.nfc.tag.uid);
					}
					else{
						memset(text_cryptogram_success_english_5Buffer, 0x00, TEXT_CRYPTOGRAM_SUCCESS_ENGLISH_5_SIZE);
						memset(text_cryptogram_success_english_6Buffer, 0x00, TEXT_CRYPTOGRAM_SUCCESS_ENGLISH_6_SIZE);
						memset(text_cryptogram_success_spanish_4Buffer, 0x00, TEXT_CRYPTOGRAM_SUCCESS_SPANISH_4_SIZE);
						memset(text_cryptogram_success_spanish_5Buffer, 0x00, TEXT_CRYPTOGRAM_SUCCESS_SPANISH_5_SIZE);

						Unicode::snprintf(text_cryptogram_success_english_5Buffer, TEXT_CRYPTOGRAM_SUCCESS_ENGLISH_5_SIZE, (const char*) "Alias ");
						Unicode::snprintf(text_cryptogram_success_spanish_4Buffer, TEXT_CRYPTOGRAM_SUCCESS_SPANISH_4_SIZE, (const char*) "Alias ");

						for(int i=0; i<TEXT_CRYPTOGRAM_SUCCESS_ENGLISH_6_SIZE; i++)
						{
							if(cuvex.nfc.tag.alias[i] == 182){	//Si '¶' (182) se convierte al caracter '€' (8364) para visualización en pantalla
								text_cryptogram_success_english_6Buffer[i] = 8364;
								text_cryptogram_success_spanish_5Buffer[i] = 8364;
							}
							else{
								text_cryptogram_success_english_6Buffer[i] = cuvex.nfc.tag.alias[i];
								text_cryptogram_success_spanish_5Buffer[i] = cuvex.nfc.tag.alias[i];
							}
						}
					}

					if(cuvex.info.language == SPANISH){
						text_cryptogram_success_spanish.setVisible(true);
						text_cryptogram_success_english.setVisible(false);
					}
					else{
						text_cryptogram_success_spanish.setVisible(false);
						text_cryptogram_success_english.setVisible(true);
					}

					s6_waitReadWriteNFC.setVisible(false);
					s9_writeSuccess.setVisible(true);
				}
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
 * Gestión de pulsaciones de los teclados
 *
 */

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::hideKeyboard1Pressed()
{
	/*** Se bajan los elementos de la pantalla ***/
	keyboard1_text_info.setPosition(0, 90, 320, 20);
	keyboard1_text_typed.setPosition(76, 125, 169, 20);
	keyboard1_text_area.setXY(45, 120);
	keyboard1_btn_enter.setPosition(245, 120, 30, 30);

	/*** Actualización pulsadores y teclado ***/
	keyboard1_numeric.setVisible(false);
	keyboard1_btn_hide.setVisible(false);
	keyboard1_btn_show.setVisible(true);
	keyboard1_btn_enter.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::showKeyboard1Pressed()
{
	/*** Se suben los elementos de la pantalla ***/
	keyboard1_text_info.setPosition(0, 40, 320, 20);
	keyboard1_text_typed.setPosition(76, 75, 169, 20);
	keyboard1_text_area.setXY(45, 70);
	keyboard1_btn_enter.setPosition(245, 70, 30, 30);

	/*** Actualización pulsadores y teclado ***/
	keyboard1_numeric.setVisible(true);
	keyboard1_btn_hide.setVisible(true);
	keyboard1_btn_show.setVisible(false);
	keyboard1_btn_enter.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::enterKeyboard1Pressed()
{
	total_words = Unicode::atoi(keyboard1_text_typedBuffer);
	actual_word = 1;

	if((total_words > 0) && (total_words <= 48))
	{
		/*** Edición de información en siguiente sub-pantalla ***/
		Unicode::snprintf(keyboard2_text_infoBuffer1, KEYBOARD2_TEXT_INFOBUFFER1_SIZE, "%d", actual_word);
		Unicode::snprintf(keyboard2_text_infoBuffer2, KEYBOARD2_TEXT_INFOBUFFER2_SIZE, "%d", total_words);

		/*** Edición de los elementos visibles/ocultos en la pantalla ***/
		s1_1_typeNumWords.setVisible(false);
		s1_2_typeWords.setVisible(true);

		/*** Borrado de los buffers del teclado y de visualización ***/
		memset(keyboard1_text_typedBuffer, 0x00, sizeof(keyboard1_text_typedBuffer));
		keyboard1_numeric.clearBuffer();

		/*** Actualización de la pantalla ***/
		background.invalidate();
	}
}

/*
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
void screen_flow_2View::hideKeyboard2Pressed()
{
	/*** Se bajan los elementos de la pantalla ***/
	keyboard2_text_info.setPosition(0, 90, 320, 20);
	keyboard2_text_typed.setPosition(76, 125, 169, 20);
	keyboard2_text_predicted.setPosition(76, 125, 169, 20);
	keyboard2_text_area.setXY(45, 120);
	keyboard2_btn_enter.setPosition(245, 120, 30, 30);

	/*** Actualización pulsadores y teclado ***/
	keyboard2_BIP39.setVisible(false);
	keyboard2_btn_hide.setVisible(false);
	keyboard2_btn_show.setVisible(true);
	keyboard2_btn_enter.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::showKeyboard2Pressed()
{
	/*** Se suben los elementos de la pantalla ***/
	keyboard2_text_info.setPosition(0, 40, 320, 20);
	keyboard2_text_typed.setPosition(76, 75, 169, 20);
	keyboard2_text_predicted.setPosition(76, 75, 169, 20);
	keyboard2_text_area.setXY(45, 70);
	keyboard2_btn_enter.setPosition(245, 70, 30, 30);

	/*** Actualización pulsadores y teclado ***/
	keyboard2_BIP39.setVisible(true);
	keyboard2_btn_hide.setVisible(true);
	keyboard2_btn_show.setVisible(false);
	keyboard2_btn_enter.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::enterKeyboard2Pressed()
{
	if((keyboard2_text_typedBuffer[0] != 0x00) && (valid_word == true))
	{
		/*** Obtención de las palabras tecleadas (formato UTF8) ***/
		Unicode::toUTF8(keyboard2_text_typedBuffer, words_to_encrypt[actual_word-1], KEYBOARD2_TEXT_TYPED_SIZE);
		Unicode::toUTF8(keyboard2_text_predictedBuffer, words_to_check[actual_word-1], KEYBOARD2_TEXT_PREDICTED_SIZE);

		/*** Edición de los elementos visibles/ocultos en la pantalla ***/
		if(actual_word == total_words){
			s1_2_typeWords.setVisible(false);
			s1_3_typePassphrase.setVisible(true);
		}
		else{
			Unicode::snprintf(keyboard2_text_infoBuffer1, KEYBOARD2_TEXT_INFOBUFFER1_SIZE, "%d", ++actual_word);
			Unicode::snprintf(keyboard2_text_infoBuffer2, KEYBOARD2_TEXT_INFOBUFFER2_SIZE, "%d", total_words);
		}

		/*** Borrado de los buffers del teclado y de visualización ***/
		memset(keyboard2_text_typedBuffer, 0x00, sizeof(keyboard2_text_typedBuffer));
		memset(keyboard2_text_predictedBuffer, 0x00, sizeof(keyboard2_text_predictedBuffer));
		keyboard2_BIP39.clearBuffer();

		/*** Actualización de la pantalla ***/
		background.invalidate();
	}
}

/*
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
void screen_flow_2View::hideKeyboard3Pressed()
{
	/*** Se bajan los elementos de la pantalla ***/
	keyboard3_text_area.setPosition(20, 40, 280, 160);
	keyboard3_text_typed.setPosition(60, 50, 230, 140);
	keyboard3_btn_up.setPosition(30, 50, 20, 20);
	keyboard3_btn_down.setPosition(30, 170, 20, 20);
	keyboard3_char_count.setPosition(250, 188, 50, 12);

	/*** Actualización pulsadores y teclado ***/
	keyboard3_passphrase.setVisible(false);
	keyboard3_btn_hide.setVisible(false);
	keyboard3_btn_show.setVisible(true);
	keyboard3_btn_enter.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::showKeyboard3Pressed()
{
	/*** Se suben los elementos de la pantalla ***/
	keyboard3_text_area.setPosition(20, 40, 280, 70);
	keyboard3_text_typed.setPosition(60, 50, 230, 60);
	keyboard3_btn_up.setPosition(30, 50, 20, 20);
	keyboard3_btn_down.setPosition(30, 80, 20, 20);
	keyboard3_char_count.setPosition(250, 98, 50, 12);

	/*** Actualización pulsadores y teclado ***/
	keyboard3_passphrase.setVisible(true);
	keyboard3_btn_hide.setVisible(true);
	keyboard3_btn_show.setVisible(false);
	keyboard3_btn_enter.setVisible(false);

	/*** Actualización de la pantalla ***/
	background.invalidate();

	/*** Flag auxiliar ***/
	flag_refresh_text_area = 1;
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::enterKeyboard3Pressed()
{
	/*** Variables de la función ***/
	char buff_aux1[TYPED_CHECK1_SIZE] = {0}, buff_aux2[10] = {0};

	/*** Obtención del texto tecleado (passphrase) ***/
	memset(buff_passphrase, 0x00, KEYBOARD3_TEXT_TYPED_SIZE);

	for(int i=0; i<KEYBOARD3_TEXT_TYPED_SIZE; i++)
	{
		if(keyboard3_text_typedBuffer[i] == 8364){	//Si '€' (8364) se convierte al caracter '¶' (182) para sólo ocupar 1 byte
			buff_passphrase[i] = 182;
		}
		else{
			buff_passphrase[i] = (uint8_t) keyboard3_text_typedBuffer[i];
		}
	}

	/*** Generación de array para visualización de words + passphrase ***/
	for(int i=0; i<total_words; i++)
	{
		snprintf(buff_aux2, 10, "%d. ", i+1);
		strcat(buff_aux1, (char *) buff_aux2);
		strcat(buff_aux1, (char *) words_to_check[i]);
		strcat(buff_aux1, (char *) "\n");
	}

	strcat(buff_aux1, (char*) "\nPassphrase:\n");
	strcat(buff_aux1, (char*) buff_passphrase);

	/*** Asignación de words + passprashe a visualizar en texto "scrollable" ***/
	memset(typed_check1Buffer, 0x00, TYPED_CHECK1_SIZE);

	for(int i=0; i<TYPED_CHECK1_SIZE; i++)
	{
		if(buff_aux1[i] == 182){	//Si '¶' (182) se convierte al caracter '€' (8364) para visualización en pantalla
			typed_check1Buffer[i] = 8364;
		}
		else{
			typed_check1Buffer[i] = buff_aux1[i];
		}
	}

	typed_check1.setPosition(0, 0, 220, (20*(total_words+1))+(20*7));
	typed_check1.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);

	/*** Edición de los elementos visibles/ocultos en la pantalla ***/
	s1_3_typePassphrase.setVisible(false);
	s1_4_checkSeedInfo.setVisible(true);

	/*** Borrado de los buffers del teclado y de visualización ***/
	memset(keyboard3_text_typedBuffer, 0x00, sizeof(keyboard3_text_typedBuffer));
	keyboard3_passphrase.clearBuffer();

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/*
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
void screen_flow_2View::hideKeyboard4Pressed()
{
	/*** Se bajan los elementos de la pantalla ***/
	keyboard4_text_area.setPosition(20, 40, 280, 160);
	keyboard4_text_typed.setPosition(60, 50, 230, 140);
	keyboard4_btn_up.setPosition(30, 50, 20, 20);
	keyboard4_btn_down.setPosition(30, 170, 20, 20);
	keyboard4_char_count.setPosition(250, 188, 50, 12);

	/*** Actualización pulsadores y teclado ***/
	keyboard4_plain_text.setVisible(false);
	keyboard4_btn_hide.setVisible(false);
	keyboard4_btn_show.setVisible(true);
	keyboard4_btn_enter.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::showKeyboard4Pressed()
{
	/*** Se suben los elementos de la pantalla ***/
	keyboard4_text_area.setPosition(20, 40, 280, 70);
	keyboard4_text_typed.setPosition(60, 50, 230, 60);
	keyboard4_btn_up.setPosition(30, 50, 20, 20);
	keyboard4_btn_down.setPosition(30, 80, 20, 20);
	keyboard4_char_count.setPosition(250, 98, 50, 12);

	/*** Actualización pulsadores y teclado ***/
	keyboard4_plain_text.setVisible(true);
	keyboard4_btn_hide.setVisible(true);
	keyboard4_btn_show.setVisible(false);
	keyboard4_btn_enter.setVisible(false);

	/*** Actualización de la pantalla ***/
	background.invalidate();

	/*** Flag auxiliar ***/
	flag_refresh_text_area = 1;
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::enterKeyboard4Pressed()
{
	if(keyboard4_text_typedBuffer[0] != 0x00)
	{
		/*** Obtención del texto tecleado (texto plano) ***/
		memset(buff_plain_text, 0x00, KEYBOARD4_TEXT_TYPED_SIZE);

		for(int i=0; i<KEYBOARD4_TEXT_TYPED_SIZE; i++)
		{
			if(keyboard4_text_typedBuffer[i] == 8364){	//Si '€' (8364) se convierte al caracter '¶' (182) para sólo ocupar 1 byte
				buff_plain_text[i] = 182;
			}
			else{
				buff_plain_text[i] = (uint8_t) keyboard4_text_typedBuffer[i];
			}
		}

		/*** Asignación del texto plano a visualizar en texto "scrollable" ***/
		memset(typed_check2Buffer, 0x00, TYPED_CHECK2_SIZE);

		for(int i=0; i<TYPED_CHECK2_SIZE; i++)
		{
			if(buff_plain_text[i] == 182){	//Si '¶' (182) se convierte al caracter '€' (8364) para visualización en pantalla
				typed_check2Buffer[i] = 8364;
			}
			else{
				typed_check2Buffer[i] = buff_plain_text[i];
			}
		}

		typed_check2.setPosition(0, 0, 220, 20*(typed_check2.getTextWidth()/220)+1*20);
		typed_check2.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);

		/*** Edición de los elementos visibles/ocultos en la pantalla ***/
		s2_1_typePlainText.setVisible(false);
		s2_2_checkPlainTextInfo.setVisible(true);

		/*** Borrado de los buffers del teclado y de visualización ***/
		memset(keyboard4_text_typedBuffer, 0x00, sizeof(keyboard4_text_typedBuffer));
		keyboard4_plain_text.clearBuffer();

		/*** Actualización de la pantalla ***/
		background.invalidate();
	}
}

/*
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
void screen_flow_2View::hideKeyboard5Pressed()
{
	/*** Se bajan los elementos de la pantalla ***/
	keyboard5_text_info_1.setPosition(0, 60, 320, 20);
	keyboard5_text_info_2.setPosition(0, 152, 320, 13);
	keyboard5_text_typed_hide_1.setPosition(76, 90, 160, 20);
	keyboard5_text_typed_hide_2.setPosition(76, 125, 160, 20);
	keyboard5_text_area_1.setXY(45, 85);
	keyboard5_text_area_2.setXY(45, 120);
	keyboard5_text_area_selected_1.setXY(45, 85);
	keyboard5_text_area_selected_2.setXY(45, 120);
	keyboard5_pwd_eye_1.setXY(245, 85);
	keyboard5_pwd_eye_2.setXY(245, 120);
	keyboard5_btn_show_1.setPosition(76, 85, 169, 30);
	keyboard5_btn_show_2.setPosition(76, 120, 169, 30);
	keyboard5_placeholder_1.setPosition(62, 90, 180, 20);
	keyboard5_placeholder_2.setPosition(62, 125, 180, 20);

	if(keyboard5_text_typed_1.getTextWidth() <= 160){
		keyboard5_text_typed_1.setPosition(160-(keyboard5_text_typed_1.getTextWidth()/2), 90, keyboard5_text_typed_1.getTextWidth(), 20);
	}
	else{
		keyboard5_text_typed_1.setPosition(76, 90, 160, 20);
	}

	if(keyboard5_text_typed_2.getTextWidth() <= 160){
		keyboard5_text_typed_2.setPosition(160-(keyboard5_text_typed_2.getTextWidth()/2), 125, keyboard5_text_typed_2.getTextWidth(), 20);
	}
	else{
		keyboard5_text_typed_2.setPosition(76, 125, 160, 20);
	}

	/*** Actualización pulsadores y teclado ***/
	keyboard5_password_1.setVisible(false);
	keyboard5_btn_show_1.setVisible(true);
	keyboard5_text_area_selected_1.setVisible(false);
	keyboard5_password_2.setVisible(false);
	keyboard5_btn_show_2.setVisible(true);
	keyboard5_text_area_selected_2.setVisible(false);
	keyboard5_btn_hide.setVisible(false);
	keyboard5_btn_enter.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::show1Keyboard5Pressed()
{
	/*** Se suben los elementos de la pantalla ***/
	keyboard5_text_info_1.setPosition(0, 10, 320, 20);
	keyboard5_text_info_2.setPosition(0, 102, 320, 13);
	keyboard5_text_typed_hide_1.setPosition(76, 40, 160, 20);
	keyboard5_text_typed_hide_2.setPosition(76, 75, 160, 20);
	keyboard5_text_area_1.setXY(45, 35);
	keyboard5_text_area_2.setXY(45, 70);
	keyboard5_text_area_selected_1.setXY(45, 35);
	keyboard5_text_area_selected_2.setXY(45, 70);
	keyboard5_pwd_eye_1.setXY(245, 35);
	keyboard5_pwd_eye_2.setXY(245, 70);
	keyboard5_btn_show_1.setPosition(76, 35, 169, 30);
	keyboard5_btn_show_2.setPosition(76, 70, 169, 30);
	keyboard5_placeholder_1.setPosition(62, 40, 180, 20);
	keyboard5_placeholder_2.setPosition(62, 75, 180, 20);

	if(keyboard5_text_typed_1.getTextWidth() <= 160){
		keyboard5_text_typed_1.setPosition(160-(keyboard5_text_typed_1.getTextWidth()/2), 40, keyboard5_text_typed_1.getTextWidth(), 20);
	}
	else{
		keyboard5_text_typed_1.setPosition(76, 40, 160, 20);
	}

	if(keyboard5_text_typed_2.getTextWidth() <= 160){
		keyboard5_text_typed_2.setPosition(160-(keyboard5_text_typed_2.getTextWidth()/2), 75, keyboard5_text_typed_2.getTextWidth(), 20);
	}
	else{
		keyboard5_text_typed_2.setPosition(76, 75, 160, 20);
	}

	/*** Actualización pulsadores y teclado ***/
	keyboard5_password_1.setVisible(true);
	keyboard5_btn_show_1.setVisible(false);
	keyboard5_text_area_selected_1.setVisible(true);
	keyboard5_password_2.setVisible(false);
	keyboard5_btn_show_2.setVisible(true);
	keyboard5_text_area_selected_2.setVisible(false);
	keyboard5_btn_hide.setVisible(true);
	keyboard5_btn_enter.setVisible(false);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::show2Keyboard5Pressed()
{
	/*** Se suben los elementos de la pantalla ***/
	keyboard5_text_info_1.setPosition(0, 10, 320, 20);
	keyboard5_text_info_2.setPosition(0, 102, 320, 13);
	keyboard5_text_typed_hide_1.setPosition(76, 40, 160, 20);
	keyboard5_text_typed_hide_2.setPosition(76, 75, 160, 20);
	keyboard5_text_area_1.setXY(45, 35);
	keyboard5_text_area_2.setXY(45, 70);
	keyboard5_text_area_selected_1.setXY(45, 35);
	keyboard5_text_area_selected_2.setXY(45, 70);
	keyboard5_pwd_eye_1.setXY(245, 35);
	keyboard5_pwd_eye_2.setXY(245, 70);
	keyboard5_btn_show_1.setPosition(76, 35, 169, 30);
	keyboard5_btn_show_2.setPosition(76, 70, 169, 30);
	keyboard5_placeholder_1.setPosition(62, 40, 180, 20);
	keyboard5_placeholder_2.setPosition(62, 75, 180, 20);

	if(keyboard5_text_typed_1.getTextWidth() <= 160){
		keyboard5_text_typed_1.setPosition(160-(keyboard5_text_typed_1.getTextWidth()/2), 40, keyboard5_text_typed_1.getTextWidth(), 20);
	}
	else{
		keyboard5_text_typed_1.setPosition(76, 40, 160, 20);
	}

	if(keyboard5_text_typed_2.getTextWidth() <= 160){
		keyboard5_text_typed_2.setPosition(160-(keyboard5_text_typed_2.getTextWidth()/2), 75, keyboard5_text_typed_2.getTextWidth(), 20);
	}
	else{
		keyboard5_text_typed_2.setPosition(76, 75, 160, 20);
	}

	/*** Actualización pulsadores y teclado ***/
	keyboard5_password_1.setVisible(false);
	keyboard5_btn_show_1.setVisible(true);
	keyboard5_text_area_selected_1.setVisible(false);
	keyboard5_password_2.setVisible(true);
	keyboard5_btn_show_2.setVisible(false);
	keyboard5_text_area_selected_2.setVisible(true);
	keyboard5_btn_hide.setVisible(true);
	keyboard5_btn_enter.setVisible(false);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::enterKeyboard5Pressed()
{
	bool flag_upercase = false, flag_lowercase = false, flag_simbol = false, flag_number = false;
	bool flag_passwords_ok = false;

	/*** Comprobación que textos tecleados cumplen con las condiciones (12 caracteres mínimo, mayúsculas, minúsculas, números y símbolos) ***/
	if((Unicode::strlen(keyboard5_text_typed_1Buffer) >= 12) && (Unicode::strlen(keyboard5_text_typed_2Buffer) >= 12)) 	//Contraseñas 1 y 2 de al menos 12 caracteres
	{
		if(Unicode::strncmp(keyboard5_text_typed_1Buffer, keyboard5_text_typed_2Buffer, KEYBOARD5_TEXT_TYPED_1_SIZE) == 0)	//Contraseñas 1 y 2 iguales
		{
			for(int i=0; i<KEYBOARD5_TEXT_TYPED_1_SIZE; i++)
			{
				if((keyboard5_text_typed_1Buffer[i] >= 32) && (keyboard5_text_typed_1Buffer[i] <= 47)){			//Símbolo (Unicode: 32-47)
					flag_simbol = true;
				}
				else if((keyboard5_text_typed_1Buffer[i] >= 48) && (keyboard5_text_typed_1Buffer[i] <= 57)){	//Números (Unicode: 48-57)
					flag_number = true;
				}
				else if((keyboard5_text_typed_1Buffer[i] >= 58) && (keyboard5_text_typed_1Buffer[i] <= 64)){	//Símbolo (Unicode: 58-64)
					flag_simbol = true;
				}
				else if((keyboard5_text_typed_1Buffer[i] >= 65) && (keyboard5_text_typed_1Buffer[i] <= 90)){	//Mayúsculas (Unicode: 65-90)
					flag_upercase = true;
				}
				else if((keyboard5_text_typed_1Buffer[i] >= 91) && (keyboard5_text_typed_1Buffer[i] <= 96)){	//Símbolo (Unicode: 91-96)
					flag_simbol = true;
				}
				else if((keyboard5_text_typed_1Buffer[i] >= 97) && (keyboard5_text_typed_1Buffer[i] <= 122)){	//Minúsculas (Unicode: 97-122)
					flag_lowercase = true;
				}
				else if((keyboard5_text_typed_1Buffer[i] >= 123) && (keyboard5_text_typed_1Buffer[i] <= 126)){	//Símbolo (Unicode: 123-126)
					flag_simbol = true;
				}
				else if((keyboard5_text_typed_1Buffer[i] >= 160) && (keyboard5_text_typed_1Buffer[i] <= 191)){	//Símbolo (Unicode: 160-191)
					flag_simbol = true;
				}
				else if(keyboard5_text_typed_1Buffer[i] == 8364){	//Símbolo '€' (Unicode: 8364)
					flag_simbol = true;
				}
			}

			if((flag_upercase == true) && (flag_lowercase == true) && (flag_number == true) && (flag_simbol == true))	//Contraseñas contienen "mayúsculas", "minúsculas", "números" y "símbolos"
			{
				flag_passwords_ok = true;
			}
		}
	}

	/*** Si todas las condiciones de las contraseñas son correctas ***/
	if(flag_passwords_ok == true)
	{
		/*** Obtención del texto tecleado (contraseña) ***/
		memset(pwds[actual_pwd], 0x00, KEYBOARD5_TEXT_TYPED_1_SIZE);

		for(int i=0; i<KEYBOARD5_TEXT_TYPED_1_SIZE; i++)
		{
			if(keyboard5_text_typed_1Buffer[i] == 8364){	//Si '€' (8364) se convierte al caracter '¶' (182) para sólo ocupar 1 byte
				pwds[actual_pwd][i] = 182;
			}
			else{
				pwds[actual_pwd][i] = (uint8_t) keyboard5_text_typed_1Buffer[i];
			}
		}

		/*** Selección de los textos a visualizar en el campo de información de password correcta (en función del idioma y del número de firmantes) ***/
		if(cuvex.info.language == SPANISH)
		{
			if(num_pwds > 1)
			{
				Unicode::snprintf(text_pwd_success_infoBuffer, TEXT_PWD_SUCCESS_INFO_SIZE, " %d", actual_pwd+1);

				if(num_pwds != actual_pwd+1){
					Unicode::snprintf(btn_store_cryptogramBuffer, BTN_STORE_CRYPTOGRAM_SIZE, "CONTINUAR");
				}
				else{
					Unicode::snprintf(btn_store_cryptogramBuffer, BTN_STORE_CRYPTOGRAM_SIZE, "GRABAR CRIPTOGRAMA");
				}
			}
		}
		else
		{
			if(num_pwds > 1)
			{
				Unicode::snprintf(text_pwd_success_infoBuffer, TEXT_PWD_SUCCESS_INFO_SIZE, " %d", actual_pwd+1);

				if(num_pwds != actual_pwd+1){
					Unicode::snprintf(btn_store_cryptogramBuffer, BTN_STORE_CRYPTOGRAM_SIZE, "CONTINUE");
				}
				else{
					Unicode::snprintf(btn_store_cryptogramBuffer, BTN_STORE_CRYPTOGRAM_SIZE, "RECORD CRYPTOGRAM");
				}
			}
		}

		/*** Borrado de los buffers del teclado y de visualización ***/
		memset(keyboard5_text_typed_1Buffer, 0x00, sizeof(keyboard5_text_typed_1Buffer));
		memset(keyboard5_text_typed_2Buffer, 0x00, sizeof(keyboard5_text_typed_2Buffer));
		memset(keyboard5_text_typed_hide_1Buffer, 0x00, sizeof(keyboard5_text_typed_hide_1Buffer));
		memset(keyboard5_text_typed_hide_2Buffer, 0x00, sizeof(keyboard5_text_typed_hide_2Buffer));
		keyboard5_password_1.clearBuffer();
		keyboard5_password_2.clearBuffer();

		/*** Edición de los elementos visibles/ocultos en la pantalla ***/
		s4_1_typePasword.setVisible(false);
		s4_2_successPassword.setVisible(true);

		if(cuvex.info.mode == DARK){
			keyboard5_text_info_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		}
		else{
			keyboard5_text_info_2.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		}
	}
	else
	{
		keyboard5_text_info_2.setColor(touchgfx::Color::getColorFromRGB(0xE7,0x44,0x3E));	//#e7443e
	}

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/*
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
void screen_flow_2View::hideKeyboard6Pressed()
{
	/*** Se bajan los elementos de la pantalla ***/
	keyboard6_text_info.setPosition(0, 90, 320, 20);
	keyboard6_text_area.setXY(45, 120);
	keyboard6_btn_enter.setPosition(245, 120, 30, 30);

	if(keyboard6_text_typed.getTextWidth() <= 160){
		keyboard6_text_typed.setPosition(160-(keyboard6_text_typed.getTextWidth()/2), 125, keyboard6_text_typed.getTextWidth(), 20);
	}
	else{
		keyboard6_text_typed.setPosition(76, 125, 160, 20);
	}

	/*** Actualización pulsadores y teclado ***/
	keyboard6_alias.setVisible(false);
	keyboard6_btn_hide.setVisible(false);
	keyboard6_btn_show.setVisible(true);
	keyboard6_btn_enter.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::showKeyboard6Pressed()
{
	/*** Se suben los elementos de la pantalla ***/
	keyboard6_text_info.setPosition(0, 40, 320, 20);
	keyboard6_text_area.setXY(45, 70);
	keyboard6_btn_enter.setPosition(245, 70, 30, 30);

	if(keyboard6_text_typed.getTextWidth() <= 160){
		keyboard6_text_typed.setPosition(160-(keyboard6_text_typed.getTextWidth()/2), 75, keyboard6_text_typed.getTextWidth(), 20);
	}
	else{
		keyboard6_text_typed.setPosition(76, 75, 160, 20);
	}

	/*** Actualización pulsadores y teclado ***/
	keyboard6_alias.setVisible(true);
	keyboard6_btn_hide.setVisible(true);
	keyboard6_btn_show.setVisible(false);
	keyboard6_btn_enter.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::enterKeyboard6Pressed()
{
	if(keyboard6_text_typedBuffer[0] != 0x00)
	{
		/*** Obtención del texto tecleado ***/
		memset(cuvex.nfc.tag.new_alias, 0x00, SIZE_ALIAS);

		for(int i=0; i<SIZE_ALIAS; i++)
		{
			if(keyboard6_text_typedBuffer[i] == 8364){	//Si '€' (8364) se convierte al caracter '¶' (182) para sólo ocupar 1 byte
				cuvex.nfc.tag.new_alias[i] = 182;
			}
			else{
				cuvex.nfc.tag.new_alias[i] = (uint8_t) keyboard6_text_typedBuffer[i];
			}
		}

		/*** Borrado de los buffers del teclado y de visualización ***/
		memset(keyboard6_text_typedBuffer, 0x00, sizeof(keyboard6_text_typedBuffer));
		keyboard6_alias.clearBuffer();

		/*** Habilitación del NFC para permitir lectura/escritura ***/
		screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);

		/*** Selección de los elementos visibles/ocultos en la pantalla ***/
		s8_writeError2.setVisible(false);
		s5_initNFC.setVisible(true);

		/*** Actualización de la pantalla ***/
		background.invalidate();
	}
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
void screen_flow_2View::seedButtonPressed()
{
	/*** Actualización variable de tipo de texto a encriptar ***/
	text_type = 0;

	/*** Selección de los elementos visibles/ocultos en la pantalla ***/
	s0_menu.setVisible(false);
	s1_seedBip39.setVisible(true);
	s1_1_typeNumWords.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::plainTextButtonPressed()
{
	/*** Actualización variable de tipo de texto a encriptar ***/
	text_type = 1;

	/*** Selección de los elementos visibles/ocultos en la pantalla ***/
	s0_menu.setVisible(false);
	s2_plainText.setVisible(true);
	s2_1_typePlainText.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/*
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
void screen_flow_2View::encryptPressed()
{
	/*** Selección de los elementos visibles/ocultos en la pantalla ***/
	s1_seedBip39.setVisible(false);
	s2_plainText.setVisible(false);
	s3_multiSignature.setVisible(true);
	s3_1_askMultiSignature.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::multisignedYesPressed()
{
	/*** Selección de los elementos visibles/ocultos en la pantalla ***/
	s3_1_askMultiSignature.setVisible(false);
	s3_2_numMultiSignature.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::multisignedNoPressed()
{
	/*** Selección de los elementos visibles/ocultos en la pantalla ***/
	s3_multiSignature.setVisible(false);
	s4_password.setVisible(true);
	s4_1_typePasword.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_2View::multisignedPlusPressed()
{
	/*** Variable auxiliar ***/
	Unicode::UnicodeChar aux_str[5] = {0};

	/*** Actualización de nº de contraseñas ***/
	if(num_pwds < 6)
	{
		Unicode::itoa(++num_pwds, aux_str, 5, 10);
		Unicode::snprintf(text_multi_numBuffer, TEXT_MULTI_NUM_SIZE, aux_str);
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
void screen_flow_2View::multisignedMinusPressed()
{
	/*** Variable auxiliar ***/
	Unicode::UnicodeChar aux_str[5] = {0};

	/*** Actualización de nº de contraseñas ***/
	if(num_pwds > 1)
	{
		Unicode::itoa(--num_pwds, aux_str, 5, 10);
		Unicode::snprintf(text_multi_numBuffer, TEXT_MULTI_NUM_SIZE, aux_str);
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
void screen_flow_2View::multisignedSelectPressed()
{
	/*** Selección de los textos a visualizar en los campos de información ***/
	Unicode::UnicodeChar degree[] = {0x00B0,0};

	if(cuvex.info.language == SPANISH){
		if(num_pwds > 1){
			Unicode::snprintf(keyboard5_text_info_1Buffer, KEYBOARD5_TEXT_INFO_1_SIZE, "Persona N%s%d", degree, actual_pwd+1);
		}
		else{
			Unicode::snprintf(keyboard5_text_info_1Buffer, KEYBOARD5_TEXT_INFO_1_SIZE, "Password para cifrar.");
		}
	}
	else{
		if(num_pwds > 1){
			Unicode::snprintf(keyboard5_text_info_1Buffer, KEYBOARD5_TEXT_INFO_1_SIZE, "Person N%s%d", degree, actual_pwd+1);
		}
		else{
			Unicode::snprintf(keyboard5_text_info_1Buffer, KEYBOARD5_TEXT_INFO_1_SIZE, "Password to encrypt.");
		}
	}

	/*** Selección de los elementos visibles/ocultos en la pantalla ***/
	s3_multiSignature.setVisible(false);
	s4_password.setVisible(true);
	s4_1_typePasword.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_2View::storeCriptogramPressed()
{
	uint8_t text_to_encrypt[SIZE_CRYPT] = {0};
	char str_num_pwds[5] = {0};

	actual_pwd++;

	if(actual_pwd != num_pwds)
	{
		/*** Selección de los textos a visualizar en los campos de información ***/
		Unicode::UnicodeChar degree[] = {0x00B0,0};

		if(cuvex.info.language == SPANISH){
			if(num_pwds > 1){
				Unicode::snprintf(keyboard5_text_info_1Buffer, KEYBOARD5_TEXT_INFO_1_SIZE, "Persona N%s%d", degree, actual_pwd+1);
			}
			else{
				Unicode::snprintf(keyboard5_text_info_1Buffer, KEYBOARD5_TEXT_INFO_1_SIZE, "Password para cifrar.");
			}
		}
		else{
			if(num_pwds > 1){
				Unicode::snprintf(keyboard5_text_info_1Buffer, KEYBOARD5_TEXT_INFO_1_SIZE, "Person N%s%d", degree, actual_pwd+1);
			}
			else{
				Unicode::snprintf(keyboard5_text_info_1Buffer, KEYBOARD5_TEXT_INFO_1_SIZE, "Password to encrypt.");
			}
		}

		/*** Selección de los elementos visibles/ocultos en la pantalla ***/
		s4_1_typePasword.setVisible(true);
		s4_2_successPassword.setVisible(false);
		keyboard5_placeholder_1.setVisible(true);
		keyboard5_placeholder_2.setVisible(true);
	}
	else
	{
		uint16_t pwd_raw_length=SIGNATURE_SIZE;
		uint8_t pwd0_length=0;
		uint8_t pwd1_length=0;
		uint8_t pwd2_length=0;
		uint8_t pwd3_length=0;
		uint8_t pwd4_length=0;
		uint8_t pwd5_length=0;

		/*** Obtención en string del número de contraseñas usadas ***/
		itoa(num_pwds, str_num_pwds, 10);

		/*** Concatenación de las contraseñas en crudo (raw) ***/
		memset(pwd_raw, 0x00, sizeof(pwd_raw));
		strncat((char*) pwd_raw, (const char*) cuvex.signature_buffer, SIGNATURE_SIZE);

		pwd0_length = strlen((const char *)pwds[0]);
		strcat((char*) pwd_raw, (const char*) pwds[0]);
		pwd1_length = strlen((const char *)pwds[1]);
		strcat((char*) pwd_raw, (const char*) pwds[1]);
		pwd2_length = strlen((const char *)pwds[2]);
		strcat((char*) pwd_raw, (const char*) pwds[2]);
		pwd3_length = strlen((const char *)pwds[3]);
		strcat((char*) pwd_raw, (const char*) pwds[3]);
		pwd4_length = strlen((const char *)pwds[4]);
		strcat((char*) pwd_raw, (const char*) pwds[4]);
		pwd5_length = strlen((const char *)pwds[5]);
		strcat((char*) pwd_raw, (const char*) pwds[5]);

		pwd_raw_length = pwd_raw_length+pwd0_length+pwd1_length+pwd2_length+pwd3_length+pwd4_length+pwd5_length;

		/*** Obtención de la contraseña cifrada (SHA-256) ***/
		HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, pwd_raw_length, pwd_sha256, HAL_MAX_DELAY);

		/*** Generación texto a encriptar (semilla bip39, texto plano) + Encriptación AES-256 ***/
		switch(text_type)
		{
		case 0:
			strcat((char*) text_to_encrypt, (const char*) "[bip39]");

			for(int i=0; i<total_words; i++){
				strcat((char*) text_to_encrypt, (const char*) ",");
				strcat((char*) text_to_encrypt, (const char*) words_to_encrypt[i]);
			}

			strcat((char*) text_to_encrypt, (const char*) "[passphrase]");
			strcat((char*) text_to_encrypt, (char*) buff_passphrase);

			changeAESPassword(pwd_sha256);
			HAL_CRYP_Encrypt(&hcryp, (uint32_t *) text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_cryptogram, HAL_MAX_DELAY);
			break;

		case 1:
			strcat((char*) text_to_encrypt, (char*) "[plain-text]");
			strcat((char*) text_to_encrypt, (char*) buff_plain_text);

			changeAESPassword(pwd_sha256);
			HAL_CRYP_Encrypt(&hcryp, (uint32_t *) text_to_encrypt, SIZE_CRYPT_MSG, (uint32_t *) cuvex.nfc.tag.new_cryptogram, HAL_MAX_DELAY);
			break;

		default:
			break;
		}

		/*** Generación texto de información con formato "ENC,vXX.XX.XX(Y),M-X,P-X,C-X" ***/
		strcat((char *) cuvex.nfc.tag.new_information, (char *) "ENC,v");
		strcat((char *) cuvex.nfc.tag.new_information, (char *) cuvex.info.fw_version);
		strcat((char *) cuvex.nfc.tag.new_information, (char *) "(");
		strcat((char *) cuvex.nfc.tag.new_information, (char *) cuvex.info.hw_version);
		strcat((char *) cuvex.nfc.tag.new_information, (char *) "),M-");
		strcat((char *) cuvex.nfc.tag.new_information, (char *) str_num_pwds);
		strcat((char *) cuvex.nfc.tag.new_information, (char *) ",P-0,C-0");

		/*** Habilitación del NFC para permitir lectura/escritura ***/
		screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);

		/*** Selección de los elementos visibles/ocultos en la pantalla ***/
		s4_password.setVisible(false);
		s5_initNFC.setVisible(true);
	}

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_2View::successPressed()
{
	application().gotoscreen_menuScreenNoTransition();
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_2View::btnUpPressed()
{
	uint8_t aux = 0;

	if(s1_seedBip39.isVisible() == true)
	{
		aux = keyboard3_text_typed.getTextWidth()/230;

		if(aux != 0)	//Multilinea
		{
			if(keyboard3_text_area.getHeight() == 70)		//Recuadro pequeño
			{
				if(keyboard3_text_typed.getHeight() > 60){
					keyboard3_text_typed.setPosition(60, keyboard3_text_typed.getY() + 20, 230, keyboard3_text_typed.getHeight() - 20);
				}
			}
			else if(keyboard3_text_area.getHeight() == 160)	//Recuadro grande
			{
				if(keyboard3_text_typed.getHeight() > 140){
					keyboard3_text_typed.setPosition(60, keyboard3_text_typed.getY() + 20, 230, keyboard3_text_typed.getHeight() - 20);
				}
			}

			keyboard3_text_area.invalidate();
		}
	}
	else if(s2_plainText.isVisible() == true)
	{
		aux = keyboard4_text_typed.getTextWidth()/230;

		if(aux != 0)	//Multilinea
		{
			if(keyboard4_text_area.getHeight() == 70)		//Recuadro pequeño
			{
				if(keyboard4_text_typed.getHeight() > 60){
					keyboard4_text_typed.setPosition(60, keyboard4_text_typed.getY() + 20, 230, keyboard4_text_typed.getHeight() - 20);
				}
			}
			else if(keyboard4_text_area.getHeight() == 160)	//Recuadro grande
			{
				if(keyboard4_text_typed.getHeight() > 140){
					keyboard4_text_typed.setPosition(60, keyboard4_text_typed.getY() + 20, 230, keyboard4_text_typed.getHeight() - 20);
				}
			}

			keyboard4_text_area.invalidate();
		}
	}
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_2View::btnDownPressed()
{
	uint8_t num_of_lines = 0;

	if(s1_seedBip39.isVisible() == true)
	{
		num_of_lines = keyboard3_text_typed.getTextWidth()/230;

		if(num_of_lines)
		{
			if(keyboard3_text_area.getHeight() == 70)		//Recuadro pequeño
			{
				if(keyboard3_text_typed.getHeight() < 60+(20*num_of_lines)){
					keyboard3_text_typed.setPosition(60, keyboard3_text_typed.getY() - 20, 230, keyboard3_text_typed.getHeight() + 20);
				}
			}
			else if(keyboard3_text_area.getHeight() == 160)	//Recuadro grande
			{
				if(keyboard3_text_typed.getHeight() < 140+(20*num_of_lines)){
					keyboard3_text_typed.setPosition(60, keyboard3_text_typed.getY() - 20, 230, keyboard3_text_typed.getHeight() + 20);
				}
			}
			keyboard3_text_area.invalidate();
		}
	}
	else if(s2_plainText.isVisible() == true)
	{
		num_of_lines = keyboard4_text_typed.getTextWidth()/230;

		if(num_of_lines != 0)
		{
			if(keyboard4_text_area.getHeight() == 70)		//Recuadro pequeño
			{
				if(keyboard4_text_typed.getHeight() < 60+(20*num_of_lines)){
					keyboard4_text_typed.setPosition(60, keyboard4_text_typed.getY() - 20, 230, keyboard4_text_typed.getHeight() + 20);
				}
			}
			else if(keyboard4_text_area.getHeight() == 160)	//Recuadro grande
			{
				if(keyboard4_text_typed.getHeight() < 140+(20*num_of_lines)){
					keyboard4_text_typed.setPosition(60, keyboard4_text_typed.getY() - 20, 230, keyboard4_text_typed.getHeight() + 20);
				}
			}
			keyboard4_text_area.invalidate();
		}
	}
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_2View::btnScrollUpPressed()
{
	switch(text_type)
	{
	case 0:
	default:
		if(typed_check1.getY() < 0){
			typed_check1.setPosition(0, typed_check1.getY() + 20, 220, (20*(total_words+1))+(20*7));
		}
		container_typed_check1.invalidate();
		break;

	case 1:
		if(typed_check2.getY() < 0){
			typed_check2.setPosition(0, typed_check2.getY() + 20, 220, 20*(typed_check2.getTextWidth()/220)+1*20);
		}
		container_typed_check2.invalidate();
		break;
	}


}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_2View::btnScrollDownPressed()
{
	switch(text_type)
	{
	case 0:
	default:
		if((typed_check1.getY() + 20*(total_words+1)) > 0){
			typed_check1.setPosition(0, typed_check1.getY() - 20, 220, (20*(total_words+1))+(20*7));
		}
		container_typed_check1.invalidate();
		break;

	case 1:
		if((typed_check2.getY() + (20*(typed_check2.getTextWidth()/220))-1*20) > 0){
			typed_check2.setPosition(0, typed_check2.getY() - 20, 220, 20*(typed_check2.getTextWidth()/220)+1*20);
		}
		container_typed_check2.invalidate();
		break;
	}
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_2View::eye1Pressed()
{
	if(keyboard5_pwd_eye_1.getCurrentlyDisplayedBitmap() == BITMAP_OJO_ABIERTO_ID){
		keyboard5_text_typed_1.setVisible(true);
		keyboard5_text_typed_hide_1.setVisible(false);
	}
	else{
		keyboard5_text_typed_1.setVisible(false);
		keyboard5_text_typed_hide_1.setVisible(true);
	}

	keyboard5_text_area_1.invalidate();
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_2View::eye2Pressed()
{
	if(keyboard5_pwd_eye_2.getCurrentlyDisplayedBitmap() == BITMAP_OJO_ABIERTO_ID){
		keyboard5_text_typed_2.setVisible(true);
		keyboard5_text_typed_hide_2.setVisible(false);
	}
	else{
		keyboard5_text_typed_2.setVisible(false);
		keyboard5_text_typed_hide_2.setVisible(true);
	}

	keyboard5_text_area_2.invalidate();
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_2View::retryPressed()
{
	/*** Habilitación del NFC para permitir lectura/escritura ***/
	screen_flow_2View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);

	/*** Selección de los elementos visibles/ocultos en la pantalla ***/
	s7_writeError1.setVisible(false);
	s5_initNFC.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_2View::assignAliasPressed()
{
	/*** Selección de los elementos visibles/ocultos en la pantalla ***/
	s8_1_viewTagInfo.setVisible(false);
	s8_2_typeAlias.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/*
 *
 * Funciones auxiliares
 *
 */

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_2View::changeAESPassword(uint8_t keyAES[])
{
	/*** Des-inicialización AES-256 ***/
	HAL_CRYP_DeInit(&hcryp);

	/*** Inicialización AES-256 con nueva contraseña***/
	hcryp.Instance = AES;
	hcryp.Init.DataType = CRYP_NO_SWAP;
	hcryp.Init.KeySize = CRYP_KEYSIZE_256B;
	hcryp.Init.pKey = (uint32_t *)keyAES;
	hcryp.Init.Algorithm = CRYP_AES_ECB;
	hcryp.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
	hcryp.Init.HeaderWidthUnit = CRYP_HEADERWIDTHUNIT_WORD;
	hcryp.Init.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ALWAYS;
	hcryp.Init.KeyMode = CRYP_KEYMODE_NORMAL;

	if(HAL_CRYP_Init(&hcryp) != HAL_OK){
		Error_Handler();
	}
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
void screen_flow_2View::setScreenMode()
{
	/*** Configuración de elementos de pantalla en función al modo (oscuro/claro) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		/***/
		btn_seed.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_seed.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_plain_text.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_plain_text.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		/***/
		keyboard1_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard1_text_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard2_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard2_text_predicted.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard2_text_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard3_text_area.setColor(touchgfx::Color::getColorFromRGB(0xFF,0xFF,0xFF));
		keyboard3_btn_enter.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard3_btn_enter.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard3_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		typed_check1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_encrypt1.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_encrypt1.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard3_text_info_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard3_text_info_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		keyboard4_text_area.setColor(touchgfx::Color::getColorFromRGB(0xFF,0xFF,0xFF));
		keyboard4_btn_enter.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard4_btn_enter.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard4_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard4_text_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		typed_check2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_encrypt2.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_encrypt2.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		btn_multi_yes.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_multi_yes.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_multi_no.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_multi_no.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_info_multi_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_multi_select.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_multi_select.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_info_multi_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_multi_num.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    btn_multi_plus.setIconBitmaps(Bitmap(BITMAP_PLUS_DARK_ID), Bitmap(BITMAP_PLUS_DARK_ID));
	    btn_multi_minus.setIconBitmaps(Bitmap(BITMAP_MINUS_DARK_ID), Bitmap(BITMAP_MINUS_DARK_ID));
		/***/
		keyboard5_btn_enter.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard5_btn_enter.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard5_text_typed_2.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard5_text_typed_1.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard5_text_typed_hide_2.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard5_text_typed_hide_1.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard5_text_info_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		keyboard5_text_info_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		btn_store_cryptogram.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		text_pwd_success_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		init_nfc_text1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		init_nfc_text2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		wait_read_write_nfc_text.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		btn_retry.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_retry.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_7.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
	    btn_assign_alias.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
	    btn_assign_alias.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    text_uid.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    text_uid_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
	    /***/
		keyboard6_text_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		btn_success.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_success.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_spanish_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_spanish_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_spanish_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_spanish_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_spanish_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_english_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_english_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_english_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_english_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_english_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_cryptogram_success_english_6.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
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
void screen_flow_2View::setScreenLanguage()
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

/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

//		/*
// 		* Debug --> Palabras encriptadas
// 		*/
//
//		printf("\r\n\r\n------------------------------------------------------------------\r\n");
//		printf("Texto a encriptar:\r\n");
//		for(int i = 0; i < strlen((const char*) text_to_encrypt); i++){
//			printf("%c", text_to_encrypt[i]);
//		}
//		printf("\r\n\r\n");
//
//		printf("Password RAW:\r\n");
//		for(int i = 0; i < strlen((const char*) pwd_raw); i++)
//		{
//			printf("%c", pwd_raw[i]);
//		}
//		printf("\r\n\r\n");
//
//		printf("Password SHA-256:\r\n");
//		for(int i = 0; i < 32; i++)
//		{
//			printf("%c", pwd_sha256[i]);
//		}
//		printf("\r\n\r\n");
//
//		printf("Texto encriptado:\r\n");
//		for(int i = 0; i < SIZE_CRYPT; i++)
//		{
//			printf("%c", cuvex.nfc.tag.new_cryptogram[i]);
//		}
//		printf("\r\n------------------------------------------------------------------\r\n\r\n");
//		/**********************************************************************************************************************************************************/












