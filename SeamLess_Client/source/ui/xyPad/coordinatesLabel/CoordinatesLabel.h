/*
=====================================================================

CoordinatesLabel.h
Created: 8 Sep 2021 11:00:00am
Author:  Fares Schulz

=====================================================================
*/

#ifndef COORDINATES_LABEL_H
#define COORDINATES_LABEL_H

#include <JuceHeader.h>

class CoordinatesLabel : public juce::Label {
    
public:
    CoordinatesLabel();

    void updateCoordinatesLabelText(float newXPosition, float newYPosition);

private:
    float limitMetricValue(float value);

private:
    juce::String coordinatesLabelText;    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CoordinatesLabel)
};

#endif /* COORDINATES_LABEL_H */