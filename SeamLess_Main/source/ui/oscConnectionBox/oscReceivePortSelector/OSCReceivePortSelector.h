/*
=====================================================================

OSCReceivePortSelector.h
Created: 14 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#ifndef OSCReceivePortSelector_h
#define OSCReceivePortSelector_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>

class OSCReceivePortSelector : public juce::Component {
public:
    OSCReceivePortSelector(juce::AudioProcessorValueTreeState &apvts);
    ~OSCReceivePortSelector() override;
    
    void resized() override;

private:
    void oscReceivePortTextChanged();

private:
    juce::AudioProcessorValueTreeState& apvts;

    juce::Label descLabel;
    juce::Label oscReceivePortText;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCReceivePortSelector)
};

#endif /* OSCReceivePortSelector_h */
