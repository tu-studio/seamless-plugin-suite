/*
=====================================================================

CustomButton.h
Created: 8 Sep 2023 03:00:00 pm
Author:  Fares Schulz

=====================================================================
*/

#ifndef COSTUM_BUTTON_H
#define COSTUM_BUTTON_H

#include <JuceHeader.h>
#include <SeamLess.h>

class CustomButton : public juce::TextButton {
public:
    CustomButton(juce::AudioProcessorValueTreeState& state, juce::String buttonID, int numberOfChoices, juce::StringArray buttonLabels, juce::String buttonTooltip);

    void buttonUpdate();

private:
    juce::AudioProcessorValueTreeState& apvts;
    juce::String id;
    int numChoices;
    juce::StringArray labels;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomButton)
};

#endif /* COSTUM_BUTTON_H */

