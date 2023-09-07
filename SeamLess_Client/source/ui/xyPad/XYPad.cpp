/*
=====================================================================

XYPad.cpp
Created: 7 Sep 2021 11:00:00am
Author:  Fares Schulz

=====================================================================
*/

# include "XYPad.h"

XYPad::XYPad(juce::AudioProcessorValueTreeState& pluginApvts) : apvts(pluginApvts) {
    addParameterAttachment(*(apvts.getParameter(SendParameters::POS_X_ID.getParamID())));
    addParameterAttachment(*(apvts.getParameter(SendParameters::POS_Y_ID.getParamID())));
    addAndMakeVisible(soundSource);
}

void XYPad::paint(juce::Graphics& g) {
    g.setColour(seamlessBlue);
    g.fillRoundedRectangle(0,0,getWidth(),getHeight(),30);

    g.setColour(seamlessLightGrey);
    g.fillRoundedRectangle(5,5,getWidth()-10,getHeight()-10,25);
}

void XYPad::resized() {
    soundSource.setBounds(convertMeterToPixel(xPosition, yPosition).getX() - sourceWidthPx/2, convertMeterToPixel(xPosition, yPosition).getY() - sourceWidthPx/2, sourceWidthPx, sourceWidthPx);
}

void XYPad::mouseDown(const juce::MouseEvent& e)
{
    auto pos = convertPixelToMeter(e.x, e.y);
    xAttachment->setValueAsCompleteGesture(pos.x);
    yAttachment->setValueAsCompleteGesture(pos.y);

    xAttachment->beginGesture();
    yAttachment->beginGesture();
}

void XYPad::mouseDrag (const juce::MouseEvent& e)
{
    auto pos = convertPixelToMeter(e.x, e.y);
    xAttachment->setValueAsPartOfGesture(pos.x);
    yAttachment->setValueAsPartOfGesture(pos.y);
}

void XYPad::mouseUp(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    xAttachment->endGesture();
    yAttachment->endGesture();
}

void XYPad::addParameterAttachment(juce::RangedAudioParameter& parameter) {
    if (parameter.paramID == SendParameters::POS_X_ID.getParamID()) {
        xAttachment = std::make_unique<juce::ParameterAttachment>(
            parameter,
            // callback function on parameter change
            [this](float newValue) {
                this->xPosition = newValue;
                resized();
            },
            // undo manager
            nullptr);
        xAttachment->sendInitialUpdate();
    } else if (parameter.paramID == SendParameters::POS_Y_ID.getParamID()) {
        yAttachment = std::make_unique<juce::ParameterAttachment>(
            parameter,
            // callback function on parameter change
            [this](float newValue) {
                this->yPosition = newValue;
                resized();
            },
            // undo manager
            nullptr);
        yAttachment->sendInitialUpdate();
    }
}

juce::Point<int> XYPad::convertMeterToPixel(float xMeter, float yMeter)
{
    int xPixel = (int) (getLocalBounds().getWidth() * (xMeter + 10.f)/20.f);
    int yPixel = (int) (getLocalBounds().getHeight() * (yMeter + 10.f)/20.f);
    return juce::Point<int>(xPixel, yPixel);
}

juce::Point<float> XYPad::convertPixelToMeter(int xPixel, int yPixel)
{   
    float xMeter = (float) (xPixel) / getLocalBounds().getWidth() * 20.f - 10.f;
    float yMeter = (float) (yPixel) / getLocalBounds().getHeight() * 20.f - 10.f;
    return juce::Point<float>(xMeter, yMeter);
}