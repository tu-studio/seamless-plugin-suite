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
        for (float i = -0.9f; i<0.91; i+=0.1) {
            g.drawLine(juce::Line<float>(convertPositionToPixel(-1.f, i).toFloat(), convertPositionToPixel(1.f, i).toFloat()));
            g.drawLine(juce::Line<float>(convertPositionToPixel(i, -1.f).toFloat(), convertPositionToPixel(i, 1.f).toFloat()));
        }
        break;
    case 2:
        for (float i = 0.1f; i < 1.31; i+=0.1f) {
            g.drawRoundedRectangle(juce::Rectangle<float>(convertPositionToPixel(-i, -i).toFloat(), convertPositionToPixel(i, i).toFloat()), 1000 * (i), 1);
        }
        g.drawLine(juce::Line<float>(convertPositionToPixel(0.f, 1.f).toFloat(), convertPositionToPixel(0.f, -1.f).toFloat()), 0.8f);
        g.drawLine(juce::Line<float>(convertPositionToPixel(-1.f, 0.f).toFloat(), convertPositionToPixel(1.f, 0.f).toFloat()), 0.8f);
        g.drawLine(juce::Line<float>(convertPositionToPixel(0.42264973081f - 1.f, 1.f).toFloat(),  convertPositionToPixel(0.57735026919f, -1.f).toFloat()), 0.8f);
        g.drawLine(juce::Line<float>(convertPositionToPixel(0.42264973081f - 1.f, -1.f).toFloat(), convertPositionToPixel(0.57735026919f, 1.f).toFloat()),  0.8f);
        g.drawLine(juce::Line<float>(convertPositionToPixel(-1.f, 0.42264973081f - 1.f).toFloat(), convertPositionToPixel(1.f, 0.57735026919f).toFloat()),  0.8f);
        g.drawLine(juce::Line<float>(convertPositionToPixel(1.f, 0.42264973081f - 1.f).toFloat(),  convertPositionToPixel(-1.f, 0.57735026919f).toFloat()), 0.8f);
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
    // Convert the HuFoPath from position to pixel coordinates
    HuFoPath.clear();
    HuFoPixel[0] = convertPositionToPixel(HuFoPosition[0].getX(), HuFoPosition[0].getY());
    HuFoPath.startNewSubPath(HuFoPixel[0].toFloat());
    for (int i = 1; i <= 33; i++) {
        HuFoPixel[i] = convertPositionToPixel(HuFoPosition[i].getX(), HuFoPosition[i].getY());
        HuFoPath.lineTo(HuFoPixel[i].toFloat());
    }
    HuFoPath.closeSubPath();

    // Convert the TUStudioPath from position to pixel coordinates
    TUStudioPath.clear();
    TUStudioPixel[0] = convertPositionToPixel(TUStudioPosition[0].getX(), TUStudioPosition[0].getY());
    TUStudioPath.startNewSubPath(TUStudioPixel[0].toFloat());
    for (int i = 1; i <= 7; i++) {
        TUStudioPixel[i] = convertPositionToPixel(TUStudioPosition[i].getX(), TUStudioPosition[i].getY());
        TUStudioPath.lineTo(TUStudioPixel[i].toFloat());
    }
    TUStudioPath.closeSubPath();
}

void Grid::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) {
    juce::ignoreUnused(treeWhosePropertyHasChanged);
    if (property.toString() == PluginParameters::GRID_CHOICE_ID || property.toString() == PluginParameters::VENUE_CHOICE_ID) repaint();
}

juce::Point<int> Grid::convertPositionToPixel(float xPosition, float yPosition)
{
    int xPixel = (int) (getLocalBounds().getWidth() * (- yPosition + 1.f)/2.f);
    int yPixel = (int) (getLocalBounds().getHeight() * (- xPosition + 1.f)/2.f);
    return juce::Point<int>(xPixel, yPixel);
}

juce::Point<float> Grid::convertPixelToPosition(int xPixel, int yPixel)
{   
    float xPosition = (float) (yPixel) / getLocalBounds().getWidth() * 2.f - 1.f;
    float yPosition = (float) (xPixel) / getLocalBounds().getHeight() * 2.f - 1.f;
    return juce::Point<float>(- xPosition, - yPosition);
}