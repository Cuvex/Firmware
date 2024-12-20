/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen_flow_settings_screen/screen_flow_settingsViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <images/BitmapDatabase.hpp>

screen_flow_settingsViewBase::screen_flow_settingsViewBase() :
    flexButtonCallback(this, &screen_flow_settingsViewBase::flexButtonCallbackHandler),
    sliderValueChangedCallback(this, &screen_flow_settingsViewBase::sliderValueChangedCallbackHandler)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 320, 240);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setPosition(0, 0, 320, 240);
    background.setColor(touchgfx::Color::getColorFromRGB(237, 237, 237));
    add(background);

    s0_menu.setPosition(0, 0, 320, 240);
    btn_version.setBoxWithBorderPosition(0, 0, 304, 34);
    btn_version.setBorderSize(0);
    btn_version.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(229, 229, 229), touchgfx::Color::getColorFromRGB(64, 92, 160), touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0));
    btn_version.setText(TypedText(T_SS_MENU_VERSION));
    btn_version.setTextPosition(0, 9, 304, 34);
    btn_version.setTextColors(touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(237, 237, 237));
    btn_version.setAction(flexButtonCallback);
    btn_version.setPosition(8, 40, 304, 34);
    s0_menu.add(btn_version);

    btn_brightness.setBoxWithBorderPosition(0, 0, 304, 34);
    btn_brightness.setBorderSize(0);
    btn_brightness.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(229, 229, 229), touchgfx::Color::getColorFromRGB(64, 92, 160), touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0));
    btn_brightness.setText(TypedText(T_SS_MENU_BRIGHTNESS));
    btn_brightness.setTextPosition(0, 9, 304, 34);
    btn_brightness.setTextColors(touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(237, 237, 237));
    btn_brightness.setAction(flexButtonCallback);
    btn_brightness.setPosition(8, 80, 304, 34);
    s0_menu.add(btn_brightness);

    btn_language.setBoxWithBorderPosition(0, 0, 304, 34);
    btn_language.setBorderSize(0);
    btn_language.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(229, 229, 229), touchgfx::Color::getColorFromRGB(64, 92, 160), touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0));
    btn_language.setText(TypedText(T_SS_MENU_LANGUAGE));
    btn_language.setTextPosition(0, 9, 304, 34);
    btn_language.setTextColors(touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(237, 237, 237));
    btn_language.setAction(flexButtonCallback);
    btn_language.setPosition(8, 120, 304, 34);
    s0_menu.add(btn_language);

    btn_appearance.setBoxWithBorderPosition(0, 0, 304, 34);
    btn_appearance.setBorderSize(0);
    btn_appearance.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(229, 229, 229), touchgfx::Color::getColorFromRGB(64, 92, 160), touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0));
    btn_appearance.setText(TypedText(T_SS_MENU_APPEARANCE));
    btn_appearance.setTextPosition(0, 9, 304, 34);
    btn_appearance.setTextColors(touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(237, 237, 237));
    btn_appearance.setAction(flexButtonCallback);
    btn_appearance.setPosition(8, 160, 304, 34);
    s0_menu.add(btn_appearance);

    add(s0_menu);

    s1_version.setPosition(0, 0, 320, 240);
    s1_version.setVisible(false);
    btn_select_update.setBoxWithBorderPosition(0, 0, 320, 30);
    btn_select_update.setBorderSize(0);
    btn_select_update.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(64, 92, 160), touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0));
    btn_select_update.setText(TypedText(T_SS_VERSION_BTN_UPDATE));
    btn_select_update.setTextPosition(0, 5, 320, 30);
    btn_select_update.setTextColors(touchgfx::Color::getColorFromRGB(237, 237, 237), touchgfx::Color::getColorFromRGB(237, 237, 237));
    btn_select_update.setAction(flexButtonCallback);
    btn_select_update.setPosition(0, 210, 320, 30);
    s1_version.add(btn_select_update);

    update_click_view.setIconBitmaps(Bitmap(BITMAP_CIRCLE_UPDATE_ID), Bitmap(BITMAP_CIRCLE_UPDATE_ID));
    update_click_view.setIconXY(0, 0);
    update_click_view.setWildcardText(TypedText(T_SS_UPDATE_CLICK));
    Unicode::snprintf(update_click_viewBuffer, UPDATE_CLICK_VIEW_SIZE, "%s", TypedText(T_SS_UPDATE_CLICK_VALUE).getText());
    update_click_view.setWildcardTextBuffer(update_click_viewBuffer);
    update_click_view.setWildcardTextPosition(0, 3, 26, 26);
    update_click_view.setWildcardTextColors(touchgfx::Color::getColorFromRGB(237, 237, 237), touchgfx::Color::getColorFromRGB(237, 237, 237));
    update_click_view.setVisible(false);
    update_click_view.setPosition(270, 212, 26, 26);
    s1_version.add(update_click_view);

    text_version.setPosition(0, 150, 320, 18);
    text_version.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_version.setLinespacing(0);
    text_versionBuffer1[0] = 0;
    text_version.setWildcard1(text_versionBuffer1);
    text_versionBuffer1[0] = 0;
    text_version.setWildcard2(text_versionBuffer2);
    text_version.setTypedText(touchgfx::TypedText(T_SS_VERSION_TEXT_VERSION));
    s1_version.add(text_version);

    logo.setXY(60, 103);
    logo.setBitmap(touchgfx::Bitmap(BITMAP_GRAFISMO_LOGO_CUVEX_ID));
    s1_version.add(logo);

    text_caution_alert_spanish.setPosition(0, 0, 320, 240);
    text_caution_alert_spanish.setVisible(false);
    text_caution_spanish_9.setXY(212, 156);
    text_caution_spanish_9.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_spanish_9.setLinespacing(0);
    text_caution_spanish_9.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_SPANISH_9));
    text_caution_alert_spanish.add(text_caution_spanish_9);

    text_caution_spanish_8.setXY(137, 156);
    text_caution_spanish_8.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_spanish_8.setLinespacing(0);
    text_caution_spanish_8.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_SPANISH_8));
    text_caution_alert_spanish.add(text_caution_spanish_8);

    text_caution_spanish_7.setXY(58, 156);
    text_caution_spanish_7.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_spanish_7.setLinespacing(0);
    text_caution_spanish_7.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_SPANISH_7));
    text_caution_alert_spanish.add(text_caution_spanish_7);

    text_caution_spanish_6.setXY(46, 85);
    text_caution_spanish_6.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_spanish_6.setLinespacing(0);
    text_caution_spanish_6.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_SPANISH_6));
    text_caution_alert_spanish.add(text_caution_spanish_6);

    text_caution_spanish_5.setXY(218, 67);
    text_caution_spanish_5.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_spanish_5.setLinespacing(0);
    text_caution_spanish_5.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_SPANISH_5));
    text_caution_alert_spanish.add(text_caution_spanish_5);

    text_caution_spanish_4.setXY(134, 67);
    text_caution_spanish_4.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_spanish_4.setLinespacing(0);
    text_caution_spanish_4.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_SPANISH_4));
    text_caution_alert_spanish.add(text_caution_spanish_4);

    text_caution_spanish_3.setXY(50, 67);
    text_caution_spanish_3.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_spanish_3.setLinespacing(0);
    text_caution_spanish_3.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_SPANISH_3));
    text_caution_alert_spanish.add(text_caution_spanish_3);

    text_caution_spanish_2.setXY(150, 49);
    text_caution_spanish_2.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_spanish_2.setLinespacing(0);
    text_caution_spanish_2.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_SPANISH_2));
    text_caution_alert_spanish.add(text_caution_spanish_2);

    text_caution_spanish_1.setXY(48, 49);
    text_caution_spanish_1.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_spanish_1.setLinespacing(0);
    text_caution_spanish_1.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_SPANISH_1));
    text_caution_alert_spanish.add(text_caution_spanish_1);

    s1_version.add(text_caution_alert_spanish);

    text_caution_alert_english.setPosition(0, 0, 320, 240);
    text_caution_english_9.setXY(193, 157);
    text_caution_english_9.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_english_9.setLinespacing(0);
    text_caution_english_9.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_ENGLISH_9));
    text_caution_alert_english.add(text_caution_english_9);

    text_caution_english_8.setXY(124, 157);
    text_caution_english_8.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_english_8.setLinespacing(0);
    text_caution_english_8.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_ENGLISH_8));
    text_caution_alert_english.add(text_caution_english_8);

    text_caution_english_7.setXY(70, 157);
    text_caution_english_7.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_english_7.setLinespacing(0);
    text_caution_english_7.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_ENGLISH_7));
    text_caution_alert_english.add(text_caution_english_7);

    text_caution_english_6.setXY(53, 85);
    text_caution_english_6.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_english_6.setLinespacing(0);
    text_caution_english_6.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_ENGLISH_6));
    text_caution_alert_english.add(text_caution_english_6);

    text_caution_english_5.setXY(213, 67);
    text_caution_english_5.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_english_5.setLinespacing(0);
    text_caution_english_5.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_ENGLISH_5));
    text_caution_alert_english.add(text_caution_english_5);

    text_caution_english_4.setXY(124, 67);
    text_caution_english_4.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_english_4.setLinespacing(0);
    text_caution_english_4.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_ENGLISH_4));
    text_caution_alert_english.add(text_caution_english_4);

    text_caution_english_3.setXY(55, 67);
    text_caution_english_3.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_english_3.setLinespacing(0);
    text_caution_english_3.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_ENGLISH_3));
    text_caution_alert_english.add(text_caution_english_3);

    text_caution_english_2.setXY(141, 49);
    text_caution_english_2.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_english_2.setLinespacing(0);
    text_caution_english_2.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_ENGLISH_2));
    text_caution_alert_english.add(text_caution_english_2);

    text_caution_english_1.setXY(50, 49);
    text_caution_english_1.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_caution_english_1.setLinespacing(0);
    text_caution_english_1.setTypedText(touchgfx::TypedText(T_SS_TEXT_CAUTION_ENGLISH_1));
    text_caution_alert_english.add(text_caution_english_1);

    s1_version.add(text_caution_alert_english);

    add(s1_version);

    s2_brightness.setPosition(0, 0, 320, 240);
    s2_brightness.setVisible(false);
    image_brightness_high.setXY(258, 108);
    image_brightness_high.setBitmap(touchgfx::Bitmap(BITMAP_BRILLO_MAXIMO_ID));
    s2_brightness.add(image_brightness_high);

    image_brightness_low.setXY(38, 109);
    image_brightness_low.setBitmap(touchgfx::Bitmap(BITMAP_BRILLO_MINIMO_ID));
    s2_brightness.add(image_brightness_low);

    slider_brightness.setXY(72, 111);
    slider_brightness.setBitmaps(touchgfx::Bitmap(BITMAP_SLIDER_BACK_ID), touchgfx::Bitmap(BITMAP_SLIDER_FRONT_ID), touchgfx::Bitmap(BITMAP_SLIDER_CIRCLE_ID));
    slider_brightness.setupHorizontalSlider(0, 6, 0, 0, 155);
    slider_brightness.setValueRange(1, 100);
    slider_brightness.setValue(100);
    slider_brightness.setNewValueCallback(sliderValueChangedCallback);
    s2_brightness.add(slider_brightness);

    text_brightness.setPosition(0, 60, 320, 20);
    text_brightness.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_brightness.setLinespacing(0);
    text_brightness.setTypedText(touchgfx::TypedText(T_SS_BRIGHTNESS_TEXT_INFO));
    s2_brightness.add(text_brightness);

    add(s2_brightness);

    s3_language.setPosition(0, 0, 320, 240);
    s3_language.setVisible(false);
    btn_select_lan_spanish.setIconBitmaps(Bitmap(BITMAP_BTN_APPEARANCE_LIGHT_ID), Bitmap(BITMAP_BTN_APPEARANCE_DARK_ID));
    btn_select_lan_spanish.setIconXY(0, 0);
    btn_select_lan_spanish.setText(TypedText(T_SS_LANGUAGE_BTN_SPANISH));
    btn_select_lan_spanish.setTextPosition(20, 15, 276, 50);
    btn_select_lan_spanish.setTextColors(touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(63, 63, 81));
    btn_select_lan_spanish.setAction(flexButtonCallback);
    btn_select_lan_spanish.setPosition(22, 134, 276, 50);
    s3_language.add(btn_select_lan_spanish);

    btn_select_lan_english.setIconBitmaps(Bitmap(BITMAP_BTN_APPEARANCE_LIGHT_ID), Bitmap(BITMAP_BTN_APPEARANCE_DARK_ID));
    btn_select_lan_english.setIconXY(0, 0);
    btn_select_lan_english.setText(TypedText(T_SS_LANGUAGE_BTN_ENGLISH));
    btn_select_lan_english.setTextPosition(20, 15, 276, 50);
    btn_select_lan_english.setTextColors(touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(63, 63, 81));
    btn_select_lan_english.setAction(flexButtonCallback);
    btn_select_lan_english.setPosition(22, 84, 276, 50);
    s3_language.add(btn_select_lan_english);

    image_english.setXY(218, 97);
    image_english.setBitmap(touchgfx::Bitmap(BITMAP_FLAG_ENGLISH_ID));
    s3_language.add(image_english);

    image_spanish.setXY(218, 147);
    image_spanish.setBitmap(touchgfx::Bitmap(BITMAP_FLAG_SPANISH_ID));
    s3_language.add(image_spanish);

    check_language.setXY(255, 94);
    check_language.setBitmap(touchgfx::Bitmap(BITMAP_CHECK_ID));
    s3_language.add(check_language);

    text_language.setPosition(0, 60, 320, 20);
    text_language.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_language.setLinespacing(0);
    text_language.setTypedText(touchgfx::TypedText(T_SS_LANGUAGE_TEXT_INFO));
    s3_language.add(text_language);

    add(s3_language);

    s4_appearance.setPosition(0, 0, 320, 240);
    s4_appearance.setVisible(false);
    btn_select_mode_dark.setIconBitmaps(Bitmap(BITMAP_BTN_APPEARANCE_DARK_ID), Bitmap(BITMAP_BTN_APPEARANCE_DARK_ID));
    btn_select_mode_dark.setIconXY(0, 0);
    btn_select_mode_dark.setText(TypedText(T_SS_APPEARANCE_BTN_DARK));
    btn_select_mode_dark.setTextPosition(20, 15, 276, 50);
    btn_select_mode_dark.setTextColors(touchgfx::Color::getColorFromRGB(237, 237, 237), touchgfx::Color::getColorFromRGB(237, 237, 237));
    btn_select_mode_dark.setAction(flexButtonCallback);
    btn_select_mode_dark.setPosition(22, 134, 276, 50);
    s4_appearance.add(btn_select_mode_dark);

    btn_select_mode_light.setIconBitmaps(Bitmap(BITMAP_BTN_APPEARANCE_LIGHT_ID), Bitmap(BITMAP_BTN_APPEARANCE_LIGHT_ID));
    btn_select_mode_light.setIconXY(0, 0);
    btn_select_mode_light.setText(TypedText(T_SS_APPEARANCE_BTN_LIGHT));
    btn_select_mode_light.setTextPosition(20, 15, 276, 50);
    btn_select_mode_light.setTextColors(touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(63, 63, 81));
    btn_select_mode_light.setAction(flexButtonCallback);
    btn_select_mode_light.setPosition(22, 84, 276, 50);
    s4_appearance.add(btn_select_mode_light);

    darkCircle3.setPosition(225, 149, 20, 20);
    darkCircle3.setCenter(10, 10);
    darkCircle3.setRadius(10);
    darkCircle3.setLineWidth(0);
    darkCircle3.setArc(0, 360);
    darkCircle3Painter.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    darkCircle3.setPainter(darkCircle3Painter);
    s4_appearance.add(darkCircle3);

    darkCircle2.setPosition(195, 149, 20, 20);
    darkCircle2.setCenter(10, 10);
    darkCircle2.setRadius(10);
    darkCircle2.setLineWidth(0);
    darkCircle2.setArc(0, 360);
    darkCircle2Painter.setColor(touchgfx::Color::getColorFromRGB(64, 92, 160));
    darkCircle2.setPainter(darkCircle2Painter);
    s4_appearance.add(darkCircle2);

    darkCircle1.setPosition(165, 149, 20, 20);
    darkCircle1.setCenter(10, 10);
    darkCircle1.setRadius(10);
    darkCircle1.setLineWidth(0);
    darkCircle1.setArc(0, 360);
    darkCircle1Painter.setColor(touchgfx::Color::getColorFromRGB(237, 237, 237));
    darkCircle1.setPainter(darkCircle1Painter);
    s4_appearance.add(darkCircle1);

    lightCircle3.setPosition(225, 99, 20, 20);
    lightCircle3.setCenter(10, 10);
    lightCircle3.setRadius(10);
    lightCircle3.setLineWidth(0);
    lightCircle3.setArc(0, 360);
    lightCircle3Painter.setColor(touchgfx::Color::getColorFromRGB(216, 217, 221));
    lightCircle3.setPainter(lightCircle3Painter);
    s4_appearance.add(lightCircle3);

    lightCircle2.setPosition(195, 99, 20, 20);
    lightCircle2.setCenter(10, 10);
    lightCircle2.setRadius(10);
    lightCircle2.setLineWidth(0);
    lightCircle2.setArc(0, 360);
    lightCircle2Painter.setColor(touchgfx::Color::getColorFromRGB(64, 92, 160));
    lightCircle2.setPainter(lightCircle2Painter);
    s4_appearance.add(lightCircle2);

    lightCircle1.setPosition(165, 99, 20, 20);
    lightCircle1.setCenter(10, 10);
    lightCircle1.setRadius(10);
    lightCircle1.setLineWidth(0);
    lightCircle1.setArc(0, 360);
    lightCircle1Painter.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    lightCircle1.setPainter(lightCircle1Painter);
    s4_appearance.add(lightCircle1);

    check_appearance.setXY(255, 94);
    check_appearance.setBitmap(touchgfx::Bitmap(BITMAP_CHECK_ID));
    s4_appearance.add(check_appearance);

    text_appearance.setPosition(0, 60, 320, 20);
    text_appearance.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_appearance.setLinespacing(0);
    text_appearance.setTypedText(touchgfx::TypedText(T_SS_APPEARANCE_TEXT_INFO));
    s4_appearance.add(text_appearance);

    add(s4_appearance);

    back_button.setBoxWithBorderPosition(0, 0, 34, 34);
    back_button.setBorderSize(0);
    back_button.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(237, 237, 237), touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0));
    back_button.setIconBitmaps(Bitmap(BITMAP_BACK_ID), Bitmap(BITMAP_BACK_DARK_ID));
    back_button.setIconXY(9, 9);
    back_button.setAction(flexButtonCallback);
    back_button.setPosition(0, 0, 34, 34);
    add(back_button);
}

