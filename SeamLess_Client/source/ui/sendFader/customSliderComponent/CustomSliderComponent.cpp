//
//  CostumSliderComponent.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "CostumSliderComponent.h"

CostumSliderComponent::CostumSliderComponent(juce::String sliderName) {
    slider.setLookAndFeel(&customSliderLookAndFeel);
    slider.setSliderStyle(juce::Slider::Rotary);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 30);
    addAndMakeVisible(slider);
    
    sliderLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    sliderLabel.setJustificationType (juce::Justification::centred);
    sliderLabel.setText (sliderName, juce::dontSendNotification);
    sliderLabel.attachToComponent(&slider,false);
    addAndMakeVisible(sliderLabel);
}

CostumSliderComponent::~CostumSliderComponent() {
    slider.setLookAndFeel(nullptr);
}

void CostumSliderComponent::addSliderAttachment(juce::AudioProcessorValueTreeState &state, const juce::String &parameterID) {
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(state, parameterID, slider);
}

void CostumSliderComponent::setDoubleClickReturnValue(double valueToSetOnDoubleClick) {
    slider.setDoubleClickReturnValue(true, valueToSetOnDoubleClick);
}

void CostumSliderComponent::resized() {
    auto area = getLocalBounds();
    slider.setBounds(area);
}
