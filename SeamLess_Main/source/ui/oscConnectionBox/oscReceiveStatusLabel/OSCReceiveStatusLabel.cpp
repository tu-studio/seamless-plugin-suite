/*
=====================================================================

OSCReceiveStatusLabel.cpp
Created: 14 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#include "OSCReceiveStatusLabel.h"

OSCReceiveStatusLabel::OSCReceiveStatusLabel(juce::AudioProcessorValueTreeState &a) : apvts(a){
    apvts.state.addListener(this);

    if ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_RECEIVE_STATUS_ID) == 1) {
        currentColor = juce::Colours::green;
        connectionStatusLabel.setColour(juce::Label::backgroundColourId, currentColor);
        connectionStatusLabel.setText("OSC Receiver connected.", juce::dontSendNotification);
    } else {
        currentColor = juce::Colours::red;
        connectionStatusLabel.setColour(juce::Label::backgroundColourId, currentColor);
        connectionStatusLabel.setText("OSC Receiver disconnected! Choose valid Port...", juce::dontSendNotification);
    }
    connectionStatusLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(connectionStatusLabel);
}

OSCReceiveStatusLabel::~OSCReceiveStatusLabel()
{
    apvts.state.removeListener(this);
}

void OSCReceiveStatusLabel::resized() {
    connectionStatusLabel.setBounds(getLocalBounds());
}

void OSCReceiveStatusLabel::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) {
    if (property.toString() == PluginParameters::OSC_RECEIVE_STATUS_ID) {
        if ((int) treeWhosePropertyHasChanged.getProperty(property) == 1) {
            currentColor = juce::Colours::green;
            connectionStatusLabel.setColour(juce::Label::backgroundColourId, currentColor);
            connectionStatusLabel.setText("OSC Receiver connected.", juce::dontSendNotification);
        } else {
            currentColor = juce::Colours::red;
            connectionStatusLabel.setColour(juce::Label::backgroundColourId, currentColor);
            connectionStatusLabel.setText("OSC Receiver disconnected! Choose valid Port...", juce::dontSendNotification);
        }
    } else if (property.toString() == PluginParameters::OSC_RECEIVE_PORT_ID) {
        int oscReceivePort = (int) treeWhosePropertyHasChanged.getProperty(property);
        if (oscReceivePort >= 1 && oscReceivePort <= 65536) {
            currentColor = juce::Colours::green;
            connectionStatusLabel.setColour(juce::Label::backgroundColourId, currentColor);
            connectionStatusLabel.setText("OSC Receiver connected.", juce::dontSendNotification);
        } else {
            currentColor = juce::Colours::red;
            connectionStatusLabel.setColour(juce::Label::backgroundColourId, currentColor);
            connectionStatusLabel.setText("OSC Receiver disconnected! Choose valid Port...", juce::dontSendNotification);
        }        
    }
}

void OSCReceiveStatusLabel::oscMessageReceived(const juce::OSCMessage& message) {
    juce::ignoreUnused(message);
    connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::navajowhite);
    startTimer(150);
}

void OSCReceiveStatusLabel::timerCallback() {
    connectionStatusLabel.setColour(juce::Label::backgroundColourId, currentColor);
    stopTimer();
}