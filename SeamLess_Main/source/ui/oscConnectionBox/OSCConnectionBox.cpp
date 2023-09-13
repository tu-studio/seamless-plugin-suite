/*
=====================================================================

OSCConnectionBox.cpp
Created: 13 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#include "OSCConnectionBox.h"

OSCConnectionBox::OSCConnectionBox(juce::AudioProcessorValueTreeState &a) : apvts(a), oscSendAdressSelector(a), oscSendStatusLabel(a), oscSendIntervalSelector(a) {
    addAndMakeVisible(oscSendAdressSelector);
    addAndMakeVisible(oscSendStatusLabel);
    addAndMakeVisible(oscSendIntervalSelector);
}

OSCConnectionBox::~OSCConnectionBox()
{
}

void OSCConnectionBox::paint(juce::Graphics& g) {
    g.setColour(seamlessBlue);
    g.fillRoundedRectangle(0,0,getWidth(),getHeight(), 30);

    g.setColour(seamlessLightGrey);
    g.fillRoundedRectangle(5,5,getWidth()-10,getHeight()-10,25);

    g.setColour (seamlessBlue);
    g.setFont (14.0f);
}

void OSCConnectionBox::resized() {
    auto area = getLocalBounds();
    auto spacingBetween = area.getWidth()/10;
    auto parameterHeight = (area.getHeight() - 4*spacingBetween)/3;
    area = area.reduced(spacingBetween);
    oscSendAdressSelector.setBounds(area.removeFromTop(parameterHeight));
    area.removeFromTop(spacingBetween);
    oscSendStatusLabel.setBounds(area.removeFromTop(parameterHeight));
    area.removeFromTop(spacingBetween);
    oscSendIntervalSelector.setBounds(area);
}