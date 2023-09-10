/*
=====================================================================

CustomChoiceButton.h
Created: 8 Sep 2023 03:00:00 pm
Author:  Fares Schulz

=====================================================================
*/

#ifndef CUSTOM_CHOICE_BUTTON_H
#define CUSTOM_CHOICE_BUTTON_H

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>

class CustomChoiceButton : public juce::TextButton, public juce::Button::Listener {
public:
    CustomChoiceButton(juce::AudioProcessorValueTreeState& state, juce::String buttonID, juce::StringArray buttonLabels, juce::String buttonTooltip);
    ~CustomChoiceButton() override;

    void buttonClicked(juce::Button* button) override;

private:
    juce::AudioProcessorValueTreeState& apvts;
    juce::String id;
    juce::StringArray labels;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomChoiceButton)
};

#endif /* CUSTOM_CHOICE_BUTTON_H */

