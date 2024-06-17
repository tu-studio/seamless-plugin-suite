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
        juce::Point<float>(-6.051f, 2.112f), juce::Point<float>(-5.392f, 2.593f), juce::Point<float>(-4.695f, 3.018f), juce::Point<float>(-3.964f, 3.382f), juce::Point<float>(-3.205f, 3.684f), juce::Point<float>(-2.424f, 3.921f), juce::Point<float>(-1.625f, 4.091f), juce::Point<float>(-0.816f, 4.194f), juce::Point<float>(-0.0f, 4.228f), juce::Point<float>(0.816f, 4.194f), juce::Point<float>(1.626f, 4.091f), juce::Point<float>(2.424f, 3.921f), juce::Point<float>(3.206f, 3.684f), juce::Point<float>(3.964f, 3.382f), juce::Point<float>(4.695f, 3.017f), juce::Point<float>(5.392f, 2.593f), juce::Point<float>(6.054f, 2.107f), juce::Point<float>(6.051f, -2.112f), juce::Point<float>(5.392f, -2.593f), juce::Point<float>(4.695f, -3.018f), juce::Point<float>(3.964f, -3.382f), juce::Point<float>(3.205f, -3.684f), juce::Point<float>(2.424f, -3.921f), juce::Point<float>(1.625f, -4.091f), juce::Point<float>(0.816f, -4.194f), juce::Point<float>(0.0f, -4.228f), juce::Point<float>(-0.816f, -4.194f), juce::Point<float>(-1.626f, -4.091f), juce::Point<float>(-2.424f, -3.921f), juce::Point<float>(-3.206f, -3.684f), juce::Point<float>(-3.964f, -3.382f), juce::Point<float>(-4.695f, -3.017f), juce::Point<float>(-5.392f, -2.593f), juce::Point<float>(-6.054f, -2.107f)
    };
        
    juce::Path TUStudioPath;
    juce::Point<int> TUStudioPixel[8];
    juce::Point<float> TUStudioPosition[8] = {
        juce::Point<float>(0.5f, -0.268f), juce::Point<float>(0.5f, 0.268f), juce::Point<float>(0.268f, 0.402f), juce::Point<float>(-0.268f, 0.402f),
        juce::Point<float>(-0.5f, 0.268f), juce::Point<float>(-0.5f, -0.268f), juce::Point<float>(-0.268f, -0.402f), juce::Point<float>(0.268f, -0.402f)
    };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Grid)
};

#endif /* GRID_H */