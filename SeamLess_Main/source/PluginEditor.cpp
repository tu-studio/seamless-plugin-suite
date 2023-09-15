#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& pluginApvts)
    : AudioProcessorEditor (&p), processorRef (p), apvts(pluginApvts), clientConnectionStatusLabel(pluginApvts), oscConnectionBox(pluginApvts)
{
    juce::ignoreUnused (processorRef);

    // window size settings
    setSize (300, 500);    
    setResizable(true, true);
    setResizeLimits(300, 500, 500, 800);

    addAndMakeVisible(clientConnectionStatusLabel);
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
    auto spacingBetween = getWidth()/20;
    area = area.reduced(spacingBetween);

    clientConnectionStatusLabel.setBounds(area.removeFromTop((area.getHeight()-spacingBetween)/6));
    area.removeFromTop(spacingBetween);
    oscConnectionBox.setBounds(area);
}
