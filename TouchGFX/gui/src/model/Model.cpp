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
			/*************************************************************************************/
		case MAIN_TO_GUI_NFC_ERROR:
			modelListener->updateStateNfc(MAIN_TO_GUI_NFC_ERROR);
			break;

		case MAIN_TO_GUI_NFC_INITIALIZED:
			modelListener->updateStateNfc(MAIN_TO_GUI_NFC_INITIALIZED);
			break;

		case MAIN_TO_GUI_NFC_TAG_READED:
			modelListener->updateStateNfc(MAIN_TO_GUI_NFC_TAG_READED);
			break;

		case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_1:
			modelListener->updateStateNfc(MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_1);
			break;

		case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_2:
			modelListener->updateStateNfc(MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_2);
			break;

		case MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_4:
			modelListener->updateStateNfc(MAIN_TO_GUI_NFC_TAG_READED_WRITED_FLOW_4);
			break;

			/*************************************************************************************/
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
void Model::changeScreen(uint16_t screen)
{
	uint16_t data = screen;

	if(osMessageQueueGetSpace(guiToMainQueueHandle) > 0){
		osMessageQueuePut(guiToMainQueueHandle, &data, 0, 0);
	}
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void Model::changeStateNfc(uint16_t state)
{
	uint16_t data = state;

	if(osMessageQueueGetSpace(guiToMainQueueHandle) > 0){
		osMessageQueuePut(guiToMainQueueHandle, &data, 0, 0);
	}
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void Model::changeFlash(uint16_t state)
{
	uint16_t data = state;

	if(osMessageQueueGetSpace(guiToMainQueueHandle) > 0){
		osMessageQueuePut(guiToMainQueueHandle, &data, 0, 0);
	}
}





