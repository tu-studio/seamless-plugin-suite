//
//  CostumRotarySlider.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "CostumRotarySlider.h"

CostumRotarySlider::CostumRotarySlider(juce::String sliderName) {
    slider.setLookAndFeel(&customSliderLookAndFeel);
    slider.setSliderStyle(juce::Slider::Rotary);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 20);
    addAndMakeVisible(slider);
    
    sliderLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    sliderLabel.setJustificationType (juce::Justification::centred);
    sliderLabel.setText (sliderName, juce::dontSendNotification);
    sliderLabel.attachToComponent(&slider,false);
    addAndMakeVisible(sliderLabel);
}

CostumRotarySlider::~CostumRotarySlider() {
    slider.setLookAndFeel(nullptr);
}

void CostumRotarySlider::paint (juce::Graphics& g)
{
    g.setColour (seamlessGrey);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 10);   // draw an outline around the component
}

void CostumRotarySlider::resized()
{
    auto area = getLocalBounds();

    sliderLabel.setBounds(area.removeFromTop(20));
    slider.setBounds(area.reduced(getWidth()/20));
}

void CostumRotarySlider::addSliderAttachment(juce::AudioProcessorValueTreeState &state, const juce::String &parameterID) {
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(state, parameterID, slider);
}

void CostumRotarySlider::setDoubleClickReturnValue(double valueToSetOnDoubleClick) {
    slider.setDoubleClickReturnValue(true, valueToSetOnDoubleClick);
}