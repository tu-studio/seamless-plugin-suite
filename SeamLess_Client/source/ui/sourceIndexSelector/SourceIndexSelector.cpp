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
    descLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    descLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(descLabel);
    
    sourceIndexText.setEditable(true);
    if (apvts.state.getChildWithName("Settings").getPropertyAsValue(SendParameters::SOURCE_IDX_NAME, nullptr).toString().getIntValue() < 1)
        sourceIndexText.setColour (juce::Label::backgroundColourId, juce::Colours::red);
    else
        sourceIndexText.setColour (juce::Label::backgroundColourId, seamlessBlue);
    sourceIndexText.setText(apvts.state.getChildWithName("Settings").getPropertyAsValue(SendParameters::SOURCE_IDX_NAME, nullptr).toString(), juce::dontSendNotification);
    sourceIndexText.setTooltip("Source Index of the audio stream that corresponds to this channel. Every channel should have a unique index.");
    addAndMakeVisible(sourceIndexText);
    
    sourceIndexText.onTextChange = [this] {sourceIndexTextChanged();};

    if (apvts.state.getChildWithName("Settings").getPropertyAsValue(PluginParameters::MAIN_CONNECTION_STATUS_ID, nullptr).toString().getIntValue() == 1) {
        connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::green);
        connectionStatusLabel.setText("Connected to Main!", juce::dontSendNotification);
    } else {
        connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::red);
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
    g.setColour(seamlessBlue);
    g.fillRoundedRectangle(0,0,getWidth(),getHeight(), 30);

    g.setColour(seamlessLightGrey);
    g.fillRoundedRectangle(5,5,getWidth()-10,getHeight()-10,25);

    g.setColour (seamlessBlue);
    g.setFont (14.0f);
}

void SourceIndexSelector::resized() {
    if (getWidth() > 200) {
        descLabel.setVisible(true);
        auto area = getLocalBounds();
        auto spacingBetween = area.getWidth()/20;
        area = area.reduced(spacingBetween);
        auto topArea = area.removeFromTop((area.getHeight()-spacingBetween)/2);
        area.removeFromTop(spacingBetween);
        auto bottomArea = area;
        auto descLabelArea = topArea.removeFromLeft(topArea.getWidth()*2/3);
        descLabel.setBounds(descLabelArea.getX()+(descLabelArea.getWidth()*1/3)/2, descLabelArea.getY()+(descLabelArea.getHeight()-25)/2, descLabelArea.getWidth()*2/3, 25);
        topArea.removeFromLeft(spacingBetween);
        sourceIndexText.setBounds(topArea.getX()+(topArea.getWidth()-50)/2, topArea.getY()+(topArea.getHeight()-25)/2, 50, 25);
        connectionStatusLabel.setBounds(bottomArea);
    } else {
        descLabel.setVisible(false);
        auto area = getLocalBounds();
        auto spacingBetween = area.getWidth()/20;
        area = area.reduced(spacingBetween);
        auto topArea = area.removeFromTop((area.getHeight()-spacingBetween)/2);
        area.removeFromTop(spacingBetween);
        auto bottomArea = area;
        sourceIndexText.setBounds(topArea.getX()+(topArea.getWidth()-50)/2, topArea.getY()+(topArea.getHeight()-25)/2, 50, 25);
        connectionStatusLabel.setBounds(bottomArea);
    }
}

void SourceIndexSelector::sourceIndexTextChanged() {
    int newSourceIdx = sourceIndexText.getText().getIntValue();
    if (newSourceIdx < 1) sourceIndexText.setColour (juce::Label::backgroundColourId, juce::Colours::red);
    else sourceIndexText.setColour (juce::Label::backgroundColourId, seamlessBlue);
    
    apvts.state.getChildWithName("Settings").setProperty(SendParameters::SOURCE_IDX_NAME, newSourceIdx, nullptr);
}

void SourceIndexSelector::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) {
    if (property.toString() == PluginParameters::MAIN_CONNECTION_STATUS_ID) {
        if (treeWhosePropertyHasChanged.getPropertyAsValue(property, nullptr).toString().getIntValue() == 1) {
            connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::green);
            connectionStatusLabel.setText("Connected to Main!", juce::dontSendNotification);
        } else {
            connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::red);
            connectionStatusLabel.setText("Not connected to Main! Retrying...", juce::dontSendNotification);
        }
    }
}