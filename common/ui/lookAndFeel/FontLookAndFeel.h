#ifndef SM_CUSTOMFONTLOOKANDFEEL_H
#define SM_CUSTOMFONTLOOKANDFEEL_H

#include "JuceHeader.h"

class FontLookAndFeel : public juce::LookAndFeel_V4
{
public:
    FontLookAndFeel() {}

    const juce::Font getCustomFont()
    {
        auto typeface = juce::Typeface::createSystemTypefaceFor (BinaryData::FiraCodeNerdFontBold_ttf, BinaryData::FiraCodeNerdFontBold_ttfSize);
        return juce::Font (typeface);
    }

    const juce::Font getCustomFontBold()
    {
        auto typeface = juce::Typeface::createSystemTypefaceFor (BinaryData::FiraCodeNerdFontMedium_ttf, BinaryData::FiraCodeNerdFontMedium_ttfSize);
        return juce::Font (typeface);
    }

    const juce::Font getCustomFontMedium()
    {
        auto typeface = juce::Typeface::createSystemTypefaceFor (BinaryData::FiraCodeNerdFontRegular_ttf, BinaryData::FiraCodeNerdFontRegular_ttfSize);
        return juce::Font (typeface);
    }

    juce::Typeface::Ptr getTypefaceForFont (const juce::Font& f) override
    {
        if (f.isBold()) {
            return getCustomFontBold().getTypefacePtr();
        } else {
            return getCustomFont().getTypefacePtr();
        }
    }
private:
};

#endif //SM_CUSTOMFONTLOOKANDFEEL_H
