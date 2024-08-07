//
//  SourceIndexSelector.cpp
//  SeamLess_Client
//
//  Created by Fares Schulz on 08.06.23.
//

#include "SourceIndexSelector.h"

SourceIndexSelector::SourceIndexSelector(juce::AudioProcessorValueTreeState &a) : apvts(a){
    apvts.state.addListener(this);

    descLabel.setText("Source Index:", juce::dontSendNotification);
    descLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    descLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(descLabel);
    
    sourceIndexText.setEditable(true);
    if ((int) apvts.state.getChildWithName("Settings").getProperty(OSCParameters::SOURCE_IDX_ID) < 1)
        sourceIndexText.setColour (juce::Label::backgroundColourId, tuStudioRed);
    else
        sourceIndexText.setColour (juce::Label::backgroundColourId, tuStudioPurple);
        
    sourceIndexText.setText(apvts.state.getChildWithName("Settings").getProperty(OSCParameters::SOURCE_IDX_ID), juce::dontSendNotification);
    sourceIndexText.setTooltip("Source Index of the audio stream that corresponds to this channel. Every channel should have a unique index.");
    sourceIndexText.setJustificationType(juce::Justification::right);
    addAndMakeVisible(sourceIndexText);
    
    sourceIndexText.onTextChange = [this] {sourceIndexTextChanged();};

    if ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::MAIN_CONNECTION_STATUS_ID) == 1) {
        connectionStatusLabel.setColour(juce::Label::backgroundColourId, tuStudioEbony);
        connectionStatusLabel.setText("Connected to Main!", juce::dontSendNotification);
    } else {
        connectionStatusLabel.setColour(juce::Label::backgroundColourId, tuStudioRed);
        connectionStatusLabel.setText("Not connected to Main! Retrying...", juce::dontSendNotification);
    }
    connectionStatusLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(connectionStatusLabel);
}

SourceIndexSelector::~SourceIndexSelector()
{
    apvts.state.removeListener(this);
}

void SourceIndexSelector::paint(juce::Graphics& g) {
    g.setColour(tuStudioPurple);
    g.fillRoundedRectangle(0.f, 0.f, getWidth(),getHeight(), 30.f);

    g.setColour(tuStudioNight);
    g.fillRoundedRectangle(5.f, 5.f, getWidth()-10, getHeight()-10, 25.f);

    g.setColour (tuStudioPurple);
    g.setFont (14.0f);
}

void SourceIndexSelector::resized() {
    descLabel.setVisible(true);
    auto area = getLocalBounds();
    auto spacingBetween = area.getWidth()/20;
    auto spacingBetweenVertical = area.getHeight()/15;
    area.removeFromLeft(spacingBetween);
    area.removeFromRight(spacingBetween);
    area.removeFromBottom(spacingBetweenVertical);
    area.removeFromTop(spacingBetweenVertical);
    auto topArea = area.removeFromTop((area.getHeight()-spacingBetween)/2);
    area.removeFromTop(spacingBetween);
    auto bottomArea = area;
    auto descLabelArea = topArea.removeFromLeft(topArea.getWidth()*2/3);
    descLabel.setBounds(descLabelArea.getX(), descLabelArea.getY()+(descLabelArea.getHeight()-25)/2, descLabelArea.getWidth(), 25);
    topArea.removeFromLeft(spacingBetween);
    sourceIndexText.setBounds(topArea.getX(), topArea.getY()+(topArea.getHeight()-25)/2, topArea.getWidth(), 25);
    bottomArea.removeFromLeft(spacingBetween);
    bottomArea.removeFromBottom(spacingBetweenVertical);
    bottomArea.removeFromRight(spacingBetween);
    connectionStatusLabel.setBounds(bottomArea);
}

void SourceIndexSelector::sourceIndexTextChanged() {
    int newSourceIdx = sourceIndexText.getText().getIntValue();
    if (newSourceIdx < 1) sourceIndexText.setColour (juce::Label::backgroundColourId, tuStudioRed);
    else sourceIndexText.setColour (juce::Label::backgroundColourId, tuStudioPurple);
    
    apvts.state.getChildWithName("Settings").setProperty(OSCParameters::SOURCE_IDX_ID, newSourceIdx, nullptr);
}

void SourceIndexSelector::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) {
    if (property.toString() == PluginParameters::MAIN_CONNECTION_STATUS_ID) {
        if ((int) treeWhosePropertyHasChanged.getProperty(property) == 1) {
            connectionStatusLabel.setColour(juce::Label::backgroundColourId, tuStudioEbony);
            connectionStatusLabel.setText("Connected to Main!", juce::dontSendNotification);
        } else {
            connectionStatusLabel.setColour(juce::Label::backgroundColourId, tuStudioRed);
            connectionStatusLabel.setText("Not connected to Main! Retrying...", juce::dontSendNotification);
        }
    }
}