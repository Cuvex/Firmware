/*
 * mainTask.c
 */

#include "mainTask.h"

/******************************************************************************************************************************************************************************
 ***** Función 		: void main_Task(void const * argument)
 ***** Descripción 	: Función principal de la tarea "mainTask"
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void main_Task(void const * argument)
{
	/*** Lectura de sectores EEPROM/SIGNATURE + inicialización + carga datos en RAM ***/
	readFlash(EEPROM_ADDR, cuvex.eeprom_buffer, EEPROM_SIZE);
	readFlash(SIGNATURE_ADDR, cuvex.signature_buffer, SIGNATURE_SIZE);

	if(memcmp(cuvex.eeprom_buffer + 96, ">>>>>Footer<<<<<", 16) != 0){
		initEEPROM();
	}

	loadEEPROM();

	/*** Inicialización de periféricos y variables + retardo ****/
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
	getCuvexVersions();
	clearNfc_all();
	osDelay(250);

	/*** Bucle principal ***/
	for(;;)
	{
		processGuiToMainQueue();	//Procesado de mensajes recibidos en cola "guiToMain"
		stateMachineScreens();		//Máquina de estados en base a la pantalla (fujo) actual
		osDelay(10);
	}
}

/*
 *
 * FUNCIONES PRINCIPALES
 *
 */

