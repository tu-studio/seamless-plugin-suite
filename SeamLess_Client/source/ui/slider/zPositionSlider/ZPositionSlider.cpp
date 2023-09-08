/*
=====================================================================

ZPositionSlider.cpp
Created: 8 Sep 2021 11:00:00am
Author:  Fares Schulz

=====================================================================
*/

#include "ZPositionSlider.h"

ZPositionSlider::ZPositionSlider(juce::AudioProcessorValueTreeState& a) : apvts(a) {
    slider.setLookAndFeel(&customSliderLookAndFeel);
    slider.setSliderStyle(juce::Slider::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 30);
    addAndMakeVisible(slider);
    
    sliderLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    sliderLabel.setJustificationType (juce::Justification::centred);
    sliderLabel.setText ("z Position", juce::dontSendNotification);
    sliderLabel.attachToComponent(&slider,false);
    addAndMakeVisible(sliderLabel);

    addSliderAttachment(apvts, SendParameters::POS_Z_ID.getParamID());
}

ZPositionSlider::~ZPositionSlider() {
    slider.setLookAndFeel(nullptr);
}

void ZPositionSlider::addSliderAttachment(juce::AudioProcessorValueTreeState &state, const juce::String &parameterID) {
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(state, parameterID, slider);
}

void ZPositionSlider::setDoubleClickReturnValue(double valueToSetOnDoubleClick) {
    slider.setDoubleClickReturnValue(true, valueToSetOnDoubleClick);
}

void ZPositionSlider::resized() {
    auto area = getLocalBounds();
    slider.setBounds(area);
}
