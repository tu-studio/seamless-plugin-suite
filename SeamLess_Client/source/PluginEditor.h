#pragma once

#include "PluginProcessor.h"
#include <SeamLess.h>
#include <PluginParameters.h>
#include <GainSliderBox.h>
#include <SourceIndexSelector.h>
#include <XYPad.h>
#include <ZPositionSlider.h>
#include <CustomButton.h>

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& parameters);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;
    GainSliderBox gainSliderBox;
    SourceIndexSelector sourceIndexSelector;
    XYPad xyPad;
    ZPositionSlider zPositionSlider;
    juce::StringArray gridChoiceArray;
    CustomButton gridChoiceButton;
    juce::StringArray venueChoiceArray;
    CustomButton venueChoiceButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
