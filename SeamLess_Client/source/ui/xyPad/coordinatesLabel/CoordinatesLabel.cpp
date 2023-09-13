/*
=====================================================================

CoordinatesLabel.cpp
Created: 8 Sep 2021
Author:  Fares Schulz

=====================================================================
*/

#include "CoordinatesLabel.h"

CoordinatesLabel::CoordinatesLabel() {
    // this makes the component ignore mouse events
    // and they reach the parent component
    setInterceptsMouseClicks(false,false);

    setText("", juce::dontSendNotification);
    setJustificationType(juce::Justification::centred);
    setColour(juce::Label::textColourId, juce::Colours::darkgrey);
    setVisible(false);
    setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), 14.0f, 0));
}

void CoordinatesLabel::updateCoordinatesLabelText(float newXPosition, float newYPosition) {
    newXPosition = limitMetricValue(newXPosition);
    newYPosition = limitMetricValue(newYPosition);
    coordinatesLabelText = "x = " + juce::String(newXPosition, 2) + "\ny = " + juce::String(newYPosition, 2);
    setText(coordinatesLabelText, juce::dontSendNotification);
}

float CoordinatesLabel::limitMetricValue(float value) {
    if (value > 10.f)
        return 10.f;
    else if (value < -10.f)
        return -10.f;
    else return value;
}