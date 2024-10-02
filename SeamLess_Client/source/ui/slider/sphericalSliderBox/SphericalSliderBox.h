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


class SphericalSliderBox : public juce::Component, private juce::Slider::Listener {
public:
    SphericalSliderBox(juce::AudioProcessorValueTreeState& apvts);
    ~SphericalSliderBox() override;
    void paint(juce::Graphics& g) override;
    void resized() override;
    
private:
    void addParameterAttachment(juce::RangedAudioParameter& parameter);
    void sliderValueChanged(juce::Slider* slider) override;
    void sliderDragStarted(juce::Slider* slider) override;
    void sliderDragEnded(juce::Slider* slider) override;
    void updateSphericalCoordinates();
    void updateCartesianCoordinates(float radius, float azimuth, float elevation);
    float limitMetricValue(float value);
    float normalizeMetricValue(float value);

private:
    CostumRotarySlider radiusSlider {"radius"};
    CostumRotarySlider azimuthSlider {"azimuth"};
    CostumRotarySlider elevationSlider {"elevation"};

    float m_x = 0.f, m_y = 0.f, m_z = 0.f;
    bool activeDrag = false;
    bool cartesianUpdate = false;
    float cartesian_coordinate_limit = 1.f;
    juce::AudioProcessorValueTreeState& apvts;
    std::unique_ptr<juce::ParameterAttachment> xAttachment;
    std::unique_ptr<juce::ParameterAttachment> yAttachment;
    std::unique_ptr<juce::ParameterAttachment> zAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SphericalSliderBox)
};

#endif /* SphericalSliderBox_h */
