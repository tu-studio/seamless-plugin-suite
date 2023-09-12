//
//  GainSliderBox.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "GainSliderBox.h"

GainSliderBox::GainSliderBox(juce::AudioProcessorValueTreeState &a) : apvts(a) {
    gain1Slider.addSliderAttachment(apvts, OSCParameters::GAIN_1_ID.getParamID());
    gain1Slider.setDoubleClickReturnValue(0.f);
    addAndMakeVisible(gain1Slider);
    gain2Slider.addSliderAttachment(apvts, OSCParameters::GAIN_2_ID.getParamID());
    gain2Slider.setDoubleClickReturnValue(0.f);
    addAndMakeVisible(gain2Slider);
    gain3Slider.addSliderAttachment(apvts, OSCParameters::GAIN_3_ID.getParamID());
    gain3Slider.setDoubleClickReturnValue(0.f);
    addAndMakeVisible(gain3Slider);
    gain4Slider.addSliderAttachment(apvts, OSCParameters::GAIN_4_ID.getParamID());
    gain4Slider.setDoubleClickReturnValue(0.f);
    addAndMakeVisible(gain4Slider);
}

void GainSliderBox::paint(juce::Graphics &g) {
    g.setColour (seamlessBlue);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 15);   // draw an outline around the component
}

void GainSliderBox::resized() {
    auto area = getLocalBounds();
    auto spacingBetween = area.getWidth()/40;
    auto sliderWidth = (area.getWidth() - 3*spacingBetween)/2;
    auto sliderHeight = (area.getHeight()/2 - 3*spacingBetween/2);
    area = area.reduced(spacingBetween);
    auto topSlider = area.removeFromTop(sliderHeight);
    area.removeFromTop(spacingBetween);
    auto bottomSlider = area;

    gain1Slider.setBounds(topSlider.removeFromLeft(sliderWidth));
    topSlider.removeFromLeft(spacingBetween);
    gain2Slider.setBounds(topSlider);
    gain3Slider.setBounds(bottomSlider.removeFromLeft(sliderWidth));
    bottomSlider.removeFromLeft(spacingBetween);
    gain4Slider.setBounds(bottomSlider);
}
