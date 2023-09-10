#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& pluginApvts)
    : AudioProcessorEditor (&p), processorRef (p), apvts(pluginApvts), gainSliderBox(pluginApvts), sphericalSliderBox(pluginApvts), sourceIndexSelector(pluginApvts), xyPad(pluginApvts), zPositionSlider(pluginApvts), gridChoiceButton(pluginApvts, PluginParameters::GRID_CHOICE_ID, PluginParameters::GRID_CHOICE_LABELS, "None"), venueChoiceButton(pluginApvts, PluginParameters::VENUE_CHOICE_ID, PluginParameters::VENUE_CHOICE_LABELS, "None"), cartesianToggleButton(pluginApvts, PluginParameters::CARTESIAN_TOGGLE_ID, PluginParameters::CARTESIAN_TOGGLE_LABEL, "None"), sphericalToggleButton(apvts, PluginParameters::SPHERICAL_TOGGLE_ID, PluginParameters::SPHERICAL_TOGGLE_LABEL, "None")
{
    juce::ignoreUnused (processorRef);

    // window size settings
    setSize (1000, 600);    
    setResizable(true, true);
    setResizeLimits(675, 600, 7000, 8000);

    addAndMakeVisible(gainSliderBox);
    addChildComponent(sphericalSliderBox);
    addAndMakeVisible(sourceIndexSelector);

    addAndMakeVisible(xyPad);
    addAndMakeVisible(zPositionSlider);

    addAndMakeVisible(gridChoiceButton);
    addAndMakeVisible(venueChoiceButton);

    addAndMakeVisible(cartesianToggleButton);
    addAndMakeVisible(sphericalToggleButton);
    // makes the cartesian toggle button toggle of if the spherical toggle button is toggled on and vice versa
    cartesianToggleButton.addListener(& sphericalToggleButton);
    sphericalToggleButton.addListener(& cartesianToggleButton);

    apvts.state.addListener(this);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    cartesianToggleButton.removeListener(& sphericalToggleButton);
    sphericalToggleButton.removeListener(& cartesianToggleButton);

    apvts.state.removeListener(this);
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

    auto middle = area.removeFromLeft(area.getWidth()/2);
    xyPad.setBounds(middle);

    auto rightSide = area;
    auto toogleButtonArea = rightSide.removeFromTop(rightSide.getHeight()/8);
    cartesianToggleButton.setBounds(toogleButtonArea.removeFromLeft(toogleButtonArea.getWidth()/2));
    sphericalToggleButton.setBounds(toogleButtonArea);

    auto sliderBoxesRightSide = rightSide.removeFromTop(rightSide.getHeight()*3/8);
    gainSliderBox.setBounds(sliderBoxesRightSide);
    sphericalSliderBox.setBounds(sliderBoxesRightSide);

    sourceIndexSelector.setBounds(rightSide);
}

void AudioPluginAudioProcessorEditor::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) {
    if (property.toString() == PluginParameters::CARTESIAN_TOGGLE_ID) {
        if (treeWhosePropertyHasChanged.getPropertyAsValue(property, nullptr).toString().getIntValue() == 1) {
            gainSliderBox.setVisible(true);
        } else {
            gainSliderBox.setVisible(false);
        }
    } else if (property.toString() == PluginParameters::SPHERICAL_TOGGLE_ID) {
        if (treeWhosePropertyHasChanged.getPropertyAsValue(property, nullptr).toString().getIntValue() == 1) {
            sphericalSliderBox.setVisible(true);
        } else {
            sphericalSliderBox.setVisible(false);
        }
    }
}