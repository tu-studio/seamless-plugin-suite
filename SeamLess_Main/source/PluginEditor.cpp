#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& pluginApvts)
    : AudioProcessorEditor (&p), processorRef (p), apvts(pluginApvts), oscSendIntervalSelector(pluginApvts)
{
    juce::ignoreUnused (processorRef);

    // window size settings
    setSize (1000, 600);    
    setResizable(true, true);
    setResizeLimits(675, 600, 7000, 8000);

    addAndMakeVisible(oscSendIntervalSelector);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (seamlessLightGrey);
}

void AudioPluginAudioProcessorEditor::resized()
{
    oscSendIntervalSelector.setBounds(getLocalBounds());
}
