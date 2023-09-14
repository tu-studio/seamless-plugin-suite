/*
=====================================================================

OSCReceiveStatusLabel.h
Created: 14 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#ifndef OSCReceiveStatusLabel_h
#define OSCReceiveStatusLabel_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>

class OSCReceiveStatusLabel : public juce::Component, private juce::ValueTree::Listener {
public:
    OSCReceiveStatusLabel(juce::AudioProcessorValueTreeState &apvts);
    ~OSCReceiveStatusLabel() override;

    void resized() override;

private:
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;

private:
    juce::AudioProcessorValueTreeState& apvts;

    juce::Label connectionStatusLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCReceiveStatusLabel)
};

#endif /* OSCReceiveStatusLabel_h */
