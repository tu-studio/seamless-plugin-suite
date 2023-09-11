/*
=====================================================================

SphericalSliderBox.cpp
Created: 10 Sep 2023 08:00:00 pm
Author:  Fares Schulz

=====================================================================
*/

#include "SphericalSliderBox.h"

SphericalSliderBox::SphericalSliderBox(juce::AudioProcessorValueTreeState &a) : apvts(a) {

    radiusSlider.slider.addListener(this);
    radiusSlider.setDoubleClickReturnValue(0.f);
    radiusSlider.slider.setRange(0.f, 14.14213562373095f, 0.01f);
    radiusSlider.slider.getValueObject().referTo(apvts.state.getChild(0).getPropertyAsValue(PluginParameters::RADIUS_ID, nullptr));
    addAndMakeVisible(radiusSlider);

    azimuthSlider.slider.addListener(this);
    azimuthSlider.setDoubleClickReturnValue(0.f);
    azimuthSlider.slider.setRange(-180.f, 180.f, 0.01f);
    azimuthSlider.slider.getValueObject().referTo(apvts.state.getChild(0).getPropertyAsValue(PluginParameters::AZIMUTH_ID, nullptr));
    addAndMakeVisible(azimuthSlider);

    elevationSlider.slider.addListener(this);
    elevationSlider.setDoubleClickReturnValue(0.f);
    elevationSlider.slider.setRange(-90.f, 90.f, 0.01f);
    elevationSlider.slider.getValueObject().referTo(apvts.state.getChild(0).getPropertyAsValue(PluginParameters::ELEVATION_ID, nullptr));
    addAndMakeVisible(elevationSlider);

    apvts.addParameterListener(SendParameters::POS_X_ID.getParamID(), this);
    apvts.addParameterListener(SendParameters::POS_Y_ID.getParamID(), this);
    apvts.addParameterListener(SendParameters::POS_Z_ID.getParamID(), this);
}

void SphericalSliderBox::resized() {
    auto area = getLocalBounds();
    radiusSlider.setBounds(0, 0, area.getWidth()/3, area.getHeight());
    azimuthSlider.setBounds(area.getWidth()/3, 0, area.getWidth()/3, area.getHeight());
    elevationSlider.setBounds(area.getWidth()*2/3, 0, area.getWidth()/3, area.getHeight());
}

void SphericalSliderBox::parameterChanged(const juce::String& parameterID, float newValue) {
    if (!activeDrag) {
        float x = apvts.getParameterAsValue(SendParameters::POS_X_ID.getParamID()).toString().getFloatValue();
        float y = apvts.getParameterAsValue(SendParameters::POS_Y_ID.getParamID()).toString().getFloatValue();
        float z = apvts.getParameterAsValue(SendParameters::POS_Z_ID.getParamID()).toString().getFloatValue();

        if (parameterID == SendParameters::POS_X_ID.getParamID()) {
            x = newValue;
        } else if (parameterID == SendParameters::POS_Y_ID.getParamID()) {
            y = newValue;
        } else if (parameterID == SendParameters::POS_Z_ID.getParamID()) {
            z = newValue;
        }
        updateSphericalCoordinates(x, y, z);
    }
}

void SphericalSliderBox::updateSphericalCoordinates(float x, float y, float z) {
    float radius = sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
    float azimuth = atan2f(y, x) * 180  / (float) M_PI;
    float elevation = asinf(z / radius) * 180 / (float) M_PI;

    apvts.state.getChild(0).setProperty(PluginParameters::RADIUS_ID, radius, nullptr);
    apvts.state.getChild(0).setProperty(PluginParameters::AZIMUTH_ID, azimuth, nullptr);
    apvts.state.getChild(0).setProperty(PluginParameters::ELEVATION_ID, elevation, nullptr);
}

void SphericalSliderBox::sliderValueChanged(juce::Slider* slider) {
    float radius = (float) radiusSlider.slider.getValue();
    float azimuth = (float) azimuthSlider.slider.getValue();
    float elevation = (float) elevationSlider.slider.getValue();

    if (slider == &radiusSlider.slider) {
        radius = (float) slider->getValue();
    } else if (slider == &azimuthSlider.slider) {
        azimuth = (float) slider->getValue();
    } else if (slider == &elevationSlider.slider) {
        elevation = (float) slider->getValue();
    }
    updateCartesianCoordinates(radius, azimuth, elevation);
}

void SphericalSliderBox::sliderDragStarted(juce::Slider* slider) {
    juce::ignoreUnused(slider);
    activeDrag = true;
}

void SphericalSliderBox::sliderDragEnded(juce::Slider* slider) {
    juce::ignoreUnused(slider);
    activeDrag = false;
}

void SphericalSliderBox::updateCartesianCoordinates(float radius, float azimuth, float elevation) {
    float x = limitMetricValue(radius * cosf(azimuth * (float) M_PI / 180) * cosf(elevation * (float) M_PI / 180));
    x = normalizeMetricValue(x);
    float y = limitMetricValue(radius * sinf(azimuth * (float) M_PI / 180) * cosf(elevation * (float) M_PI / 180));
    y = normalizeMetricValue(y);
    float z = limitMetricValue(radius * sinf(elevation * (float) M_PI / 180));
    z = normalizeMetricValue(z);
    
    juce::AudioProcessorParameterWithID *xParam = apvts.getParameter(SendParameters::POS_X_ID.getParamID());
    juce::AudioProcessorParameterWithID *yParam = apvts.getParameter(SendParameters::POS_Y_ID.getParamID());
    juce::AudioProcessorParameterWithID *zParam = apvts.getParameter(SendParameters::POS_Z_ID.getParamID());


    xParam->beginChangeGesture();
    xParam->setValueNotifyingHost(x);
    xParam->endChangeGesture();

    yParam->beginChangeGesture();
    yParam->setValueNotifyingHost(y);
    yParam->endChangeGesture();

    zParam->beginChangeGesture();
    zParam->setValueNotifyingHost(z);
    zParam->endChangeGesture();
}

float SphericalSliderBox::limitMetricValue(float value) {
    if (value > 10.f) {
        return 10.f;
    } else if (value < -10.f) {
        return -10.f;
    } else {
        return value;
    }
}

float SphericalSliderBox::normalizeMetricValue(float value) {
    return (value + 10.f) / 20.f;
}