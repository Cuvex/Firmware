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

#ifndef QR_CODE_HPP
#define QR_CODE_HPP

#include <touchgfx/hal/Types.hpp>
#include "qrcode.h"

/**
* @class QRCode
*
* @brief An interface for getting the value of a qr code at a particular x,y position
*
*        This implementation generates random values for the different x,y coordinates.
*        A real qr code will probably save the qr code values in an array like structure and report these instead.
*/
class QR
{
public:
	QR(const char* text, uint8_t version);
	~QR();
    /**
     * @fn bool QRCode::at(uint16_t x, uint16_t y);
     *
     * @brief Get the qr code value at a particular coordinate
     *
     * @param x x coordinate
     * @param y y coordinate
     *
     * @return The value of the qr code at the supplied coordinate
     */
    bool at(uint16_t x, uint16_t y) const;

    /**
     * @fn uint16_t QRCode::getWidth();
     *
     * @brief Get the width of the qr code
     *
     * @return The width
     */
    uint16_t getWidth() const;

    /**
     * @fn uint16_t QRCode::getHeight();
     *
     * @brief Get the height of the qr code
     *
     * @return The height
     */
    uint16_t getHeight() const;
    QRCode   *qrcode;
    uint8_t  *qrcodeData;
};

#endif
