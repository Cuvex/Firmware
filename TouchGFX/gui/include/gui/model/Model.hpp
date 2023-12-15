#ifndef MODEL_HPP
#define MODEL_HPP

/********** Custom includes ************/
#include "main.h"
#include "cmsis_os2.h"

extern "C"
{
extern osMessageQueueId_t guiToMainQueueHandle;
extern osMessageQueueId_t mainToGuiQueueHandle;
}
/***************************************/

class ModelListener;

class Model
{
public:
	Model();

	void bind(ModelListener* listener)
	{
		modelListener = listener;
	}

	void tick();

	/*********** Custom public *************/
	void changeScreen(uint16_t screen);
	void changeStateNfc(uint16_t state);
	void changeFlash(uint16_t state);
	/***************************************/

protected:
	ModelListener* modelListener;

};

#endif // MODEL_HPP
