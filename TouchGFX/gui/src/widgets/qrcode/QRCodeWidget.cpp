
#include <gui/widgets/qrcode/QRCodeWidget.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/lcd/LCD.hpp>

/*******************************/
#include "main.h"
extern struct cuvex cuvex;
/*******************************/

QRCodeWidget::QRCodeWidget() : code(0), scale(1)
{

}

void QRCodeWidget::setQRCode(QR *qrCode)
{
	code = qrCode;
	updateSize();
}

void QRCodeWidget::draw(const touchgfx::Rect& invalidatedArea) const
{
	if(!code){
		return;
	}

	bool result = true;

	for(int y = 0; y < code->getHeight(); y++)
	{
		for(int x = 0; x < code->getWidth(); x++)
		{
			result = code->at(x, y);
			touchgfx::Rect rect(x*scale, y*scale, scale, scale);
			translateRectToAbsolute(rect);

			if(cuvex.info.mode == DARK){
				touchgfx::HAL::lcd().fillRect(rect, result ? 0xFFEDEDED : 0xFF3F3F51, 255);	//Alpha...rojo...verde...azul
			}
			else{
				touchgfx::HAL::lcd().fillRect(rect, result ? 0xFF405CA0 : 0xFFEDEDED, 255);	//Alpha...rojo...verde...azul
			}
		}
	}

	code = nullptr;
}

touchgfx::Rect QRCodeWidget::getSolidRect() const
{
	return touchgfx::Rect(0, 0, getWidth(), getHeight());
}

void QRCodeWidget::setScale(uint8_t s)
{
	scale = s;
	updateSize();
}

void QRCodeWidget::updateSize()
{
	if(code)
	{
		setWidth(code->getWidth() * scale);
		setHeight(code->getHeight() * scale);
	}
}
