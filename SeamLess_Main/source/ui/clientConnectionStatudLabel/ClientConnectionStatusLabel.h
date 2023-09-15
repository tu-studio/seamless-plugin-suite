/*
=====================================================================

ClientConnectionStatusLabel.h
Created: 15 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#ifndef ClientConnectionStatusLabel_h
#define ClientConnectionStatusLabel_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>

class ClientConnectionStatusLabel : public juce::Component, juce::ValueTree::Listener {
public:
    ClientConnectionStatusLabel(juce::AudioProcessorValueTreeState &apvts);
    ~ClientConnectionStatusLabel() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;

private:
    juce::AudioProcessorValueTreeState& apvts;

    juce::Label descLabel;
    juce::Label numClientsLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClientConnectionStatusLabel)
};

#endif /* ClientConnectionStatusLabel_h */
