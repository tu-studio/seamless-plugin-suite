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

class OSCReceiveStatusLabel : public juce::Component, private juce::ValueTree::Listener, public juce::OSCReceiver::Listener<juce::OSCReceiver::MessageLoopCallback>, juce::Timer {
public:
    OSCReceiveStatusLabel(juce::AudioProcessorValueTreeState &apvts);
    ~OSCReceiveStatusLabel() override;

    void resized() override;

private:
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;
    void timerCallback() override;
    void oscMessageReceived(const juce::OSCMessage& message) override;

private:
    juce::AudioProcessorValueTreeState& apvts;

    juce::Label connectionStatusLabel;
    juce::Colour currentColor;
    juce::String currentText;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCReceiveStatusLabel)
};

#endif /* OSCReceiveStatusLabel_h */
