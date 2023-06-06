#pragma once

#include "PluginProcessor.h"
#include <SeamLess.h>
#include <SendFader.h>

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Button::Listener
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&, juce::AudioProcessorValueTreeState& parameters);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void buttonClicked(juce::Button* button) override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;
    juce::TextButton testButton;
    SendFader sendFader;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
