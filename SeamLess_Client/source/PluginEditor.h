#pragma once

#include "PluginProcessor.h"
#include <SeamLess.h>
#include <PluginParameters.h>
#include <GainSliderBox.h>
#include <SphericalSliderBox.h>
#include <SourceIndexSelector.h>
#include <XYPad.h>
#include <ZPositionSlider.h>
#include <CustomChoiceButton.h>
#include <CustomToggleButton.h>

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::ValueTree::Listener
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& parameters);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;
    juce::AudioProcessorValueTreeState& apvts;
    GainSliderBox gainSliderBox;
    SphericalSliderBox sphericalSliderBox;
    SourceIndexSelector sourceIndexSelector;
    XYPad xyPad;
    ZPositionSlider zPositionSlider;
    CustomChoiceButton gridChoiceButton;
    CustomChoiceButton venueChoiceButton;
    CustomToggleButton gainToggleButton;
    CustomToggleButton sphericalToggleButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
