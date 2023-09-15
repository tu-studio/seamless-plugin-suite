/*
=====================================================================

CustomChoiceButton.cpp
Created: 8 Sep 2023 03:00:00 pm
Author:  Fares Schulz

=====================================================================
*/

#include <CustomChoiceButton.h>

// TODO Button needs to be updated when the value changes, better Architecture?

CustomChoiceButton::CustomChoiceButton(juce::AudioProcessorValueTreeState& state, juce::String buttonID, juce::StringArray buttonLabels, juce::String buttonTooltip) : apvts(state), id(buttonID), labels(buttonLabels) {
    setColour(juce::TextButton::buttonColourId,seamlessBlue);
    setColour(juce::ComboBox::outlineColourId,seamlessBlue);
    setComponentID(buttonID);
    setButtonText(labels[(int) apvts.state.getChildWithName("Settings").getProperty(id)]);
    setTooltip(buttonTooltip);
    addListener(this);
}

CustomChoiceButton::~CustomChoiceButton() {
    removeListener(this);
}

void CustomChoiceButton::buttonClicked(juce::Button* button) {
    juce::ignoreUnused(button);
    int i = (int) apvts.state.getChildWithName("Settings").getProperty(id);
    if (i == labels.size() - 1) i = 0;
    else i++;
    apvts.state.getChildWithName("Settings").setProperty(id, i, nullptr);
    setButtonText(labels[i]);
}