/******************************************************************************************************************************************************************************
 ***** Función 		: void processGuiToMainQueue(void)
 ***** Descripción 	: Procesado de mensajes provenientes de "guiTask"
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void processGuiToMainQueue(void)
{
	uint16_t rcv_data_gui = 0;

	if((osMessageQueueGetCount(guiToMainQueueHandle) > 0) && (osMessageQueueGet(guiToMainQueueHandle, &rcv_data_gui, 0, 0) == osOK))
	{
		switch(rcv_data_gui)
		{
		default:
			break;

			/********************************************************/
		case GUI_TO_MAIN_SCREEN_INIT:
			cuvex.screen = SCREEN_INIT;
			clearNfc_all();
			break;

		case GUI_TO_MAIN_SCREEN_MAIN_MENU:
			cuvex.screen = SCREEN_MAIN_MENU;
			clearNfc_all();
			break;

		case GUI_TO_MAIN_SCREEN_FLOW_1:
			cuvex.screen = SCREEN_FLOW_1;
			break;

		case GUI_TO_MAIN_SCREEN_FLOW_2:
			cuvex.screen = SCREEN_FLOW_2;
			break;

		case GUI_TO_MAIN_SCREEN_FLOW_3:
			cuvex.screen = SCREEN_FLOW_3;
			break;

		case GUI_TO_MAIN_SCREEN_FLOW_4:
			cuvex.screen = SCREEN_FLOW_4;
			break;

		case GUI_TO_MAIN_SCREEN_FLOW_5:
			cuvex.screen = SCREEN_FLOW_5;
			break;

			/********************************************************/
		case GUI_TO_MAIN_NFC_DISABLE:
			clearNfc_readerFlags();
			clearNfc_tagFlags();
			cuvex.nfc.flag_enabled = false;
			break;

		case GUI_TO_MAIN_NFC_ENABLE:
			clearNfc_readerFlags();
			clearNfc_tagFlags();
			cuvex.nfc.flag_enabled = true;
			break;

		case GUI_TO_MAIN_NFC_TAG_NONE:
			clearNfc_tagFlags();
			cuvex.nfc.tag.action = NFC_TAG_NONE;
			break;

		case GUI_TO_MAIN_NFC_TAG_READ:
			clearNfc_tagFlags();
			cuvex.nfc.tag.action = NFC_TAG_READ;
			break;

		case GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_1:
			clearNfc_tagFlags();
			cuvex.nfc.tag.action = NFC_TAG_READ_WRITE_FLOW_1;
			break;

		case GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_2:
			clearNfc_tagFlags();
			cuvex.nfc.tag.action = NFC_TAG_READ_WRITE_FLOW_2;
			break;

		case GUI_TO_MAIN_NFC_TAG_READ_WRITE_FLOW_4:
			clearNfc_tagFlags();
			cuvex.nfc.tag.action = NFC_TAG_READ_WRITE_FLOW_4;
			break;

			/********************************************************/
		case GUI_TO_MAIN_FLASH_SAVE_SETTINGS:
			editEEPROM();
			break;

		case GUI_TO_MAIN_FLASH_ERASE_SIGNATURE:
			eraseSignature();
			break;
		}
	}
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void stateMachineScreens(void)
 ***** Descripción 	: Máquina de estados específica para cada flujo (si procede)
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void stateMachineScreens(void)
{
	switch(cuvex.screen)
	{
	case SCREEN_INIT:
	case SCREEN_MAIN_MENU:
	case SCREEN_FLOW_5:
	default:
		break;

		/*
		 * Flujo 1: Administrar tarjeta
		 */

	case SCREEN_FLOW_1:
		if((cuvex.nfc.flag_enabled == true) && (cuvex.nfc.flag_initialized == true))
		{
			/*** Inicialización de lector/escritor NFC (si solicitada) ***/
			if(cuvex.nfc.flag_notify_init == false)
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_INITIALIZED}, 0, 0);
				}
				cuvex.nfc.flag_notify_init = true;
			}

			/*** Lectura de tag NFC (si solicitada) ***/
			if((cuvex.nfc.tag.action == NFC_TAG_READ) && (cuvex.nfc.tag.flag_readed == true))
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_TAG_READED}, 0, 0);
				}
				cuvex.nfc.tag.action = NFC_TAG_NONE;
				cuvex.nfc.tag.flag_readed = false;
			}

			/*** Lectura + escritura de tag NFC (si solicitada) ***/
			if((cuvex.nfc.tag.action == NFC_TAG_READ_WRITE_FLOW_1) && (cuvex.nfc.tag.flag_readed_writed_flow_1 == true))
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_1}, 0, 0);
				}
				cuvex.nfc.tag.action = NFC_TAG_NONE;
				cuvex.nfc.tag.flag_readed_writed_flow_1 = false;
			}
		}
		break;

		/*
		 * Flujo 2: Encriptar
		 */

	case SCREEN_FLOW_2:
		if((cuvex.nfc.flag_enabled == true) && (cuvex.nfc.flag_initialized == true))
		{
			/*** Inicialización de lector/escritor NFC (si solicitada) ***/
			if(cuvex.nfc.flag_notify_init == false)
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_INITIALIZED}, 0, 0);
				}
				cuvex.nfc.flag_notify_init = true;
			}

			/*** Lectura + escritura de tag NFC (si solicitada) ***/
			if((cuvex.nfc.tag.action == NFC_TAG_READ_WRITE_FLOW_2) && (cuvex.nfc.tag.flag_readed_writed_flow_2 == true))
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_2}, 0, 0);
				}
				cuvex.nfc.tag.action = NFC_TAG_NONE;
				cuvex.nfc.tag.flag_readed_writed_flow_2 = false;
			}
		}
		break;

		/*
		 * Flujo 3: Desencriptar
		 */

	case SCREEN_FLOW_3:
		if((cuvex.nfc.flag_enabled == true) && (cuvex.nfc.flag_initialized == true))
		{
			/*** Inicialización de lector/escritor NFC (si solicitada) ***/
			if(cuvex.nfc.flag_notify_init == false)
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_INITIALIZED}, 0, 0);
				}
				cuvex.nfc.flag_notify_init = true;
			}

			/*** Lectura de tag NFC (si solicitada) ***/
			if((cuvex.nfc.tag.action == NFC_TAG_READ) && (cuvex.nfc.tag.flag_readed == true))
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_TAG_READED}, 0, 0);
				}
				cuvex.nfc.tag.action = NFC_TAG_NONE;
				cuvex.nfc.tag.flag_readed = false;
			}
		}
		break;


		/*
		 * Flujo 4: Clonar
		 */

	case SCREEN_FLOW_4:
		if((cuvex.nfc.flag_enabled == true) && (cuvex.nfc.flag_initialized == true))
		{
			/*** Inicialización de lector/escritor NFC (si solicitada) ***/
			if(cuvex.nfc.flag_notify_init == false)
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_INITIALIZED}, 0, 0);
				}
				cuvex.nfc.flag_notify_init = true;
			}

			/*** Lectura de tag NFC (si solicitada) ***/
			if((cuvex.nfc.tag.action == NFC_TAG_READ) && (cuvex.nfc.tag.flag_readed == true))
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_TAG_READED}, 0, 0);
				}
				cuvex.nfc.tag.action = NFC_TAG_NONE;
				cuvex.nfc.tag.flag_readed = false;
			}

			/*** Lectura + escritura de tag NFC (si solicitada) ***/
			if((cuvex.nfc.tag.action == NFC_TAG_READ_WRITE_FLOW_4) && (cuvex.nfc.tag.flag_readed_writed_flow_4 == true))
			{
				if(osMessageQueueGetSpace(mainToGuiQueueHandle) > 0){
					osMessageQueuePut(mainToGuiQueueHandle, (void*)&(int){MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_4}, 0, 0);
				}
				cuvex.nfc.tag.action = NFC_TAG_NONE;
				cuvex.nfc.tag.flag_readed_writed_flow_4 = false;
			}
		}
		break;
	}
}

