/**
 ******************************************************************************
 * @file           : mainTask.h
 * @brief          : Header for mainTask.c file.
 *                   This file contains the common defines of the mainTask.
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
void saveDeviceAlias(void);
void eraseSignature(void);
void getCuvexVersions(void);

/********************************************************************** Extern's ***********************************************************************/
extern osMessageQueueId_t guiToMainQueueHandle;	//RX --> guiTask to mainTask
extern osMessageQueueId_t mainToGuiQueueHandle;	//TX --> mainTask to guiTask
extern CRYP_HandleTypeDef hcryp;
extern struct cuvex cuvex;

#endif
