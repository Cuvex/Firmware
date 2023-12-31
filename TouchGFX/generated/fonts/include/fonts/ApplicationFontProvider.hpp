/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#ifndef TOUCHGFX_APPLICATIONFONTPROVIDER_HPP
#define TOUCHGFX_APPLICATIONFONTPROVIDER_HPP

#include <touchgfx/FontManager.hpp>

namespace touchgfx
{
class FlashDataReader;
}

struct Typography
{
    static const touchgfx::FontId NEUE_BOLD_15PX = 0;
    static const touchgfx::FontId NEUE_BOLD_20PX = 1;
    static const touchgfx::FontId NEUE_BOLD_25PX = 2;
    static const touchgfx::FontId NEUE_MEDIUM_15PX = 3;
    static const touchgfx::FontId NEUE_MEDIUM_20PX = 4;
    static const touchgfx::FontId NEUE_MEDIUM_25PX = 5;
    static const touchgfx::FontId DISPLAY = 6;
    static const touchgfx::FontId MODE = 7;
    static const touchgfx::FontId KEYBOARD = 8;
    static const touchgfx::FontId NEUE_MEDIUM_10PX = 9;
    static const touchgfx::FontId NEUE_BOLD_10PX = 10;
    static const touchgfx::FontId NEUE_MEDIUM_12PX = 11;
    static const touchgfx::FontId NEUE_BOLD_12PX = 12;
    static const touchgfx::FontId NEUE_MEDIUM_11PX = 13;
};

struct TypographyFontIndex
{
    static const touchgfx::FontId NEUE_BOLD_15PX = 0;   // NeueMontreal_Bold_otf_15_4bpp
    static const touchgfx::FontId NEUE_BOLD_20PX = 1;   // NeueMontreal_Bold_otf_20_4bpp
    static const touchgfx::FontId NEUE_BOLD_25PX = 2;   // NeueMontreal_Bold_otf_25_4bpp
    static const touchgfx::FontId NEUE_MEDIUM_15PX = 3; // NeueMontreal_Medium_otf_15_4bpp
    static const touchgfx::FontId NEUE_MEDIUM_20PX = 4; // NeueMontreal_Medium_otf_20_4bpp
    static const touchgfx::FontId NEUE_MEDIUM_25PX = 5; // NeueMontreal_Medium_otf_25_4bpp
    static const touchgfx::FontId DISPLAY = 6;          // NeueMontreal_Medium_otf_18_4bpp
    static const touchgfx::FontId MODE = 6;             // NeueMontreal_Medium_otf_18_4bpp
    static const touchgfx::FontId KEYBOARD = 6;         // NeueMontreal_Medium_otf_18_4bpp
    static const touchgfx::FontId NEUE_MEDIUM_10PX = 7; // NeueMontreal_Medium_otf_10_4bpp
    static const touchgfx::FontId NEUE_BOLD_10PX = 8;   // NeueMontreal_Bold_otf_10_4bpp
    static const touchgfx::FontId NEUE_MEDIUM_12PX = 9; // NeueMontreal_Medium_otf_12_4bpp
    static const touchgfx::FontId NEUE_BOLD_12PX = 10;   // NeueMontreal_Bold_otf_12_4bpp
    static const touchgfx::FontId NEUE_MEDIUM_11PX = 11; // NeueMontreal_Medium_otf_11_4bpp
    static const uint16_t NUMBER_OF_FONTS = 12;
};

class ApplicationFontProvider : public touchgfx::FontProvider
{
public:
    virtual touchgfx::Font* getFont(touchgfx::FontId typography);

    static void setFlashReader(touchgfx::FlashDataReader* /*flashReader*/)
    {
    }

    static touchgfx::FlashDataReader* getFlashReader()
    {
        return 0;
    }
};

#endif // TOUCHGFX_APPLICATIONFONTPROVIDER_HPP
