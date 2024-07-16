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
    sliderLabel.setText ("z Position", juce::dontSendNotification);
    sliderLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible(sliderLabel);

    addSliderAttachment(apvts, OSCParameters::POS_Z_ID.getParamID());
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

void ZPositionSlider::paint(juce::Graphics &g) {
    g.setColour (tuStudioPurple);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 15);   // draw an outline around the component
}

void ZPositionSlider::resized() {
    auto area = getLocalBounds();
    sliderLabel.setBounds(area.removeFromTop(30));
    slider.setBounds(area);
}
