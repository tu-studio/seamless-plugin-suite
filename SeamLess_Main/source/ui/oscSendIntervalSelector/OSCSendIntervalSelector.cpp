/*
=====================================================================

OSCSendIntervalSelector.cpp
Created: 13 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#include "OSCSendIntervalSelector.h"

OSCSendIntervalSelector::OSCSendIntervalSelector(juce::AudioProcessorValueTreeState &a) : apvts(a){
    apvts.state.addListener(this);

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

    // if (apvts.state.getChildWithName("Settings").getPropertyAsValue(PluginParameters::MAIN_CONNECTION_STATUS_ID, nullptr).toString().getIntValue() == 1) {
    //     connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::green);
    //     connectionStatusLabel.setText("Connected to Main!", juce::dontSendNotification);
    // } else {
    //     connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::red);
    //     connectionStatusLabel.setText("Not connected to Main! Retrying...", juce::dontSendNotification);
    // }
    // connectionStatusLabel.setJustificationType(juce::Justification::centred);
    // addAndMakeVisible(connectionStatusLabel);
}

OSCSendIntervalSelector::~OSCSendIntervalSelector()
{
    apvts.state.removeListener(this);
}

void OSCSendIntervalSelector::paint(juce::Graphics& g) {
    g.setColour(seamlessBlue);
    g.fillRoundedRectangle(0,0,getWidth(),getHeight(), 30);

    g.setColour(seamlessLightGrey);
    g.fillRoundedRectangle(5,5,getWidth()-10,getHeight()-10,25);

    g.setColour (seamlessBlue);
    g.setFont (14.0f);
}

void OSCSendIntervalSelector::resized() {
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
        oscSendIntervalText.setBounds(topArea.getX()+(topArea.getWidth()-50)/2, topArea.getY()+(topArea.getHeight()-25)/2, 50, 25);
        connectionStatusLabel.setBounds(bottomArea);
    } else {
        descLabel.setVisible(false);
        auto area = getLocalBounds();
        auto spacingBetween = area.getWidth()/20;
        area = area.reduced(spacingBetween);
        auto topArea = area.removeFromTop((area.getHeight()-spacingBetween)/2);
        area.removeFromTop(spacingBetween);
        auto bottomArea = area;
        oscSendIntervalText.setBounds(topArea.getX()+(topArea.getWidth()-50)/2, topArea.getY()+(topArea.getHeight()-25)/2, 50, 25);
        connectionStatusLabel.setBounds(bottomArea);
    }
}

void OSCSendIntervalSelector::oscSendIntervalTextChanged() {
    int newOSCSendInterval = oscSendIntervalText.getText().getIntValue();
    if (! (newOSCSendInterval >= 0)) oscSendIntervalText.setColour (juce::Label::backgroundColourId, juce::Colours::red);
    else oscSendIntervalText.setColour (juce::Label::backgroundColourId, seamlessBlue);
    
    apvts.state.getChildWithName("Settings").setProperty(PluginParameters::OSC_SEND_INTERVAL_ID, (juce::String) newOSCSendInterval , nullptr);
}

// void OSCSendIntervalSelector::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) {
//     if (property.toString() == PluginParameters::MAIN_CONNECTION_STATUS_ID) {
//         if (treeWhosePropertyHasChanged.getPropertyAsValue(property, nullptr).toString().getIntValue() == 1) {
//             connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::green);
//             connectionStatusLabel.setText("Connected to Main!", juce::dontSendNotification);
//         } else {
//             connectionStatusLabel.setColour(juce::Label::backgroundColourId, juce::Colours::red);
//             connectionStatusLabel.setText("Not connected to Main! Retrying...", juce::dontSendNotification);
//         }
//     }
// }