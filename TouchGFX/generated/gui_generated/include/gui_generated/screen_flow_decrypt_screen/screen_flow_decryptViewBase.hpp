/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN_FLOW_DECRYPTVIEWBASE_HPP
#define SCREEN_FLOW_DECRYPTVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen_flow_decrypt_screen/screen_flow_decryptPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <gui/containers/thinking_circles.hpp>
#include <touchgfx/containers/buttons/Buttons.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/containers/keyboard_decrypt_password.hpp>
#include <gui/containers/textArea.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <gui/containers/close_btn.hpp>

class screen_flow_decryptViewBase : public touchgfx::View<screen_flow_decryptPresenter>
{
public:
    screen_flow_decryptViewBase();
    virtual ~screen_flow_decryptViewBase();
    virtual void setupScreen();
    virtual void handleTickEvent();

    /*
     * Virtual Action Handlers
     */
    virtual void tickEventScreen()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void hideKeyboardPressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void showKeyboardPressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void enterKeyboardPressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void decryptPressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void retryPressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void moreTimePressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void eyePressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void resetMicrocontrollerPressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void btnUpPressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void btnDownPressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void qrSmallPressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void backPressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void btnError1Pressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void btnError2Pressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void btnCautionMsgPressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void btnQrSeedPressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void btnQrPrivateKeyPressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }
    virtual void btnQrPublicKeyPressed()
    {
        // Override and implement this function in screen_flow_decrypt
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box background;
    touchgfx::Container s0_temporalBlock;
    touchgfx::Image image_temporal_block;
    touchgfx::Container text_temporal_block_spanish;
    touchgfx::TextArea temporal_block_spanish_1;
    touchgfx::TextArea temporal_block_spanish_2;
    touchgfx::TextArea temporal_block_spanish_3;
    touchgfx::TextArea temporal_block_spanish_4;
    touchgfx::TextArea temporal_block_spanish_5;
    touchgfx::TextArea temporal_block_spanish_6;
    touchgfx::TextArea temporal_block_spanish_7;
    touchgfx::Container text_temporal_block_english;
    touchgfx::TextArea temporal_block_english_1;
    touchgfx::TextArea temporal_block_english_2;
    touchgfx::TextArea temporal_block_english_3;
    touchgfx::TextArea temporal_block_english_4;
    touchgfx::TextArea temporal_block_english_5;
    touchgfx::TextArea temporal_block_english_6;
    touchgfx::Container s1_initNFC;
    thinking_circles init_nfc_thinking_circles;
    touchgfx::Image init_nfc_image;
    touchgfx::TextArea init_nfc_text1;
    touchgfx::TextArea init_nfc_text2;
    touchgfx::Container s2_waitReadNFC;
    touchgfx::TextArea text_wait_read_nfc;
    touchgfx::Image image_wait_read_nfc;
    touchgfx::Container s3_viewTagInfo;
    touchgfx::TextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  btn_decrypt;
    touchgfx::TextArea text_uid_info;
    touchgfx::TextAreaWithOneWildcard text_uid;
    touchgfx::TextArea text_alias_info;
    touchgfx::TextAreaWithOneWildcard text_alias;
    touchgfx::Container s4_readError;
    touchgfx::TextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  btn_retry;
    touchgfx::TextArea text_read_error;
    touchgfx::Image image_read_error;
    touchgfx::Container s5_typePassword;
    keyboard_decrypt_password keyboard_password;
    touchgfx::IconButtonStyle< touchgfx::ClickButtonTrigger >  keyboard_btn_hide;
    textArea keyboard_text_area;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  keyboard_btn_show;
    touchgfx::WildcardTextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  keyboard_btn_enter;
    touchgfx::ToggleButton keyboard_pwd_eye;
    touchgfx::TextAreaWithOneWildcard keyboard_text_typed;
    touchgfx::TextAreaWithOneWildcard keyboard_text_typed_hide;
    touchgfx::TextAreaWithOneWildcard keyboard_text_info;
    touchgfx::TextArea keyboard_placeholder;
    touchgfx::Container s6_passwordError1;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  btn_password_error_1;
    touchgfx::Container text_password_error1_spanish;
    touchgfx::TextArea password_error1_spanish_1;
    touchgfx::TextArea password_error1_spanish_2;
    touchgfx::TextArea password_error1_spanish_3;
    touchgfx::TextArea password_error1_spanish_4;
    touchgfx::TextArea password_error1_spanish_5;
    touchgfx::Container text_password_error1_english;
    touchgfx::TextArea password_error1_english_1;
    touchgfx::TextArea password_error1_english_2;
    touchgfx::TextArea password_error1_english_3;
    touchgfx::TextArea password_error1_english_4;
    touchgfx::TextArea password_error1_english_5;
    touchgfx::Container s7_passwordError2;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  btn_password_error2;
    touchgfx::Container text_password_error2_spanish;
    touchgfx::TextArea password_error2_spanish_1;
    touchgfx::TextArea password_error2_spanish_2;
    touchgfx::TextArea password_error2_spanish_3;
    touchgfx::TextArea password_error2_spanish_4;
    touchgfx::TextArea password_error2_spanish_5;
    touchgfx::Container text_password_error2_english;
    touchgfx::TextArea password_error2_english_1;
    touchgfx::TextArea password_error2_english_2;
    touchgfx::TextArea password_error2_english_3;
    touchgfx::TextArea password_error2_english_4;
    touchgfx::TextArea password_error2_english_5;
    touchgfx::Container s8_viewSecret;
    touchgfx::Container container_qr_small_code;
    touchgfx::Circle circle_qr_small;
    touchgfx::PainterRGB888 circle_qr_smallPainter;
    touchgfx::TextArea text_qr_small;
    touchgfx::IconButtonStyle< touchgfx::ClickButtonTrigger >  btn_qr_small;
    touchgfx::Container container_typed_check;
    touchgfx::IconButtonStyle< touchgfx::RepeatButtonTrigger >  btn_down;
    touchgfx::IconButtonStyle< touchgfx::RepeatButtonTrigger >  btn_up;
    touchgfx::ScrollableContainer scrollable_container_typed_check;
    touchgfx::TextAreaWithOneWildcard text_secret_check;
    touchgfx::Container container_caution_msg;
    touchgfx::TextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  btn_caution_msg;
    touchgfx::Container text_caution_msg_spanish;
    touchgfx::TextArea caution_msg_spanish_1;
    touchgfx::TextArea caution_msg_spanish_2;
    touchgfx::TextArea caution_msg_spanish_3;
    touchgfx::Container text_caution_msg_english;
    touchgfx::TextArea caution_msg_english_1;
    touchgfx::TextArea caution_msg_english_2;
    touchgfx::TextArea caution_msg_english_3;
    touchgfx::Container container_qr_to_check_menu;
    touchgfx::TextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  btn_1_qr_seed;
    touchgfx::TextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  btn_2_qr_private_key;
    touchgfx::TextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  btn_3_qr_public_key;
    touchgfx::TextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  btn_more_time;
    touchgfx::TextAreaWithOneWildcard text_timeout;
    touchgfx::IconButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  btn_back;
    touchgfx::Container s9_timeoutSecret;
    touchgfx::TextArea text_timeout_secret;
    touchgfx::Image image_timeout_secret;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  btn_reset_mcu_timeout;
    close_btn close_button;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXT_UID_SIZE = 25;
    touchgfx::Unicode::UnicodeChar text_uidBuffer[TEXT_UID_SIZE];
    static const uint16_t TEXT_ALIAS_SIZE = 25;
    touchgfx::Unicode::UnicodeChar text_aliasBuffer[TEXT_ALIAS_SIZE];
    static const uint16_t KEYBOARD_BTN_ENTER_SIZE = 25;
    touchgfx::Unicode::UnicodeChar keyboard_btn_enterBuffer[KEYBOARD_BTN_ENTER_SIZE];
    static const uint16_t KEYBOARD_TEXT_TYPED_SIZE = 45;
    touchgfx::Unicode::UnicodeChar keyboard_text_typedBuffer[KEYBOARD_TEXT_TYPED_SIZE];
    static const uint16_t KEYBOARD_TEXT_TYPED_HIDE_SIZE = 45;
    touchgfx::Unicode::UnicodeChar keyboard_text_typed_hideBuffer[KEYBOARD_TEXT_TYPED_HIDE_SIZE];
    static const uint16_t KEYBOARD_TEXT_INFO_SIZE = 50;
    touchgfx::Unicode::UnicodeChar keyboard_text_infoBuffer[KEYBOARD_TEXT_INFO_SIZE];
    static const uint16_t TEXT_SECRET_CHECK_SIZE = 2005;
    touchgfx::Unicode::UnicodeChar text_secret_checkBuffer[TEXT_SECRET_CHECK_SIZE];
    static const uint16_t TEXT_TIMEOUT_SIZE = 5;
    touchgfx::Unicode::UnicodeChar text_timeoutBuffer[TEXT_TIMEOUT_SIZE];

private:

    /*
     * Canvas Buffer Size
     */
    static const uint32_t CANVAS_BUFFER_SIZE = 4800;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

    /*
     * Tick Counter Declarations
     */
    static const uint32_t TICK_TICKEVENT_INTERVAL = 10;
    uint32_t frameCountTickEventInterval;

    /*
     * Callback Declarations
     */
    touchgfx::Callback<screen_flow_decryptViewBase, const touchgfx::AbstractButtonContainer&> flexButtonCallback;
    touchgfx::Callback<screen_flow_decryptViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src);
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // SCREEN_FLOW_DECRYPTVIEWBASE_HPP