/*
=====================================================================

XYPad.cpp
Created: 7 Sep 2021 11:00:00am
Author:  Fares Schulz

=====================================================================
*/

# include "XYPad.h"

XYPad::XYPad(juce::AudioProcessorValueTreeState& pluginApvts) : apvts(pluginApvts), grid(pluginApvts) {
    addParameterAttachment(*(apvts.getParameter(OSCParameters::POS_X_ID.getParamID())));
    addParameterAttachment(*(apvts.getParameter(OSCParameters::POS_Y_ID.getParamID())));
    addParameterAttachment(*(apvts.getParameter(OSCParameters::POS_Z_ID.getParamID())));

    addAndMakeVisible(grid);

    addAndMakeVisible(soundSource);

    addAndMakeVisible(coordinatesLabel);
    coordinatesLabel.setVisible(false);
}

void XYPad::paint(juce::Graphics& g) {
    paintSourceShadow(g);
}

void XYPad::resized() {
    grid.setBounds(getLocalBounds());
    if (xPosition < -1.7f && yPosition < -6.7f)
        coordinatesLabel.setBounds(getLocalBounds().getX() + getLocalBounds().getWidth() - 90 - 10, getLocalBounds().getY() + getLocalBounds().getHeight() - 45, 90, 30);
    else coordinatesLabel.setBounds(getLocalBounds().getX() + 10, getLocalBounds().getY() + getLocalBounds().getHeight() - 45, 90, 30);
    soundSource.setBounds(convertMeterToPixel(xPosition, yPosition).getX() - sourceWidthPx/2, convertMeterToPixel(xPosition, yPosition).getY() - sourceWidthPx/2, sourceWidthPx, sourceWidthPx);
}

void XYPad::mouseDown(const juce::MouseEvent& e)
{
    auto pos = convertPixelToMeter(e.x, e.y);
    xAttachment->setValueAsCompleteGesture(pos.x);
    yAttachment->setValueAsCompleteGesture(pos.y);

    xAttachment->beginGesture();
    yAttachment->beginGesture();

    coordinatesLabel.updateCoordinatesLabelText(pos.x, pos.y);
    coordinatesLabel.setVisible(true);
}

void XYPad::mouseDrag (const juce::MouseEvent& e)
{
    auto pos = convertPixelToMeter(e.x, e.y);
    xAttachment->setValueAsPartOfGesture(pos.x);
    yAttachment->setValueAsPartOfGesture(pos.y);

    coordinatesLabel.updateCoordinatesLabelText(pos.x, pos.y);
}

void XYPad::mouseUp(const juce::MouseEvent& e)
{
    juce::ignoreUnused(e);

    xAttachment->endGesture();
    yAttachment->endGesture();

    coordinatesLabel.setVisible(false);
}

void XYPad::setSourceWidthPx(int newSourceWidthPx) {
    this->sourceWidthPx = newSourceWidthPx;
}

void XYPad::addParameterAttachment(juce::RangedAudioParameter& parameter) {
    if (parameter.paramID == OSCParameters::POS_X_ID.getParamID()) {
        xAttachment = std::make_unique<juce::ParameterAttachment>(
            parameter,
            // callback function on parameter change
            [this](float newValue) {
                this->xPosition = newValue;
                resized();
                repaint();
            },
            // undo manager
            nullptr);
        xAttachment->sendInitialUpdate();
    } else if (parameter.paramID == OSCParameters::POS_Y_ID.getParamID()) {
        yAttachment = std::make_unique<juce::ParameterAttachment>(
            parameter,
            // callback function on parameter change
            [this](float newValue) {
                this->yPosition = newValue;
                resized();
                repaint();
            },
            // undo manager
            nullptr);
        yAttachment->sendInitialUpdate();
    } else if (parameter.paramID == OSCParameters::POS_Z_ID.getParamID()) {
        zAttachment = std::make_unique<juce::ParameterAttachment>(
            parameter,
            // callback function on parameter change
            [this](float newValue) {
                this->zPosition = newValue;
                updateSourceWidthPx();
                resized();
                repaint();
            },
            // undo manager
            nullptr);
        zAttachment->sendInitialUpdate();
    }
}

juce::Point<int> XYPad::convertMeterToPixel(float xMeter, float yMeter)
{
    int xPixel = (int) (getLocalBounds().getWidth() * (xMeter + 10.f)/20.f);
    int yPixel = (int) (getLocalBounds().getHeight() * (- yMeter + 10.f)/20.f);
    return juce::Point<int>(xPixel, yPixel);
}

juce::Point<float> XYPad::convertPixelToMeter(int xPixel, int yPixel)
{   
    float xMeter = (float) (xPixel) / getLocalBounds().getWidth() * 20.f - 10.f;
    float yMeter = (float) (yPixel) / getLocalBounds().getHeight() * 20.f - 10.f;
    return juce::Point<float>(xMeter, - yMeter);
}

void XYPad::updateSourceWidthPx() {
    this->sourceWidthPx = (int) (20 + this->zPosition);
}

// TODO paint Shadow in SoundSource class
void XYPad::paintSourceShadow(juce::Graphics &g) {
    g.setColour(juce::Colours::darkgrey);
    float shadowWidth = sourceWidthPx*(1.1f + zPosition/20.f);
    float shadowXShift = xPosition * (1.f + zPosition/10.f);
    float shadowYShift = - yPosition * (1.f + zPosition/10.f);
    shadowOrigin.addEllipse((convertMeterToPixel(xPosition, yPosition).getX() - shadowWidth/2) + shadowXShift,
                            (convertMeterToPixel(xPosition, yPosition).getY() - shadowWidth/2) + shadowYShift,
                            shadowWidth,
                            shadowWidth);
    sourceShadow.drawForPath(g, shadowOrigin);
    shadowOrigin.clear();
}