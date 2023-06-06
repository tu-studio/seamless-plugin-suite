#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& parameters)
    : AudioProcessorEditor (&p), processorRef (p), sendFader(parameters)
{
//    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    testButton.addListener(this);
    addAndMakeVisible(testButton);
    addAndMakeVisible(sendFader);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (seamlessLightGrey);
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    area.removeFromTop(20);
    sendFader.setBounds(area.getWidth()/2, area.getY(), area.getWidth()/2, area.getHeight()/2);
    testButton.setBounds(getWidth()/2, getHeight()/2+10, getWidth()/4, getHeight()/4);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void AudioPluginAudioProcessorEditor::buttonClicked(juce::Button* button) {
    if (button == &testButton) processorRef.pluginConnection.sendMessageToMain("test", "cool");
}
