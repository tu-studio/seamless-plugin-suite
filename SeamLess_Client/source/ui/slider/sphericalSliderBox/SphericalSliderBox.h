/*
=====================================================================

SphericalSliderBox.cpp
Created: 10 Sep 2023 08:00:00 pm
Author:  Fares Schulz

=====================================================================
*/

#ifndef SphericalSliderBox_h
#define SphericalSliderBox_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>
#include <CostumRotarySlider.h>
#include <XYPad.h>


class SphericalSliderBox : public juce::Component, private juce::Slider::Listener, private juce::AudioProcessorValueTreeState::Listener {
public:
    SphericalSliderBox(juce::AudioProcessorValueTreeState& apvts);
    void resized() override;
    
private:
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void sliderDragStarted(juce::Slider* slider) override;
    void sliderDragEnded(juce::Slider* slider) override;
    void updateSphericalCoordinates(float x, float y, float z);
    void updateCartesianCoordinates(float radius, float azimuth, float elevation);
    float limitMetricValue(float value);
    float normalizeMetricValue(float value);

private:
    CostumRotarySlider radiusSlider {"radius"};
    CostumRotarySlider azimuthSlider {"azimuth"};
    CostumRotarySlider elevationSlider {"elevation"};

    bool activeDrag = false;
    bool cartesianUpdate = false;
    
    juce::AudioProcessorValueTreeState& apvts;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SphericalSliderBox)
};

#endif /* SphericalSliderBox_h */
