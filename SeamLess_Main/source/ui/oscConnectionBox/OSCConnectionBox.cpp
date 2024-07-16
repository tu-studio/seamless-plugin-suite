/*
=====================================================================

OSCConnectionBox.cpp
Created: 13 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#include "OSCConnectionBox.h"

OSCConnectionBox::OSCConnectionBox(juce::AudioProcessorValueTreeState &a) : apvts(a), oscReceivePortSelector(a), oscReceiveStatusLabel(a), oscSendAdressSelector(a), oscSendStatusLabel(a), oscSendIntervalSelector(a) {
    addAndMakeVisible(oscReceiveStatusLabel);
    addAndMakeVisible(oscReceivePortSelector);
    addAndMakeVisible(oscSendAdressSelector);
    addAndMakeVisible(oscSendStatusLabel);
    addAndMakeVisible(oscSendIntervalSelector);
}

OSCConnectionBox::~OSCConnectionBox()
{
}

void OSCConnectionBox::paint(juce::Graphics& g) {
    g.setColour(tuStudioPurple);
    g.fillRoundedRectangle(0.f, 0.f, getWidth(), getHeight(), 30.f);

    g.setColour(tuStudioNight);
    g.fillRoundedRectangle(5.f, 5.f, getWidth()-10, getHeight()-10, 25.f);

    g.setColour (tuStudioPurple);
    g.setFont (14.0f);
}

void OSCConnectionBox::resized() {
    auto area = getLocalBounds();
    auto spacingBetween = area.getWidth()/10;
    auto parameterHeight = (area.getHeight() - 5*spacingBetween)/6;
    area = area.reduced(spacingBetween);
    oscReceivePortSelector.setBounds(area.removeFromTop(parameterHeight));
    area.removeFromTop(spacingBetween/2);
    oscReceiveStatusLabel.setBounds(area.removeFromTop(parameterHeight));
    area.removeFromTop(spacingBetween);
    oscSendAdressSelector.setBounds(area.removeFromTop(parameterHeight*2));
    area.removeFromTop(spacingBetween/2);
    oscSendStatusLabel.setBounds(area.removeFromTop(parameterHeight));
    area.removeFromTop(spacingBetween);
    oscSendIntervalSelector.setBounds(area);
}

void OSCConnectionBox::addOSCReceiverListener(OSCReceiver& newOSCReceiver) {
    newOSCReceiver.addListener(& oscReceiveStatusLabel);
}

void OSCConnectionBox::removeOSCReceiverListener(OSCReceiver& newOSCReceiver) {
    newOSCReceiver.removeListener(& oscReceiveStatusLabel);
}