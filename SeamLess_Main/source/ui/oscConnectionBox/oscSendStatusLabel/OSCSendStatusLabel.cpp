/*
=====================================================================

OSCSendStatusLabel.cpp
Created: 13 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#include "OSCSendStatusLabel.h"

OSCSendStatusLabel::OSCSendStatusLabel(juce::AudioProcessorValueTreeState &a) : apvts(a){
    apvts.state.addListener(this);

    if ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_STATUS_ID) == 1) {
        connectionStatusLabel.setColour(juce::Label::backgroundColourId, tuStudioEbony);
        connectionStatusLabel.setText("OSC Sender connected.", juce::dontSendNotification);
    } else {
        connectionStatusLabel.setColour(juce::Label::backgroundColourId, tuStudioRed);
        connectionStatusLabel.setText("OSC Sender disconnected! Choose valid IP...", juce::dontSendNotification);
    }
    connectionStatusLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(connectionStatusLabel);
}

OSCSendStatusLabel::~OSCSendStatusLabel()
{
    apvts.state.removeListener(this);
}

void OSCSendStatusLabel::resized() {
    connectionStatusLabel.setBounds(getLocalBounds());
}

void OSCSendStatusLabel::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) {
    if (property.toString() == PluginParameters::OSC_SEND_STATUS_ID) {
        if ((int) treeWhosePropertyHasChanged.getProperty(property) == 1) {
            connectionStatusLabel.setColour(juce::Label::backgroundColourId, tuStudioEbony);
            connectionStatusLabel.setText("OSC Sender connected.", juce::dontSendNotification);
        } else {
            connectionStatusLabel.setColour(juce::Label::backgroundColourId, tuStudioRed);
            connectionStatusLabel.setText("OSC Sender disconnected! Choose valid IP...", juce::dontSendNotification);
        }
    }
}