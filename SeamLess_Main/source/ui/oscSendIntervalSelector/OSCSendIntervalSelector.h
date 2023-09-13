/*
=====================================================================

OSCSendIntervalSelector.h
Created: 13 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#ifndef OSCSendIntervalSelector_h
#define OSCSendIntervalSelector_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>

class OSCSendIntervalSelector : public juce::Component, private juce::ValueTree::Listener {
public:
    OSCSendIntervalSelector(juce::AudioProcessorValueTreeState &apvts);
    ~OSCSendIntervalSelector() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    void oscSendIntervalTextChanged();
    // void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;

private:
    juce::AudioProcessorValueTreeState& apvts;

    juce::Label descLabel;
    juce::Label oscSendIntervalText;
    juce::Label connectionStatusLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCSendIntervalSelector)
};

#endif /* OSCSendIntervalSelector_h */
