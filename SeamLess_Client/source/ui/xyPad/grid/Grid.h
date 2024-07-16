/*
=====================================================================

Grid.h
Created: 8 Sep 2021 14:00:00am
Author:  Fares Schulz

=====================================================================
*/

#ifndef GRID_H
#define GRID_H

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>

class Grid : public juce::Component, public juce::ValueTree::Listener {
    
public:
    Grid(juce::AudioProcessorValueTreeState& pluginApvts);
    ~Grid() override;

private:
    juce::Point<int> convertPositionToPixel(float xPosition, float yPosition);
    juce::Point<float> convertPixelToPosition(int xPixel, int yPixel);
    void paint(juce::Graphics& g) override;
    void resized() override;
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;

private:

    juce::AudioProcessorValueTreeState& apvts;

    // HuFo graphical shape
    juce::Path HuFoPath;
    juce::Point<int> HuFoPixel[34];
    juce::Point<float> HuFoPosition[34] = {
        juce::Point<float>(0.174f, -0.500f), juce::Point<float>(0.214f, -0.445f), juce::Point<float>(0.249f, -0.388f), juce::Point<float>(0.279f, -0.327f), juce::Point<float>(0.304f, -0.265f), juce::Point<float>(0.324f, -0.200f), juce::Point<float>(0.338f, -0.134f), juce::Point<float>(0.346f, -0.067f), juce::Point<float>(0.349f, -0.000f), juce::Point<float>(0.346f, 0.067f), juce::Point<float>(0.338f, 0.134f), juce::Point<float>(0.324f, 0.200f), juce::Point<float>(0.304f, 0.265f), juce::Point<float>(0.279f, 0.327f), juce::Point<float>(0.249f, 0.388f), juce::Point<float>(0.214f, 0.445f), juce::Point<float>(0.174f, 0.500f), juce::Point<float>(-0.174f, 0.500f), juce::Point<float>(-0.214f, 0.445f), juce::Point<float>(-0.249f, 0.388f), juce::Point<float>(-0.279f, 0.327f), juce::Point<float>(-0.304f, 0.265f), juce::Point<float>(-0.324f, 0.200f), juce::Point<float>(-0.338f, 0.134f), juce::Point<float>(-0.346f, 0.067f), juce::Point<float>(-0.349f, 0.000f), juce::Point<float>(-0.346f, -0.067f), juce::Point<float>(-0.338f, -0.134f), juce::Point<float>(-0.324f, -0.200f), juce::Point<float>(-0.304f, -0.265f), juce::Point<float>(-0.279f, -0.327f), juce::Point<float>(-0.249f, -0.388f), juce::Point<float>(-0.214f, -0.445f), juce::Point<float>(-0.174f, -0.500f)
    };
        
    juce::Path TUStudioPath;
    juce::Point<int> TUStudioPixel[8];
    juce::Point<float> TUStudioPosition[8] = {
        juce::Point<float>(0.5f, -0.268f), juce::Point<float>(0.5f, 0.268f), juce::Point<float>(0.268f, 0.402f), juce::Point<float>(-0.268f, 0.402f),
        juce::Point<float>(-0.5f, 0.268f), juce::Point<float>(-0.5f, -0.268f), juce::Point<float>(-0.268f, -0.402f), juce::Point<float>(0.268f, -0.402f)
    };

    juce::Path H0104Path;
    juce::Point<int> H0104Pixel[6];
    juce::Point<float> H0104Position[6] = {
        juce::Point<float>(0.5f, -0.3050369756220235f),
        juce::Point<float>(0.16967676783553115f, -0.3998940634676139f),
        juce::Point<float>(-0.4999993320025777f, -0.3932502003992267f),
        juce::Point<float>(-0.4972911132766452f, 0.3998967747512691f),
        juce::Point<float>(0.16842281879194626f, 0.39935184603052354f),
        juce::Point<float>(0.5f, 0.3012348521760998f),
    };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Grid)
};

#endif /* GRID_H */