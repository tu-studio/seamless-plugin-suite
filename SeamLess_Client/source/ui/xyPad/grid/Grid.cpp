/*
=====================================================================

Grid.cpp
Created: 8 Sep 2021 14:00:00am
Author:  Fares Schulz

=====================================================================
*/

#include "Grid.h"

Grid::Grid(juce::AudioProcessorValueTreeState& pluginApvts) : apvts(pluginApvts) {
    setInterceptsMouseClicks(false,false);
    apvts.state.addListener(this);
}

Grid::~Grid() {
    apvts.state.removeListener(this);
}

void Grid::paint(juce::Graphics& g) {

    // draw the Grid
    g.setColour(juce::Colours::silver);
    switch ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::GRID_CHOICE_ID)) {
    case 0:
        break;
    case 1:
        // TODO update so that it is coherent with the XYPad x and y axis
        for (int i = -9; i<=9; i++) {
            g.drawLine(juce::Line<float>(convertMeterToPixel(-10.f, i), convertMeterToPixel(10.f, i)));
            g.drawLine(juce::Line<float>(convertMeterToPixel(i, -10.f), convertMeterToPixel(i, 10.f)));
        }
        break;
    case 2:
        // TODO update so that it is coherent with the XYPad x and y axis
        for (int i = 1; i <= 13; i++)
            g.drawRoundedRectangle(juce::Rectangle<float>(convertMeterToPixel(-i, -i), convertMeterToPixel(i, i)), 100 * (i), 1);
        
            g.drawLine(juce::Line<float>(convertMeterToPixel(0.f, 10.f), convertMeterToPixel(0.f, -10.f)), 0.8f);
            g.drawLine(juce::Line<float>(convertMeterToPixel(-10.f, 0.f), convertMeterToPixel(10.f, 0.f)), 0.8f);
            g.drawLine(juce::Line<float>(convertMeterToPixel(4.2264973081f - 10.f, 10.f),  convertMeterToPixel(5.7735026919f, -10.f)), 0.8f);
            g.drawLine(juce::Line<float>(convertMeterToPixel(4.2264973081f - 10.f, -10.f), convertMeterToPixel(5.7735026919f, 10.f)),  0.8f);
            g.drawLine(juce::Line<float>(convertMeterToPixel(-10.f, 4.2264973081f - 10.f), convertMeterToPixel(10.f, 5.7735026919f)),  0.8f);
            g.drawLine(juce::Line<float>(convertMeterToPixel(10.f, 4.2264973081f - 10.f),  convertMeterToPixel(-10.f, 5.7735026919f)), 0.8f);
        break;
    }

    // draw the Venue
    g.setColour(seamlessBlue);
    switch ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::VENUE_CHOICE_ID)) {
    case 0:
        g.strokePath(TUStudioPath, juce::PathStrokeType(5.0f));
        break;
    case 1:
        g.strokePath(HuFoPath, juce::PathStrokeType(5.0f));
        break;
    }

    // draw the outline
    g.drawRoundedRectangle(juce::Rectangle<float>(juce::Point<float>(4.f,4.f), juce::Point<float>((float) (getWidth()-4), (float) (getHeight()-4))), 25.f, 6.f);


}

void Grid::resized() {
    // Convert the HuFoPath from meter to pixel coordinates
    HuFoPath.clear();
    HuFoPixel[0] = convertMeterToPixel(HuFoMeter[0].getX(), HuFoMeter[0].getY());
    HuFoPath.startNewSubPath(HuFoPixel[0]);
    for (int i = 1; i <= 33; i++) {
        HuFoPixel[i] = convertMeterToPixel(HuFoMeter[i].getX(), HuFoMeter[i].getY());
        HuFoPath.lineTo(HuFoPixel[i]);
    }
    HuFoPath.closeSubPath();

    // Convert the TUStudioPath from meter to pixel coordinates
    TUStudioPath.clear();
    TUStudioPixel[0] = convertMeterToPixel(TUStudioMeter[0].getX(), TUStudioMeter[0].getY());
    TUStudioPath.startNewSubPath(TUStudioPixel[0]);
    for (int i = 1; i <= 7; i++) {
        TUStudioPixel[i] = convertMeterToPixel(TUStudioMeter[i].getX(), TUStudioMeter[i].getY());
        TUStudioPath.lineTo(TUStudioPixel[i]);
    }
    TUStudioPath.closeSubPath();
}

void Grid::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) {
    juce::ignoreUnused(treeWhosePropertyHasChanged);
    if (property.toString() == PluginParameters::GRID_CHOICE_ID || property.toString() == PluginParameters::VENUE_CHOICE_ID) repaint();
}

// TODO update so that it is coherent with the XYPad x and y axis
juce::Point<float> Grid::convertMeterToPixel(float xMeter, float yMeter)
{
    float xPixel = getLocalBounds().getWidth() * (xMeter + 10.f)/20.f;
    float yPixel = getLocalBounds().getHeight() * (- yMeter + 10.f)/20.f;
    return juce::Point<float>(xPixel, yPixel);
}

// TODO update so that it is coherent with the XYPad x and y axis
juce::Point<float> Grid::convertPixelToMeter(int xPixel, int yPixel)
{   
    float xMeter = (float) (xPixel) / getLocalBounds().getWidth() * 20.f - 10.f;
    float yMeter = (float) (yPixel) / getLocalBounds().getHeight() * 20.f - 10.f;
    return juce::Point<float>(xMeter, - yMeter);
}