
#include <gui/widgets/qrcode/QRCode.hpp>
#include <stdlib.h>

QR::QR(const char* text, uint8_t version)
{
	qrcode = new QRCode();
	qrcodeData = (uint8_t*) malloc(qrcode_getBufferSize(version));
	qrcode_initText(qrcode, qrcodeData, version, 0, text);
}

QR::~QR()
{
	free(qrcodeData);
	delete qrcode;
}

bool QR::at(uint16_t x, uint16_t y) const
{
	return qrcode_getModule(qrcode, x, y);
}

uint16_t QR::getWidth() const
{
	return qrcode->size;
}

uint16_t QR::getHeight() const
{
	return qrcode->size;
}
