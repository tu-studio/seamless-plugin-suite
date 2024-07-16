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
    setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    setColour(juce::Slider::textBoxOutlineColourId, transparent);
    setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::white);
    setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, tuStudioNight);
    setColour(juce::Slider::ColourIds::backgroundColourId, tuStudioNight);
    setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
    setColour(juce::Slider::ColourIds::thumbColourId, tuStudioLightLavender);
}
