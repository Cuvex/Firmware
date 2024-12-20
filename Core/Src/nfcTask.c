/**
 ******************************************************************************
 * @file           : nfcTask.c
 * @brief          : NFC task (freeRTOS)
 ******************************************************************************
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

#include "nfcTask.h"
#include "ndef_buffer.h"
#include "stdbool.h"
#include "st_errno.h"

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void nfc_Task(void const * argument)
{
	for(;;)
	{
		if(cuvex.nfc.flag_enabled == true){
			if(cuvex.nfc.flag_initialized == true){
				nfcCycle();
			}
			else{
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
		else{
			disableNFC();
		}

		osDelay(10);
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void enableNFC(void)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);	//Green --> OFF
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);		//Red --> OFF
	HAL_GPIO_WritePin(NFC_EN_GPIO_Port, NFC_EN_Pin, GPIO_PIN_SET);
	HAL_UART_Init(&huart3);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void disableNFC(void)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);	//Green --> OFF
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);		//Red --> OFF
	HAL_GPIO_WritePin(NFC_EN_GPIO_Port, NFC_EN_Pin, GPIO_PIN_RESET);
	HAL_UART_DeInit(&huart3);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
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

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void nfcCycle(void)
{
	static rfalNfcDevice *nfcDevice;
	rfalNfcaSensRes       sensRes;

	rfalNfcWorker();

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
		if((rfalNfcIsDevActivated(rfalNfcGetState())) && (rfalNfcGetActiveDevice(&nfcDevice) == ERR_NONE))
		{
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);	//Green --> ON
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);		//Red --> OFF
			platformDelay(50);

			if((nfcDevice->type == RFAL_NFC_LISTEN_TYPE_NFCA) && ((nfcDevice->dev.nfca.type == RFAL_NFCA_T2T) || (nfcDevice->dev.nfca.type == RFAL_NFCA_T4T)))
			{
				if(nfcActionNdef(nfcDevice) == ERROR){
					HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);	//Green --> OFF
					HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);		//Red --> OFF
				}

				if(nfcDevice->dev.nfca.type == RFAL_NFCA_T4T){
					rfalIsoDepDeselect();
				}
				else{
					rfalNfcaPollerSleep();
				}

				rfalNfcaPollerInitialize();

				while((rfalNfcaPollerCheckPresence(RFAL_14443A_SHORTFRAME_CMD_WUPA, &sensRes) == ERR_NONE) && (cuvex.nfc.flag_enabled == true) && (cuvex.nfc.flag_initialized == true)){
					rfalNfcaPollerSleep();
					platformDelay(130);
				}
			}

			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);	//Green --> OFF
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);		//Red --> OFF
			rfalNfcDeactivate(false);
			platformDelay(500);
			state = NFC_START_DISCOVERY;
		}
		break;
	}
}


/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int nfcActionNdef(rfalNfcDevice *pNfcDevice)
{
	static ndefContext 	ndefCtx;
	ndefInfo info;

	/*
	 * Initialization of context and detection process and check if tag version is allowed
	 */
	if(cuvex.nfc.tag.action != NFC_TAG_NONE)
	{
		if((ndefPollerContextInitialization(&ndefCtx, pNfcDevice) != ERR_NONE) || (ndefPollerNdefDetect(&ndefCtx, &info) != ERR_NONE)){
			return ERROR;
		}

		switch(pNfcDevice->dev.nfca.type)
		{
		case RFAL_NFCA_T2T:
		default:
			if(getVersionT2T_NTAG216(pNfcDevice) == ERROR){
				return ERROR;
			}
			else{
				cuvex.nfc.tag.type = NFC_TAG_TYPE_T2T_NTAG216;
			}
			break;

		case RFAL_NFCA_T4T:
			if(getVersionT4T_8K(&ndefCtx, &info) == ERROR){
				return ERROR;
			}
			else{
				cuvex.nfc.tag.type = NFC_TAG_TYPE_T4T_8K;
			}
			break;
		}
	}

	/*
	 * State machine based on the action to be performed by the NFC reader/writer
	 */
	switch(cuvex.nfc.tag.type)
	{
	case NFC_TAG_TYPE_NONE:
	default:
		return ERROR;
		break;

	case NFC_TAG_TYPE_T2T_NTAG216:
		if(stateMachineTagActionT2T_NTAG216(pNfcDevice, &ndefCtx, &info) == ERROR){
			return ERROR;
		}
		break;

	case NFC_TAG_TYPE_T4T_8K:
		if(stateMachineTagActionT4T_8K(pNfcDevice, &ndefCtx, &info) == ERROR){
			return ERROR;
		}
		break;
	}

	return SUCCESS;
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
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int stateMachineTagActionT2T_NTAG216(rfalNfcDevice *pNfcDevice, ndefContext *pNdefCtx, ndefInfo *pInfo)
{
	ReturnCode 			err;
	uint8_t 			raw_message_buf[1000] = {0};
	ndefBuffer       	buf_raw_message;
	uint32_t         	raw_message_len;
	ndefConstBuffer  	buf_const_raw_message;
	ndefConstBuffer8 	buf_lan_code_1, buf_lan_code_2, buf_lan_code_3;
	ndefConstBuffer 	buf_record_1, buf_record_2, buf_record_3;
	ndefRecord      	record_1, record_2, record_3;
	ndefType         	text_1, text_2, text_3;
	ndefMessage      	message;

	switch(cuvex.nfc.tag.action)
	{
	case NFC_TAG_NONE:
	default:
		break;

		/*******************************************************************************************************************************************/
	case NFC_TAG_READ:

		/*** Obtaining the UID (first read) ***/
		memcpy(cuvex.nfc.tag.uid, hex2Str(pNfcDevice->nfcid, pNfcDevice->nfcidLen), 14);

		/*** Reading the tag (if it has information) ***/
		if(pInfo->state != NDEF_STATE_INITIALIZED)
		{
			/*** Obtaining the message in Raw format ***/
			if(ndefPollerReadRawMessage(pNdefCtx, raw_message_buf, sizeof(raw_message_buf), &raw_message_len) != ERR_NONE){
				return ERROR;
			}

			/*** Decoding the message in Raw format ***/
			buf_const_raw_message.buffer = raw_message_buf;
			buf_const_raw_message.length = raw_message_len;

			if(ndefMessageDecode(&buf_const_raw_message, &message) != ERR_NONE){
				return ERROR;
			}

			/*** Retrieval of information stored on the NFC tag ***/
			if(ndefMessageGetInfoT2T_NTAG216(&message) == ERROR){
				cuvex.nfc.tag.encripted	= false;
			}

#ifdef DEBUG_NFC_PRINTF
			printf("[NDEF] -> Read success...\r\n");
#endif
		}
		else{
			cuvex.nfc.tag.encripted	= false;
		}

		cuvex.nfc.tag.flag_readed = true;
		break;

		/*******************************************************************************************************************************************/
	case NFC_TAG_READ_FROM_NFC:

		/*** Reading the tag (if it has information) ***/
		if(pInfo->state != NDEF_STATE_INITIALIZED)
		{
			/*** Obtaining the message in Raw format ***/
			if(ndefPollerReadRawMessage(pNdefCtx, raw_message_buf, sizeof(raw_message_buf), &raw_message_len) != ERR_NONE){
				return ERROR;
			}

			/*** Decoding the message in Raw format ***/
			buf_const_raw_message.buffer = raw_message_buf;
			buf_const_raw_message.length = raw_message_len;

			if(ndefMessageDecode(&buf_const_raw_message, &message) != ERR_NONE){
				return ERROR;
			}

			/*** Retrieval of information stored on the NFC tag ***/
			if(ndefMessageGetInfo_fromNFC(&message) == ERROR){
				cuvex.nfc.tag.from_nfc_type = 0;
			}
		}
		else{
			cuvex.nfc.tag.from_nfc_type = 0;
		}

		cuvex.nfc.tag.flag_readed_from_nfc = true;
		break;

		/*******************************************************************************************************************************************/
	case NFC_TAG_READ_WRITE_FLOW_ENCRYPT_T4T_8K:
		cuvex.nfc.tag.flag_readed_writed = true;
		break;

		/*******************************************************************************************************************************************/
	case NFC_TAG_READ_WRITE_FLOW_ENCRYPT:

		/*** Obtaining the UID (first read) ***/
		memcpy(cuvex.nfc.tag.uid, hex2Str(pNfcDevice->nfcid, pNfcDevice->nfcidLen), 14);

		/*** READ --> if tag not formatted ***/
		if(pInfo->state != NDEF_STATE_INITIALIZED)
		{
			/*** Obtaining the message in Raw format ***/
			if(ndefPollerReadRawMessage(pNdefCtx, raw_message_buf, sizeof(raw_message_buf), &raw_message_len) != ERR_NONE){
				return ERROR;
			}

			/*** Decoding the message in Raw format ***/
			buf_const_raw_message.buffer = raw_message_buf;
			buf_const_raw_message.length = raw_message_len;

			if(ndefMessageDecode(&buf_const_raw_message, &message) != ERR_NONE){
				return ERROR;
			}

			/*** Retrieval of information stored on the NFC tag ***/
			if(ndefMessageGetInfoT2T_NTAG216(&message) == ERROR){
				cuvex.nfc.tag.encripted	= false;
			}

#ifdef DEBUG_NFC_PRINTF
			printf("[NDEF-flow-encrypt] -> Read success...\r\n");
#endif
		}
		else{
			cuvex.nfc.tag.encripted	= false;
		}

		/*** WRITE --> if tag does not have a cryptogram ***/
		if(cuvex.nfc.tag.encripted == false)
		{
			/*** Buffers --> Initialization of read buffers and assignment of new values ***/
			memset(cuvex.nfc.tag.alias, 0x00, sizeof(cuvex.nfc.tag.alias));
			memset(cuvex.nfc.tag.cryptogram, 0x00, sizeof(cuvex.nfc.tag.cryptogram));
			memset(cuvex.nfc.tag.information, 0x00, sizeof(cuvex.nfc.tag.information));
			memcpy(cuvex.nfc.tag.alias, cuvex.nfc.tag.new_alias, sizeof(cuvex.nfc.tag.alias));
			memcpy(cuvex.nfc.tag.cryptogram, cuvex.nfc.tag.new_cryptogram, sizeof(cuvex.nfc.tag.cryptogram));
			memcpy(cuvex.nfc.tag.information, cuvex.nfc.tag.new_information, sizeof(cuvex.nfc.tag.information));

			/*** Text/record 1 --> Initialization and encoding ***/
			buf_lan_code_1.buffer = (uint8_t *) "A:";
			buf_lan_code_1.length = 2;
			buf_record_1.buffer   = cuvex.nfc.tag.alias;
			buf_record_1.length   = sizeof(cuvex.nfc.tag.alias);

			err |= ndefRtdText(&text_1, TEXT_ENCODING_UTF8, &buf_lan_code_1, &buf_record_1);
			err |= ndefRtdTextToRecord(&text_1, &record_1);

			/*** Text/record 2 --> Initialization and encoding ***/
			buf_lan_code_2.buffer = (uint8_t *) "C:";
			buf_lan_code_2.length = 2;
			buf_record_2.buffer   = cuvex.nfc.tag.cryptogram;
			buf_record_2.length   = sizeof(cuvex.nfc.tag.cryptogram);

			err |= ndefRtdText(&text_2, TEXT_ENCODING_UTF8, &buf_lan_code_2, &buf_record_2);
			err |= ndefRtdTextToRecord(&text_2, &record_2);

			/*** Text/record 3 --> Initialization and encoding ***/
			buf_lan_code_3.buffer = (uint8_t *) "I:";
			buf_lan_code_3.length = 2;
			buf_record_3.buffer   = cuvex.nfc.tag.information;
			buf_record_3.length   = sizeof(cuvex.nfc.tag.information);

			err |= ndefRtdText(&text_3, TEXT_ENCODING_UTF8, &buf_lan_code_3, &buf_record_3);
			err |= ndefRtdTextToRecord(&text_3, &record_3);

			/*** Message --> Initialization and appending of records ***/
			err  = ndefMessageInit(&message);
			err |= ndefMessageAppend(&message, &record_1);
			err |= ndefMessageAppend(&message, &record_2);
			err |= ndefMessageAppend(&message, &record_3);

			/*** Raw Buffer --> Encoding and writing of the message ***/
			buf_raw_message.buffer = raw_message_buf;
			buf_raw_message.length = sizeof(raw_message_buf);

			err |= ndefMessageEncode(&message, &buf_raw_message);

			if(err != ERR_NONE){
				return ERROR;
			}

			err = ndefPollerWriteRawMessage(pNdefCtx, buf_raw_message.buffer, buf_raw_message.length);

			if(err != ERR_NONE){
				return ERROR;
			}

#ifdef DEBUG_NFC_PRINTF
			printf("[NDEF-flow-encrypt] -> Write success...\r\n");
#endif
		}

		cuvex.nfc.tag.flag_readed_writed = true;
		break;

		/*******************************************************************************************************************************************/
	case NFC_TAG_READ_WRITE_FLOW_CLONE_T4T_8K:
		cuvex.nfc.tag.flag_readed_writed = true;
		break;

		/*******************************************************************************************************************************************/
	case NFC_TAG_READ_WRITE_FLOW_CLONE:

		/*** Obtaining the UID (first read) ***/
		memcpy(cuvex.nfc.tag.new_uid, hex2Str(pNfcDevice->nfcid, pNfcDevice->nfcidLen), 14);

		/*** Saving the values of tag1 (before reading tag_2) ***/
		memcpy(cuvex.nfc.tag.new_alias, cuvex.nfc.tag.alias, sizeof(cuvex.nfc.tag.new_alias));
		memcpy(cuvex.nfc.tag.new_cryptogram, cuvex.nfc.tag.cryptogram, sizeof(cuvex.nfc.tag.new_cryptogram));
		memcpy(cuvex.nfc.tag.new_information, cuvex.nfc.tag.information, sizeof(cuvex.nfc.tag.new_information));

		/*** READ + WRITE --> if tag1 equals tag2 ***/
		if(strstr((char *) cuvex.nfc.tag.uid, (char *) cuvex.nfc.tag.new_uid) == 0x00)
		{
			/*** READ --> if tag2 not formatted ***/
			if(pInfo->state != NDEF_STATE_INITIALIZED)
			{
				/*** Obtaining the message in Raw format ***/
				if(ndefPollerReadRawMessage(pNdefCtx, raw_message_buf, sizeof(raw_message_buf), &raw_message_len) != ERR_NONE){
					return ERROR;
				}

				/*** Decoding the message in Raw format ***/
				buf_const_raw_message.buffer = raw_message_buf;
				buf_const_raw_message.length = raw_message_len;

				if(ndefMessageDecode(&buf_const_raw_message, &message) != ERR_NONE){
					return ERROR;
				}

				/*** Retrieval of information stored on the NFC tag ***/
				if(ndefMessageGetInfoT2T_NTAG216(&message) == ERROR){
					cuvex.nfc.tag.encripted	= false;
				}

#ifdef DEBUG_NFC_PRINTF
				printf("[NDEF-flow-clone] -> Read success...\r\n");
#endif
			}
			else{
				cuvex.nfc.tag.encripted	= false;
			}

			/*** WRITE --> if tag_2 does not have a cryptogram ***/
			if(cuvex.nfc.tag.encripted == false)
			{
				/*** Buffers --> Initialization of read buffers and assignment of new values ***/
				memset(cuvex.nfc.tag.alias, 0x00, sizeof(cuvex.nfc.tag.alias));
				memset(cuvex.nfc.tag.cryptogram, 0x00, sizeof(cuvex.nfc.tag.cryptogram));
				memset(cuvex.nfc.tag.information, 0x00, sizeof(cuvex.nfc.tag.information));
				memcpy(cuvex.nfc.tag.alias, cuvex.nfc.tag.new_alias, sizeof(cuvex.nfc.tag.alias));
				memcpy(cuvex.nfc.tag.cryptogram, cuvex.nfc.tag.new_cryptogram, sizeof(cuvex.nfc.tag.cryptogram));
				memcpy(cuvex.nfc.tag.information, cuvex.nfc.tag.new_information, sizeof(cuvex.nfc.tag.information));
				cuvex.nfc.tag.information[strlen((char *) cuvex.nfc.tag.information) - 1] = '1';

				/*** Text/record 1 --> Initialization and encoding ***/
				buf_lan_code_1.buffer = (uint8_t *) "A:";
				buf_lan_code_1.length = 2;
				buf_record_1.buffer   = cuvex.nfc.tag.alias;
				buf_record_1.length   = sizeof(cuvex.nfc.tag.alias);

				err |= ndefRtdText(&text_1, TEXT_ENCODING_UTF8, &buf_lan_code_1, &buf_record_1);
				err |= ndefRtdTextToRecord(&text_1, &record_1);

				/*** Text/record 2 --> Initialization and encoding ***/
				buf_lan_code_2.buffer = (uint8_t *) "C:";
				buf_lan_code_2.length = 2;
				buf_record_2.buffer   = cuvex.nfc.tag.cryptogram;
				buf_record_2.length   = sizeof(cuvex.nfc.tag.cryptogram);

				err |= ndefRtdText(&text_2, TEXT_ENCODING_UTF8, &buf_lan_code_2, &buf_record_2);
				err |= ndefRtdTextToRecord(&text_2, &record_2);

				/*** Text/record 3 --> Initialization and encoding ***/
				buf_lan_code_3.buffer = (uint8_t *) "I:";
				buf_lan_code_3.length = 2;
				buf_record_3.buffer   = cuvex.nfc.tag.information;
				buf_record_3.length   = sizeof(cuvex.nfc.tag.information);

				err |= ndefRtdText(&text_3, TEXT_ENCODING_UTF8, &buf_lan_code_3, &buf_record_3);
				err |= ndefRtdTextToRecord(&text_3, &record_3);

				/*** Message --> Initialization and appending of records ***/
				err  = ndefMessageInit(&message);
				err |= ndefMessageAppend(&message, &record_1);
				err |= ndefMessageAppend(&message, &record_2);
				err |= ndefMessageAppend(&message, &record_3);

				/*** Raw Buffer --> Encoding and writing of the message ***/
				buf_raw_message.buffer = raw_message_buf;
				buf_raw_message.length = sizeof(raw_message_buf);

				err |= ndefMessageEncode(&message, &buf_raw_message);

				if(err != ERR_NONE){
					return ERROR;
				}

				err = ndefPollerWriteRawMessage(pNdefCtx, buf_raw_message.buffer, buf_raw_message.length);

				if(err != ERR_NONE){
					return ERROR;
				}

#ifdef DEBUG_NFC_PRINTF
				printf("[NDEF-flow-clone] -> Write success...\r\n");
#endif
			}

			cuvex.nfc.tag.flag_readed_writed = true;
		}
		break;
	}

	return SUCCESS;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int stateMachineTagActionT4T_8K(rfalNfcDevice *pNfcDevice, ndefContext *pNdefCtx, ndefInfo *pInfo)
{
	ReturnCode 			err;
	uint8_t 			raw_message_buf[1750] = {0};
	ndefBuffer       	buf_raw_message;
	uint32_t         	raw_message_len;
	ndefConstBuffer  	buf_const_raw_message;
	ndefConstBuffer8 	buf_lan_code_1, buf_lan_code_2, buf_lan_code_3, buf_lan_code_4;
	ndefConstBuffer 	buf_record_1, buf_record_2, buf_record_3, buf_record_4;
	ndefRecord      	record_1, record_2, record_3, record_4;
	ndefType         	text_1, text_2, text_3, text_4;
	ndefMessage      	message;

	switch(cuvex.nfc.tag.action)
	{
	case NFC_TAG_NONE:
	default:
		break;

		/*******************************************************************************************************************************************/
	case NFC_TAG_READ:

		/*** Obtaining the UID (first read) ***/
		memcpy(cuvex.nfc.tag.uid, hex2Str(pNfcDevice->nfcid, pNfcDevice->nfcidLen), 14);

		/*** Reading the tag (if it has information) ***/
		if(pInfo->state != NDEF_STATE_INITIALIZED)
		{
			/*** Obtaining the message in Raw format ***/
			if(ndefPollerReadRawMessage(pNdefCtx, raw_message_buf, sizeof(raw_message_buf), &raw_message_len) != ERR_NONE){
				return ERROR;
			}

			/*** Decoding the message in Raw format ***/
			buf_const_raw_message.buffer = raw_message_buf;
			buf_const_raw_message.length = raw_message_len;

			if(ndefMessageDecode(&buf_const_raw_message, &message) != ERR_NONE){
				return ERROR;
			}

			/*** Retrieval of information stored on the NFC tag ***/
			if(ndefMessageGetInfoT4T_8K(&message) == ERROR){
				cuvex.nfc.tag.encripted	= false;
			}

#ifdef DEBUG_NFC_PRINTF
			printf("[NDEF] -> Read success...\r\n");
#endif
		}
		else{
			cuvex.nfc.tag.encripted	= false;
		}

		cuvex.nfc.tag.flag_readed = true;
		break;

		/*******************************************************************************************************************************************/
	case NFC_TAG_READ_FROM_NFC:

		/*** Reading the tag (if it has information) ***/
		if(pInfo->state != NDEF_STATE_INITIALIZED)
		{
			/*** Obtaining the message in Raw format ***/
			if(ndefPollerReadRawMessage(pNdefCtx, raw_message_buf, sizeof(raw_message_buf), &raw_message_len) != ERR_NONE){
				return ERROR;
			}

			/*** Decoding the message in Raw format ***/
			buf_const_raw_message.buffer = raw_message_buf;
			buf_const_raw_message.length = raw_message_len;

			if(ndefMessageDecode(&buf_const_raw_message, &message) != ERR_NONE){
				return ERROR;
			}

			/*** Retrieval of information stored on the NFC tag ***/
			if(ndefMessageGetInfo_fromNFC(&message) == ERROR){
				cuvex.nfc.tag.from_nfc_type = 0;
			}
		}
		else{
			cuvex.nfc.tag.from_nfc_type = 0;
		}

		cuvex.nfc.tag.flag_readed_from_nfc = true;
		break;

		/*******************************************************************************************************************************************/
	case NFC_TAG_READ_WRITE_FLOW_ENCRYPT_T4T_8K:
	case NFC_TAG_READ_WRITE_FLOW_ENCRYPT:

		/*** Obtaining the UID (first read) ***/
		memcpy(cuvex.nfc.tag.uid, hex2Str(pNfcDevice->nfcid, pNfcDevice->nfcidLen), 14);

		/*** READ --> if tag not formatted ***/
		if(pInfo->state != NDEF_STATE_INITIALIZED)
		{
			/*** Obtaining the message in Raw format ***/
			if(ndefPollerReadRawMessage(pNdefCtx, raw_message_buf, sizeof(raw_message_buf), &raw_message_len) != ERR_NONE){
				return ERROR;
			}

			/*** Decoding the message in Raw format ***/
			buf_const_raw_message.buffer = raw_message_buf;
			buf_const_raw_message.length = raw_message_len;

			if(ndefMessageDecode(&buf_const_raw_message, &message) != ERR_NONE){
				return ERROR;
			}

			/*** Retrieval of information stored on the NFC tag ***/
			if(ndefMessageGetInfoT4T_8K(&message) == ERROR){
				cuvex.nfc.tag.encripted	= false;
			}

#ifdef DEBUG_NFC_PRINTF
			printf("[NDEF-flow-encrypt] -> Read success...\r\n");
#endif
		}
		else{
			cuvex.nfc.tag.encripted	= false;
		}

		/*** WRITE --> if tag does not have a cryptogram ***/
		if(cuvex.nfc.tag.encripted == false)
		{
			/*** Buffers --> Initialization of read buffers and assignment of new values ***/
			memset(cuvex.nfc.tag.alias, 0x00, sizeof(cuvex.nfc.tag.alias));
			memset(cuvex.nfc.tag.cryptogram, 0x00, sizeof(cuvex.nfc.tag.cryptogram));
			memset(cuvex.nfc.tag.information, 0x00, sizeof(cuvex.nfc.tag.information));
			memset(cuvex.nfc.tag.multisignature, 0x00, sizeof(cuvex.nfc.tag.multisignature));
			memcpy(cuvex.nfc.tag.alias, cuvex.nfc.tag.new_alias, sizeof(cuvex.nfc.tag.alias));
			memcpy(cuvex.nfc.tag.cryptogram, cuvex.nfc.tag.new_cryptogram, sizeof(cuvex.nfc.tag.cryptogram));
			memcpy(cuvex.nfc.tag.information, cuvex.nfc.tag.new_information, sizeof(cuvex.nfc.tag.information));
			memcpy(cuvex.nfc.tag.multisignature, cuvex.nfc.tag.new_multisignature, sizeof(cuvex.nfc.tag.multisignature));

			/*** Text/record 1 --> Initialization and encoding ***/
			buf_lan_code_1.buffer = (uint8_t *) "A:";
			buf_lan_code_1.length = 2;
			buf_record_1.buffer   = cuvex.nfc.tag.alias;
			buf_record_1.length   = sizeof(cuvex.nfc.tag.alias);

			err |= ndefRtdText(&text_1, TEXT_ENCODING_UTF8, &buf_lan_code_1, &buf_record_1);
			err |= ndefRtdTextToRecord(&text_1, &record_1);

			/*** Text/record 2 --> Initialization and encoding ***/
			buf_lan_code_2.buffer = (uint8_t *) "C:";
			buf_lan_code_2.length = 2;
			buf_record_2.buffer   = cuvex.nfc.tag.cryptogram;
			buf_record_2.length   = sizeof(cuvex.nfc.tag.cryptogram);

			err |= ndefRtdText(&text_2, TEXT_ENCODING_UTF8, &buf_lan_code_2, &buf_record_2);
			err |= ndefRtdTextToRecord(&text_2, &record_2);

			/*** Text/record 3 --> Initialization and encoding ***/
			buf_lan_code_3.buffer = (uint8_t *) "I:";
			buf_lan_code_3.length = 2;
			buf_record_3.buffer   = cuvex.nfc.tag.information;
			buf_record_3.length   = sizeof(cuvex.nfc.tag.information);

			err |= ndefRtdText(&text_3, TEXT_ENCODING_UTF8, &buf_lan_code_3, &buf_record_3);
			err |= ndefRtdTextToRecord(&text_3, &record_3);

			/*** Text/record 4 --> Initialization and encoding ***/
			buf_lan_code_4.buffer = (uint8_t *) "M:";
			buf_lan_code_4.length = 2;
			buf_record_4.buffer   = cuvex.nfc.tag.multisignature;
			buf_record_4.length   = sizeof(cuvex.nfc.tag.multisignature);

			err |= ndefRtdText(&text_4, TEXT_ENCODING_UTF8, &buf_lan_code_4, &buf_record_4);
			err |= ndefRtdTextToRecord(&text_4, &record_4);

			/*** Message --> Initialization and appending of records ***/
			err  = ndefMessageInit(&message);
			err |= ndefMessageAppend(&message, &record_1);
			err |= ndefMessageAppend(&message, &record_2);
			err |= ndefMessageAppend(&message, &record_3);
			err |= ndefMessageAppend(&message, &record_4);

			/*** Raw Buffer --> Encoding and writing of the message ***/
			buf_raw_message.buffer = raw_message_buf;
			buf_raw_message.length = sizeof(raw_message_buf);

			err |= ndefMessageEncode(&message, &buf_raw_message);

			if(err != ERR_NONE){
				return ERROR;
			}

			err = ndefPollerWriteRawMessage(pNdefCtx, buf_raw_message.buffer, buf_raw_message.length);

			if(err != ERR_NONE){
				return ERROR;
			}

#ifdef DEBUG_NFC_PRINTF
			printf("[NDEF-flow-encrypt] -> Write success...\r\n");
#endif
		}

		cuvex.nfc.tag.flag_readed_writed = true;
		break;

		/*******************************************************************************************************************************************/
	case NFC_TAG_READ_WRITE_FLOW_CLONE_T4T_8K:
	case NFC_TAG_READ_WRITE_FLOW_CLONE:

		/*** Obtaining the UID (first read) ***/
		memcpy(cuvex.nfc.tag.new_uid, hex2Str(pNfcDevice->nfcid, pNfcDevice->nfcidLen), 14);

		/*** Saving the values of tag1 (before reading tag_2) ***/
		memcpy(cuvex.nfc.tag.new_alias, cuvex.nfc.tag.alias, sizeof(cuvex.nfc.tag.new_alias));
		memcpy(cuvex.nfc.tag.new_cryptogram, cuvex.nfc.tag.cryptogram, sizeof(cuvex.nfc.tag.new_cryptogram));
		memcpy(cuvex.nfc.tag.new_information, cuvex.nfc.tag.information, sizeof(cuvex.nfc.tag.new_information));
		memcpy(cuvex.nfc.tag.new_multisignature, cuvex.nfc.tag.multisignature, sizeof(cuvex.nfc.tag.new_multisignature));

		/*** READ + WRITE --> if tag1 equals tag2 ***/
		if(strstr((char *) cuvex.nfc.tag.uid, (char *) cuvex.nfc.tag.new_uid) == 0x00)
		{
			/*** READ --> if tag2 not formatted ***/
			if(pInfo->state != NDEF_STATE_INITIALIZED)
			{
				/*** Obtaining the message in Raw format ***/
				if(ndefPollerReadRawMessage(pNdefCtx, raw_message_buf, sizeof(raw_message_buf), &raw_message_len) != ERR_NONE){
					return ERROR;
				}

				/*** Decoding the message in Raw format ***/
				buf_const_raw_message.buffer = raw_message_buf;
				buf_const_raw_message.length = raw_message_len;

				if(ndefMessageDecode(&buf_const_raw_message, &message) != ERR_NONE){
					return ERROR;
				}

				/*** Retrieval of information stored on the NFC tag ***/
				if(ndefMessageGetInfoT4T_8K(&message) == ERROR){
					cuvex.nfc.tag.encripted	= false;
				}

#ifdef DEBUG_NFC_PRINTF
				printf("[NDEF-flow-clone] -> Read success...\r\n");
#endif
			}
			else{
				cuvex.nfc.tag.encripted	= false;
			}

			/*** WRITE --> if tag_2 does not have a cryptogram ***/
			if(cuvex.nfc.tag.encripted == false)
			{
				/*** Buffers --> Initialization of read buffers and assignment of new values ***/
				memset(cuvex.nfc.tag.alias, 0x00, sizeof(cuvex.nfc.tag.alias));
				memset(cuvex.nfc.tag.cryptogram, 0x00, sizeof(cuvex.nfc.tag.cryptogram));
				memset(cuvex.nfc.tag.information, 0x00, sizeof(cuvex.nfc.tag.information));
				memset(cuvex.nfc.tag.multisignature, 0x00, sizeof(cuvex.nfc.tag.multisignature));
				memcpy(cuvex.nfc.tag.alias, cuvex.nfc.tag.new_alias, sizeof(cuvex.nfc.tag.alias));
				memcpy(cuvex.nfc.tag.cryptogram, cuvex.nfc.tag.new_cryptogram, sizeof(cuvex.nfc.tag.cryptogram));
				memcpy(cuvex.nfc.tag.information, cuvex.nfc.tag.new_information, sizeof(cuvex.nfc.tag.information));
				memcpy(cuvex.nfc.tag.multisignature, cuvex.nfc.tag.new_multisignature, sizeof(cuvex.nfc.tag.multisignature));
				cuvex.nfc.tag.information[strlen((char *) cuvex.nfc.tag.information) - 1] = '1';

				/*** Text/record 1 --> Initialization and encoding ***/
				buf_lan_code_1.buffer = (uint8_t *) "A:";
				buf_lan_code_1.length = 2;
				buf_record_1.buffer   = cuvex.nfc.tag.alias;
				buf_record_1.length   = sizeof(cuvex.nfc.tag.alias);

				err |= ndefRtdText(&text_1, TEXT_ENCODING_UTF8, &buf_lan_code_1, &buf_record_1);
				err |= ndefRtdTextToRecord(&text_1, &record_1);

				/*** Text/record 2 --> Initialization and encoding ***/
				buf_lan_code_2.buffer = (uint8_t *) "C:";
				buf_lan_code_2.length = 2;
				buf_record_2.buffer   = cuvex.nfc.tag.cryptogram;
				buf_record_2.length   = sizeof(cuvex.nfc.tag.cryptogram);

				err |= ndefRtdText(&text_2, TEXT_ENCODING_UTF8, &buf_lan_code_2, &buf_record_2);
				err |= ndefRtdTextToRecord(&text_2, &record_2);

				/*** Text/record 3 --> Initialization and encoding ***/
				buf_lan_code_3.buffer = (uint8_t *) "I:";
				buf_lan_code_3.length = 2;
				buf_record_3.buffer   = cuvex.nfc.tag.information;
				buf_record_3.length   = sizeof(cuvex.nfc.tag.information);

				err |= ndefRtdText(&text_3, TEXT_ENCODING_UTF8, &buf_lan_code_3, &buf_record_3);
				err |= ndefRtdTextToRecord(&text_3, &record_3);

				/*** Text/record 4 --> Initialization and encoding ***/
				buf_lan_code_4.buffer = (uint8_t *) "M:";
				buf_lan_code_4.length = 2;
				buf_record_4.buffer   = cuvex.nfc.tag.multisignature;
				buf_record_4.length   = sizeof(cuvex.nfc.tag.multisignature);

				err |= ndefRtdText(&text_4, TEXT_ENCODING_UTF8, &buf_lan_code_4, &buf_record_4);
				err |= ndefRtdTextToRecord(&text_4, &record_4);

				/*** Message --> Initialization and appending of records ***/
				err  = ndefMessageInit(&message);
				err |= ndefMessageAppend(&message, &record_1);
				err |= ndefMessageAppend(&message, &record_2);
				err |= ndefMessageAppend(&message, &record_3);
				err |= ndefMessageAppend(&message, &record_4);

				/*** Raw Buffer --> Encoding and writing of the message ***/
				buf_raw_message.buffer = raw_message_buf;
				buf_raw_message.length = sizeof(raw_message_buf);

				err |= ndefMessageEncode(&message, &buf_raw_message);

				if(err != ERR_NONE){
					return ERROR;
				}

				err = ndefPollerWriteRawMessage(pNdefCtx, buf_raw_message.buffer, buf_raw_message.length);

				if(err != ERR_NONE){
					return ERROR;
				}

#ifdef DEBUG_NFC_PRINTF
				printf("[NDEF-flow-clone] -> Write success...\r\n");
#endif
			}

			cuvex.nfc.tag.flag_readed_writed = true;
		}
		break;
	}

	return SUCCESS;
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
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int ndefMessageGetInfoT2T_NTAG216(const ndefMessage* message)
{
	ndefRecord* record;
	record = ndefMessageGetFirstRecord(message);

	while(record != NULL)
	{
		if(ndefRecordGetInfoT2T_NTAG216(record) != SUCCESS){
			return ERROR;
		}

		record = ndefMessageGetNextRecord(record);
	}

	return SUCCESS;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int ndefRecordGetInfoT2T_NTAG216(const ndefRecord* record)
{
	static uint32_t index = 0;
	ndefType type;
	uint8_t utfEncoding;
	ndefConstBuffer8 bufLanguageCode;
	ndefConstBuffer  bufSentence;

	/*** Update record index ***/
	if(ndefHeaderIsSetMB(record)){
		index = 1;
	}
	else{
		index++;
	}

#ifdef DEBUG_NFC_PRINTF
	printf("### Record #%d: --> MB:%d,ME:%d,CF:%d,SR:%d,IL:%d,TNF:%d\r\n", index, ndefHeaderMB(record), ndefHeaderME(record), ndefHeaderCF(record), ndefHeaderSR(record), ndefHeaderIL(record), ndefHeaderTNF(record));
#endif

	/*** Get record type ***/
	ndefRecordToType(record, &type);

	/*** Get record info (if type text) ***/
	if((type.id == NDEF_TYPE_RTD_TEXT) && (ndefGetRtdText(&type, &utfEncoding, &bufLanguageCode, &bufSentence) != ERR_PARAM))
	{
		switch(index)
		{
		case 1:	//Record 1 (alias)

			if((bufLanguageCode.length == 2) && (bufLanguageCode.buffer[0] == 'A') && (bufLanguageCode.buffer[1] == ':'))
			{
				memset(cuvex.nfc.tag.alias, 0x00, sizeof(cuvex.nfc.tag.alias));
				memcpy(cuvex.nfc.tag.alias, bufSentence.buffer, bufSentence.length);

#ifdef DEBUG_NFC_PRINTF
				printf("\r\nAlias:\r\n");
				for(int i=0; i<sizeof(cuvex.nfc.tag.alias); i++){
					printf("%c", cuvex.nfc.tag.alias[i]);
				}
				printf("\r\n\r\n");
#endif

				return SUCCESS;
			}

			break;

		case 2:	//Record 2 (criptogram)

			if((bufLanguageCode.length == 2) && (bufLanguageCode.buffer[0] == 'C') && (bufLanguageCode.buffer[1] == ':'))
			{
				memset(cuvex.nfc.tag.cryptogram, 0x00, sizeof(cuvex.nfc.tag.cryptogram));
				memcpy(cuvex.nfc.tag.cryptogram, bufSentence.buffer, bufSentence.length);

#ifdef DEBUG_NFC_PRINTF
				printf("\r\nCriptogram:\r\n");
				for(int i=0; i<sizeof(cuvex.nfc.tag.cryptogram); i++){
					printf("%c", cuvex.nfc.tag.cryptogram[i]);
				}
				printf("\r\n\r\n");
#endif
				return SUCCESS;
			}

			break;

		case 3:	//Record 3 (information --> Format "ENC,vXX.XX.XX(Y),M-X,P-X,C-X")

			if((bufLanguageCode.length == 2) && (bufLanguageCode.buffer[0] == 'I') && (bufLanguageCode.buffer[1] == ':'))
			{
				memset(cuvex.nfc.tag.information, 0x00, sizeof(cuvex.nfc.tag.information));
				memcpy(cuvex.nfc.tag.information, bufSentence.buffer, bufSentence.length);

				char *ptr;
				ptr = strstr((char *) cuvex.nfc.tag.information, "ENC,");

				if(ptr != 0x00)	//Get encripted tag info
				{
					cuvex.nfc.tag.encripted = true;

					ptr = strstr((char *) cuvex.nfc.tag.information, ",M-");

					if(ptr != 0x00)	//Get signed tag info
					{
						if(ptr[3] == '1'){
							cuvex.nfc.tag.multisigned_total = 1;
						}
						else if(ptr[3] == '2'){
							cuvex.nfc.tag.multisigned_total = 2;
						}
						else if(ptr[3] == '3'){
							cuvex.nfc.tag.multisigned_total = 3;
						}
						else if(ptr[3] == '4'){
							cuvex.nfc.tag.multisigned_total = 4;
						}
						else if(ptr[3] == '5'){
							cuvex.nfc.tag.multisigned_total = 5;
						}
						else if(ptr[3] == '6'){
							cuvex.nfc.tag.multisigned_total = 6;
						}
						else{
							cuvex.nfc.tag.multisigned_total = 0;
						}

						if(ptr[4] == ':'){
							if(ptr[5] == '1'){
								cuvex.nfc.tag.multisigned_mandatory = 1;
							}
							else if(ptr[5] == '2'){
								cuvex.nfc.tag.multisigned_mandatory = 2;
							}
							else if(ptr[5] == '3'){
								cuvex.nfc.tag.multisigned_mandatory = 3;
							}
							else if(ptr[5] == '4'){
								cuvex.nfc.tag.multisigned_mandatory = 4;
							}
							else if(ptr[5] == '5'){
								cuvex.nfc.tag.multisigned_mandatory = 5;
							}
							else if(ptr[5] == '6'){
								cuvex.nfc.tag.multisigned_mandatory = 6;
							}
							else{
								cuvex.nfc.tag.multisigned_mandatory = 0;
							}
						}
						else{
							cuvex.nfc.tag.multisigned_mandatory = cuvex.nfc.tag.multisigned_total;
						}
					}

					ptr = strstr((char *) cuvex.nfc.tag.information, ",P-");

					if(ptr != 0x00)	//Get packed tag info
					{
						if(ptr[3] == '1'){
							cuvex.nfc.tag.packed = 1;
						}
						else{
							cuvex.nfc.tag.packed = 0;
						}
					}

					ptr = strstr((char *) cuvex.nfc.tag.information, ",C-");

					if(ptr != 0x00)	//Get cloned tag info
					{
						if(ptr[3] == '1'){
							cuvex.nfc.tag.cloned = 1;
						}
						else{
							cuvex.nfc.tag.cloned = 0;
						}
					}

					return SUCCESS;
				}
				else{
					cuvex.nfc.tag.encripted = false;
				}

#ifdef DEBUG_NFC_PRINTF
				printf("\r\nInformation:\r\n");
				for(int i=0; i<sizeof(cuvex.nfc.tag.information); i++){
					printf("%c", cuvex.nfc.tag.information[i]);
				}
				printf("\r\n");
#endif
			}

			break;

		default:
			break;
		}
	}

	return ERROR;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int ndefMessageGetInfoT4T_8K(const ndefMessage* message)
{
	ndefRecord* record;
	record = ndefMessageGetFirstRecord(message);

	while(record != NULL)
	{
		if(ndefRecordGetInfoT4T_8K(record) != SUCCESS){
			return ERROR;
		}

		record = ndefMessageGetNextRecord(record);
	}

	return SUCCESS;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int ndefRecordGetInfoT4T_8K(const ndefRecord* record)
{
	static uint32_t index = 0;
	ndefType type;
	uint8_t utfEncoding;
	ndefConstBuffer8 bufLanguageCode;
	ndefConstBuffer  bufSentence;

	/*** Update record index ***/
	if(ndefHeaderIsSetMB(record)){
		index = 1;
	}
	else{
		index++;
	}

#ifdef DEBUG_NFC_PRINTF
	printf("### Record #%d: --> MB:%d,ME:%d,CF:%d,SR:%d,IL:%d,TNF:%d\r\n", index, ndefHeaderMB(record), ndefHeaderME(record), ndefHeaderCF(record), ndefHeaderSR(record), ndefHeaderIL(record), ndefHeaderTNF(record));
#endif

	/*** Get record type ***/
	ndefRecordToType(record, &type);

	/*** Get record info (if type text) ***/
	if((type.id == NDEF_TYPE_RTD_TEXT) && (ndefGetRtdText(&type, &utfEncoding, &bufLanguageCode, &bufSentence) != ERR_PARAM))
	{
		switch(index)
		{
		case 1:	//Record 1 (alias)

			if((bufLanguageCode.length == 2) && (bufLanguageCode.buffer[0] == 'A') && (bufLanguageCode.buffer[1] == ':'))
			{
				memset(cuvex.nfc.tag.alias, 0x00, sizeof(cuvex.nfc.tag.alias));
				memcpy(cuvex.nfc.tag.alias, bufSentence.buffer, bufSentence.length);

#ifdef DEBUG_NFC_PRINTF
				printf("\r\nAlias:\r\n");
				for(int i=0; i<sizeof(cuvex.nfc.tag.alias); i++){
					printf("%c", cuvex.nfc.tag.alias[i]);
				}
				printf("\r\n\r\n");
#endif
				return SUCCESS;
			}

			break;

		case 2:	//Record 2 (criptogram)

			if((bufLanguageCode.length == 2) && (bufLanguageCode.buffer[0] == 'C') && (bufLanguageCode.buffer[1] == ':'))
			{
				memset(cuvex.nfc.tag.cryptogram, 0x00, sizeof(cuvex.nfc.tag.cryptogram));
				memcpy(cuvex.nfc.tag.cryptogram, bufSentence.buffer, bufSentence.length);

#ifdef DEBUG_NFC_PRINTF
				printf("\r\nCriptogram:\r\n");
				for(int i=0; i<sizeof(cuvex.nfc.tag.cryptogram); i++){
					printf("%c", cuvex.nfc.tag.cryptogram[i]);
				}
				printf("\r\n\r\n");
#endif
				return SUCCESS;
			}

			break;

		case 3:	//Record 3 (information --> Format "ENC,vXX.XX.XX(Y),M-X,P-X,C-X")

			if((bufLanguageCode.length == 2) && (bufLanguageCode.buffer[0] == 'I') && (bufLanguageCode.buffer[1] == ':'))
			{
				memset(cuvex.nfc.tag.information, 0x00, sizeof(cuvex.nfc.tag.information));
				memcpy(cuvex.nfc.tag.information, bufSentence.buffer, bufSentence.length);

				char *ptr;
				ptr = strstr((char *) cuvex.nfc.tag.information, "ENC,");

				if(ptr != 0x00)	//Get encripted tag info
				{
					cuvex.nfc.tag.encripted = true;

					ptr = strstr((char *) cuvex.nfc.tag.information, ",M-");

					if(ptr != 0x00)	//Get signed tag info
					{
						if(ptr[3] == '1'){
							cuvex.nfc.tag.multisigned_total = 1;
						}
						else if(ptr[3] == '2'){
							cuvex.nfc.tag.multisigned_total = 2;
						}
						else if(ptr[3] == '3'){
							cuvex.nfc.tag.multisigned_total = 3;
						}
						else if(ptr[3] == '4'){
							cuvex.nfc.tag.multisigned_total = 4;
						}
						else if(ptr[3] == '5'){
							cuvex.nfc.tag.multisigned_total = 5;
						}
						else if(ptr[3] == '6'){
							cuvex.nfc.tag.multisigned_total = 6;
						}
						else{
							cuvex.nfc.tag.multisigned_total = 0;
						}

						if(ptr[4] == ':'){
							if(ptr[5] == '1'){
								cuvex.nfc.tag.multisigned_mandatory = 1;
							}
							else if(ptr[5] == '2'){
								cuvex.nfc.tag.multisigned_mandatory = 2;
							}
							else if(ptr[5] == '3'){
								cuvex.nfc.tag.multisigned_mandatory = 3;
							}
							else if(ptr[5] == '4'){
								cuvex.nfc.tag.multisigned_mandatory = 4;
							}
							else if(ptr[5] == '5'){
								cuvex.nfc.tag.multisigned_mandatory = 5;
							}
							else if(ptr[5] == '6'){
								cuvex.nfc.tag.multisigned_mandatory = 6;
							}
							else{
								cuvex.nfc.tag.multisigned_mandatory = 0;
							}
						}
						else{
							cuvex.nfc.tag.multisigned_mandatory = cuvex.nfc.tag.multisigned_total;
						}
					}

					ptr = strstr((char *) cuvex.nfc.tag.information, ",P-");

					if(ptr != 0x00)	//Get packed tag info
					{
						if(ptr[3] == '1'){
							cuvex.nfc.tag.packed = 1;
						}
						else{
							cuvex.nfc.tag.packed = 0;
						}
					}

					ptr = strstr((char *) cuvex.nfc.tag.information, ",C-");

					if(ptr != 0x00)	//Get cloned tag info
					{
						if(ptr[3] == '1'){
							cuvex.nfc.tag.cloned = 1;
						}
						else{
							cuvex.nfc.tag.cloned = 0;
						}
					}
				}
				else{
					cuvex.nfc.tag.encripted = false;
				}

#ifdef DEBUG_NFC_PRINTF
				printf("\r\nInformation:\r\n");
				for(int i=0; i<sizeof(cuvex.nfc.tag.information); i++){
					printf("%c", cuvex.nfc.tag.information[i]);
				}
				printf("\r\n");
#endif
				return SUCCESS;
			}

			break;

		case 4:	//Record 4 (multisignature --> Format "Num.Comb.+comb1+comb2+...+combN")

			if((bufLanguageCode.length == 2) && (bufLanguageCode.buffer[0] == 'M') && (bufLanguageCode.buffer[1] == ':'))
			{
				memset(cuvex.nfc.tag.multisignature, 0x00, sizeof(cuvex.nfc.tag.multisignature));
				memcpy(cuvex.nfc.tag.multisignature, bufSentence.buffer, bufSentence.length);

#ifdef DEBUG_NFC_PRINTF
				printf("\r\nMultisignature:\r\n");
				for(int i=0; i<sizeof(cuvex.nfc.tag.multisignature); i++){
					printf("%c", cuvex.nfc.tag.multisignature[i]);
				}
				printf("\r\n");
#endif
				return SUCCESS;
			}

			break;

		default:
			break;
		}
	}

	return ERROR;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int ndefMessageGetInfo_fromNFC(const ndefMessage* message)
{
	ndefRecord* record;
	record = ndefMessageGetFirstRecord(message);

	while(record != NULL)
	{
		if(ndefRecordGetInfo_fromNFC(record) != SUCCESS){
			return ERROR;
		}

		record = ndefMessageGetNextRecord(record);
	}

	return SUCCESS;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int ndefRecordGetInfo_fromNFC(const ndefRecord* record)
{
	static uint32_t index = 0;
	ndefType type;
	uint8_t utfEncoding;
	ndefConstBuffer8 bufLanguageCode;
	ndefConstBuffer  bufSentence;

	/*** Update record index ***/
	if(ndefHeaderIsSetMB(record)){
		index = 1;
	}
	else{
		index++;
	}

	/*** Get record type ***/
	ndefRecordToType(record, &type);

	/*** Get record info (if type text) ***/
	if((type.id == NDEF_TYPE_RTD_TEXT) && (ndefGetRtdText(&type, &utfEncoding, &bufLanguageCode, &bufSentence) != ERR_PARAM))
	{
		switch(index)
		{
		default:
			break;

		case 1:	//Record 1
			if((bufLanguageCode.length == 2) && (bufLanguageCode.buffer[0] == 'e') && (bufLanguageCode.buffer[1] == 'n'))
			{
				if(strstr((char *) bufSentence.buffer, (char *) "seed-bip39") != 0x00){
					cuvex.nfc.tag.from_nfc_type = 1;
					return SUCCESS;
				}
				else if(strstr((char *) bufSentence.buffer, (char *) "Plain_text") != 0x00){
					cuvex.nfc.tag.from_nfc_type = 2;
					return SUCCESS;
				}
				else{
					cuvex.nfc.tag.from_nfc_type = 0;
				}
			}
			break;

		case 2:	//Record 2
			if((cuvex.nfc.tag.from_nfc_type == 1) || (cuvex.nfc.tag.from_nfc_type == 2))
			{
				if((bufLanguageCode.length == 2) && (bufLanguageCode.buffer[0] == 'e') && (bufLanguageCode.buffer[1] == 'n'))
				{
					switch(cuvex.nfc.tag.from_nfc_type)
					{
					case 0:
					default:
						break;

					case 1:	//seed bip-39
						int aux = 0, j = 0;

						for(int i=0; i<bufSentence.length;i++)
						{
							if(aux == 0){
								if((bufSentence.buffer[i] == '\"') && (bufSentence.buffer[i+1] == '-') && (bufSentence.buffer[i+2] == '\"')){
									aux = 1;
									i = i+2;
									j = 0;
								}
								else{
									if(bufSentence.buffer[i] != '\"'){
										cuvex.nfc.tag.from_nfc_seed[j++] = bufSentence.buffer[i];
									}
								}
							}
							else if(aux == 1){
								if((bufSentence.buffer[i] == '\"') && (bufSentence.buffer[i+1] == '-') && (bufSentence.buffer[i+2] == '\"')){
									aux = 2;
									i = i+2;
									j = 0;
								}
								else{
									if(bufSentence.buffer[i] != '\"'){
										cuvex.nfc.tag.from_nfc_private_key[j++] = bufSentence.buffer[i];
									}
								}
							}
							else if(aux == 2){
								if(bufSentence.buffer[i] != '\"'){
									cuvex.nfc.tag.from_nfc_public_key[j++] = bufSentence.buffer[i];
								}
							}
						}
						break;

					case 2: //plain-text
						memset(cuvex.nfc.tag.from_nfc_plain_text, 0x00, sizeof(cuvex.nfc.tag.from_nfc_plain_text));
						memcpy(cuvex.nfc.tag.from_nfc_plain_text, bufSentence.buffer, bufSentence.length);
						break;
					}

					return SUCCESS;
				}
			}
			break;

		case 3:	//Record 3
			if(cuvex.nfc.tag.from_nfc_type == 1)
			{
				if((bufLanguageCode.length == 2) && (bufLanguageCode.buffer[0] == 'e') && (bufLanguageCode.buffer[1] == 'n'))
				{
					memset(cuvex.nfc.tag.from_nfc_pass_deriv, 0x00, sizeof(cuvex.nfc.tag.from_nfc_pass_deriv));
					memcpy(cuvex.nfc.tag.from_nfc_pass_deriv, bufSentence.buffer, bufSentence.length);

					return SUCCESS;
				}
			}
			break;
		}
	}

	return ERROR;
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
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int getVersionT2T_NTAG216(rfalNfcDevice *nfcDevice)
{
	uint8_t getVersionCmd = 0x60;
	uint8_t response[10] = {0};
	uint16_t responseLen = 0;

	if(rfalTransceiveBlockingTxRx(&getVersionCmd, 1, response, sizeof(response), &responseLen, RFAL_TXRX_FLAGS_DEFAULT, RFAL_FWT_NONE) == ERR_NONE)
	{
		if((response[0] == 0x00) && (response[1] == 0x04) && (response[2] == 0x04) && (response[3] == 0x02) && (response[4] == 0x01) && (response[5] == 0x00) && (response[6] == 0x13) && (response[7] == 0x03)){
			return SUCCESS;
		}
	}

	return ERROR;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
int getVersionT4T_8K(ndefContext *ctx, ndefInfo *info)
{
	if(ctx->cc.t4t.fileSize >= 7000){
		return SUCCESS;
	}

	return ERROR;
}

