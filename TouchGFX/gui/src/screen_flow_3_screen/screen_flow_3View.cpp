#include <gui/screen_flow_3_screen/screen_flow_3View.hpp>

/*******************************/
#include "main.h"
extern struct cuvex cuvex;
extern HASH_HandleTypeDef hhash;
extern CRYP_HandleTypeDef hcryp;
/*******************************/

screen_flow_3View::screen_flow_3View(): temporal_block(0), text_type(0), total_words(0), index_words(0), num_pwds(1), actual_pwd(0), pwd_ok(false), decrypted_text{0}, decrypted_lenght(0), words_decrypted{0}, words_to_check{0}, buff_passphrase{0}, buff_plain_text{0}, pwds{0}, pwd_raw{0}, pwd_sha256{0}
{
	add(qr_code);
}

void screen_flow_3View::setupScreen()
{
	screen_flow_3ViewBase::setupScreen();
	screen_flow_3View::checkTemporalBlock();
	screen_flow_3View::setScreenMode();
	screen_flow_3View::setScreenLanguage();
	screen_flow_3View::changeScreen(GUI_TO_MAIN_SCREEN_FLOW_3);

	/*** Borrado de buffer's ***/
	memset(keyboard_text_typedBuffer, 0x00, sizeof(keyboard_text_typedBuffer));
	keyboard_password.clearBuffer();
}

