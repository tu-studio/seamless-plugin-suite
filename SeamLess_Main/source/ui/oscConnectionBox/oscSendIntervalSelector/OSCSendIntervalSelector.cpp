/*
=====================================================================

OSCSendIntervalSelector.cpp
Created: 13 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#include "OSCSendIntervalSelector.h"

OSCSendIntervalSelector::OSCSendIntervalSelector(juce::AudioProcessorValueTreeState &a) : apvts(a){
    descLabel.setText("OSC Send Interval:", juce::dontSendNotification);
    descLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    descLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(descLabel);
    
    oscSendIntervalText.setEditable(true);
    if ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_INTERVAL_ID) > 0) {
        oscSendIntervalText.setColour (juce::Label::backgroundColourId, seamlessBlue);
    }
    else {
        oscSendIntervalText.setColour (juce::Label::backgroundColourId, juce::Colours::red);
    }
        
    oscSendIntervalText.setText(apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_INTERVAL_ID), juce::dontSendNotification);
    oscSendIntervalText.setTooltip("OSC Send Interval in ms. Set to 0 to disable.");
    addAndMakeVisible(oscSendIntervalText);
    
    oscSendIntervalText.onTextChange = [this] {oscSendIntervalTextChanged();};
}

OSCSendIntervalSelector::~OSCSendIntervalSelector() {
}

void OSCSendIntervalSelector::paint(juce::Graphics& g) {
    juce::ignoreUnused(g);
}

void OSCSendIntervalSelector::resized() {
    auto area = getLocalBounds();
    auto spacingBetween = area.getWidth()/20;
    auto descLabelArea = area.removeFromLeft(area.getWidth()*2/3);
    descLabel.setBounds(descLabelArea.getX()+(descLabelArea.getWidth()*1/3)/2, descLabelArea.getY()+(descLabelArea.getHeight()-25)/2, descLabelArea.getWidth()*2/3, 25);
    area.removeFromLeft(spacingBetween);
    oscSendIntervalText.setBounds(area.getX()+(area.getWidth()-50)/2, area.getY()+(area.getHeight()-25)/2, 50, 25);
}

void OSCSendIntervalSelector::oscSendIntervalTextChanged() {
    int newOSCSendInterval = oscSendIntervalText.getText().getIntValue();
    if (! (newOSCSendInterval >= 0)) oscSendIntervalText.setColour (juce::Label::backgroundColourId, juce::Colours::red);
    else oscSendIntervalText.setColour (juce::Label::backgroundColourId, seamlessBlue);
    
    apvts.state.getChildWithName("Settings").setProperty(PluginParameters::OSC_SEND_INTERVAL_ID, (juce::String) newOSCSendInterval , nullptr);
}