/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/keyboardBIP39_containerBase.hpp>
#include <images/BitmapDatabase.hpp>

keyboardBIP39_containerBase::keyboardBIP39_containerBase()
{
    setWidth(320);
    setHeight(123);
    keyboardAlphaNum.setXY(0, 0);
    keyboardAlphaNum.setBitmap(touchgfx::Bitmap(BITMAP_KEYBOARDALPHANUM_BACKGROUND_1_ID));
    add(keyboardAlphaNum);
}

keyboardBIP39_containerBase::~keyboardBIP39_containerBase()
{

}

void keyboardBIP39_containerBase::initialize()
{

}