void screen_flow_3View::tearDownScreen()
{
	screen_flow_3ViewBase::tearDownScreen();
	screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);
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
void screen_flow_3View::tickEventScreen()
{
	static uint8_t tick = 0;
	static uint16_t tick_temporal_block = 0;

	/*** Temporización de bloqueo temporal dentro del flujo ***/
	if(temporal_block == 1)
	{
		tick_temporal_block++;

		if(tick_temporal_block >= 5*60*5)	//Cada 4 entradas en la función es aproximadamente 1 segundo... 5' en total (aprox.)
		{
			temporal_block = 0;
			tick_temporal_block = 0;
			cuvex.info.errors = 0;
			screen_flow_3View::changeFlash(GUI_TO_MAIN_FLASH_SAVE_SETTINGS);
			screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
			screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ);
			s0_temporalBlock.setVisible(false);
			s1_initNFC.setVisible(true);
			close_button.setVisible(true);
			background.invalidate();
		}
	}

	/*** Gestión del teclado (password) ***/
	if(keyboard_password.isVisible() == true)
	{
		if(Unicode::strncmp(keyboard_text_typedBuffer, keyboard_password.getBuffer(), KEYBOARD_TEXT_TYPED_SIZE) != 0)
		{
			Unicode::snprintf(keyboard_text_typedBuffer, KEYBOARD_TEXT_TYPED_SIZE, keyboard_password.getBuffer());
			keyboard_text_typed.setWideTextAction(touchgfx::WIDE_TEXT_NONE);

			if(keyboard_text_typed.getTextWidth() <= 160){
				keyboard_text_typed.setPosition(160-(keyboard_text_typed.getTextWidth()/2), 75, keyboard_text_typed.getTextWidth(), 20);
			}
			else{
				keyboard_text_typed.setPosition(76, 75, 160, 20);
			}

			for(int i=0; i<KEYBOARD_TEXT_TYPED_HIDE_SIZE; i++){
				keyboard_text_typed_hideBuffer[i] = 0x00;
			}
			for(int i=0; i<Unicode::strlen(keyboard_text_typedBuffer); i++){
				keyboard_text_typed_hideBuffer[i] = 8226;	//U+8226 (bullet '•')
			}

			if(keyboard_text_typedBuffer[0] == 0x00){
				keyboard_placeholder.setVisible(true);
			}
			else{
				keyboard_placeholder.setVisible(false);
			}

			keyboard_text_area.invalidate();
		}
	}

	/*** Gestión del temporizador ***/
	if(s8_viewSecret.isVisible() == true)
	{
		if(tick++ > 4)
		{
			if((Unicode::atoi(text_timeoutBuffer) - 1) > 9)
			{
				Unicode::snprintf(text_timeoutBuffer, TEXT_TIMEOUT_SIZE, "%d", Unicode::atoi(text_timeoutBuffer) - 1);
				background.invalidate();
				tick = 0;
			}
			else if(((Unicode::atoi(text_timeoutBuffer) - 1) <= 9) && ((Unicode::atoi(text_timeoutBuffer) - 1) > 0))
			{
				Unicode::snprintf(text_timeoutBuffer, TEXT_TIMEOUT_SIZE, "0%d", Unicode::atoi(text_timeoutBuffer) - 1);
				background.invalidate();
				tick = 0;
			}
			else
			{
				qr_code.setVisible(false);
				btn_back.setVisible(false);
				close_button.setVisible(false);
				s8_viewSecret.setVisible(false);
				s9_timeoutSecret.setVisible(true);
				background.invalidate();
			}
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
void screen_flow_3View::changeScreen(uint8_t screen)
{
	presenter->changeScreen(screen);
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::changeFlash(uint8_t state)
{
	presenter->changeFlash(state);
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::changeStateNfc(uint8_t state)
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
void screen_flow_3View::updateStateNfc(uint16_t state)
{
	/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
	switch(state)
	{
	case MAIN_TO_GUI_NFC_ERROR:
	default:
		application().gotoscreen_menuScreenNoTransition();
		break;

	case MAIN_TO_GUI_NFC_INITIALIZED:
		if(s1_initNFC.isVisible() == true)
		{
			s1_initNFC.setVisible(false);
			s2_waitReadNFC.setVisible(true);
		}
		break;

	case MAIN_TO_GUI_NFC_TAG_READED:
		if(s2_waitReadNFC.isVisible() == true)
		{
			s2_waitReadNFC.setVisible(false);

			if(cuvex.nfc.tag.encripted == true)
			{
				s3_viewTagInfo.setVisible(true);
				screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_DISABLE);

				if(cuvex.nfc.tag.alias[0] == 0x00)	//Si tag leido no tiene alias => Texto con el uid (sino alias)
				{
					text_uid.setVisible(true);
					text_uid_info.setVisible(true);
					text_alias.setVisible(false);
					text_alias_info.setVisible(false);
					memset(text_uidBuffer, 0x00, TEXT_UID_SIZE);
					Unicode::snprintf(text_uidBuffer, TEXT_UID_SIZE, (const char*) cuvex.nfc.tag.uid);
				}
				else
				{
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
			else
			{
				s4_readError.setVisible(true);
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
 * Gestión de las pulsaciones del teclado
 *
 */

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::hideKeyboardPressed()
{
	/*** Se bajan los elementos de la pantalla (textos, recuadro y enter) ***/
	keyboard_text_info.setPosition(0, 90, 320, 20);
	keyboard_text_typed_hide.setPosition(76, 125, 160, 20);
	keyboard_text_area.setXY(45, 120);
	keyboard_pwd_eye.setXY(245, 120);
	keyboard_placeholder.setPosition(62, 125, 180, 20);

	if(keyboard_text_typed.getTextWidth() <= 160){
		keyboard_text_typed.setPosition(160-(keyboard_text_typed.getTextWidth()/2), 125, keyboard_text_typed.getTextWidth(), 20);
	}
	else{
		keyboard_text_typed.setPosition(76, 125, 160, 20);
	}

	/*** Actualización pulsadores y teclado ***/
	keyboard_password.setVisible(false);
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
void screen_flow_3View::showKeyboardPressed()
{
	/*** Se suben los elementos de la pantalla (textos, recuadro y enter) ***/
	keyboard_text_info.setPosition(0, 40, 320, 20);
	keyboard_text_typed_hide.setPosition(76, 75, 160, 20);
	keyboard_text_area.setXY(45, 70);
	keyboard_pwd_eye.setXY(245, 70);
	keyboard_placeholder.setPosition(62, 75, 180, 20);

	if(keyboard_text_typed.getTextWidth() <= 160){
		keyboard_text_typed.setPosition(160-(keyboard_text_typed.getTextWidth()/2), 75, keyboard_text_typed.getTextWidth(), 20);
	}
	else{
		keyboard_text_typed.setPosition(76, 75, 160, 20);
	}


	/*** Actualización pulsadores y teclado ***/
	keyboard_password.setVisible(true);
	keyboard_btn_hide.setVisible(true);
	keyboard_btn_show.setVisible(false);
	keyboard_btn_enter.setVisible(false);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::enterKeyboardPressed()
{
	char buff_aux1[TEXT_SECRET_CHECK_SIZE] = {0}, buff_aux2[10] = {0};
	char *ptr1, *ptr2;

	if(keyboard_text_typedBuffer[0] != 0x00)
	{
		/*** Obtención del texto tecleado (contraseña) ***/
		memset(pwds[actual_pwd], 0x00, KEYBOARD_TEXT_TYPED_SIZE);

		for(int i=0; i<KEYBOARD_TEXT_TYPED_SIZE; i++)
		{
			if(keyboard_text_typedBuffer[i] == 8364){	//Si '€' (8364) se convierte al caracter '¶' (182)
				pwds[actual_pwd][i] = 182;
			}
			else{
				pwds[actual_pwd][i] = (uint8_t) keyboard_text_typedBuffer[i];
			}
		}

		actual_pwd++;

		if(actual_pwd < num_pwds)
		{
			/*** Selección de los textos a visualizar en el campo de información de password (en función del idioma y del número de firmantes) ***/
			Unicode::UnicodeChar degree[] = {0x00B0,0};

			if(cuvex.info.language == SPANISH){
				if(num_pwds > 1){
					Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Persona N%s%d", degree, actual_pwd+1);
				}
				else{
					Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Introduce tu Password.");
				}

				if(num_pwds != actual_pwd+1){
					Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "CONTINUAR");
				}
				else{
					Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "DESCIFRAR");
				}
			}
			else{
				if(num_pwds > 1){
					Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Person N%s%d", degree, actual_pwd+1);
				}
				else{
					Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Enter your Password.");
				}

				if(num_pwds != actual_pwd+1){
					Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "CONTINUE");
				}
				else{
					Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "DECRYPT");
				}
			}
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

			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
			/*Concatenación de las contraseñas en crudo (raw)*/
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

			if(pwd0_length != 0)
			{
				/*** Obtención de la contraseña cifrada (SHA-256) ***/
				HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, pwd_raw_length, pwd_sha256, HAL_MAX_DELAY);

				/*** Des-encriptación AES-256 + Comprobación de contraseña válida ***/
				changeAESPassword(pwd_sha256);
				HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.cryptogram, SIZE_CRYPT_MSG, (uint32_t *) decrypted_text, HAL_MAX_DELAY);

				if(strstr((const char *) decrypted_text, "[bip39]") != NULL){
					text_type = 0;
					pwd_ok = true;
				}
				else if(strstr((const char *) decrypted_text, "[plain-text]") != NULL){
					text_type = 1;
					pwd_ok = true;
				}
				else{
					pwd_ok = false;
				}

				/*** Se deben comprobar todas las posibles combinaciones ***/
				uint8_t iteration_length=0;

				if(pwd5_length!=0){
					iteration_length=6;
				}
				else if(pwd4_length!=0){
					iteration_length=5;
				}
				else if(pwd3_length!=0){
					iteration_length=4;
				}
				else if(pwd2_length!=0){
					iteration_length=3;
				}
				else{
					iteration_length=2;
				}

				uint16_t i = 0;
				uint16_t c[iteration_length] = {0};
				uint8_t aux[KEYBOARD_TEXT_TYPED_SIZE]={0};

				/*** Algoritmo de Heap ***/
				while(i<iteration_length)
				{
					if(pwd_ok == true){
						break;
					}
					else{
						if(c[i]<i)
						{
							if(i%2==0)
							{
								memset(aux, 0, KEYBOARD_TEXT_TYPED_SIZE);
								memcpy(aux, &pwds[0], strlen((const char *)pwds[0]));

								memset(&pwds[0], 0, KEYBOARD_TEXT_TYPED_SIZE);
								memcpy(&pwds[0], &pwds[i], strlen((const char *)pwds[i]));

								memset(&pwds[i], 0, KEYBOARD_TEXT_TYPED_SIZE);
								memcpy(&pwds[i], aux, strlen((const char *)aux));
							}
							else
							{
								memset(aux, 0, KEYBOARD_TEXT_TYPED_SIZE);
								memcpy(aux, &pwds[c[i]], strlen((const char *)pwds[c[i]]));

								memset(&pwds[c[i]], 0, KEYBOARD_TEXT_TYPED_SIZE);
								memcpy(&pwds[c[i]], &pwds[i], strlen((const char *)pwds[i]));

								memset(&pwds[i], 0, KEYBOARD_TEXT_TYPED_SIZE);
								memcpy(&pwds[i], aux, strlen((const char *)aux));
							}

							memset(pwd_raw, 0x00, sizeof(pwd_raw));
							strncat((char*) pwd_raw, (const char*) cuvex.signature_buffer, SIGNATURE_SIZE);
							strcat((char*) pwd_raw, (const char*) pwds[0]);
							strcat((char*) pwd_raw, (const char*) pwds[1]);
							strcat((char*) pwd_raw, (const char*) pwds[2]);
							strcat((char*) pwd_raw, (const char*) pwds[3]);
							strcat((char*) pwd_raw, (const char*) pwds[4]);
							strcat((char*) pwd_raw, (const char*) pwds[5]);

							/*** Obtención de la contraseña cifrada (SHA-256) ***/
							HAL_HASHEx_SHA256_Start(&hhash, pwd_raw, pwd_raw_length, pwd_sha256, HAL_MAX_DELAY);

							/*** Des-encriptación AES-256 + Comprobación de contraseña válida ***/
							changeAESPassword(pwd_sha256);
							HAL_CRYP_Decrypt(&hcryp, (uint32_t *) cuvex.nfc.tag.cryptogram, SIZE_CRYPT_MSG, (uint32_t *) decrypted_text, HAL_MAX_DELAY);

							if(strstr((const char *) decrypted_text, "[bip39]") != NULL){
								text_type = 0;
								pwd_ok = true;
							}
							else if(strstr((const char *) decrypted_text, "[plain-text]") != NULL){
								text_type = 1;
								pwd_ok = true;
							}
							else{
								pwd_ok = false;
							}

							c[i]+=1;
							i=0;
						}
						else{
							c[i]=0;
							i++;
						}
					}
				}
			}

			/*** Obtención de texto descifrado (semilla bip39, texto plano) --> Si contraseña válida ***/
			if(pwd_ok == true)
			{
				switch(text_type)
				{
				case 0:
					/*** Parseo de las palabras bip39 y del passphrase ***/
					ptr1 = strstr((char *) decrypted_text, "[bip39]");
					ptr2 = strstr((char *) decrypted_text, "[passphrase]");

					for(int i=8; i<ptr2-ptr1; i++)
					{
						if(decrypted_text[i] == ','){
							total_words++;
							index_words = 0;
						}
						else{
							words_decrypted[total_words][index_words++] = decrypted_text[i];
						}
					}
					total_words++;

					for(int j=0; j<total_words; j++){
						for(int i=0; i<15; i++){
							words_to_check[j][i] = words_decrypted[j][i];
						}
						getBip39Word((char *) words_to_check[j]);
					}

					decrypted_lenght = strlen((char *) decrypted_text);

					for(int i=0; i<((decrypted_lenght)-(ptr2-ptr1)+(12)); i++){
						buff_passphrase[i] = decrypted_text[i+((ptr2-ptr1)+(12))];
					}

					/*** Generación de array para visualización ***/
					for(int i=0; i<total_words; i++)
					{
						snprintf(buff_aux2, 5, "%d. ", i+1);
						strcat(buff_aux1, (char *) buff_aux2);
						strcat(buff_aux1, (char *) words_to_check[i]);
						strcat(buff_aux1, (char *) "\n");
					}

					strcat(buff_aux1, (char*) "\nPassphrase:\n");
					strcat(buff_aux1, (char*) buff_passphrase);

					/*** Asignación de palabras+passprashe a visualizar en texto "scrollable" (si '¶' (182) se convierte al caracter '€' (8364)) ***/
					Unicode::snprintf(text_secret_checkBuffer, TEXT_SECRET_CHECK_SIZE, buff_aux1);

					for(int i = 0; i<TEXT_SECRET_CHECK_SIZE; i++){
						if(text_secret_checkBuffer[i] == 182){
							text_secret_checkBuffer[i] = 8364;
						}
					}

					text_secret_check.setPosition(0, 0, 200, (20*(total_words+1))+(20*5));
					text_secret_check.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);
					s5_typePassword.setVisible(false);
					s8_viewSecret.setVisible(true);
					break;

				case 1:
					/*** Generación de array para visualización ***/
					memset(buff_plain_text, 0x00, sizeof(buff_plain_text));

					decrypted_lenght = strlen((char *) decrypted_text);

					for(int i=0; i<decrypted_lenght; i++){
						buff_plain_text[i] = decrypted_text[i+12];
					}

					/*** Asignación de texto plano a visualizar en campo "scrollable" (si '¶' (182) se convierte al caracter '€' (8364)) ***/
					Unicode::snprintf(text_secret_checkBuffer, TEXT_SECRET_CHECK_SIZE, (char *) buff_plain_text);

					for(int i = 0; i<TEXT_SECRET_CHECK_SIZE; i++){
						if(text_secret_checkBuffer[i] == 182){
							text_secret_checkBuffer[i] = 8364;
						}
					}

					text_secret_check.setPosition(0, 0, 200, 20*(text_secret_check.getTextWidth()/200)+2*20);
					text_secret_check.setWideTextAction(touchgfx::WIDE_TEXT_CHARWRAP);
					s5_typePassword.setVisible(false);
					s8_viewSecret.setVisible(true);
					break;

				default:
					break;
				}
			}
			else
			{
				cuvex.info.errors++;

				if(cuvex.info.errors == 1)	//Advertencia
				{
					close_button.setVisible(false);
					s5_typePassword.setVisible(false);
					s6_passwordError1.setVisible(true);

					if(cuvex.info.language == SPANISH){
						text_password_error1_spanish.setVisible(true);
						text_password_error1_english.setVisible(false);
					}
					else{
						text_password_error1_spanish.setVisible(false);
						text_password_error1_english.setVisible(true);
					}
				}
				else	//Bloqueo temporal
				{
					close_button.setVisible(false);
					s5_typePassword.setVisible(false);
					s7_passwordError2.setVisible(true);

					if(cuvex.info.language == SPANISH){
						text_password_error2_spanish.setVisible(true);
						text_password_error2_english.setVisible(false);
					}
					else{
						text_password_error2_spanish.setVisible(false);
						text_password_error2_english.setVisible(true);
					}

					screen_flow_3View::changeFlash(GUI_TO_MAIN_FLASH_SAVE_SETTINGS);
				}
			}
		}

		/*** Borrado de los buffers del teclado y de visualización ***/
		memset(keyboard_text_typedBuffer, 0x00, sizeof(keyboard_text_typedBuffer));
		memset(keyboard_text_typed_hideBuffer, 0x00, sizeof(keyboard_text_typed_hideBuffer));
		keyboard_password.clearBuffer();

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
 * Gestión de las pulsaciones táctiles
 *
 */

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::decryptPressed()
{
	num_pwds = cuvex.nfc.tag.multisigned;

	/*** Selección de los textos a visualizar en los campos de información ***/
	Unicode::UnicodeChar degree[] = {0x00B0,0};

	if(cuvex.info.language == SPANISH){
		if(num_pwds > 1){
			Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Persona N%s%d", degree, actual_pwd+1);
			Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "CONTINUAR");
		}
		else{
			Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Introduce tu Password.");
			Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "DESCIFRAR");
		}
	}
	else{
		if(num_pwds > 1){
			Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Person N%s%d", degree, actual_pwd+1);
			Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "CONTINUE");
		}
		else{
			Unicode::snprintf(keyboard_text_infoBuffer, KEYBOARD_TEXT_INFO_SIZE, "Enter your Password.");
			Unicode::snprintf(keyboard_btn_enterBuffer, KEYBOARD_BTN_ENTER_SIZE, "DECRYPT");
		}
	}

	/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
	s3_viewTagInfo.setVisible(false);
	s5_typePassword.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::retryPressed()
{
	/*** Re-inicialización del NFC ***/
	screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
	screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ);

	/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
	s4_readError.setVisible(false);
	s1_initNFC.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::moreTimePressed()
{
	Unicode::snprintf(text_timeoutBuffer, TEXT_TIMEOUT_SIZE, "60");
	text_timeout.invalidate();
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_3View::eyePressed()
{
	if(keyboard_pwd_eye.getCurrentlyDisplayedBitmap() == BITMAP_OJO_ABIERTO_ID){
		keyboard_text_typed.setVisible(true);
		keyboard_text_typed_hide.setVisible(false);
	}
	else{
		keyboard_text_typed.setVisible(false);
		keyboard_text_typed_hide.setVisible(true);
	}

	keyboard_text_area.invalidate();
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_3View::resetMicrocontrollerPressed()
{
	NVIC_SystemReset();
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_3View::btnUpPressed()
{
	switch(text_type)
	{
	case 0:
	default:
		if(text_secret_check.getY() < 0){
			text_secret_check.setPosition(0, text_secret_check.getY() + 20, 200, (20*(total_words+1)) + (20*5));
		}
		break;

	case 1:
		if(text_secret_check.getY() < 0){
			text_secret_check.setPosition(0, text_secret_check.getY() + 20, 200, 20*(text_secret_check.getTextWidth()/200));
		}
		break;
	}

	container_typed_check.invalidate();
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_3View::btnDownPressed()
{
	switch(text_type)
	{
	case 0:
	default:
		if((text_secret_check.getY() + 20*(total_words+1)) > 0){
			text_secret_check.setPosition(0, text_secret_check.getY() - 20, 200, (20*(total_words+1))+(20*5));
		}
		break;

	case 1:
		if((text_secret_check.getY() + (20*(text_secret_check.getTextWidth()/200))-3*20) > 0){
			text_secret_check.setPosition(0, text_secret_check.getY() - 20, 200, 20*(text_secret_check.getTextWidth()/200)+2*20);
		}
		break;
	}

	container_typed_check.invalidate();
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_3View::qrSmallPressed()
{
	/*** Generación código QR ***/
	char qr_text[1000] = {0};

	if(text_type == 1)	//Texto plano
	{
		strcpy(qr_text, (char *) buff_plain_text);
	}
	else	//Bip39
	{
		for(int i=0; i<total_words; i++)
		{
			strcat(qr_text, (char *) words_to_check[i]);
			strcat(qr_text, (char *) " ");
		}
	}

	code = new QR(qr_text, 15);
	qr_code.setXY(83,45);
	qr_code.setScale(2);
	qr_code.setQRCode(code);

	/*** Desplazamiento del temporizador ***/
	text_timeout.setPosition(130, 5, 60, 30);

	/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
	container_qr_small_code.setVisible(false);
	container_typed_check.setVisible(false);
	close_button.setVisible(false);
	btn_back.setVisible(true);
	qr_code.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();

}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_3View::backPressed()
{
	/*** Desplazamiento del temporizador ***/
	text_timeout.setPosition(80, 25, 60, 30);

	/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
	container_qr_small_code.setVisible(true);
	container_typed_check.setVisible(true);
	close_button.setVisible(true);
	btn_back.setVisible(false);
	qr_code.setVisible(false);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_3View::btnError1Pressed()
{
	/*** Borrado variables vinculadas a la obtención de la contraseña ***/
	for(int i=0; i<10; i++){
		memset(pwds[i], 0x00, KEYBOARD_TEXT_TYPED_SIZE);
	}
	memset(pwd_raw, 0x00, 10*KEYBOARD_TEXT_TYPED_SIZE);
	memset(pwd_sha256, 0x00, 32);
	num_pwds 	= cuvex.nfc.tag.multisigned;
	actual_pwd 	= 0;
	pwd_ok 		= false;

	/*** Llamada a la función que da salto al screen anterior a la pantalla a saltar para que se carguen los elementos bien ***/
	screen_flow_3View::decryptPressed();

	/*** Seleccion de los elementos visibles/ocultos en la pantalla ***/
	s6_passwordError1.setVisible(false);
	s5_typePassword.setVisible(true);
	close_button.setVisible(true);

	/*** Actualización de la pantalla ***/
	background.invalidate();
}

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_3View::btnError2Pressed()
{
	NVIC_SystemReset();
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

/******************************************************************************************************************************************************************************
 ***** Función 		:
 ***** Descripción 	:
 ***** Parámetros 	:
 ***** Respuesta 	:
 ******************************************************************************************************************************************************************************/
void screen_flow_3View::changeAESPassword(uint8_t keyAES[])
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

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void screen_flow_3View::checkTemporalBlock()
{
	/*** Configuración de elementos de pantalla en base a si hay un bloqueo temporal activo o no ***/
	switch(cuvex.info.errors)
	{
	case 0:
	case 1:
	default:
		screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_ENABLE);
		screen_flow_3View::changeStateNfc(GUI_TO_MAIN_NFC_TAG_READ);
		s0_temporalBlock.setVisible(false);
		s1_initNFC.setVisible(true);
		temporal_block = 0;
		break;

	case 2:
		s0_temporalBlock.setVisible(true);
		s1_initNFC.setVisible(false);
		close_button.setVisible(false);

		if(cuvex.info.language == SPANISH){
			text_temporal_block_spanish.setVisible(true);
			text_temporal_block_english.setVisible(false);
		}
		else{
			text_temporal_block_spanish.setVisible(false);
			text_temporal_block_english.setVisible(true);
		}

		temporal_block = 1;
		break;
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
void screen_flow_3View::setScreenMode()
{
	/*** Configuración de elementos de pantalla en función al modo (oscuro/claro) ***/
	if(cuvex.info.mode == DARK)
	{
		background.setColor(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51));
		btn_back.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x3F,0x3F,0x51), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_back.setIconBitmaps(Bitmap(BITMAP_BACK_DARK_ID), Bitmap(BITMAP_BACK_ID));
		/***/
		init_nfc_text1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		init_nfc_text2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		text_wait_read_nfc.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		btn_decrypt.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_decrypt.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_alias_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_alias.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_uid_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_uid.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		btn_retry.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_retry.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_read_error.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		keyboard_btn_enter.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_typed.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_typed_hide.setColor(touchgfx::Color::getColorFromRGB(0,0,0));
		keyboard_text_info.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		password_error1_english_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_english_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_english_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_english_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_english_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_spanish_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_spanish_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_spanish_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_spanish_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error1_spanish_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_english_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_english_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_english_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_english_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_english_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_spanish_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_spanish_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_spanish_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_spanish_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		password_error2_spanish_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		btn_more_time.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D), touchgfx::Color::getColorFromRGB(0x40,0x5C,0xA0), touchgfx::Color::getColorFromRGB(0,0,0), touchgfx::Color::getColorFromRGB(0,0,0));
		btn_more_time.setTextColors(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED), touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		text_secret_check.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		text_timeout.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		text_timeout_secret.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		/***/
		temporal_block_english_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_english_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_english_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_english_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_english_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_english_6.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_spanish_1.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_spanish_2.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_spanish_3.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_spanish_4.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_spanish_5.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_spanish_6.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
		temporal_block_spanish_7.setColor(touchgfx::Color::getColorFromRGB(0xED,0xED,0xED));
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
void screen_flow_3View::setScreenLanguage()
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

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

///*
// * Debug --> Palabras desencriptadas
// */
//	printf("\r\n\r\n---------------------------------\r\n");
//	for(int j = 0; j < total_words; j++)
//	{
//		printf("word %d:", j);
//		for(int i = 0; i < 20; i++)
//		{
//			printf("%c", words[j][i]);
//		}
//		printf("\r\n");
//	}
//	printf("---------------------------------\r\n\r\n");

///*
// * Debug --> Textos desencriptados
// */
//				printf("-----------------------------------------------------------\r\n");
//				for(int j=0; j<total_words; j++)
//				{
//					for(int i=0; i<5; i++)
//					{
//						printf("%c", words_decrypted[j][i]);
//					}
//					printf("\r\n");
//				}
//				printf("-----------------------------------------------------------\r\n");
//				for(int j=0; j<total_words; j++)
//				{
//					for(int i=0; i<15; i++)
//					{
//						printf("%c", words_to_check[j][i]);
//					}
//					printf("\r\n");
//				}
//				printf("-----------------------------------------------------------\r\n");
//				for(int i=0; i<105; i++)
//				{
//					printf("%c", buff_passphrase[i]);
//				}
//				printf("\r\n");
//				printf("-----------------------------------------------------------\r\n");

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/




