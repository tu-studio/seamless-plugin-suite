//
//  SliderLookAndFeel.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 05.06.23.
//

#include "SliderLookAndFeel.h"

//==============================================================================
//            Rotary Slider
//==============================================================================

SliderLookAndFeel::SliderLookAndFeel() {
    setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    setColour(juce::Slider::textBoxOutlineColourId, transparent);
}
