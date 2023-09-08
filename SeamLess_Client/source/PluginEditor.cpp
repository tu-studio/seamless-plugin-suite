#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& apvts)
    : AudioProcessorEditor (&p), processorRef (p), gainSliderBox(apvts), sourceIndexSelector(apvts), xyPad(apvts), zPositionSlider(apvts), gridChoiceArray({"Grid OFF", "Grid \nON \nxyz", juce::CharPointer_UTF8("Grid \nON \n r \xcf\x86 \xce\xb8\t")}), gridChoiceButton(apvts, PluginParameters::GRID_TYPE_ID, 3, gridChoiceArray, "None"),venueChoiceArray({"TU Studio", "HuFo"}), venueChoiceButton(apvts, PluginParameters::VENUE_TYPE_ID, 3, venueChoiceArray, "None")
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
    gridChoiceButton.addListener(& xyPad.grid);
    addAndMakeVisible(venueChoiceButton);
    venueChoiceButton.addListener(& xyPad.grid);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    gridChoiceButton.removeListener(& xyPad.grid);
    venueChoiceButton.removeListener(& xyPad.grid);
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
    auto leftSide = area.removeFromLeft(area.getWidth()/8);
    zPositionSlider.setBounds(leftSide.removeFromTop(2 * leftSide.getHeight()/3));
    gridChoiceButton.setBounds(leftSide.removeFromTop(leftSide.getHeight()/2));
    venueChoiceButton.setBounds(leftSide);
    xyPad.setBounds(area.getX(), area.getY(), area.getWidth()/2, area.getHeight());
    gainSliderBox.setBounds(area.getX() + area.getWidth()/2, area.getY(), area.getWidth()/2, area.getHeight()/2);
    sourceIndexSelector.setBounds(area.getX() + area.getWidth()/2, area.getHeight()/2, area.getWidth()/2, area.getHeight()/2);
}