/*
=====================================================================

OSCSendAdressSelector.h
Created: 13 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#ifndef OSCSendAdressSelector_h
#define OSCSendAdressSelector_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>

class OSCSendAdressSelector : public juce::Component {
public:
    OSCSendAdressSelector(juce::AudioProcessorValueTreeState &apvts);
    ~OSCSendAdressSelector() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    void oscSendAdressTextChanged();
    void oscSendPortTextChanged();

private:
    juce::AudioProcessorValueTreeState& apvts;

    juce::Label descLabel;
    juce::Label oscSendAdressText;
    juce::Label oscSendPortText;
    juce::Label connectionStatusLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCSendAdressSelector)
};

#endif /* OSCSendAdressSelector_h */
