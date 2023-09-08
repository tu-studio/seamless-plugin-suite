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
}

void Grid::paint(juce::Graphics& g) {

    // draw the Grid
    g.setColour(juce::Colours::silver);
    switch (apvts.state.getChild(0).getPropertyAsValue(PluginParameters::GRID_TYPE_ID, nullptr).toString().getIntValue()) {
    case 0:
        break;
    case 1:
        for (int i = -9; i<=9; i++) {
            g.drawLine(juce::Line<float>(convertMeterToPixel(-10, i), convertMeterToPixel(10, i)));
            g.drawLine(juce::Line<float>(convertMeterToPixel(i, -10), convertMeterToPixel(i, 10)));
        }
        break;
    case 2:
        for (int i = 1; i <= 13; i++)
            g.drawRoundedRectangle(juce::Rectangle<float>(convertMeterToPixel(-i, -i), convertMeterToPixel(i, i)), 100 * (i), 1);
        
            g.drawLine(juce::Line<float>(convertMeterToPixel(0, 10), convertMeterToPixel(0, -10)), 0.8f);
            g.drawLine(juce::Line<float>(convertMeterToPixel(-10, 0), convertMeterToPixel(10, 0)), 0.8f);
            g.drawLine(juce::Line<float>(convertMeterToPixel(4.2264973081f - 10, 10),  convertMeterToPixel(5.7735026919f, -10)), 0.8f);
            g.drawLine(juce::Line<float>(convertMeterToPixel(4.2264973081f - 10, -10), convertMeterToPixel(5.7735026919f, 10)),  0.8f);
            g.drawLine(juce::Line<float>(convertMeterToPixel(-10, 4.2264973081f - 10), convertMeterToPixel(10, 5.7735026919f)),  0.8f);
            g.drawLine(juce::Line<float>(convertMeterToPixel(10, 4.2264973081f - 10),  convertMeterToPixel(-10, 5.7735026919f)), 0.8f);
        break;
    }

    // draw the Venue
    g.setColour(seamlessBlue);
    switch (apvts.state.getChild(0).getPropertyAsValue(PluginParameters::VENUE_TYPE_ID, nullptr).toString().getIntValue()) {
    case 0:
        g.strokePath(TUStudioPath, juce::PathStrokeType(5.0f));
        break;
    case 1:
        g.strokePath(HuFoPath, juce::PathStrokeType(5.0f));
        break;
    }

    // draw the outline
    g.drawRoundedRectangle(juce::Rectangle<float>(juce::Point<float>(4,4), juce::Point<float>(getWidth()-4, getHeight()-4)), 25, 6);


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

void Grid::buttonClicked(juce::Button* button) {
    if (button->getComponentID() == PluginParameters::GRID_TYPE_ID) {
        switch (apvts.state.getChild(0).getPropertyAsValue(PluginParameters::GRID_TYPE_ID, nullptr).toString().getIntValue()) {
            case 0:
                button->setButtonText("Grid \nON \nxyz");
                apvts.state.getChild(0).setProperty(PluginParameters::GRID_TYPE_ID, 1, nullptr);
                break;
            case 1:
                button->setButtonText(juce::CharPointer_UTF8("Grid \nON \n r \xcf\x86 \xce\xb8\t"));
                apvts.state.getChild(0).setProperty(PluginParameters::GRID_TYPE_ID, 2, nullptr);
                break;
            case 2:
                button->setButtonText("Grid OFF");
                apvts.state.getChild(0).setProperty(PluginParameters::GRID_TYPE_ID, 0, nullptr);
                break;
        }
    }
    else if (button->getComponentID() == PluginParameters::VENUE_TYPE_ID) {
        switch (apvts.state.getChild(0).getPropertyAsValue(PluginParameters::VENUE_TYPE_ID, nullptr).toString().getIntValue()) {
            case 0:
                button->setButtonText("HuFo");
                apvts.state.getChild(0).setProperty(PluginParameters::VENUE_TYPE_ID, 1, nullptr);
                break;
            case 1:
                button->setButtonText("TU Studio");
                apvts.state.getChild(0).setProperty(PluginParameters::VENUE_TYPE_ID, 0, nullptr);
                break;
        }
    }
    repaint();
}

juce::Point<float> Grid::convertMeterToPixel(float xMeter, float yMeter)
{
    float xPixel = getLocalBounds().getWidth() * (xMeter + 10.f)/20.f;
    float yPixel = getLocalBounds().getHeight() * (- yMeter + 10.f)/20.f;
    return juce::Point<float>(xPixel, yPixel);
}

juce::Point<float> Grid::convertPixelToMeter(int xPixel, int yPixel)
{   
    float xMeter = (float) (xPixel) / getLocalBounds().getWidth() * 20.f - 10.f;
    float yMeter = (float) (yPixel) / getLocalBounds().getHeight() * 20.f - 10.f;
    return juce::Point<float>(xMeter, - yMeter);
}