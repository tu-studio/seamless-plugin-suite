/*
=====================================================================

ClientConnectionStatusLabel.cpp
Created: 15 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#include "ClientConnectionStatusLabel.h"

ClientConnectionStatusLabel::ClientConnectionStatusLabel(juce::AudioProcessorValueTreeState &a) : apvts(a){
    descLabel.setText("Connected Clients:", juce::dontSendNotification);
    descLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    descLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(descLabel);
    
    int numConnectedClients = (int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::NUM_CLIENTS_ID);
        
    numClientsLabel.setText((juce::String) numConnectedClients, juce::dontSendNotification);
    numClientsLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    numClientsLabel.setJustificationType(juce::Justification::right);
    addAndMakeVisible(numClientsLabel);

    apvts.state.addListener(this);
}

ClientConnectionStatusLabel::~ClientConnectionStatusLabel() {
}

void ClientConnectionStatusLabel::paint(juce::Graphics& g) {
    g.setColour(seamlessBlue);
    g.fillRoundedRectangle(0,0,getWidth(),getHeight(), 30);

    g.setColour(seamlessLightGrey);
    g.fillRoundedRectangle(5,5,getWidth()-10,getHeight()-10,25);

    g.setColour (seamlessBlue);
    g.setFont (14.0f);
}

void ClientConnectionStatusLabel::resized() {
    auto area = getLocalBounds();
    area = area.reduced(area.getWidth()/10);

    auto spacingBetween = area.getWidth()/20;
    auto descLabelArea = area.removeFromLeft((area.getWidth()-spacingBetween)*2/3);
    descLabel.setBounds(descLabelArea.getX(), descLabelArea.getY()+(descLabelArea.getHeight()-25)/2, descLabelArea.getWidth(), 25);
    area.removeFromLeft(spacingBetween);
    numClientsLabel.setBounds(area.getX(), area.getY()+(area.getHeight()-25)/2, area.getWidth(), 25);
}

void ClientConnectionStatusLabel::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) {
    if (property.toString() == PluginParameters::NUM_CLIENTS_ID) {
        int numConnectedClients = (int) treeWhosePropertyHasChanged.getProperty(property);
        numClientsLabel.setText((juce::String) numConnectedClients, juce::dontSendNotification);
    }
}