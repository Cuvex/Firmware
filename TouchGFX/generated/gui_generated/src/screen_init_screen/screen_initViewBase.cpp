/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen_init_screen/screen_initViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

screen_initViewBase::screen_initViewBase() :
    frameCountTickEventInterval(0),
    flexButtonCallback(this, &screen_initViewBase::flexButtonCallbackHandler)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 320, 240);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setPosition(0, 0, 320, 240);
    background.setColor(touchgfx::Color::getColorFromRGB(237, 237, 237));
    add(background);

    s0_logo.setPosition(0, 0, 320, 240);
    logo.setXY(60, 103);
    logo.setBitmap(touchgfx::Bitmap(BITMAP_GRAFISMO_LOGO_CUVEX_ID));
    s0_logo.add(logo);

    device_alias.setPosition(0, 145, 320, 36);
    device_alias.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    device_alias.setLinespacing(0);
    device_alias.setWideTextAction(WIDE_TEXT_CHARWRAP);
    Unicode::snprintf(device_aliasBuffer, DEVICE_ALIAS_SIZE, "%s", touchgfx::TypedText(T_SI_DEVICE_ALIAS_VALUE).getText());
    device_alias.setWildcard(device_aliasBuffer);
    device_alias.setTypedText(touchgfx::TypedText(T_SI_DEVICE_ALIAS));
    s0_logo.add(device_alias);

    fw_version.setPosition(0, 217, 320, 18);
    fw_version.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    fw_version.setLinespacing(0);
    Unicode::snprintf(fw_versionBuffer, FW_VERSION_SIZE, "%s", touchgfx::TypedText(T_SI_FW_VERSION_VALUE).getText());
    fw_version.setWildcard(fw_versionBuffer);
    fw_version.setTypedText(touchgfx::TypedText(T_SI_FW_VERSION));
    s0_logo.add(fw_version);

    btn_menu.setBoxWithBorderPosition(0, 0, 320, 240);
    btn_menu.setBorderSize(5);
    btn_menu.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    btn_menu.setAlpha(0);
    btn_menu.setVisible(false);
    btn_menu.setAction(flexButtonCallback);
    btn_menu.setPosition(0, 0, 320, 240);
    s0_logo.add(btn_menu);

    btn_settings.setBoxWithBorderPosition(0, 0, 320, 240);
    btn_settings.setBorderSize(5);
    btn_settings.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    btn_settings.setAlpha(0);
    btn_settings.setVisible(false);
    btn_settings.setAction(flexButtonCallback);
    btn_settings.setPosition(0, 0, 320, 240);
    s0_logo.add(btn_settings);

    add(s0_logo);

    s1_settings.setPosition(0, 0, 320, 240);
    s1_settings.setVisible(false);
    s1_1_language.setPosition(0, 0, 320, 240);
    s1_1_language.setVisible(false);
    btn_confirm_lan.setBoxWithBorderPosition(0, 0, 320, 30);
    btn_confirm_lan.setBorderSize(0);
    btn_confirm_lan.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(64, 92, 160), touchgfx::Color::getColorFromRGB(237, 237, 237), touchgfx::Color::getColorFromRGB(51, 102, 153));
    btn_confirm_lan.setText(TypedText(T_SI_LANGUAGE_BTN_CONFIRM));
    btn_confirm_lan.setTextPosition(0, 5, 320, 30);
    btn_confirm_lan.setTextColors(touchgfx::Color::getColorFromRGB(237, 237, 237), touchgfx::Color::getColorFromRGB(237, 237, 237));
    btn_confirm_lan.setAction(flexButtonCallback);
    btn_confirm_lan.setPosition(0, 210, 320, 30);
    s1_1_language.add(btn_confirm_lan);

    btn_select_lan_spanish.setIconBitmaps(Bitmap(BITMAP_BTN_APPEARANCE_LIGHT_ID), Bitmap(BITMAP_BTN_APPEARANCE_DARK_ID));
    btn_select_lan_spanish.setIconXY(0, 0);
    btn_select_lan_spanish.setText(TypedText(T_SI_LANGUAGE_BTN_SPANISH));
    btn_select_lan_spanish.setTextPosition(20, 15, 276, 50);
    btn_select_lan_spanish.setTextColors(touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(63, 63, 81));
    btn_select_lan_spanish.setAction(flexButtonCallback);
    btn_select_lan_spanish.setPosition(22, 134, 276, 50);
    s1_1_language.add(btn_select_lan_spanish);

    btn_select_lan_english.setIconBitmaps(Bitmap(BITMAP_BTN_APPEARANCE_LIGHT_ID), Bitmap(BITMAP_BTN_APPEARANCE_DARK_ID));
    btn_select_lan_english.setIconXY(0, 0);
    btn_select_lan_english.setText(TypedText(T_SI_LANGUAGE_BTN_ENGLISH));
    btn_select_lan_english.setTextPosition(20, 15, 276, 50);
    btn_select_lan_english.setTextColors(touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(63, 63, 81));
    btn_select_lan_english.setAction(flexButtonCallback);
    btn_select_lan_english.setPosition(22, 84, 276, 50);
    s1_1_language.add(btn_select_lan_english);

    image_english.setXY(218, 97);
    image_english.setBitmap(touchgfx::Bitmap(BITMAP_FLAG_ENGLISH_ID));
    s1_1_language.add(image_english);

    image_spanish.setXY(218, 147);
    image_spanish.setBitmap(touchgfx::Bitmap(BITMAP_FLAG_SPANISH_ID));
    s1_1_language.add(image_spanish);

    check_language.setXY(255, 94);
    check_language.setBitmap(touchgfx::Bitmap(BITMAP_CHECK_ID));
    s1_1_language.add(check_language);

    text_language.setPosition(0, 60, 320, 20);
    text_language.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    text_language.setLinespacing(0);
    text_language.setTypedText(touchgfx::TypedText(T_SI_LANGUAGE_TEXT_INFO));
    s1_1_language.add(text_language);

    s1_settings.add(s1_1_language);

    s1_2_typeDeviceAlias.setPosition(0, 0, 320, 240);
    s1_2_typeDeviceAlias.setVisible(false);
    keyboard_device_alias.setXY(0, 117);
    keyboard_device_alias.setVisible(false);
    s1_2_typeDeviceAlias.add(keyboard_device_alias);

    keyboard_btn_hide.setIconBitmaps(Bitmap(BITMAP___KEYBOARDALPHANUM_HIDE_RELEASED_ID), Bitmap(BITMAP___KEYBOARDALPHANUM_HIDE_PRESSED_ID));
    keyboard_btn_hide.setIconXY(0, 0);
    keyboard_btn_hide.setVisible(false);
    keyboard_btn_hide.setAction(flexButtonCallback);
    keyboard_btn_hide.setPosition(235, 211, 80, 27);
    s1_2_typeDeviceAlias.add(keyboard_btn_hide);

    keyboard_text_area.setXY(45, 120);
    s1_2_typeDeviceAlias.add(keyboard_text_area);

    keyboard_btn_show.setBoxWithBorderPosition(0, 0, 169, 30);
    keyboard_btn_show.setBorderSize(5);
    keyboard_btn_show.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    keyboard_btn_show.setAlpha(0);
    keyboard_btn_show.setAction(flexButtonCallback);
    keyboard_btn_show.setPosition(76, 120, 169, 30);
    s1_2_typeDeviceAlias.add(keyboard_btn_show);

    keyboard_btn_enter.setIconBitmaps(Bitmap(BITMAP_GRAFISMO_BOTON_FLECHA_ACEPTAR_CUVEX_ID), Bitmap(BITMAP_GRAFISMO_BOTON_FLECHA_ACEPTAR_CUVEX_ID));
    keyboard_btn_enter.setIconXY(1, 1);
    keyboard_btn_enter.setAction(flexButtonCallback);
    keyboard_btn_enter.setPosition(245, 120, 30, 30);
    s1_2_typeDeviceAlias.add(keyboard_btn_enter);

    keyboard_text_typed.setPosition(76, 125, 169, 20);
    keyboard_text_typed.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    keyboard_text_typed.setLinespacing(0);
    Unicode::snprintf(keyboard_text_typedBuffer, KEYBOARD_TEXT_TYPED_SIZE, "%s", touchgfx::TypedText(T_SI_KEYBOARD_TYPED_VALUE).getText());
    keyboard_text_typed.setWildcard(keyboard_text_typedBuffer);
    keyboard_text_typed.setTypedText(touchgfx::TypedText(T_SI_KEYBOARD_TYPED));
    s1_2_typeDeviceAlias.add(keyboard_text_typed);

    keyboard_text_info_2.setPosition(0, 90, 320, 20);
    keyboard_text_info_2.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    keyboard_text_info_2.setLinespacing(0);
    keyboard_text_info_2.setTypedText(touchgfx::TypedText(T_SI_KEYBOARD_INFO_2));
    s1_2_typeDeviceAlias.add(keyboard_text_info_2);

    keyboard_text_info_1.setPosition(0, 70, 320, 20);
    keyboard_text_info_1.setColor(touchgfx::Color::getColorFromRGB(63, 63, 81));
    keyboard_text_info_1.setLinespacing(0);
    keyboard_text_info_1.setTypedText(touchgfx::TypedText(T_SI_KEYBOARD_INFO_1));
    s1_2_typeDeviceAlias.add(keyboard_text_info_1);

    btn_confirm_dev_alias.setBoxWithBorderPosition(0, 0, 320, 30);
    btn_confirm_dev_alias.setBorderSize(0);
    btn_confirm_dev_alias.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(63, 63, 81), touchgfx::Color::getColorFromRGB(64, 92, 160), touchgfx::Color::getColorFromRGB(237, 237, 237), touchgfx::Color::getColorFromRGB(51, 102, 153));
    btn_confirm_dev_alias.setText(TypedText(T_SI_DEV_ALIAS_BTN_CONFIRM));
    btn_confirm_dev_alias.setTextPosition(0, 5, 320, 30);
    btn_confirm_dev_alias.setTextColors(touchgfx::Color::getColorFromRGB(237, 237, 237), touchgfx::Color::getColorFromRGB(237, 237, 237));
    btn_confirm_dev_alias.setAction(flexButtonCallback);
    btn_confirm_dev_alias.setPosition(0, 210, 320, 30);
    s1_2_typeDeviceAlias.add(btn_confirm_dev_alias);

    s1_settings.add(s1_2_typeDeviceAlias);

    add(s1_settings);
}

