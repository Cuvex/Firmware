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

#include <gui/containers/thinking_circles.hpp>
#include <touchgfx/Color.hpp>

extern struct cuvex cuvex;

thinking_circles::thinking_circles()
{

}

void thinking_circles::initialize()
{
    thinking_circlesBase::initialize();

	/*** Setting screen elements based on mode (dark/light) ***/
	if(cuvex.info.mode == DARK)
	{
	    circle1_smallPainter.setColor(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D));
	    circle1_small.setPainter(circle1_smallPainter);
	    circle2_smallPainter.setColor(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D));
	    circle2_small.setPainter(circle2_smallPainter);
	    circle3_smallPainter.setColor(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D));
	    circle3_small.setPainter(circle3_smallPainter);
	    circle1_bigPainter.setColor(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D));
	    circle1_big.setPainter(circle1_bigPainter);
	    circle2_bigPainter.setColor(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D));
	    circle2_big.setPainter(circle2_bigPainter);
	    circle3_bigPainter.setColor(touchgfx::Color::getColorFromRGB(0x6B,0x6B,0x7D));
	    circle3_big.setPainter(circle3_bigPainter);
	}

	/*** Screen update ***/
	circle1_small.invalidate();
	circle2_small.invalidate();
	circle3_small.invalidate();
	circle1_big.invalidate();
	circle2_big.invalidate();
	circle3_big.invalidate();
}
