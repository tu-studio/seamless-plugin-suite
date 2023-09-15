/*
=====================================================================

CustomToggleButton.cpp
Created: 10 Sep 2023 03:00:00 pm
Author:  Fares Schulz

=====================================================================
*/

#include <CustomToggleButton.h>

// TODO Button needs to be updated when the value changes, better Architecture?

CustomToggleButton::CustomToggleButton(juce::AudioProcessorValueTreeState& state, juce::String buttonID, juce::String buttonLabel, juce::String buttonTooltip) : apvts(state), id(buttonID), label(buttonLabel) {
    setComponentID(buttonID);
    if ((int) apvts.state.getChildWithName("Settings").getProperty(id) == 0) setColour(juce::TextButton::buttonColourId, seamlessBlue);
    else setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    setButtonText(label);
    setTooltip(buttonTooltip);
    addListener(this);
}

CustomToggleButton::~CustomToggleButton() {
    removeListener(this);
}

void CustomToggleButton::buttonClicked(juce::Button* button) {
    if (button == this) {
        apvts.state.getChildWithName("Settings").setProperty(id, 1, nullptr);
        setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    } else {
        apvts.state.getChildWithName("Settings").setProperty(id, 0, nullptr);
        setColour(juce::TextButton::buttonColourId, seamlessBlue);
    }
}