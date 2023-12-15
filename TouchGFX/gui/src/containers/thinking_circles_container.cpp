#include <gui/containers/thinking_circles_container.hpp>
#include <touchgfx/Color.hpp>

/*******************************/
extern struct cuvex cuvex;
/*******************************/

thinking_circles_container::thinking_circles_container()
{

}

void thinking_circles_container::initialize()
{
    thinking_circles_containerBase::initialize();

	/*** Configuración de elementos de pantalla en función al modo (oscuro/claro) ***/
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

	/*** Actualización de la pantalla ***/
	circle1_small.invalidate();
	circle2_small.invalidate();
	circle3_small.invalidate();
	circle1_big.invalidate();
	circle2_big.invalidate();
	circle3_big.invalidate();
}
