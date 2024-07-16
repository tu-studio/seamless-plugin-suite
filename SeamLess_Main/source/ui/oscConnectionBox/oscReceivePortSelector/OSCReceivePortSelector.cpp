/*
=====================================================================

OSCReceivePortSelector.cpp
Created: 14 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#include "OSCReceivePortSelector.h"

OSCReceivePortSelector::OSCReceivePortSelector(juce::AudioProcessorValueTreeState &a) : apvts(a){
    descLabel.setText("OSC Receive Port:", juce::dontSendNotification);
    descLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    descLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(descLabel);
    
    oscReceivePortText.setEditable(true);
    int oscReceivePort = apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_RECEIVE_PORT_ID);
    if (! (oscReceivePort >= 1 && oscReceivePort <= 65536)) oscReceivePortText.setColour (juce::Label::backgroundColourId, tuStudioRed);
    else oscReceivePortText.setColour (juce::Label::backgroundColourId, tuStudioPurple);
        
    oscReceivePortText.setText((juce::String) oscReceivePort, juce::dontSendNotification);
    oscReceivePortText.setTooltip("Port to receive OSC messages.");
    oscReceivePortText.setJustificationType(juce::Justification::right);
    addAndMakeVisible(oscReceivePortText);
    
    oscReceivePortText.onTextChange = [this] {oscReceivePortTextChanged();};
}

OSCReceivePortSelector::~OSCReceivePortSelector() {
}

void OSCReceivePortSelector::resized() {
    auto area = getLocalBounds();
    auto spacingBetween = area.getWidth()/20;
    auto descLabelArea = area.removeFromLeft((area.getWidth()-spacingBetween)*2/3);

    descLabel.setBounds(descLabelArea.getX(), descLabelArea.getY()+(descLabelArea.getHeight()-25)/2, descLabelArea.getWidth(), 25);
    area.removeFromLeft(spacingBetween);
    oscReceivePortText.setBounds(area.getX(), area.getY()+(area.getHeight()-25)/2, area.getWidth(), 25);
}

void OSCReceivePortSelector::oscReceivePortTextChanged() {
    int newOSCReceivePort = oscReceivePortText.getText().getIntValue();
    if (! (newOSCReceivePort >= 1 && newOSCReceivePort <= 65536)) oscReceivePortText.setColour (juce::Label::backgroundColourId, tuStudioRed);
    else oscReceivePortText.setColour (juce::Label::backgroundColourId, tuStudioPurple);
    
    apvts.state.getChildWithName("Settings").setProperty(PluginParameters::OSC_RECEIVE_PORT_ID, (juce::String) newOSCReceivePort , nullptr);
}