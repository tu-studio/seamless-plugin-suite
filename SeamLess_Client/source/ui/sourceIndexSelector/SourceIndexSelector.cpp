//
//  SourceIndexSelector.cpp
//  SeamLess_Client
//
//  Created by Fares Schulz on 08.06.23.
//

#include "SourceIndexSelector.h"

SourceIndexSelector::SourceIndexSelector(juce::AudioProcessorValueTreeState &a) : apvts(a){
    descLabel.setText("Source Index", juce::dontSendNotification);
    descLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    descLabel.setJustificationType(juce::Justification::right);
    descLabel.attachToComponent(&sourceIndexText, true);
    
    sourceIndexText.setEditable(true);
    if (sourceIndexText.getText().getIntValue() < 1)
        sourceIndexText.setColour (juce::Label::backgroundColourId, juce::Colours::red);
    else
        sourceIndexText.setColour (juce::Label::backgroundColourId, seamlessBlue);
    sourceIndexText.setTooltip("Source Index of the audio stream that corresponds to this channel. Every channel should have a unique index.");
    addAndMakeVisible(sourceIndexText);
    
    sourceIndexText.onTextChange = [this] {sourceIndexTextChanged();};
}

SourceIndexSelector::~SourceIndexSelector()
{
}

void SourceIndexSelector::resized() {
    descLabel.setBounds(0, 0, getWidth()/2, getHeight());
    sourceIndexText.setBounds(getWidth()/2, 0, getWidth()/2, getHeight());
}

void SourceIndexSelector::sourceIndexTextChanged() {
    int newSourceIdx = sourceIndexText.getText().getIntValue();
    if (newSourceIdx < 1) sourceIndexText.setColour (juce::Label::backgroundColourId, juce::Colours::red);
    else sourceIndexText.setColour (juce::Label::backgroundColourId, seamlessBlue);
    
    apvts.state.getChildWithName("Settings").setProperty(SendParameters::SOURCE_IDX_NAME, newSourceIdx, nullptr);
}
