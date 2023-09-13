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
    descLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    descLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(descLabel);
    
    oscSendAdressText.setEditable(true);
    oscSendAdressText.setColour (juce::Label::backgroundColourId, seamlessBlue);
    
    if (apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_ADRESS_ID) == "127.0.0.1") {
        oscSendAdressText.setText("localhost", juce::dontSendNotification);
    } else {
        oscSendAdressText.setText(apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_ADRESS_ID), juce::dontSendNotification);
    }
    oscSendAdressText.setTooltip("IP Adress to send OSC messages to.");
    oscSendAdressText.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(oscSendAdressText);
    
    oscSendAdressText.onTextChange = [this] {oscSendAdressTextChanged();};
}

OSCSendAdressSelector::~OSCSendAdressSelector() {
}

void OSCSendAdressSelector::paint(juce::Graphics& g) {
    juce::ignoreUnused(g);
}

void OSCSendAdressSelector::resized() {
    auto area = getLocalBounds();
    auto spacingBetween = area.getWidth()/20;
    auto descLabelArea = area.removeFromLeft(area.getWidth()*2/3);
    descLabel.setBounds(descLabelArea.getX()+(descLabelArea.getWidth()*1/3)/2, descLabelArea.getY()+(descLabelArea.getHeight()-25)/2, descLabelArea.getWidth()*2/3, 25);
    area.removeFromLeft(spacingBetween);
    oscSendAdressText.setBounds(area.getX()+(area.getWidth()-130)/2, area.getY()+(area.getHeight()-25)/2, 130, 25);
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