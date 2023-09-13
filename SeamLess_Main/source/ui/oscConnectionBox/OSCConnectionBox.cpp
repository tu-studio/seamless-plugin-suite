/*
=====================================================================

OSCConnectionBox.cpp
Created: 13 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#include "OSCConnectionBox.h"

OSCConnectionBox::OSCConnectionBox(juce::AudioProcessorValueTreeState &a) : apvts(a), oscSendIntervalSelector(a) {
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
    oscSendIntervalSelector.setBounds(getLocalBounds());
}