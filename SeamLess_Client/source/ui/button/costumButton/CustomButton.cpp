/*
=====================================================================

CustomButton.cpp
Created: 8 Sep 2023 03:00:00 pm
Author:  Fares Schulz

=====================================================================
*/

#include <CustomButton.h>

// TODO Button needs to be updated when the value changes, better Architecture?

CustomButton::CustomButton(juce::AudioProcessorValueTreeState& state, juce::String buttonID, int numberOfChoices, juce::StringArray buttonLabels, juce::String buttonTooltip) : apvts(state), id(buttonID), numChoices(numberOfChoices), labels(buttonLabels) {
    setColour(juce::TextButton::buttonColourId,seamlessBlue);
    setColour(juce::ComboBox::outlineColourId,seamlessBlue);
    setComponentID(buttonID);
    for (int i = 0; i < numChoices; i++) {
        if (apvts.state.getChild(0).getPropertyAsValue(id, nullptr).toString().getIntValue() == i) {
            setButtonText(labels[i]);
            break;
        }
    }
    setTooltip(buttonTooltip);
}

void CustomButton::buttonUpdate() {
    for (int i = 0; i < numChoices; i++) {
        if (apvts.state.getChild(0).getPropertyAsValue(id, nullptr).toString().getIntValue() == i) {
            setButtonText(labels[i]);
            break;
        }
    }
}