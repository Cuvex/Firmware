/*
 *****************************************************************************
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

#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
#ifndef SIMULATOR

	uint16_t rcv_data = 0;

	if((osMessageQueueGetCount(mainToGuiQueueHandle) > 0) && (osMessageQueueGet(mainToGuiQueueHandle, &rcv_data, 0, 0) == osOK))
	{
		switch(rcv_data)
		{
		case MAIN_TO_GUI_NFC_ERROR:
			modelListener->updateStateNfc(MAIN_TO_GUI_NFC_ERROR);
			break;

		case MAIN_TO_GUI_NFC_INITIALIZED:
			modelListener->updateStateNfc(MAIN_TO_GUI_NFC_INITIALIZED);
			break;

		case MAIN_TO_GUI_NFC_TAG_READED:
			modelListener->updateStateNfc(MAIN_TO_GUI_NFC_TAG_READED);
			break;

		case MAIN_TO_GUI_NFC_TAG_READED_FROM_NFC:
			modelListener->updateStateNfc(MAIN_TO_GUI_NFC_TAG_READED_FROM_NFC);
			break;

		case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_ENCRYPT:
			modelListener->updateStateNfc(MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_ENCRYPT);
			break;

		case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_ENCRYPT_T4T_8K:
			modelListener->updateStateNfc(MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_ENCRYPT_T4T_8K);
			break;

		case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_CLONE:
			modelListener->updateStateNfc(MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_CLONE);
			break;

		case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_CLONE_T4T_8K:
			modelListener->updateStateNfc(MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_CLONE_T4T_8K);
			break;

		default:
			break;
		}
	}

#endif
}

/*************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************
 *************************************************************************************************************************************************************************************************************/

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void Model::changeScreen(uint16_t screen)
{
	uint16_t data = screen;

	if(osMessageQueueGetSpace(guiToMainQueueHandle) > 0){
		osMessageQueuePut(guiToMainQueueHandle, &data, 0, 0);
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void Model::changeStateNfc(uint16_t state)
{
	uint16_t data = state;

	if(osMessageQueueGetSpace(guiToMainQueueHandle) > 0){
		osMessageQueuePut(guiToMainQueueHandle, &data, 0, 0);
	}
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void Model::changeFlash(uint16_t state)
{
	uint16_t data = state;

	if(osMessageQueueGetSpace(guiToMainQueueHandle) > 0){
		osMessageQueuePut(guiToMainQueueHandle, &data, 0, 0);
	}
}





