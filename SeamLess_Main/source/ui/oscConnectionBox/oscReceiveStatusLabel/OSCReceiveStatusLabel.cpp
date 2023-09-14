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
        connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::green);
        connectionStatusLabel.setText("OSC Receiver connected.", juce::dontSendNotification);
    } else {
        connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::red);
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
            connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::green);
            connectionStatusLabel.setText("OSC Receiver connected.", juce::dontSendNotification);
        } else {
            connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::red);
            connectionStatusLabel.setText("OSC Receiver disconnected! Choose valid Port...", juce::dontSendNotification);
        }
    } else if (property.toString() == PluginParameters::OSC_RECEIVE_PORT_ID) {
        int oscReceivePort = (int) treeWhosePropertyHasChanged.getProperty(property);
        if (oscReceivePort >= 1 && oscReceivePort <= 65536) {
            connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::green);
            connectionStatusLabel.setText("OSC Receiver connected.", juce::dontSendNotification);
        } else {
            connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::red);
            connectionStatusLabel.setText("OSC Receiver disconnected! Choose valid Port...", juce::dontSendNotification);
        }        
    }
}