/*
=====================================================================

OSCSendAdressSelector.cpp
Created: 13 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#include "OSCSendAdressSelector.h"

OSCSendAdressSelector::OSCSendAdressSelector(juce::AudioProcessorValueTreeState &a) : apvts(a){
    descLabel.setText("OSC Send Adress:", juce::dontSendNotification);
    descLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    descLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(descLabel);
    
    oscSendAdressText.setEditable(true);
    oscSendAdressText.setColour (juce::Label::backgroundColourId, tuStudioPurple);
    
    if (apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_ADRESS_ID) == "127.0.0.1") {
        oscSendAdressText.setText("localhost", juce::dontSendNotification);
    } else {
        oscSendAdressText.setText(apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_ADRESS_ID), juce::dontSendNotification);
    }
    oscSendAdressText.setTooltip("IP Adress to send OSC messages to.");
    oscSendAdressText.setJustificationType(juce::Justification::right);
    addAndMakeVisible(oscSendAdressText);
    
    oscSendAdressText.onTextChange = [this] {oscSendAdressTextChanged();};

    oscSendPortText.setEditable(true);
    oscSendPortText.setColour (juce::Label::backgroundColourId, tuStudioPurple);
    oscSendPortText.setText(apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_PORT_ID), juce::dontSendNotification);
    oscSendPortText.setTooltip("Port to send OSC messages to.");
    oscSendPortText.setJustificationType(juce::Justification::right);
    addAndMakeVisible(oscSendPortText);

    oscSendPortText.onTextChange = [this] {oscSendPortTextChanged();};
}

OSCSendAdressSelector::~OSCSendAdressSelector() {
}

void OSCSendAdressSelector::paint(juce::Graphics& g) {
    juce::ignoreUnused(g);
}

void OSCSendAdressSelector::resized() {
    auto area = getLocalBounds();
    auto spacingBetween = area.getWidth()/20;
    auto descLabelArea = area.removeFromTop((area.getHeight()-spacingBetween)/2);
    descLabel.setBounds(descLabelArea);
    area.removeFromTop(spacingBetween);
    auto oscSendAdressTextArea = area.removeFromLeft((area.getWidth()-spacingBetween)*2/3); 
    oscSendAdressText.setBounds(oscSendAdressTextArea.getX(), oscSendAdressTextArea.getY()+(oscSendAdressTextArea.getHeight()-25)/2, oscSendAdressTextArea.getWidth(), 25);
    area.removeFromLeft(spacingBetween);
    oscSendPortText.setBounds(area.getX(), area.getY()+(oscSendAdressTextArea.getHeight()-25)/2, area.getWidth(), 25);
}

void OSCSendAdressSelector::oscSendAdressTextChanged() {
    juce::String newOSCSendAdress = oscSendAdressText.getText();
    if (newOSCSendAdress == "localhost" || newOSCSendAdress == "Localhost" || newOSCSendAdress == "LOCALHOST" || newOSCSendAdress == "127.0.0.1") {
        apvts.state.getChildWithName("Settings").setProperty(PluginParameters::OSC_SEND_ADRESS_ID, "127.0.0.1", nullptr);    
        oscSendAdressText.setText("localhost", juce::dontSendNotification);
    } else {
        apvts.state.getChildWithName("Settings").setProperty(PluginParameters::OSC_SEND_ADRESS_ID, newOSCSendAdress, nullptr);
    }
}

void OSCSendAdressSelector::oscSendPortTextChanged() {
    int newOSCSendPort = oscSendPortText.getText().getIntValue();
    if (! (newOSCSendPort >= 0 && newOSCSendPort <= 65536)) oscSendPortText.setColour (juce::Label::backgroundColourId, tuStudioRed);
    else oscSendPortText.setColour (juce::Label::backgroundColourId, tuStudioPurple);
    
    apvts.state.getChildWithName("Settings").setProperty(PluginParameters::OSC_SEND_PORT_ID, (juce::String) newOSCSendPort , nullptr);
}