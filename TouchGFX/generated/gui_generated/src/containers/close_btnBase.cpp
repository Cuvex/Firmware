/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/close_btnBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

close_btnBase::close_btnBase() :
    flexButtonCallback(this, &close_btnBase::flexButtonCallbackHandler)
{
    setWidth(320);
    setHeight(240);
    cross_button.setBoxWithBorderPosition(0, 0, 34, 34);
    cross_button.setBorderSize(0);
    cross_button.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(237, 237, 237), touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0));
    cross_button.setIconBitmaps(Bitmap(BITMAP_CERRAR_ID), Bitmap(BITMAP_CERRAR_DARK_ID));
    cross_button.setIconXY(5, 5);
    cross_button.setAction(flexButtonCallback);
    cross_button.setPosition(286, 0, 34, 34);
    add(cross_button);

    confirm_close_window.setPosition(0, 0, 320, 240);
    confirm_close_window.setVisible(false);
    background.setPosition(0, 0, 320, 240);
    background.setColor(touchgfx::Color::getColorFromRGB(237, 237, 237));
    confirm_close_window.add(background);

    image.setXY(122, 50);
    image.setBitmap(touchgfx::Bitmap(BITMAP_GRAFISMO_PROCESO_ERROR_CUVEX_ID));
    confirm_close_window.add(image);

    textArea.setXY(52, 140);
    textArea.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    textArea.setLinespacing(0);
    textArea.setTypedText(touchgfx::TypedText(T_CONTAINER_CLOSE_TEXT_INFO));
    confirm_close_window.add(textArea);

    cancel_button.setBoxWithBorderPosition(0, 0, 159, 30);
    cancel_button.setBorderSize(0);
    cancel_button.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(64, 92, 160), touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0));
    cancel_button.setText(TypedText(T_CONTAINER_CLOSE_BTN_CANCEL));
    cancel_button.setTextPosition(0, 5, 159, 30);
    cancel_button.setTextColors(touchgfx::Color::getColorFromRGB(237, 237, 237), touchgfx::Color::getColorFromRGB(237, 237, 237));
    cancel_button.setAction(flexButtonCallback);
    cancel_button.setPosition(0, 210, 159, 30);
    confirm_close_window.add(cancel_button);

    confirm_button.setBoxWithBorderPosition(0, 0, 159, 30);
    confirm_button.setBorderSize(0);
    confirm_button.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(64, 92, 160), touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0));
    confirm_button.setText(TypedText(T_CONTAINER_CLOSE_BTN_CONFIRM));
    confirm_button.setTextPosition(0, 5, 159, 30);
    confirm_button.setTextColors(touchgfx::Color::getColorFromRGB(237, 237, 237), touchgfx::Color::getColorFromRGB(237, 237, 237));
    confirm_button.setAction(flexButtonCallback);
    confirm_button.setPosition(161, 210, 159, 30);
    confirm_close_window.add(confirm_button);

    add(confirm_close_window);
}

close_btnBase::~close_btnBase()
{

}

void close_btnBase::initialize()
{

}

void close_btnBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &cross_button)
    {
        //Interaction1
        //When cross_button clicked call virtual function
        //Call crossButtonClicked
        crossButtonClicked();
    }
    if (&src == &cancel_button)
    {
        //Interaction2
        //When cancel_button clicked call virtual function
        //Call cancelButtonClicked
        cancelButtonClicked();
    }
    if (&src == &confirm_button)
    {
        //Interaction3
        //When confirm_button clicked call virtual function
        //Call confirmButtonClicked
        confirmButtonClicked();
    }
}