/*
 *
 * FUNCIONES DE INICIALIZACIÓN/BORRADO DE FLAGS/VARIABLES "NFC"
 *
 */

/******************************************************************************************************************************************************************************
 ***** Función 		: void clearNfc_all(void)
 ***** Descripción 	: Borrado de datos en RAM del lector/escritor NFC, de los flags del tag NFC y de la información del tag NFC
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void clearNfc_all(void)
{
	clearNfc_readerFlags();
	clearNfc_tagFlags();
	clearNfc_tagInfo();
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void clearNfc_readerFlags(void)
 ***** Descripción 	: Borrado de datos en RAM del lector/escritor NFC
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void clearNfc_readerFlags(void)
{
	cuvex.nfc.flag_enabled     = false;
	cuvex.nfc.flag_initialized = false;
	cuvex.nfc.flag_notify_init = false;
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void clearNfc_tagFlags(void)
 ***** Descripción 	: Borrado de los flags en RAM del tag NFC
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void clearNfc_tagFlags(void)
{
	cuvex.nfc.tag.action 	  				= NFC_TAG_NONE;
	cuvex.nfc.tag.flag_readed 				= false;
	cuvex.nfc.tag.flag_readed_writed_flow_1 = false;
	cuvex.nfc.tag.flag_readed_writed_flow_2 = false;
	cuvex.nfc.tag.flag_readed_writed_flow_4 = false;
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void clearNfc_tagInfo(void)
 ***** Descripción 	: Borrado de la información en RAM del tag NFC (buffers y variables)
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void clearNfc_tagInfo(void)
{
	memset(cuvex.nfc.tag.uid, 0x00, sizeof(cuvex.nfc.tag.uid));
	memset(cuvex.nfc.tag.alias, 0x00, sizeof(cuvex.nfc.tag.alias));
	memset(cuvex.nfc.tag.cryptogram, 0x00, sizeof(cuvex.nfc.tag.cryptogram));
	memset(cuvex.nfc.tag.information, 0x00, sizeof(cuvex.nfc.tag.information));
	memset(cuvex.nfc.tag.new_uid, 0x00, sizeof(cuvex.nfc.tag.new_uid));
	memset(cuvex.nfc.tag.new_alias, 0x00, sizeof(cuvex.nfc.tag.new_alias));
	memset(cuvex.nfc.tag.new_cryptogram, 0x00, sizeof(cuvex.nfc.tag.new_cryptogram));
	memset(cuvex.nfc.tag.new_information, 0x00, sizeof(cuvex.nfc.tag.new_information));
	cuvex.nfc.tag.encripted	  = 0;
	cuvex.nfc.tag.multisigned = 0;
	cuvex.nfc.tag.packed	  = 0;
	cuvex.nfc.tag.cloned	  = 0;
}

/*
 *
 * FUNCIONES DE INTERACCIÓN CON LA MEMORIA FLASH PARA "EEPROM" SIMULADA
 *
 */

