/*
=====================================================================

CustomToggleButton.h
Created: 10 Sep 2023 03:00:00 pm
Author:  Fares Schulz

=====================================================================
*/

#ifndef COSTUM_TOGGLE_BUTTON_H
#define COSTUM_TOGGLE_BUTTON_H

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>

class CustomToggleButton : public juce::TextButton, public juce::Button::Listener{
public:
    CustomToggleButton(juce::AudioProcessorValueTreeState& state, juce::String buttonID, juce::String buttonLabel, juce::String buttonTooltip);
    ~CustomToggleButton() override;

    void buttonClicked(juce::Button* button) override;

private:
    juce::AudioProcessorValueTreeState& apvts;
    juce::String id;
    juce::String label;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomToggleButton)
};

#endif /* COSTUM_TOGGLE_BUTTON_H */

