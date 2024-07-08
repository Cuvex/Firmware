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

#ifndef MODEL_HPP
#define MODEL_HPP

#include "main.h"
#include "cmsis_os2.h"

extern "C"
{
extern osMessageQueueId_t guiToMainQueueHandle;
extern osMessageQueueId_t mainToGuiQueueHandle;
}

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

	void changeScreen(uint16_t screen);
	void changeStateNfc(uint16_t state);
	void changeFlash(uint16_t state);

protected:
	ModelListener* modelListener;

};

#endif // MODEL_HPP
