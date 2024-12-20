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

#ifndef BOXDICE_HPP
#define BOXDICE_HPP

#include <gui_generated/containers/boxDiceBase.hpp>

class boxDice : public boxDiceBase
{
public:
    boxDice();
    virtual ~boxDice() {}

    virtual void initialize();
    virtual void btnDicePressed();
    virtual void setId(uint8_t id);
    virtual void setBoxColour(uint8_t red, uint8_t green, uint8_t blue);
    virtual void setHighlightColour(uint8_t red, uint8_t green, uint8_t blue);
    virtual void setTextColour(uint8_t red, uint8_t green, uint8_t blue);
    virtual void setHighlight();
    virtual void resetHighlight();
    virtual void setValue(uint8_t value);
protected:
    uint8_t dice_id;
};

#endif // BOXDICE_HPP
