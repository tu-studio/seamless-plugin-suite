#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& apvts)
    : AudioProcessorEditor (&p), processorRef (p), gainSliderBox(apvts), sourceIndexSelector(apvts), xyPad(apvts), zPositionSlider(apvts), gridChoiceButton(apvts, PluginParameters::GRID_CHOICE_ID, PluginParameters::GRID_CHOICE_LABELS, "None"), venueChoiceButton(apvts, PluginParameters::VENUE_CHOICE_ID, PluginParameters::VENUE_CHOICE_LABELS, "None")
{
    juce::ignoreUnused (processorRef);

    // window size settings
    setSize (1000, 600);    
    setResizable(true, true);
    setResizeLimits(675, 600, 7000, 8000);

    addAndMakeVisible(gainSliderBox);
    addAndMakeVisible(sourceIndexSelector);
    addAndMakeVisible(xyPad);
    addAndMakeVisible(zPositionSlider);

    addAndMakeVisible(gridChoiceButton);
    addAndMakeVisible(venueChoiceButton);
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
    // Borders for the GUI
    auto area = getLocalBounds();
    area.removeFromTop(20);
    area.removeFromBottom(20);
    area.removeFromLeft(20);
    area.removeFromRight(20);

    auto leftSide = area.removeFromLeft(area.getWidth()/8);
    zPositionSlider.setBounds(leftSide.removeFromTop(2 * leftSide.getHeight()/3));
    gridChoiceButton.setBounds(leftSide.removeFromTop(leftSide.getHeight()/2));
    venueChoiceButton.setBounds(leftSide);
    xyPad.setBounds(area.getX(), area.getY(), area.getWidth()/2, area.getHeight());
    gainSliderBox.setBounds(area.getX() + area.getWidth()/2, area.getY(), area.getWidth()/2, area.getHeight()/2);
    sourceIndexSelector.setBounds(area.getX() + area.getWidth()/2, area.getHeight()/2, area.getWidth()/2, area.getHeight()/2);
}