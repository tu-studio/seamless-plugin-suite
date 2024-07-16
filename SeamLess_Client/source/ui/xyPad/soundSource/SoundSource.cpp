/*
=====================================================================

SoundSource.cpp
Created: 7 Sep 2021 11:00:00am
Author:  Fares Schulz

=====================================================================
*/

# include "SoundSource.h"

SoundSource::SoundSource() {
    // this makes the component ignore mouse events
    // and they reach the parent component
    setInterceptsMouseClicks(false,false);
}

void SoundSource::paint(juce::Graphics& g) {
    auto area = getLocalBounds();
    g.setGradientFill(gradient);
    g.fillEllipse(area.getX(), area.getY(), area.getWidth(), area.getHeight());
}

void SoundSource::resized() {
    auto area = getLocalBounds();
    gradient = juce::ColourGradient(juce::Colours::whitesmoke, area.getWidth()/2, area.getHeight()/2, tuStudioPurple, area.getX(), area.getY(), true);
}