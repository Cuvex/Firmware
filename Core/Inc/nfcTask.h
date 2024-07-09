/**
 ******************************************************************************
 * @file           : nfcTask.h
 * @brief          : Header for nfcTask.c file.
 *                   This file contains the common defines of the nfcTask.
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

#ifndef INC_NFCTASK_H_
#define INC_NFCTASK_H_

/********************************************************************** Include's **********************************************************************/
#include "stm32u5xx_hal.h"
#include "main.h"
#include "rfal_nfc.h"
#include "ndef_poller.h"
#include "ndef_types.h"

/********************************************************************* Functions's *********************************************************************/
void nfc_Task(void const * argument);
void enableNFC(void);
void disableNFC(void);
bool nfcInitialize(void);
void nfcCycle(void);
int nfcActionNdef(rfalNfcDevice *pNfcDevice);
int stateMachineTagActionT2T_NTAG216(rfalNfcDevice *pNfcDevice, ndefContext *ndefCtx, ndefInfo *info);
int stateMachineTagActionT4T_8K(rfalNfcDevice *pNfcDevice, ndefContext *ndefCtx, ndefInfo *info);
int ndefMessageGetInfoT2T_NTAG216(const ndefMessage* message);
int ndefRecordGetInfoT2T_NTAG216(const ndefRecord* record);
int ndefMessageGetInfoT4T_8K(const ndefMessage* message);
int ndefRecordGetInfoT4T_8K(const ndefRecord* record);
int ndefMessageGetInfo_fromNFC(const ndefMessage* message);
int ndefRecordGetInfo_fromNFC(const ndefRecord* record);
int getVersionT2T_NTAG216(rfalNfcDevice *nfcDevice);
int getVersionT4T_8K(ndefContext *ctx, ndefInfo *info);

/********************************************************************** Defines's **********************************************************************/
#define NFC_NOINIT         		0
#define NFC_START_DISCOVERY		1
#define NFC_DISCOVERY     		2

/********************************************************************* Variable's **********************************************************************/
static rfalNfcDiscoverParam discParam;
static uint8_t state = NFC_NOINIT;

/********************************************************************* Extern's **********************************************************************/
extern struct cuvex cuvex;

#endif
