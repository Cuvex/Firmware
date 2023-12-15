/*
 * nfcTask.c
 */

#include "nfcTask.h"

/******************************************************************************************************************************************************************************
 ***** Función 		: void nfc_Task(void const * argument)
 ***** Descripción 	: Función principal de la tarea "nfcTask"
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void nfc_Task(void const * argument)
{
	/*** Bucle principal ***/
	for(;;)
	{
		if(cuvex.nfc.flag_enabled == true)	//NFC -> habilitado
		{
			if(cuvex.nfc.flag_initialized == true)
			{
				nfcCycle();
			}
			else
			{
				disableNFC();
				osDelay(10);
				enableNFC();
				osDelay(10);

				if(nfcInitialize() == true){
					osDelay(1000);
					cuvex.nfc.flag_initialized = true;
				}
			}
		}
		else	//NFC -> des-habilitado
		{
			disableNFC();
		}

		osDelay(10);
	}
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void enableNFC(void)
 ***** Descripción 	: Habilitación del ldo que alimenta el lector/escritor NFC
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void enableNFC(void)
{
	HAL_GPIO_WritePin(NFC_EN_GPIO_Port, NFC_EN_Pin, GPIO_PIN_SET);
	HAL_UART_Init(&huart3);
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void disableNFC(void)
 ***** Descripción 	: Des-habilitación del ldo que alimenta el lector/escritor NFC
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void disableNFC(void)
{
	HAL_GPIO_WritePin(NFC_EN_GPIO_Port, NFC_EN_Pin, GPIO_PIN_RESET);
	HAL_UART_DeInit(&huart3);
}

/******************************************************************************************************************************************************************************
 ***** Función 		: bool nfcInitialize(void)
 ***** Descripción 	: Inicialización del lector/escritor NFC
 ***** Parámetros 	: N/A
 ***** Respuesta 	: 	- true 	--> OK
 ***** 					- false --> ERROR
 ******************************************************************************************************************************************************************************/
bool nfcInitialize(void)
{
	static uint8_t NFCID3[] = {0x01, 0xFE, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
	static uint8_t GB[] = {0x46, 0x66, 0x6d, 0x01, 0x01, 0x11, 0x02, 0x02, 0x07, 0x80, 0x03, 0x02, 0x00, 0x03, 0x04, 0x01, 0x32, 0x07, 0x01, 0x03};

	if(rfalNfcInitialize() == ERR_NONE)
	{
		memcpy(&discParam.nfcid3, NFCID3, sizeof(NFCID3));
		memcpy(&discParam.GB, GB, sizeof(GB) );

		discParam.GBLen 				= sizeof(GB);
		discParam.compMode      		= RFAL_COMPLIANCE_MODE_NFC;
		discParam.devLimit      		= 1U;
		discParam.nfcfBR        		= RFAL_BR_212;
		discParam.ap2pBR        		= RFAL_BR_424;
		discParam.notifyCb             	= NULL;
		discParam.totalDuration        	= 250U;
		discParam.wakeupEnabled        	= false;
		discParam.wakeupConfigDefault  	= true;
		discParam.techs2Find           	= RFAL_NFC_POLL_TECH_A;

		state = NFC_START_DISCOVERY;
		return true;
	}

	return false;
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void nfcCycle(void)
 ***** Descripción 	: Máquina de estados ciclica que se ejecuta cuando el lector/escritor NFC está habilitado y ha sido inicializado
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void nfcCycle(void)
{
	static rfalNfcDevice *nfcDevice;
	rfalNfcaSensRes       sensRes;

	rfalNfcWorker();	//Ejecución periodica del "worker RFAL"

	switch(state)
	{
	case NFC_NOINIT:
	default:
		break;

	case NFC_START_DISCOVERY:

		rfalNfcDeactivate(false);
		rfalNfcDiscover(&discParam);
		state = NFC_DISCOVERY;
		break;

	case NFC_DISCOVERY:

		if(rfalNfcIsDevActivated(rfalNfcGetState()))
		{
			rfalNfcGetActiveDevice(&nfcDevice);
			platformDelay(50);

			if(nfcDevice->type == RFAL_NFC_LISTEN_TYPE_NFCA)
			{
#ifdef DEBUG_NFC_PRINTF
				printf("%x...%x...%x...%x...\r\n", nfcDevice->dev.nfca.type, nfcDevice->dev.nfca.sensRes.anticollisionInfo, nfcDevice->dev.nfca.sensRes.platformInfo, nfcDevice->dev.nfca.selRes.sak);
#endif

				if((nfcDevice->dev.nfca.type == RFAL_NFCA_T2T) && (nfcDevice->dev.nfca.sensRes.anticollisionInfo == 0x44) && (nfcDevice->dev.nfca.sensRes.platformInfo == 0x00) && (nfcDevice->dev.nfca.selRes.sak == 0x00))
				{
#ifdef DEBUG_NFC_PRINTF
					printf("NFC -> Tag detectada...\r\n");
#endif

					if(cuvex.nfc.tag.action != NFC_TAG_NONE){
						nfcActionNdef(nfcDevice);
					}

					rfalNfcaPollerSleep();
				}

				rfalNfcaPollerInitialize();

				while(rfalNfcaPollerCheckPresence(RFAL_14443A_SHORTFRAME_CMD_WUPA, &sensRes) == ERR_NONE)	//Mientras se sigue detectando presencia
				{
					rfalNfcaPollerSleep();
					platformDelay(130);
				}
			}

			rfalNfcDeactivate(false);
			platformDelay(500);
			state = NFC_START_DISCOVERY;
		}
		break;
	}
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void ndefRecord_GetInfo(const ndefRecord* record)
 ***** Descripción 	: Obtención de la información grabada en los records del tag NFC
 ***** Parámetros 	:	- record --> Número de record
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void ndefRecord_GetInfo(const ndefRecord* record)
{
	/*** Declaración de variables ***/
	static uint32_t index = 0;
	ndefType type;
	uint8_t utfEncoding;
	ndefConstBuffer8 bufLanguageCode;
	ndefConstBuffer  bufSentence;

	/*** Índice del record actual ***/
	if(ndefHeaderIsSetMB(record)){
		index = 1;
	}
	else{
		index++;
	}

	/*** Debug: nº de record y bits de información ***/
#ifdef DEBUG_NFC_PRINTF
	printf("\r\n--- Record #%d ---\r\n", index);
	printf("(MB:%d,ME:%d,CF:%d,SR:%d,IL:%d,TNF:%d)\r\n", ndefHeaderMB(record), ndefHeaderME(record), ndefHeaderCF(record), ndefHeaderSR(record), ndefHeaderIL(record), ndefHeaderTNF(record));
#endif

	/*** Obtención del contenido en el record y asignación a variable ***/
	switch(index)
	{
	case 1:	//Record 1 (alias)
		ndefRecordToType(record, &type);
		ndefGetRtdText(&type, &utfEncoding, &bufLanguageCode, &bufSentence);

		memset(cuvex.nfc.tag.alias, 0x00, sizeof(cuvex.nfc.tag.alias));
		memcpy(cuvex.nfc.tag.alias, bufSentence.buffer, bufSentence.length);

#ifdef DEBUG_NFC_PRINTF
		printf("\r\nAlias:\r\n");
		for(int i=0; i<sizeof(cuvex.nfc.tag.alias); i++)
		{
			printf("%c", cuvex.nfc.tag.alias[i]);
		}
		printf("\r\n");
#endif
		break;

	case 2:	//Record 2 (criptograma)
		ndefRecordToType(record, &type);
		ndefGetRtdText(&type, &utfEncoding, &bufLanguageCode, &bufSentence);

		memset(cuvex.nfc.tag.cryptogram, 0x00, sizeof(cuvex.nfc.tag.cryptogram));
		memcpy(cuvex.nfc.tag.cryptogram, bufSentence.buffer, bufSentence.length);

#ifdef DEBUG_NFC_PRINTF
		printf("\r\nCriptograma:\r\n");
		for(int i=0; i<sizeof(cuvex.nfc.tag.cryptogram); i++)
		{
			printf("%c", cuvex.nfc.tag.cryptogram[i]);
		}
		printf("\r\n");
#endif
		break;

	case 3:	//Record 3 (información --> Con formato "ENC,vXX.XX.XX(Y),M-X,P-X,C-X")
		ndefRecordToType(record, &type);
		ndefGetRtdText(&type, &utfEncoding, &bufLanguageCode, &bufSentence);

		memset(cuvex.nfc.tag.information, 0x00, sizeof(cuvex.nfc.tag.information));
		memcpy(cuvex.nfc.tag.information, bufSentence.buffer, bufSentence.length);

		/*** Obtención información de tarjeta encriptada ***/
		char *ptr;
		ptr = strstr((char *) cuvex.nfc.tag.information, "ENC,");

		if(ptr != 0x00)
		{
			cuvex.nfc.tag.encripted = true;

			/*** Obtención información de tarjeta con multifirma ***/
			ptr = strstr((char *) cuvex.nfc.tag.information, ",M-");

			if(ptr != 0x00)
			{
				if(ptr[3] == '1'){
					cuvex.nfc.tag.multisigned = 1;
				}
				else if(ptr[3] == '2'){
					cuvex.nfc.tag.multisigned = 2;
				}
				else if(ptr[3] == '3'){
					cuvex.nfc.tag.multisigned = 3;
				}
				else if(ptr[3] == '4'){
					cuvex.nfc.tag.multisigned = 4;
				}
				else if(ptr[3] == '5'){
					cuvex.nfc.tag.multisigned = 5;
				}
				else if(ptr[3] == '6'){
					cuvex.nfc.tag.multisigned = 6;
				}
				else{
					cuvex.nfc.tag.multisigned = 0;
				}
			}

			/*** Obtención información de tarjeta comprimida ***/
			ptr = strstr((char *) cuvex.nfc.tag.information, ",P-");

			if(ptr != 0x00)
			{
				if(ptr[3] == '1'){
					cuvex.nfc.tag.packed = 1;
				}
				else{
					cuvex.nfc.tag.packed = 0;
				}
			}

			/*** Obtención información de tarjeta clonada ***/
			ptr = strstr((char *) cuvex.nfc.tag.information, ",C-");

			if(ptr != 0x00)
			{
				if(ptr[3] == '1'){
					cuvex.nfc.tag.cloned = 1;
				}
				else{
					cuvex.nfc.tag.cloned = 0;
				}
			}
		}
		else
		{
			cuvex.nfc.tag.encripted = false;
		}

#ifdef DEBUG_NFC_PRINTF
		printf("\r\nInformacion:\r\n");
		for(int i=0; i<sizeof(cuvex.nfc.tag.information); i++)
		{
			printf("%c", cuvex.nfc.tag.information[i]);
		}
		printf("\r\n\r\n");
#endif
		break;

	default:
		break;
	}
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void ndefMessage_GetInfo(const ndefMessage* message)
 ***** Descripción 	: Obtención de la información grabada en el tag NFC
 ***** Parámetros 	:	- message --> Mensaje completo
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void ndefMessage_GetInfo(const ndefMessage* message)
{
	ndefRecord* record;
	record = ndefMessageGetFirstRecord(message);

#ifdef DEBUG_NFC_PRINTF
	printf("----------------------------------------------------------------------\r\n");
	printf("----------------------------------------------------------------------\r\n");
#endif

	while(record != NULL)
	{
		ndefRecord_GetInfo(record);
		record = ndefMessageGetNextRecord(record);
	}

#ifdef DEBUG_NFC_PRINTF
	printf("----------------------------------------------------------------------\r\n");
	printf("----------------------------------------------------------------------\r\n");
#endif
}

/******************************************************************************************************************************************************************************
 ***** Función 		: void nfcActionNdef(rfalNfcDevice *pNfcDevice)
 ***** Descripción 	: Acción a realizar sobre tag NFC
 ***** Parámetros 	:	- pNfcDevice --> Puntero a estructura de datos con información del tag NFC
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void nfcActionNdef(rfalNfcDevice *pNfcDevice)
{
	static ndefContext 	ndefCtx;
	ReturnCode 			err;
	ndefInfo 			info;
	uint8_t 			raw_message_buf[1000] = {0};
	ndefBuffer       	buf_raw_message;
	uint32_t         	raw_message_len;
	ndefConstBuffer  	buf_const_raw_message;
	ndefConstBuffer8 	buf_lan_code_1;
	ndefConstBuffer8 	buf_lan_code_2;
	ndefConstBuffer8 	buf_lan_code_3;
	ndefConstBuffer 	buf_record_1;
	ndefConstBuffer 	buf_record_2;
	ndefConstBuffer 	buf_record_3;
	ndefRecord      	record_1;
	ndefRecord      	record_2;
	ndefRecord      	record_3;
	ndefType         	text_1;
	ndefType         	text_2;
	ndefType         	text_3;
	ndefMessage      	message;

	/*
	 * Inicialización del contexto y proceso de detección
	 */
	if((ndefPollerContextInitialization(&ndefCtx, pNfcDevice) != ERR_NONE) || (ndefPollerNdefDetect(&ndefCtx, &info) != ERR_NONE))
	{
#ifdef DEBUG_NFC_PRINTF
		printf("[NDEF] -> Error en la deteccion...\r\n");
#endif
		return;
	}
	else
	{
#ifdef DEBUG_NFC_PRINTF
		printf("[NDEF] -> Detectado correctamente...\r\n");
#endif
	}

	/*
	 * Máquina de estados en base a la acción a realizar por el lector/escritor NFC
	 */
	switch(cuvex.nfc.tag.action)
	{
	case NFC_TAG_NONE:
	default:
		break;

		/*******************************************************************************************************************************************/
	case NFC_TAG_READ:

		/*** Obtención del UID (primera lectura) ***/
		memcpy(cuvex.nfc.tag.uid, hex2Str(pNfcDevice->nfcid, pNfcDevice->nfcidLen), 14);

		/*** Lectura del tag (si tiene información) ***/
		if(info.state != NDEF_STATE_INITIALIZED)
		{
			/*** Obtención del mensaje en formato Raw ***/
			if(ndefPollerReadRawMessage(&ndefCtx, raw_message_buf, sizeof(raw_message_buf), &raw_message_len) != ERR_NONE){
				return;
			}

			/*** Decodificación del mensaje en formato Raw ***/
			buf_const_raw_message.buffer = raw_message_buf;
			buf_const_raw_message.length = raw_message_len;

			if(ndefMessageDecode(&buf_const_raw_message, &message) != ERR_NONE){
				return;
			}

			/*** Obtención de la información guardada en el tag NFC ***/
			ndefMessage_GetInfo(&message);

#ifdef DEBUG_NFC_PRINTF
			printf("[NDEF] -> Lectura correcta...\r\n");
#endif
		}
		else{
			cuvex.nfc.tag.encripted	= false;
		}

		/*** Se ha leído un tag correctamente (actualización flag) ***/
		cuvex.nfc.tag.flag_readed = true;
		break;

		/*******************************************************************************************************************************************/
	case NFC_TAG_READ_WRITE_FLOW_1:

		/*** Obtención del UID (nueva lectura) ***/
		memcpy(cuvex.nfc.tag.new_uid, hex2Str(pNfcDevice->nfcid, pNfcDevice->nfcidLen), 14);

		/*** LECTURA + ESCRITURA --> si tag1 igual a tag2 ***/
		if(strstr((char *) cuvex.nfc.tag.uid, (char *) cuvex.nfc.tag.new_uid) != 0x00)
		{
			/*** LECTURA --> si tag2 no formateada ***/
			if(info.state != NDEF_STATE_INITIALIZED)
			{
				/*** Obtención del mensaje en formato Raw ***/
				if(ndefPollerReadRawMessage(&ndefCtx, raw_message_buf, sizeof(raw_message_buf), &raw_message_len) != ERR_NONE){
					return;
				}

				/*** Decodificación del mensaje en formato Raw ***/
				buf_const_raw_message.buffer = raw_message_buf;
				buf_const_raw_message.length = raw_message_len;

				if(ndefMessageDecode(&buf_const_raw_message, &message) != ERR_NONE){
					return;
				}

				/*** Obtención de la información guardada en el tag NFC ***/
				ndefMessage_GetInfo(&message);

#ifdef DEBUG_NFC_PRINTF
				printf("[NDEF-flow1] -> Lectura correcta...\r\n");
#endif
			}
			else{
				cuvex.nfc.tag.encripted	= false;
			}

			/*** ESCRITURA --> si tag_2 no tiene criptograma ***/
			if(cuvex.nfc.tag.encripted == false)
			{
				/*** Buffers --> Inicialización de buffers leídos y asignación de nuevos valores ***/
				memset(cuvex.nfc.tag.alias, 0x00, sizeof(cuvex.nfc.tag.alias));
				memset(cuvex.nfc.tag.cryptogram, 0x00, sizeof(cuvex.nfc.tag.cryptogram));
				memset(cuvex.nfc.tag.information, 0x00, sizeof(cuvex.nfc.tag.information));
				memcpy(cuvex.nfc.tag.alias, cuvex.nfc.tag.new_alias, sizeof(cuvex.nfc.tag.alias));

				/*** Texto/record 1 --> Inicialización y codificación ***/
				buf_lan_code_1.buffer = (uint8_t *) "A:";
				buf_lan_code_1.length = 2;
				buf_record_1.buffer   = cuvex.nfc.tag.alias;
				buf_record_1.length   = sizeof(cuvex.nfc.tag.alias);

				err |= ndefRtdText(&text_1, TEXT_ENCODING_UTF8, &buf_lan_code_1, &buf_record_1);
				err |= ndefRtdTextToRecord(&text_1, &record_1);

				/*** Texto/record 2 --> Inicialización y codificación ***/
				buf_lan_code_2.buffer = (uint8_t *) "C:";
				buf_lan_code_2.length = 2;
				buf_record_2.buffer   = cuvex.nfc.tag.cryptogram;
				buf_record_2.length   = sizeof(cuvex.nfc.tag.cryptogram);

				err |= ndefRtdText(&text_2, TEXT_ENCODING_UTF8, &buf_lan_code_2, &buf_record_2);
				err |= ndefRtdTextToRecord(&text_2, &record_2);

				/*** Texto/record 3 --> Inicialización y codificación ***/
				buf_lan_code_3.buffer = (uint8_t *) "I:";
				buf_lan_code_3.length = 2;
				buf_record_3.buffer   = cuvex.nfc.tag.information;
				buf_record_3.length   = sizeof(cuvex.nfc.tag.information);

				err |= ndefRtdText(&text_3, TEXT_ENCODING_UTF8, &buf_lan_code_3, &buf_record_3);
				err |= ndefRtdTextToRecord(&text_3, &record_3);

				/*** Mensaje --> Inicialización y anexo de records ***/
				err  = ndefMessageInit(&message);
				err |= ndefMessageAppend(&message, &record_1);
				err |= ndefMessageAppend(&message, &record_2);
				err |= ndefMessageAppend(&message, &record_3);

				/*** Buffer Raw --> Codificación y escritura del mensaje ***/
				buf_raw_message.buffer = raw_message_buf;
				buf_raw_message.length = sizeof(raw_message_buf);

				err |= ndefMessageEncode(&message, &buf_raw_message);

				if(err != ERR_NONE){
					return;
				}

				err = ndefPollerWriteRawMessage(&ndefCtx, buf_raw_message.buffer, buf_raw_message.length);

				if(err != ERR_NONE){
					return;
				}

#ifdef DEBUG_NFC_PRINTF
				printf("[NDEF-flow1] -> Escritura correcta...\r\n");
#endif

				/*** Se ha escrito un tag correctamente (actualización flag) ***/
				cuvex.nfc.tag.flag_readed_writed_flow_1 = true;
			}
		}
		break;

		/*******************************************************************************************************************************************/
	case NFC_TAG_READ_WRITE_FLOW_2:

		/*** Obtención del UID (primera lectura) ***/
		memcpy(cuvex.nfc.tag.uid, hex2Str(pNfcDevice->nfcid, pNfcDevice->nfcidLen), 14);

		/*** LECTURA --> si tag no formateada ***/
		if(info.state != NDEF_STATE_INITIALIZED)
		{
			/*** Obtención del mensaje en formato Raw ***/
			if(ndefPollerReadRawMessage(&ndefCtx, raw_message_buf, sizeof(raw_message_buf), &raw_message_len) != ERR_NONE){
				return;
			}

			/*** Decodificación del mensaje en formato Raw ***/
			buf_const_raw_message.buffer = raw_message_buf;
			buf_const_raw_message.length = raw_message_len;

			if(ndefMessageDecode(&buf_const_raw_message, &message) != ERR_NONE){
				return;
			}

			/*** Obtención de la información guardada en el tag NFC ***/
			ndefMessage_GetInfo(&message);

#ifdef DEBUG_NFC_PRINTF
			printf("[NDEF-flow2] -> Lectura correcta...\r\n");
#endif
		}
		else{
			memset(cuvex.nfc.tag.alias, 0x00, sizeof(cuvex.nfc.tag.alias));
			cuvex.nfc.tag.encripted	= false;
		}

		/*** ESCRITURA --> si tag no tiene criptograma ***/
		if(cuvex.nfc.tag.encripted == false)
		{
			if((cuvex.nfc.tag.alias[0] != 0x00) || (cuvex.nfc.tag.new_alias[0] != 0x00))
			{
				/*** Buffers --> Inicialización de buffers leídos y asignación de nuevos valores ***/
				memset(cuvex.nfc.tag.cryptogram, 0x00, sizeof(cuvex.nfc.tag.cryptogram));
				memset(cuvex.nfc.tag.information, 0x00, sizeof(cuvex.nfc.tag.information));
				memcpy(cuvex.nfc.tag.cryptogram, cuvex.nfc.tag.new_cryptogram, sizeof(cuvex.nfc.tag.cryptogram));
				memcpy(cuvex.nfc.tag.information, cuvex.nfc.tag.new_information, sizeof(cuvex.nfc.tag.information));

				if((cuvex.nfc.tag.alias[0] == 0x00) && (cuvex.nfc.tag.new_alias[0] != 0x00)){
					memset(cuvex.nfc.tag.alias, 0x00, sizeof(cuvex.nfc.tag.alias));
					memcpy(cuvex.nfc.tag.alias, cuvex.nfc.tag.new_alias, sizeof(cuvex.nfc.tag.alias));
				}

				/*** Texto/record 1 --> Inicialización y codificación ***/
				buf_lan_code_1.buffer = (uint8_t *) "A:";
				buf_lan_code_1.length = 2;
				buf_record_1.buffer   = cuvex.nfc.tag.alias;
				buf_record_1.length   = sizeof(cuvex.nfc.tag.alias);

				err |= ndefRtdText(&text_1, TEXT_ENCODING_UTF8, &buf_lan_code_1, &buf_record_1);
				err |= ndefRtdTextToRecord(&text_1, &record_1);

				/*** Texto/record 2 --> Inicialización y codificación ***/
				buf_lan_code_2.buffer = (uint8_t *) "C:";
				buf_lan_code_2.length = 2;
				buf_record_2.buffer   = cuvex.nfc.tag.cryptogram;
				buf_record_2.length   = sizeof(cuvex.nfc.tag.cryptogram);

				err |= ndefRtdText(&text_2, TEXT_ENCODING_UTF8, &buf_lan_code_2, &buf_record_2);
				err |= ndefRtdTextToRecord(&text_2, &record_2);

				/*** Texto/record 3 --> Inicialización y codificación ***/
				buf_lan_code_3.buffer = (uint8_t *) "I:";
				buf_lan_code_3.length = 2;
				buf_record_3.buffer   = cuvex.nfc.tag.information;
				buf_record_3.length   = sizeof(cuvex.nfc.tag.information);

				err |= ndefRtdText(&text_3, TEXT_ENCODING_UTF8, &buf_lan_code_3, &buf_record_3);
				err |= ndefRtdTextToRecord(&text_3, &record_3);

				/*** Mensaje --> Inicialización y anexo de records ***/
				err  = ndefMessageInit(&message);
				err |= ndefMessageAppend(&message, &record_1);
				err |= ndefMessageAppend(&message, &record_2);
				err |= ndefMessageAppend(&message, &record_3);

				/*** Buffer Raw --> Codificación y escritura del mensaje ***/
				buf_raw_message.buffer = raw_message_buf;
				buf_raw_message.length = sizeof(raw_message_buf);

				err |= ndefMessageEncode(&message, &buf_raw_message);

				if(err != ERR_NONE){
					return;
				}

				err = ndefPollerWriteRawMessage(&ndefCtx, buf_raw_message.buffer, buf_raw_message.length);

				if(err != ERR_NONE){
					return;
				}

#ifdef DEBUG_NFC_PRINTF
				printf("[NDEF-flow2] -> Escritura correcta...\r\n");
#endif
			}
		}

		/*** Se ha tratado de escribir un tag (actualización flag) ***/
		cuvex.nfc.tag.flag_readed_writed_flow_2 = true;

		break;

		/*******************************************************************************************************************************************/
	case NFC_TAG_READ_WRITE_FLOW_4:

		/*** Obtención del UID (nueva lectura) ***/
		memcpy(cuvex.nfc.tag.new_uid, hex2Str(pNfcDevice->nfcid, pNfcDevice->nfcidLen), 14);

		/*** Se guardan los valores del tag1 (antes de leer tag_2) ***/
		memcpy(cuvex.nfc.tag.new_alias, cuvex.nfc.tag.alias, sizeof(cuvex.nfc.tag.new_alias));
		memcpy(cuvex.nfc.tag.new_cryptogram, cuvex.nfc.tag.cryptogram, sizeof(cuvex.nfc.tag.new_cryptogram));
		memcpy(cuvex.nfc.tag.new_information, cuvex.nfc.tag.information, sizeof(cuvex.nfc.tag.new_information));

		/*** LECTURA + ESCRITURA --> si tag1 igual a tag2 ***/
		if(strstr((char *) cuvex.nfc.tag.uid, (char *) cuvex.nfc.tag.new_uid) == 0x00)
		{
			/*** LECTURA --> si tag2 no formateada ***/
			if(info.state != NDEF_STATE_INITIALIZED)
			{
				/*** Obtención del mensaje en formato Raw ***/
				if(ndefPollerReadRawMessage(&ndefCtx, raw_message_buf, sizeof(raw_message_buf), &raw_message_len) != ERR_NONE){
					return;
				}

				/*** Decodificación del mensaje en formato Raw ***/
				buf_const_raw_message.buffer = raw_message_buf;
				buf_const_raw_message.length = raw_message_len;

				if(ndefMessageDecode(&buf_const_raw_message, &message) != ERR_NONE){
					return;
				}

				/*** Obtención de la información guardada en el tag NFC ***/
				ndefMessage_GetInfo(&message);

#ifdef DEBUG_NFC_PRINTF
				printf("[NDEF-flow4] -> Lectura correcta...\r\n");
#endif
			}
			else{
				cuvex.nfc.tag.encripted	= false;
			}

			/*** ESCRITURA --> si tag_2 no tiene criptograma ***/
			if(cuvex.nfc.tag.encripted == false)
			{
				/*** Buffers --> Inicialización de buffers leídos y asignación de nuevos valores ***/
				memset(cuvex.nfc.tag.alias, 0x00, sizeof(cuvex.nfc.tag.alias));
				memset(cuvex.nfc.tag.cryptogram, 0x00, sizeof(cuvex.nfc.tag.cryptogram));
				memset(cuvex.nfc.tag.information, 0x00, sizeof(cuvex.nfc.tag.information));
				memcpy(cuvex.nfc.tag.alias, cuvex.nfc.tag.new_alias, sizeof(cuvex.nfc.tag.alias));
				memcpy(cuvex.nfc.tag.cryptogram, cuvex.nfc.tag.new_cryptogram, sizeof(cuvex.nfc.tag.cryptogram));
				memcpy(cuvex.nfc.tag.information, cuvex.nfc.tag.new_information, sizeof(cuvex.nfc.tag.information));
				cuvex.nfc.tag.information[strlen((char *) cuvex.nfc.tag.information) - 1] = '1';

				/*** Texto/record 1 --> Inicialización y codificación ***/
				buf_lan_code_1.buffer = (uint8_t *) "A:";
				buf_lan_code_1.length = 2;
				buf_record_1.buffer   = cuvex.nfc.tag.alias;
				buf_record_1.length   = sizeof(cuvex.nfc.tag.alias);

				err |= ndefRtdText(&text_1, TEXT_ENCODING_UTF8, &buf_lan_code_1, &buf_record_1);
				err |= ndefRtdTextToRecord(&text_1, &record_1);

				/*** Texto/record 2 --> Inicialización y codificación ***/
				buf_lan_code_2.buffer = (uint8_t *) "C:";
				buf_lan_code_2.length = 2;
				buf_record_2.buffer   = cuvex.nfc.tag.cryptogram;
				buf_record_2.length   = sizeof(cuvex.nfc.tag.cryptogram);

				err |= ndefRtdText(&text_2, TEXT_ENCODING_UTF8, &buf_lan_code_2, &buf_record_2);
				err |= ndefRtdTextToRecord(&text_2, &record_2);

				/*** Texto/record 3 --> Inicialización y codificación ***/
				buf_lan_code_3.buffer = (uint8_t *) "I:";
				buf_lan_code_3.length = 2;
				buf_record_3.buffer   = cuvex.nfc.tag.information;
				buf_record_3.length   = sizeof(cuvex.nfc.tag.information);

				err |= ndefRtdText(&text_3, TEXT_ENCODING_UTF8, &buf_lan_code_3, &buf_record_3);
				err |= ndefRtdTextToRecord(&text_3, &record_3);

				/*** Mensaje --> Inicialización y anexo de records ***/
				err  = ndefMessageInit(&message);
				err |= ndefMessageAppend(&message, &record_1);
				err |= ndefMessageAppend(&message, &record_2);
				err |= ndefMessageAppend(&message, &record_3);

				/*** Buffer Raw --> Codificación y escritura del mensaje ***/
				buf_raw_message.buffer = raw_message_buf;
				buf_raw_message.length = sizeof(raw_message_buf);

				err |= ndefMessageEncode(&message, &buf_raw_message);

				if(err != ERR_NONE){
					return;
				}

				err = ndefPollerWriteRawMessage(&ndefCtx, buf_raw_message.buffer, buf_raw_message.length);

				if(err != ERR_NONE){
					return;
				}

#ifdef DEBUG_NFC_PRINTF
				printf("[NDEF-flow4] -> Escritura correcta...\r\n");
#endif
			}

			/*** Se ha tratado de escribir un tag (actualización flag) ***/
			cuvex.nfc.tag.flag_readed_writed_flow_4 = true;
		}
		break;
	}
}

/*
 *
 * FUNCIONES AUXILIARES
 *
 */

/******************************************************************************************************************************************************************************
 ***** Función 		: void setLedColour(uint8_t colour)
 ***** Descripción 	: Selección del color a visualizar de los dos led accesibles desde el mcu (rojo, verde)
 ***** Parámetros 	:	- colour --> color a visualizar
 ***** Respuesta 	: N/A
 ******************************************************************************************************************************************************************************/
void setLedColour(uint8_t colour)
{
	switch(colour)
	{
	case NONE:
	default:
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
		break;

	case RED:
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
		break;

	case GREEN:
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
		break;

	case YELLOW:
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
		break;
	}
}








