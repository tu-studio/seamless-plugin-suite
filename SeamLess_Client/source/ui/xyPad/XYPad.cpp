/*
=====================================================================

XYPad.cpp
Created: 7 Sep 2021 11:00:00am
Author:  Fares Schulz

=====================================================================
*/

# include "XYPad.h"

XYPad::XYPad(juce::AudioProcessorValueTreeState& pluginApvts) : apvts(pluginApvts), grid(pluginApvts), sourceShadow(tuStudioTransparentLightLavender, 4, juce::Point<int>(0, 0)) {
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
    soundSource.setBounds(convertPositionToPixel(xPosition, yPosition).getX() - sourceWidthPx/2, convertPositionToPixel(xPosition, yPosition).getY() - sourceWidthPx/2, sourceWidthPx, sourceWidthPx);
}

void XYPad::mouseDown(const juce::MouseEvent& e)
{
    auto pos = convertPixelToPosition(e.x, e.y);
    xAttachment->setValueAsCompleteGesture(pos.x);
    yAttachment->setValueAsCompleteGesture(pos.y);

    xAttachment->beginGesture();
    yAttachment->beginGesture();

    coordinatesLabel.updateCoordinatesLabelText(pos.x, pos.y);
    coordinatesLabel.setVisible(true);
}

void XYPad::mouseDrag (const juce::MouseEvent& e)
{
    auto pos = convertPixelToPosition(e.x, e.y);
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

juce::Point<int> XYPad::convertPositionToPixel(float xPosition, float yPosition)
{
    int xPixel = (int) (getLocalBounds().getWidth() * (- yPosition + 1.f)/2.f);
    int yPixel = (int) (getLocalBounds().getHeight() * (- xPosition + 1.f)/2.f);
    return juce::Point<int>(xPixel, yPixel);
}

juce::Point<float> XYPad::convertPixelToPosition(int xPixel, int yPixel)
{   
    float xPosition = (float) (yPixel) / getLocalBounds().getWidth() * 2.f - 1.f;
    float yPosition = (float) (xPixel) / getLocalBounds().getHeight() * 2.f - 1.f;
    return juce::Point<float>(- xPosition, - yPosition);
}

void XYPad::updateSourceWidthPx() {
    this->sourceWidthPx = (int) (20.f + 10.f*this->zPosition);
}

// TODO paint Shadow in SoundSource class
void XYPad::paintSourceShadow(juce::Graphics &g) {
    float shadowWidth = sourceWidthPx*(1.1f + zPosition/2.f);
    float shadowXShift = - 10.f*yPosition * (1.f + zPosition);
    float shadowYShift = - 10.f*xPosition * (1.f + zPosition);
    shadowOrigin.addEllipse((convertPositionToPixel(xPosition, yPosition).getX() - shadowWidth/2) + shadowXShift,
                            (convertPositionToPixel(xPosition, yPosition).getY() - shadowWidth/2) + shadowYShift,
                            shadowWidth,
                            shadowWidth);
    sourceShadow.drawForPath(g, shadowOrigin);
    shadowOrigin.clear();
}