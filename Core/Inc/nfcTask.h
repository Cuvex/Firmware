/*
 * nfcTask.h
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
void nfcActionNdef(rfalNfcDevice *pNfcDevice);
void setLedColour(uint8_t colour);

/********************************************************************** Defines's **********************************************************************/
#define NFC_NOINIT         		0	//Not initialized
#define NFC_START_DISCOVERY		1	//Start Discovery
#define NFC_DISCOVERY     		2	//Discovery

/****************************************************************** Enum's + Struct's ******************************************************************/


/********************************************************************* Variable's **********************************************************************/
static rfalNfcDiscoverParam discParam;
static uint8_t state = NFC_NOINIT;

/********************************************************************* Extern's **********************************************************************/
extern struct cuvex cuvex;

#endif