screen_initViewBase::~screen_initViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void screen_initViewBase::setupScreen()
{
    keyboard_device_alias.initialize();
    keyboard_text_area.initialize();
}

void screen_initViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &btn_menu)
    {
        //menuPressed
        //When btn_menu clicked change screen to screen_menu
        //Go to screen_menu with no screen transition
        application().gotoscreen_menuScreenNoTransition();
    }
    if (&src == &btn_settings)
    {
        //settingsPressed
        //When btn_settings clicked call virtual function
        //Call settingsPressed
        settingsPressed();
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
    if (&src == &btn_confirm_lan)
    {
        //languageConfirmPressed
        //When btn_confirm_lan clicked call virtual function
        //Call languageConfirmPressed
        languageConfirmPressed();
    }
    if (&src == &keyboard_btn_hide)
    {
        //hideKeyboardPressed
        //When keyboard_btn_hide clicked call virtual function
        //Call hideKeyboardPressed
        hideKeyboardPressed();
    }
    if (&src == &keyboard_btn_show)
    {
        //showKeyboardPressed
        //When keyboard_btn_show clicked call virtual function
        //Call showKeyboardPressed
        showKeyboardPressed();
    }
    if (&src == &keyboard_btn_enter)
    {
        //enterKeyboardPressed
        //When keyboard_btn_enter clicked call virtual function
        //Call enterKeyboardPressed
        enterKeyboardPressed();
    }
    if (&src == &btn_confirm_dev_alias)
    {
        //devAliasConfirmPressed
        //When btn_confirm_dev_alias clicked call virtual function
        //Call enterKeyboardPressed
        enterKeyboardPressed();
    }
}

void screen_initViewBase::handleTickEvent()
{
    frameCountTickEventInterval++;
    if(frameCountTickEventInterval == TICK_TICKEVENT_INTERVAL)
    {
        //tickEvent
        //When every N tick call virtual function
        //Call tickEventScreen
        tickEventScreen();
        frameCountTickEventInterval = 0;
    }
}
