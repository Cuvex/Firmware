/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <fonts/ApplicationFontProvider.hpp>
#include <fonts/GeneratedFont.hpp>
#include <texts/TypedTextDatabase.hpp>

touchgfx::Font* ApplicationFontProvider::getFont(touchgfx::FontId typography)
{
    switch (typography)
    {
    case Typography::NEUE_MEDIUM_10PX:
        // NeueMontreal_Medium_otf_10_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[0]);
    case Typography::NEUE_MEDIUM_11PX:
        // NeueMontreal_Medium_otf_11_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[1]);
    case Typography::NEUE_MEDIUM_12PX:
        // NeueMontreal_Medium_otf_12_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[2]);
    case Typography::NEUE_MEDIUM_13PX:
        // NeueMontreal_Medium_otf_13_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[3]);
    case Typography::NEUE_MEDIUM_14PX:
        // NeueMontreal_Medium_otf_14_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[4]);
    case Typography::NEUE_MEDIUM_15PX:
        // NeueMontreal_Medium_otf_15_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[5]);
    case Typography::NEUE_MEDIUM_20PX:
        // NeueMontreal_Medium_otf_20_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[6]);
    case Typography::NEUE_MEDIUM_25PX:
        // NeueMontreal_Medium_otf_25_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[7]);
    case Typography::NEUE_BOLD_10PX:
        // NeueMontreal_Bold_otf_10_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[8]);
    case Typography::NEUE_BOLD_12PX:
        // NeueMontreal_Bold_otf_12_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[9]);
    case Typography::NEUE_BOLD_15PX:
        // NeueMontreal_Bold_otf_15_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[10]);
    case Typography::NEUE_BOLD_20PX:
        // NeueMontreal_Bold_otf_20_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[11]);
    case Typography::NEUE_BOLD_25PX:
        // NeueMontreal_Bold_otf_25_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[12]);
    case Typography::DISPLAY:
        // NeueMontreal_Medium_otf_18_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[13]);
    case Typography::MODE:
        // NeueMontreal_Medium_otf_18_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[13]);
    case Typography::KEYBOARD:
        // NeueMontreal_Medium_otf_18_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[13]);
    default:
        return 0;
    }
}
