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
		{ 1, Rect(2 + 32*0 + 1, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 2, Rect(2 + 32*1 + 0, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 3, Rect(2 + 32*2 + 0, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 4, Rect(2 + 32*3 + 0, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 5, Rect(2 + 32*4 + 0, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 6, Rect(2 + 32*5 - 1, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 7, Rect(2 + 32*6 - 1, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 8, Rect(2 + 32*7 - 2, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 9, Rect(2 + 32*8 - 2, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{10, Rect(2 + 32*9 - 3, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},

		{11, Rect(18 + 32*0 + 1, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{12, Rect(18 + 32*1 + 0, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{13, Rect(18 + 32*2 + 0, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{14, Rect(18 + 32*3 + 0, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{15, Rect(18 + 32*4 - 1, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{16, Rect(18 + 32*5 - 1, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{17, Rect(18 + 32*6 - 2, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{18, Rect(18 + 32*7 - 2, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{19, Rect(18 + 32*8 - 3, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},

		{20, Rect(50 + 32*0 + 0, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{21, Rect(50 + 32*1 + 0, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{22, Rect(50 + 32*2 + 0, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{23, Rect(50 + 32*3 - 1, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{24, Rect(50 + 32*4 - 1, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{25, Rect(50 + 32*5 - 2, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{26, Rect(50 + 32*6 - 2, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},

		{27, Rect(82, 93, 156, 25), BITMAP_KEYBOARDALPHANUM_PRESSED_SPACE_ID}
};

/*
 * Definition of callback zones for special keys, for custom keyboard 1
 */
static Keyboard::CallbackArea callbackAreas_layout_1[3] =
{
		{Rect(3, 65, 38, 26), 0, BITMAP_KEYBOARDALPHANUM_PRESSED_SHIFT_1_ID},     //Shift key
		{Rect(279, 65, 38, 26), 0, BITMAP_KEYBOARDALPHANUM_PRESSED_DELETE_1_ID},  //Delete key
		{Rect(3, 93, 76, 26), 0, BITMAP_KEYBOARDALPHANUM_PRESSED_MODE_ID},        //Mode key
};

/*
 * Layout for custom keyboard 1
 */
static const Keyboard::Layout layout_1 =
{
		BITMAP_KEYBOARDALPHANUM_BACKGROUND_1_ID,
		keyArray_layout_1,
		27,
		callbackAreas_layout_1,
		3,
		Rect(0, 0, 0, 0),
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
		{ 1, Rect(2 + 32*0 + 1, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 2, Rect(2 + 32*1 + 1, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 3, Rect(2 + 32*2 + 0, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 4, Rect(2 + 32*3 + 0, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 5, Rect(2 + 32*4 + 0, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 6, Rect(2 + 32*5 - 1, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 7, Rect(2 + 32*6 - 1, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 8, Rect(2 + 32*7 - 1, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 9, Rect(2 + 32*8 - 2, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{10, Rect(2 + 32*9 - 3, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},

		{11, Rect(2 + 32*0 + 1, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{12, Rect(2 + 32*1 + 1, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{13, Rect(2 + 32*2 + 0, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{14, Rect(2 + 32*3 + 0, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{15, Rect(2 + 32*4 - 1, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{16, Rect(2 + 32*5 - 1, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{17, Rect(2 + 32*6 - 1, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{18, Rect(2 + 32*7 - 2, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{19, Rect(2 + 32*8 - 2, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{20, Rect(2 + 32*9 - 2, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},

		{21, Rect(77 + 32*0 + 1, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{22, Rect(77 + 32*1 + 3, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{23, Rect(77 + 32*2 + 6, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{24, Rect(77 + 32*3 + 7, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{25, Rect(77 + 32*4 + 9, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},

		{26, Rect(82, 93, 156, 25), BITMAP_KEYBOARDALPHANUM_PRESSED_SPACE_ID}
};


/*
 * Definition of callback zones for special keys, for custom keyboard 2
 */
static Keyboard::CallbackArea callbackAreas_layout_2[3] =
{
		{Rect(3, 65, 61, 27), 0, BITMAP_KEYBOARDALPHANUM_PRESSED_SHIFT_2_ID},     //Shift key
		{Rect(258, 64, 60, 27), 0, BITMAP_KEYBOARDALPHANUM_PRESSED_DELETE_2_ID},  //Delete key
		{Rect(3, 93, 76, 26), 0, BITMAP_KEYBOARDALPHANUM_PRESSED_MODE_ID},     	  //Mode key
};

/*
 * Layout for custom keyboard 2
 */
static const Keyboard::Layout layout_2 =
{
		BITMAP_KEYBOARDALPHANUM_BACKGROUND_2_ID,
		keyArray_layout_2,
		26,
		callbackAreas_layout_2,
		3,
		Rect(0, 0, 0, 0),
		TypedText(T_ENTEREDTEXT),
		0x00FF00,
		Typography::KEYBOARD,
		0
};

/************************************************************************************************************************************************************************************************************************
 **************************************************************************************** LAYOUT 3 - Keyboard num *******************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/

/*
 * Array specifying the keys used on custom keyboard 3
 */
static const Keyboard::Key keyArray_layout_3[10] =
{
		{ 1, Rect(2 + 0*(104 + 2), 2, 104, 28),  BITMAP_KEYBOARDNUM_PRESSED_ID},
		{ 2, Rect(2 + 1*(104 + 2), 2, 104, 28),  BITMAP_KEYBOARDNUM_PRESSED_ID},
		{ 3, Rect(2 + 2*(104 + 2), 2, 104, 28),  BITMAP_KEYBOARDNUM_PRESSED_ID},
		{ 4, Rect(2 + 0*(104 + 2), 31, 104, 28), BITMAP_KEYBOARDNUM_PRESSED_ID},
		{ 5, Rect(2 + 1*(104 + 2), 31, 104, 28), BITMAP_KEYBOARDNUM_PRESSED_ID},
		{ 6, Rect(2 + 2*(104 + 2), 31, 104, 28), BITMAP_KEYBOARDNUM_PRESSED_ID},
		{ 7, Rect(2 + 0*(104 + 2), 60, 104, 28), BITMAP_KEYBOARDNUM_PRESSED_ID},
		{ 8, Rect(2 + 1*(104 + 2), 60, 104, 28), BITMAP_KEYBOARDNUM_PRESSED_ID},
		{ 9, Rect(2 + 2*(104 + 2), 60, 104, 28), BITMAP_KEYBOARDNUM_PRESSED_ID},
		{10, Rect(2 + 1*(104 + 2), 90, 104, 28), BITMAP_KEYBOARDNUM_PRESSED_ID}
};


/*
 * Definition of callback zones for special keys, for custom keyboard 3
 */
static Keyboard::CallbackArea callbackAreas_layout_3[1] =
{
		{Rect(1, 91, 104, 28), 0, BITMAP_KEYBOARDNUM_DELETE_PRESSED_ID}  //Delete key
};

/*
 * Layout for custom keyboard 3
 */
static const Keyboard::Layout layout_3 =
{
		BITMAP_KEYBOARDNUM_BACKGROUND_ID,
		keyArray_layout_3,
		10,
		callbackAreas_layout_3,
		1,
		Rect(0, 0, 0, 0),
		TypedText(T_ENTEREDTEXT),
		0x0000FF,
		Typography::KEYBOARD,
		0
};

/************************************************************************************************************************************************************************************************************************
 *************************************************************************************** LAYOUT 4 - Keyboard upper ******************************************************************************************************
 ************************************************************************************************************************************************************************************************************************/

/*
 * Array specifying the keys used on custom keyboard 4
 */
static const Keyboard::Key keyArray_layout_4[26] =
{
		{ 1, Rect(2 + 32*0 + 1, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 2, Rect(2 + 32*1 + 0, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 3, Rect(2 + 32*2 + 0, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 4, Rect(2 + 32*3 + 0, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 5, Rect(2 + 32*4 + 0, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 6, Rect(2 + 32*5 - 1, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 7, Rect(2 + 32*6 - 1, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 8, Rect(2 + 32*7 - 2, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{ 9, Rect(2 + 32*8 - 2, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{10, Rect(2 + 32*9 - 3, 3, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},

		{11, Rect(18 + 32*0 + 1, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{12, Rect(18 + 32*1 + 0, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{13, Rect(18 + 32*2 + 0, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{14, Rect(18 + 32*3 + 0, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{15, Rect(18 + 32*4 - 1, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{16, Rect(18 + 32*5 - 1, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{17, Rect(18 + 32*6 - 2, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{18, Rect(18 + 32*7 - 2, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{19, Rect(18 + 32*8 - 3, 33, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},

		{20, Rect(50 + 32*0 + 0, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{21, Rect(50 + 32*1 + 0, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{22, Rect(50 + 32*2 + 0, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{23, Rect(50 + 32*3 - 1, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{24, Rect(50 + 32*4 - 1, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{25, Rect(50 + 32*5 - 2, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID},
		{26, Rect(50 + 32*6 - 2, 63, 29, 28), BITMAP_KEYBOARDALPHANUM_PRESSED_NORMAL_ID}
};

/*
 * Definition of callback zones for special keys, for custom keyboard 4
 */
static Keyboard::CallbackArea callbackAreas_layout_4[3] =
{
		{Rect(279, 65, 38, 26), 0, BITMAP_KEYBOARDALPHANUM_PRESSED_DELETE_1_ID},  //Delete key
};

/*
 * Layout for custom keyboard 4
 */
static const Keyboard::Layout layout_4 =
{
		BITMAP_KEYBOARDALPHANUM_BACKGROUND_1_ID,
		keyArray_layout_4,
		26,
		callbackAreas_layout_4,
		1,
		Rect(0, 0, 0, 0),
		TypedText(T_ENTEREDTEXT),
		0xFF0000,
		Typography::KEYBOARD,
		0
};

#endif
