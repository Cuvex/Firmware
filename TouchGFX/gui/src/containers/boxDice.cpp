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

#include <gui/containers/boxDice.hpp>
#include <touchgfx/Color.hpp>
#include "main.h"

extern struct cuvex cuvex;

boxDice::boxDice(): dice_id(0)
{

}

void boxDice::initialize()
{
	boxDiceBase::initialize();
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
void boxDice::btnDicePressed()
{
	if((dice_id >= DICE_COLOUR_1) && (dice_id <= DICE_COLOUR_8))
	{
		if((cuvex.wallet.dice_selected[0] != dice_id) && (cuvex.wallet.dice_selected[1] != dice_id) && (cuvex.wallet.dice_selected[2] != dice_id) && (cuvex.wallet.dice_selected[3] != dice_id))	//Press detected and dice not selected --> Then try select
		{
			if(cuvex.wallet.dice_selected[0] == 0){
				cuvex.wallet.dice_selected[0] = dice_id;
				Unicode::snprintf(text_diceBuffer, TEXT_DICE_SIZE, "1");
				text_dice.setVisible(true);
			}
			else if(cuvex.wallet.dice_selected[1] == 0){
				cuvex.wallet.dice_selected[1] = dice_id;
				Unicode::snprintf(text_diceBuffer, TEXT_DICE_SIZE, "2");
				text_dice.setVisible(true);
			}
			else if(cuvex.wallet.dice_selected[2] == 0){
				cuvex.wallet.dice_selected[2] = dice_id;
				Unicode::snprintf(text_diceBuffer, TEXT_DICE_SIZE, "3");
				text_dice.setVisible(true);
			}
			else if(cuvex.wallet.dice_selected[3] == 0){
				cuvex.wallet.dice_selected[3] = dice_id;
				Unicode::snprintf(text_diceBuffer, TEXT_DICE_SIZE, "4");
				text_dice.setVisible(true);
			}
			else{
				Unicode::snprintf(text_diceBuffer, TEXT_DICE_SIZE, "---");
				text_dice.setVisible(false);
			}
		}
		else	//Press detected and dice selected --> Then deselect
		{
			if(cuvex.wallet.dice_selected[0] == dice_id){
				cuvex.wallet.dice_selected[0] = 0;
			}
			else if(cuvex.wallet.dice_selected[1] == dice_id){
				cuvex.wallet.dice_selected[1] = 0;
			}
			else if(cuvex.wallet.dice_selected[2] == dice_id){
				cuvex.wallet.dice_selected[2] = 0;
			}
			else if(cuvex.wallet.dice_selected[3] == dice_id){
				cuvex.wallet.dice_selected[3] = 0;
			}

			Unicode::snprintf(text_diceBuffer, TEXT_DICE_SIZE, "---");
			text_dice.setVisible(false);
		}
	}
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
void boxDice::setId(uint8_t id)
{
	dice_id = id;
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void boxDice::setBoxColour(uint8_t red, uint8_t green, uint8_t blue)
{
	box_1.setColor(touchgfx::Color::getColorFromRGB(red,green,blue));
	box_2.setColor(touchgfx::Color::getColorFromRGB(red,green,blue));
	circle_1Painter.setColor(touchgfx::Color::getColorFromRGB(red,green,blue));
	circle_2Painter.setColor(touchgfx::Color::getColorFromRGB(red,green,blue));
	circle_3Painter.setColor(touchgfx::Color::getColorFromRGB(red,green,blue));
	circle_4Painter.setColor(touchgfx::Color::getColorFromRGB(red,green,blue));
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void boxDice::setHighlightColour(uint8_t red, uint8_t green, uint8_t blue)
{
	boxh_1.setColor(touchgfx::Color::getColorFromRGB(red,green,blue));
	boxh_2.setColor(touchgfx::Color::getColorFromRGB(red,green,blue));
	circleh_1Painter.setColor(touchgfx::Color::getColorFromRGB(red,green,blue));
	circleh_2Painter.setColor(touchgfx::Color::getColorFromRGB(red,green,blue));
	circleh_3Painter.setColor(touchgfx::Color::getColorFromRGB(red,green,blue));
	circleh_4Painter.setColor(touchgfx::Color::getColorFromRGB(red,green,blue));
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void boxDice::setTextColour(uint8_t red, uint8_t green, uint8_t blue)
{
	text_dice.setColor(touchgfx::Color::getColorFromRGB(red,green,blue));
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void boxDice::setHighlight()
{
	highlight.setVisible(true);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void boxDice::resetHighlight()
{
	highlight.setVisible(false);
}

/**************************************************************************************************************************************
 ***** Function 	: N/A
 ***** Description 	: N/A
 ***** Parameters 	: N/A
 ***** Response 	: N/A
 **************************************************************************************************************************************/
void boxDice::setValue(uint8_t value)
{
	if((value >= 1) && (value <= 6)){
		Unicode::snprintf(text_diceBuffer, TEXT_DICE_SIZE, "%d", value);
		text_dice.setVisible(true);
	}
	else
	{
		Unicode::snprintf(text_diceBuffer, TEXT_DICE_SIZE, "---");
		text_dice.setVisible(false);
	}
}
