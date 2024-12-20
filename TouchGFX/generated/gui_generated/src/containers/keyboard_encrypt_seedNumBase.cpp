/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/keyboard_encrypt_seedNumBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

keyboard_encrypt_seedNumBase::keyboard_encrypt_seedNumBase()
{
    setWidth(320);
    setHeight(123);
    keyboard_background.setPosition(0, 0, 320, 123);
    keyboard_background.setColor(touchgfx::Color::getColorFromRGB(237, 237, 237));
    add(keyboard_background);

    key_hide.setXY(212, 89);
    key_hide.setBitmap(touchgfx::Bitmap(BITMAP_KEYBOARDNUM_HIDE_1_RELEASED_ID));
    add(key_hide);

    key_delete.setXY(2, 89);
    key_delete.setBitmap(touchgfx::Bitmap(BITMAP_KEYBOARDNUM_DELETE_RELEASED_ID));
    add(key_delete);

    key_1.setXY(2, 2);
    key_1.setBitmap(touchgfx::Bitmap(BITMAP_KEYBOARDNUM_KEY_RELEASED_ID));
    add(key_1);

    key_2.setXY(107, 2);
    key_2.setBitmap(touchgfx::Bitmap(BITMAP_KEYBOARDNUM_KEY_RELEASED_ID));
    add(key_2);

    key_3.setXY(212, 2);
    key_3.setBitmap(touchgfx::Bitmap(BITMAP_KEYBOARDNUM_KEY_RELEASED_ID));
    add(key_3);

    key_4.setXY(2, 31);
    key_4.setBitmap(touchgfx::Bitmap(BITMAP_KEYBOARDNUM_KEY_RELEASED_ID));
    add(key_4);

    key_5.setXY(107, 31);
    key_5.setBitmap(touchgfx::Bitmap(BITMAP_KEYBOARDNUM_KEY_RELEASED_ID));
    add(key_5);

    key_6.setXY(212, 31);
    key_6.setBitmap(touchgfx::Bitmap(BITMAP_KEYBOARDNUM_KEY_RELEASED_ID));
    add(key_6);

    key_7.setXY(2, 60);
    key_7.setBitmap(touchgfx::Bitmap(BITMAP_KEYBOARDNUM_KEY_RELEASED_ID));
    add(key_7);

    key_8.setXY(107, 60);
    key_8.setBitmap(touchgfx::Bitmap(BITMAP_KEYBOARDNUM_KEY_RELEASED_ID));
    add(key_8);

    key_9.setXY(212, 60);
    key_9.setBitmap(touchgfx::Bitmap(BITMAP_KEYBOARDNUM_KEY_RELEASED_ID));
    add(key_9);

    key_10.setXY(107, 89);
    key_10.setBitmap(touchgfx::Bitmap(BITMAP_KEYBOARDNUM_KEY_RELEASED_ID));
    add(key_10);
}

keyboard_encrypt_seedNumBase::~keyboard_encrypt_seedNumBase()
{

}

void keyboard_encrypt_seedNumBase::initialize()
{

}
