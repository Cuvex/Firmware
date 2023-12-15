/*
 * mainTask.h
 */

#ifndef INC_MAINTASK_H_
#define INC_MAINTASK_H_

/********************************************************************** Include's **********************************************************************/
#include "stm32u5xx_hal.h"
#include "main.h"

/********************************************************************* Functions's *********************************************************************/
void main_Task(void const * argument);
void processGuiToMainQueue(void);
void stateMachineScreens(void);
void clearNfc_all(void);
void clearNfc_readerFlags(void);
void clearNfc_tagFlags(void);
void clearNfc_tagInfo(void);
void readFlash(uint32_t address, char* data, size_t data_size);
void writeFlash(uint32_t address, char* data, size_t data_size);
void eraseFlash(uint32_t Banks, uint32_t Page, uint32_t NbPages);
void initEEPROM(void);
void loadEEPROM(void);
void editEEPROM(void);
void eraseSignature(void);
void getCuvexVersions(void);

/********************************************************************** Defines's **********************************************************************/

/****************************************************************** Enum's + Struct's ******************************************************************/

/********************************************************************* Variable's **********************************************************************/

/********************************************************************** Extern's ***********************************************************************/
extern osMessageQueueId_t guiToMainQueueHandle;	//RX --> guiTask a mainTask
extern osMessageQueueId_t mainToGuiQueueHandle;	//TX --> mainTask a guiTask
extern CRYP_HandleTypeDef hcryp;
extern struct cuvex cuvex;

#endif
