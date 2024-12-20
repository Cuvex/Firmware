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

#ifndef KEYBOARD_LAYOUT
#define KEYBOARD_LAYOUT

#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/hal/Types.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include "BitmapDatabase.hpp"

using namespace touchgfx;

/************************************************************************************************************************************************************************************************************************
 ******************************************************************************* LAYOUT 1 - Keyboard alpha/num (alpha) **************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/

/*
 * Array specifying the keys used on custom keyboard 1
 */
static const Keyboard::Key keyArray_layout_1[27] =
{
		{ 1, Rect(6, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 2, Rect(37, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 3, Rect(68, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 4, Rect(99, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 5, Rect(130, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 6, Rect(161, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 7, Rect(192, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 8, Rect(223, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 9, Rect(254, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{10, Rect(285, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{11, Rect(25, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{12, Rect(55, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{13, Rect(85, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{14, Rect(115, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{15, Rect(145, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{16, Rect(175, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{17, Rect(205, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{18, Rect(235, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{19, Rect(265, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{20, Rect(55, 	64, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{21, Rect(85, 	64, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{22, Rect(115, 	64, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{23, Rect(145, 	64, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{24, Rect(175, 	64, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{25, Rect(205, 	64, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{26, Rect(235, 	64, 30,	28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{27, Rect(85, 	94, 150, 27), BITMAP___KEYBOARDALPHANUM_SPACE_PRESSED_ID}
};

/*
 * Definition of callback zones for special keys, for custom keyboard 1
 */
static Keyboard::CallbackArea callbackAreas_layout_1[3] =
{
		{Rect(5, 64, 44, 28), 0, BITMAP___KEYBOARDALPHANUM_SHIFT_1_PRESSED_ID},     //Shift key
		{Rect(271, 64, 44, 28), 0, BITMAP___KEYBOARDALPHANUM_DELETE_1_PRESSED_ID},  //Delete key
		{Rect(5, 94, 80, 27), 0, BITMAP___KEYBOARDALPHANUM_MODE_PRESSED_ID},        //Mode key
};

/*
 * Layout for custom keyboard 1
 */
static const Keyboard::Layout layout_1 =
{
		UINT16_MAX,
		keyArray_layout_1,
		27,
		callbackAreas_layout_1,
		3,
		Rect(0,0,0,0),
		TypedText(T_ENTEREDTEXT),
		0xFF0000,
		Typography::KEYBOARD,
		0
};

/************************************************************************************************************************************************************************************************************************
 ***************************************************************************** LAYOUT 2 - Keyboard alpha/num (num+simb) *************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/

/*
 * Array specifying the keys used on custom keyboard 2
 */
static const Keyboard::Key keyArray_layout_2[26] =
{
		{ 1, Rect(6, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 2, Rect(37, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 3, Rect(68, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 4, Rect(99, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 5, Rect(130, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 6, Rect(161, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 7, Rect(192, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 8, Rect(223, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 9, Rect(254, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{10, Rect(285, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{11, Rect(6, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{12, Rect(37, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{13, Rect(68, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{14, Rect(99, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{15, Rect(130, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{16, Rect(161, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{17, Rect(192, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{18, Rect(223, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{19, Rect(254, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{20, Rect(285, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{21, Rect(85, 	64, 29, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{22, Rect(115, 	64, 29, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{23, Rect(145, 	64, 29, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{24, Rect(175, 	64, 29, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{25, Rect(205, 	64, 29, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{26, Rect(85, 	94, 150, 27), BITMAP___KEYBOARDALPHANUM_SPACE_PRESSED_ID}
};

/*
 * Definition of callback zones for special keys, for custom keyboard 2
 */
static Keyboard::CallbackArea callbackAreas_layout_2[3] =
{
		{Rect(6, 64, 61, 28), 0, BITMAP___KEYBOARDALPHANUM_SHIFT_2_PRESSED_ID},     //Shift key
		{Rect(254, 64, 61, 28), 0, BITMAP___KEYBOARDALPHANUM_DELETE_2_PRESSED_ID},  //Delete key
		{Rect(5, 94, 80, 27), 0, BITMAP___KEYBOARDALPHANUM_MODE_PRESSED_ID},        //Mode key
};

/*
 * Layout for custom keyboard 2
 */
static const Keyboard::Layout layout_2 =
{
		UINT16_MAX,
		keyArray_layout_2,
		26,
		callbackAreas_layout_2,
		3,
		Rect(0,0,0,0),
		TypedText(T_ENTEREDTEXT),
		0x00FF00,
		Typography::KEYBOARD,
		0
};

/************************************************************************************************************************************************************************************************************************
 ******************************************************************************* LAYOUT 3 - Keyboard alpha/num (alpha -> lower) *****************************************************************************************
 ************************************************************************************************************************************************************************************************************************/

/*
 * Array specifying the keys used on custom keyboard 3
 */
static const Keyboard::Key keyArray_layout_3[26] =
{
		{ 1, Rect(6, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 2, Rect(37, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 3, Rect(68, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 4, Rect(99, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 5, Rect(130, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 6, Rect(161, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 7, Rect(192, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 8, Rect(223, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{ 9, Rect(254, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{10, Rect(285, 	4, 	30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{11, Rect(25, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{12, Rect(55, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{13, Rect(85, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{14, Rect(115, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{15, Rect(145, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{16, Rect(175, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{17, Rect(205, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{18, Rect(235, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{19, Rect(265, 	34, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{20, Rect(55, 	64, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{21, Rect(85, 	64, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{22, Rect(115, 	64, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{23, Rect(145, 	64, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{24, Rect(175, 	64, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{25, Rect(205, 	64, 30, 28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID},
		{26, Rect(235, 	64, 30,	28), BITMAP___KEYBOARDALPHANUM_KEY_PRESSED_ID}
};

/*
 * Definition of callback zones for special keys, for custom keyboard 3
 */
static Keyboard::CallbackArea callbackAreas_layout_3[3] =
{
		{Rect(271, 64, 44, 28), 0, BITMAP___KEYBOARDALPHANUM_DELETE_1_PRESSED_ID},  //Delete key
};

/*
 * Layout for custom keyboard 3
 */
static const Keyboard::Layout layout_3 =
{
		UINT16_MAX,
		keyArray_layout_3,
		26,
		callbackAreas_layout_3,
		1,
		Rect(0,0,0,0),
		TypedText(T_ENTEREDTEXT),
		0xFF0000,
		Typography::KEYBOARD,
		0
};

/************************************************************************************************************************************************************************************************************************
 **************************************************************************************** LAYOUT 4 - Keyboard num *******************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/

/*
 * Array specifying the keys used on custom keyboard 4
 */
static const Keyboard::Key keyArray_layout_4[10] =
{
		{ 1, Rect(2,	2, 	105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID},
		{ 2, Rect(107, 	2, 	105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID},
		{ 3, Rect(212, 	2, 	105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID},
		{ 4, Rect(2, 	31, 105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID},
		{ 5, Rect(107, 	31, 105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID},
		{ 6, Rect(212, 	31, 105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID},
		{ 7, Rect(2, 	60, 105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID},
		{ 8, Rect(107, 	60, 105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID},
		{ 9, Rect(212, 	60, 105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID},
		{10, Rect(107, 	89, 105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID}
};

/*
 * Definition of callback zones for special keys, for custom keyboard 4
 */
static Keyboard::CallbackArea callbackAreas_layout_4[1] =
{
		{Rect(2, 88, 105, 29), 0, BITMAP_KEYBOARDNUM_DELETE_PRESSED_ID}  //Delete key
};

/*
 * Layout for custom keyboard 4
 */
static const Keyboard::Layout layout_4 =
{
		UINT16_MAX,
		keyArray_layout_4,
		10,
		callbackAreas_layout_4,
		1,
		Rect(0, 0, 0, 0),
		TypedText(T_ENTEREDTEXT),
		0x0000FF,
		Typography::KEYBOARD,
		0
};

/************************************************************************************************************************************************************************************************************************
 **************************************************************************************** LAYOUT 5 - Keyboard num short *************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/

/*
 * Array specifying the keys used on custom keyboard 5
 */
static const Keyboard::Key keyArray_layout_5[6] =
{
		{ 1, Rect(2, 	1, 	105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID},
		{ 2, Rect(107, 	1, 	105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID},
		{ 3, Rect(212, 	1, 	105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID},
		{ 4, Rect(2, 	30, 105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID},
		{ 5, Rect(107, 	30, 105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID},
		{ 6, Rect(212, 	30, 105, 29), BITMAP_KEYBOARDNUM_KEY_PRESSED_ID}
};

/*
 * Layout for custom keyboard 5
 */
static const Keyboard::Layout layout_5 =
{
		UINT16_MAX,
		keyArray_layout_5,
		6,
		nullptr,
		0,
		Rect(0, 0, 0, 0),
		TypedText(T_ENTEREDTEXT),
		0x0000FF,
		Typography::KEYBOARD,
		0
};

#endif
