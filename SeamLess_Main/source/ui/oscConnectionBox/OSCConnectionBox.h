/*
=====================================================================

OSCConnectionBox.h
Created: 13 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#ifndef OSCConnectionBox_h
#define OSCConnectionBox_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>
#include <OSCReceivePortSelector.h>
#include <OSCReceiveStatusLabel.h>
#include <OSCSendAdressSelector.h>
#include <OSCSendIntervalSelector.h>
#include <OSCSendStatusLabel.h>

class OSCConnectionBox : public juce::Component {
public:
    OSCConnectionBox(juce::AudioProcessorValueTreeState &apvts);
    ~OSCConnectionBox() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::AudioProcessorValueTreeState& apvts;

    OSCReceivePortSelector oscReceivePortSelector;
    OSCReceiveStatusLabel oscReceiveStatusLabel;
    OSCSendAdressSelector oscSendAdressSelector;
    OSCSendStatusLabel oscSendStatusLabel;
    OSCSendIntervalSelector oscSendIntervalSelector;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCConnectionBox)
};

#endif /* OSCConnectionBox_h */
