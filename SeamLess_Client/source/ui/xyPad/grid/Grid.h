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

class Grid : public juce::Component, public juce::Button::Listener {
    
public:
    Grid(juce::AudioProcessorValueTreeState& pluginApvts);

private:
    juce::Point<float> convertMeterToPixel(float xMeter, float yMeter);
    juce::Point<float> convertPixelToMeter(int xPixel, int yPixel);
    void paint(juce::Graphics& g) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:

    juce::AudioProcessorValueTreeState& apvts;

    // HuFo graphical shape
    juce::Path HuFoPath;
    juce::Point<float> HuFoPixel[34];
    juce::Point<float> HuFoMeter[34] = {
        juce::Point<float>(-6.051f, 2.112f), juce::Point<float>(-5.392f, 2.593f), juce::Point<float>(-4.695f, 3.018f), juce::Point<float>(-3.964f, 3.382f), juce::Point<float>(-3.205f, 3.684f), juce::Point<float>(-2.424f, 3.921f), juce::Point<float>(-1.625f, 4.091f), juce::Point<float>(-0.816f, 4.194f), juce::Point<float>(-0.0f, 4.228f), juce::Point<float>(0.816f, 4.194f), juce::Point<float>(1.626f, 4.091f), juce::Point<float>(2.424f, 3.921f), juce::Point<float>(3.206f, 3.684f), juce::Point<float>(3.964f, 3.382f), juce::Point<float>(4.695f, 3.017f), juce::Point<float>(5.392f, 2.593f), juce::Point<float>(6.054f, 2.107f), juce::Point<float>(6.051f, -2.112f), juce::Point<float>(5.392f, -2.593f), juce::Point<float>(4.695f, -3.018f), juce::Point<float>(3.964f, -3.382f), juce::Point<float>(3.205f, -3.684f), juce::Point<float>(2.424f, -3.921f), juce::Point<float>(1.625f, -4.091f), juce::Point<float>(0.816f, -4.194f), juce::Point<float>(0.0f, -4.228f), juce::Point<float>(-0.816f, -4.194f), juce::Point<float>(-1.626f, -4.091f), juce::Point<float>(-2.424f, -3.921f), juce::Point<float>(-3.206f, -3.684f), juce::Point<float>(-3.964f, -3.382f), juce::Point<float>(-4.695f, -3.017f), juce::Point<float>(-5.392f, -2.593f), juce::Point<float>(-6.054f, -2.107f)
    };
        
    juce::Path TUStudioPath;
    juce::Point<float> TUStudioPixel[34];
    juce::Point<float> TUStudioMeter[8] = {
        juce::Point<float>(-1.620f, 3.023f), juce::Point<float>(1.620f, 3.023f), juce::Point<float>(2.430f, 1.620f), juce::Point<float>(2.430f, -1.620f),
        juce::Point<float>(1.620f, -3.023f), juce::Point<float>(-1.620f, -3.023f), juce::Point<float>(-2.430f, -1.620f), juce::Point<float>(-2.430f,1.620f)
    };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Grid)
};

#endif /* GRID_H */