screen_flow_settingsViewBase::~screen_flow_settingsViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void screen_flow_settingsViewBase::setupScreen()
{

}

void screen_flow_settingsViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &btn_version)
    {
        //menuVersionPressed
        //When btn_version clicked call virtual function
        //Call menuVersionPressed
        menuVersionPressed();
    }
    if (&src == &btn_brightness)
    {
        //menuBrightnessPressed
        //When btn_brightness clicked call virtual function
        //Call menuBrightnessPressed
        menuBrightnessPressed();
    }
    if (&src == &btn_language)
    {
        //menuLanguagePressed
        //When btn_language clicked call virtual function
        //Call menuLanguagePressed
        menuLanguagePressed();
    }
    if (&src == &btn_appearance)
    {
        //menuAppearancePressed
        //When btn_appearance clicked call virtual function
        //Call menuAppearancePressed
        menuAppearancePressed();
    }
    if (&src == &btn_select_update)
    {
        //versionUpdatePressed
        //When btn_select_update clicked call virtual function
        //Call versionUpdatePressed
        versionUpdatePressed();
    }
    if (&src == &btn_select_lan_english)
    {
        //languageEnglishPressed
        //When btn_select_lan_english clicked call virtual function
        //Call languageEnglishPressed
        languageEnglishPressed();
    }
    if (&src == &btn_select_lan_spanish)
    {
        //languageSpanishPressed
        //When btn_select_lan_spanish clicked call virtual function
        //Call languageSpanishPressed
        languageSpanishPressed();
    }
    if (&src == &btn_select_mode_light)
    {
        //appearanceLightPressed
        //When btn_select_mode_light clicked call virtual function
        //Call appearanceLightPressed
        appearanceLightPressed();
    }
    if (&src == &btn_select_mode_dark)
    {
        //appearanceDarkPressed
        //When btn_select_mode_dark clicked call virtual function
        //Call appearanceDarkPressed
        appearanceDarkPressed();
    }
    if (&src == &back_button)
    {
        //backPressed
        //When back_button clicked call virtual function
        //Call backPressed
        backPressed();
    }
}

void screen_flow_settingsViewBase::sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value)
{
    if (&src == &slider_brightness)
    {
        //sliderSetDutyCicle
        //When slider_brightness value changed call virtual function
        //Call sliderSetDutyCicle
        sliderSetDutyCicle(value);
    }
}