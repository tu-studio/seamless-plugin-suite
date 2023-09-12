#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& pluginApvts)
    : AudioProcessorEditor (&p), processorRef (p), apvts(pluginApvts), gainSliderBox(pluginApvts), sphericalSliderBox(pluginApvts), sourceIndexSelector(pluginApvts), xyPad(pluginApvts), zPositionSlider(pluginApvts), gridChoiceButton(pluginApvts, PluginParameters::GRID_CHOICE_ID, PluginParameters::GRID_CHOICE_LABELS, "None"), venueChoiceButton(pluginApvts, PluginParameters::VENUE_CHOICE_ID, PluginParameters::VENUE_CHOICE_LABELS, "None"), gainToggleButton(pluginApvts, PluginParameters::GAIN_TOGGLE_ID, PluginParameters::GAIN_TOGGLE_LABEL, "None"), sphericalToggleButton(apvts, PluginParameters::SPHERICAL_TOGGLE_ID, PluginParameters::SPHERICAL_TOGGLE_LABEL, "None")
{
    juce::ignoreUnused (processorRef);

    // window size settings
    setSize (1000, 600);    
    setResizable(true, true);
    setResizeLimits(675, 600, 7000, 8000);

    if (apvts.state.getChild(0).getPropertyAsValue(PluginParameters::GAIN_TOGGLE_ID, nullptr).toString().getIntValue() == 1) addAndMakeVisible(gainSliderBox);
    else addChildComponent(gainSliderBox);

    if (apvts.state.getChild(0).getPropertyAsValue(PluginParameters::SPHERICAL_TOGGLE_ID, nullptr).toString().getIntValue() == 1) addAndMakeVisible(sphericalSliderBox);
    else addChildComponent(sphericalSliderBox);
    
    addAndMakeVisible(sourceIndexSelector);

    addAndMakeVisible(xyPad);
    addAndMakeVisible(zPositionSlider);

    addAndMakeVisible(gridChoiceButton);
    addAndMakeVisible(venueChoiceButton);

    addAndMakeVisible(gainToggleButton);
    addAndMakeVisible(sphericalToggleButton);
    // makes the gain toggle button toggle of if the spherical toggle button is toggled on and vice versa
    gainToggleButton.addListener(& sphericalToggleButton);
    sphericalToggleButton.addListener(& gainToggleButton);

    addAndMakeVisible(tooltipWindow);

    apvts.state.addListener(this);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    gainToggleButton.removeListener(& sphericalToggleButton);
    if (JUCE_DEBUG) std::cout << "sphericalToogleButton stopped listener on gainToggleButton." << std::endl;
    sphericalToggleButton.removeListener(& gainToggleButton);
    if (JUCE_DEBUG) std::cout << "gainToggleButton stopped listener on sphericalToogleButton." << std::endl;

    apvts.state.removeListener(this);
    if (JUCE_DEBUG) std::cout << "processorEditor stopped listener on apvts.state." << std::endl;
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
    auto spacingBetween = getWidth()/80;
    area.removeFromTop(spacingBetween);
    area.removeFromBottom(spacingBetween);
    area.removeFromLeft(spacingBetween);
    area.removeFromRight(spacingBetween);

    auto leftSide = area.removeFromLeft(area.getWidth()/10);
    leftSide.removeFromRight(spacingBetween);
    zPositionSlider.setBounds(leftSide.removeFromTop((leftSide.getHeight()-spacingBetween)*3/4));
    leftSide.removeFromTop(spacingBetween);
    gridChoiceButton.setBounds(leftSide.removeFromTop((leftSide.getHeight()-spacingBetween)/2));
    leftSide.removeFromTop(spacingBetween);
    venueChoiceButton.setBounds(leftSide);

    auto middle = area.removeFromLeft(area.getHeight());
    xyPad.setBounds(middle);

    area.removeFromLeft(spacingBetween);
    auto rightSide = area;

    auto toogleButtonArea = rightSide.removeFromTop((rightSide.getHeight()-spacingBetween)/8);
    gainToggleButton.setBounds(toogleButtonArea.removeFromLeft((toogleButtonArea.getWidth()/2)));
    sphericalToggleButton.setBounds(toogleButtonArea);

    rightSide.removeFromTop(spacingBetween);
    auto sliderBoxesRightSide = rightSide.removeFromTop((rightSide.getHeight()-spacingBetween)*3/4);
    gainSliderBox.setBounds(sliderBoxesRightSide);
    sphericalSliderBox.setBounds(sliderBoxesRightSide);

    rightSide.removeFromTop(spacingBetween);
    sourceIndexSelector.setBounds(rightSide);
}

void AudioPluginAudioProcessorEditor::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) {
    if (property.toString() == PluginParameters::GAIN_TOGGLE_ID) {
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