/******************************************************************************************************************************************************************************
 ***** Función 		: void readFlash(uint32_t address, char* data, size_t data_size)
 ***** Descripción 	: Lectura de la memoria flash
 ***** Parámetros 	: 	- address	--> dirección de memoria
 ***** 					- data		--> puntero a array
 ***** 					- data_size	--> tamaño del array
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void readFlash(uint32_t address, char* data, size_t data_size)
{
	uint32_t i=0;

	for(i = 0; i < data_size; i+=1){
		data[i] = *((char*)address+i);
	}
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void writeFlash(uint32_t address, char* data, size_t data_size)
 ***** Descripción 	: Escritura de la memoria flash
 ***** Parámetros 	: 	- address	--> dirección de memoria
 ***** 					- data		--> puntero a array
 ***** 					- data_size	--> tamaño del array
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void writeFlash(uint32_t address, char* data, size_t data_size)
{
	uint32_t *data_p = (uint32_t*)data;

	HAL_FLASH_Unlock();
	FLASH_WaitForLastOperation(100);

	for(int i=0; i<data_size; i+=16, data_p+=4, address+=16){
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_QUADWORD, address, (uint32_t)data_p) != HAL_OK){
			NVIC_SystemReset();
		}
	}

	FLASH_WaitForLastOperation(100);
	HAL_FLASH_Lock();
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void eraseFlash(uint32_t Banks, uint32_t Page, uint32_t NbPages)
 ***** Descripción 	: Borrado de la memoria flash
 ***** Parámetros 	:	- banks		--> banco de memoria
 ***** 					- page		--> página
 ***** 					- NbPages	--> nº de páginas
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void eraseFlash(uint32_t Banks, uint32_t Page, uint32_t NbPages)
{
	FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PageError;

	HAL_FLASH_Unlock();

	FLASH_WaitForLastOperation(100);

	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Banks       = Banks;
	EraseInitStruct.Page        = Page;
	EraseInitStruct.NbPages     = NbPages;

	if(HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK){
		NVIC_SystemReset();
	}

	FLASH_WaitForLastOperation(100);
	HAL_FLASH_Lock();
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void initEEPROM(void)
 ***** Descripción 	: Inicialización del sector de memoria donde se simula la "EEPROM" y guardado en flash
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void initEEPROM(void)
{
	/*** Reseteo del buffer ***/
	memset(cuvex.eeprom_buffer, 0x00, EEPROM_SIZE);

	/*** Header (16 Bytes) ***/
	memcpy(cuvex.eeprom_buffer, ">>>>>Header<<<<<", 16);

	/*** Campos del mapeado (10 x 16 Bytes) ***/
	memcpy(cuvex.eeprom_buffer + 16, "#B:100", 	 6);	//Brillo (1-100)
	memcpy(cuvex.eeprom_buffer + 32, "#M:LIGHT", 8);	//Modo (LIGHT, DARK)
	memcpy(cuvex.eeprom_buffer + 48, "#L:GB", 	 5);	//Lengua (GB, SP)
	memcpy(cuvex.eeprom_buffer + 64, "#E:0", 	 4);	//Errores al descifrar (0-2)

	/*** Footer de flash (11 Bytes) ***/
	memcpy(cuvex.eeprom_buffer + 96, ">>>>>Footer<<<<<", 16);

	/*** Guardado en memoria flash ***/
	eraseFlash(FLASH_BANK_2, EEPROM_PAGE, 1);
	writeFlash(EEPROM_ADDR, cuvex.eeprom_buffer, EEPROM_SIZE);
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void loadEEPROM(void)
 ***** Descripción 	: Carga en RAM de los valores almacenados en el sector que simula la "EEPROM"
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void loadEEPROM(void)
{
	char brightness_str[5] = {0};

	/*** Brillo (1-100) ***/
	memcpy(brightness_str, cuvex.eeprom_buffer + 16 + 3, 5);
	cuvex.info.brightness = atoi(brightness_str);
	TIM1->CCR1 = cuvex.info.brightness;

	/*** Modo (LIGHT, DARK) ***/
	if(memcmp(cuvex.eeprom_buffer + 32, "#M:DARK", 7) == 0){
		cuvex.info.mode = DARK;
	}
	else{
		cuvex.info.mode = LIGHT;
	}

	/*** Lengua (GB, SP) ***/
	if(memcmp(cuvex.eeprom_buffer + 48, "#L:SP", 5) == 0){
		cuvex.info.language = SPANISH;
	}
	else{
		cuvex.info.language = ENGLISH;
	}

	/*** Errores al descifrar (0-2) ***/
	if(memcmp(cuvex.eeprom_buffer + 64, "#E:1", 4) == 0){
		cuvex.info.errors = 1;
	}
	else if(memcmp(cuvex.eeprom_buffer + 64, "#E:2", 4) == 0){
		cuvex.info.errors = 2;
	}
	else{
		cuvex.info.errors = 0;
	}
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void editEEPROM(void)
 ***** Descripción 	: Edición del sector de memoria donde se simula la "EEPROM" y guardado en flash
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void editEEPROM(void)
{
	static uint8_t last_brightness = 0, last_mode = 0, last_language = 0, last_errors = 0;
	char brightness_str[5] = {0};

	if((last_brightness != cuvex.info.brightness) || (last_mode != cuvex.info.mode) || (last_language != cuvex.info.language) || (last_errors != cuvex.info.errors))
	{
		/*** Reseteo del buffer + "header" + "footer" ***/
		memset(cuvex.eeprom_buffer, 0x00, EEPROM_SIZE);
		memcpy(cuvex.eeprom_buffer, ">>>>>Header<<<<<", 16);
		memcpy(cuvex.eeprom_buffer + 96, ">>>>>Footer<<<<<", 16);

		/*** Brillo ***/
		if((cuvex.info.brightness >= 1) && (cuvex.info.brightness <= 100)){
			itoa(cuvex.info.brightness, brightness_str, 10);
			memcpy(cuvex.eeprom_buffer + 16, "#B:", 3);
			memcpy(cuvex.eeprom_buffer + 16 + 3, brightness_str, 5);
		}

		/*** Modo ***/
		if(cuvex.info.mode == DARK){
			memcpy(cuvex.eeprom_buffer + 32, "#M:DARK", 7);
		}
		else{
			memcpy(cuvex.eeprom_buffer + 32, "#M:LIGHT", 8);
		}

		/*** Lengua ***/
		if(cuvex.info.language == SPANISH){
			memcpy(cuvex.eeprom_buffer + 48, "#L:SP", 5);
		}
		else{
			memcpy(cuvex.eeprom_buffer + 48, "#L:GB", 5);
		}

		/*** Errores al descifrar ***/
		if(cuvex.info.errors == 1){
			memcpy(cuvex.eeprom_buffer + 64, "#E:1", 4);
		}
		else if(cuvex.info.errors == 2){
			memcpy(cuvex.eeprom_buffer + 64, "#E:2", 4);
		}
		else{
			memcpy(cuvex.eeprom_buffer + 64, "#E:0", 4);
		}

		/*** Guardado en memoria flash ***/
		eraseFlash(FLASH_BANK_2, EEPROM_PAGE, 1);
		writeFlash(EEPROM_ADDR, cuvex.eeprom_buffer, EEPROM_SIZE);

		/*** Guardado en RAM de valores pasados ***/
		last_brightness = cuvex.info.brightness;
		last_mode 		= cuvex.info.mode;
		last_language 	= cuvex.info.language;
		last_errors 	= cuvex.info.errors;
	}
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void eraseSignature(void)
 ***** Descripción 	: Borrado completo del sector de memoria que almacena la firma y reseteo del mcu
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void eraseSignature(void)
{
	eraseFlash(FLASH_BANK_2, SIGNATURE_PAGE, 1);
	NVIC_SystemReset();
}

/*
 *
 * FUNCIONES AUXILIARES
 *
 */

/******************************************************************************************************************************************************************************
 ***** Función 		: void getCuvexVersions(void)
 ***** Descripción 	: Obtención de las versiones de firmware/hardware del dispositivo
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void getCuvexVersions(void)
{
	/*** Obtención de la versión de firmware ***/
	memset(cuvex.info.fw_version, 0x00, sizeof(cuvex.info.fw_version));
	memcpy(cuvex.info.fw_version, FIRMWARE_VERSION, strlen(FIRMWARE_VERSION));

	/*** Obtención de la versión de hardware ***/
	memset(cuvex.info.hw_version, 0x00, sizeof(cuvex.info.hw_version));

	if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_RESET)){
		memcpy(cuvex.info.hw_version, "1", 1);
	}
	else if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_SET)){
		memcpy(cuvex.info.hw_version, "2", 1);
	}
	else if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_RESET)){
		memcpy(cuvex.info.hw_version, "3", 1);
	}
	else if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_SET)){
		memcpy(cuvex.info.hw_version, "4", 1);
	}
	else if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_RESET)){
		memcpy(cuvex.info.hw_version, "5", 1);
	}
	else if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_SET)){
		memcpy(cuvex.info.hw_version, "6", 1);
	}
	else if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_RESET)){
		memcpy(cuvex.info.hw_version, "7", 1);
	}
	else if((HAL_GPIO_ReadPin(HW_VER_3_GPIO_Port, HW_VER_3_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_2_GPIO_Port, HW_VER_2_Pin) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(HW_VER_1_GPIO_Port, HW_VER_1_Pin) == GPIO_PIN_SET)){
		memcpy(cuvex.info.hw_version, "8", 1);
	}
}


