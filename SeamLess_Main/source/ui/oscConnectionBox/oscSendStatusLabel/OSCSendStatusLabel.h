/*
=====================================================================

OSCSendStatusLabel.h
Created: 13 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#ifndef OSCSendStatusLabel_h
#define OSCSendStatusLabel_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>

class OSCSendStatusLabel : public juce::Component, private juce::ValueTree::Listener {
public:
    OSCSendStatusLabel(juce::AudioProcessorValueTreeState &apvts);
    ~OSCSendStatusLabel() override;

    void resized() override;

private:
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;

private:
    juce::AudioProcessorValueTreeState& apvts;

    juce::Label connectionStatusLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCSendStatusLabel)
};

#endif /* OSCSendStatusLabel_h */
