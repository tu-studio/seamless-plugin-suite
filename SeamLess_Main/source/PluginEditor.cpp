#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& pluginApvts)
    : AudioProcessorEditor (&p), processorRef (p), apvts(pluginApvts), oscConnectionBox(pluginApvts)
{
    juce::ignoreUnused (processorRef);

    // window size settings
    setSize (1000, 600);    
    setResizable(true, true);
    setResizeLimits(675, 600, 7000, 8000);

    addAndMakeVisible(oscConnectionBox);

    oscConnectionBox.addOSCReceiverListener(processorRef.getOSCReceiverRef());
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    oscConnectionBox.removeOSCReceiverListener(processorRef.getOSCReceiverRef());
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (seamlessLightGrey);
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    auto spacingBetween = getWidth()/80;
    area = area.reduced(spacingBetween);
    auto openGLContextArea = area.removeFromLeft(area.getHeight());
    juce::ignoreUnused(openGLContextArea);

    area.removeFromLeft(spacingBetween);
    oscConnectionBox.setBounds(area);
}
