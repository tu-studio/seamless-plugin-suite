/*
=====================================================================

SphericalSliderBox.cpp
Created: 10 Sep 2023 08:00:00 pm
Author:  Fares Schulz

=====================================================================
*/

#include "SphericalSliderBox.h"

SphericalSliderBox::SphericalSliderBox(juce::AudioProcessorValueTreeState &a) : apvts(a) {

    radiusSlider.setDoubleClickReturnValue(0.f);
    // maximum value of radius is outer most corner of bounding box
    radiusSlider.slider.setRange(0.f, sqrt(3*(cartesian_coordinate_limit*cartesian_coordinate_limit)), 0.001f);
    radiusSlider.slider.getValueObject().referTo(apvts.state.getChildWithName("Settings").getPropertyAsValue(PluginParameters::RADIUS_ID, nullptr));
    addAndMakeVisible(radiusSlider);

    azimuthSlider.setDoubleClickReturnValue(0.f);
    azimuthSlider.slider.setRange(-180.f, 180.f, 0.01f);
    azimuthSlider.slider.setInverted(true);
    azimuthSlider.slider.getValueObject().referTo(apvts.state.getChildWithName("Settings").getPropertyAsValue(PluginParameters::AZIMUTH_ID, nullptr));
    addAndMakeVisible(azimuthSlider);

    elevationSlider.setDoubleClickReturnValue(0.f);
    elevationSlider.slider.setRange(-90.f, 90.f, 0.01f);
    elevationSlider.slider.getValueObject().referTo(apvts.state.getChildWithName("Settings").getPropertyAsValue(PluginParameters::ELEVATION_ID, nullptr));
    addAndMakeVisible(elevationSlider);

    radiusSlider.slider.addListener(this);
    azimuthSlider.slider.addListener(this);
    elevationSlider.slider.addListener(this);
    addParameterAttachment(*(apvts.getParameter(OSCParameters::POS_X_ID.getParamID())));
    addParameterAttachment(*(apvts.getParameter(OSCParameters::POS_Y_ID.getParamID())));
    addParameterAttachment(*(apvts.getParameter(OSCParameters::POS_Z_ID.getParamID())));
}

SphericalSliderBox::~SphericalSliderBox() {
    radiusSlider.slider.removeListener(this);
    azimuthSlider.slider.removeListener(this);
    elevationSlider.slider.removeListener(this);
}


void SphericalSliderBox::paint(juce::Graphics &g) {
    g.setColour (tuStudioPurple);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 15);   // draw an outline around the component
}

void SphericalSliderBox::resized() {
    auto area = getLocalBounds();
    auto spacingBetween = area.getWidth()/40;
    auto sliderWidth = (area.getWidth() - 3*spacingBetween)/2;
    auto sliderHeight = (area.getHeight() - 3*spacingBetween)/2;
    area = area.reduced(spacingBetween);
    auto topSlider = area.removeFromTop(sliderHeight);
    area.removeFromTop(spacingBetween);
    auto bottomSlider = area;

    azimuthSlider.setBounds(topSlider.removeFromLeft(sliderWidth));
    topSlider.removeFromLeft(spacingBetween);
    elevationSlider.setBounds(topSlider.removeFromLeft(sliderWidth));
    bottomSlider.removeFromLeft(bottomSlider.getWidth()/4);
    radiusSlider.setBounds(bottomSlider.removeFromLeft(sliderWidth));
}

void SphericalSliderBox::addParameterAttachment(juce::RangedAudioParameter& parameter) {
    if (parameter.paramID == OSCParameters::POS_X_ID.getParamID()) {
        xAttachment = std::make_unique<juce::ParameterAttachment>(
            parameter,
            // callback function on parameter change
            [this] (float newValue) {
                this->m_x = newValue;
                this->updateSphericalCoordinates();
            },
            // undo manager
            nullptr);
        xAttachment->sendInitialUpdate();
    } else if (parameter.paramID == OSCParameters::POS_Y_ID.getParamID()) {
        yAttachment = std::make_unique<juce::ParameterAttachment>(
            parameter,
            // callback function on parameter change
            [this] (float newValue) {
                this->m_y = newValue;
                this->updateSphericalCoordinates();
            },
            // undo manager
            nullptr);
        yAttachment->sendInitialUpdate();
    } else if (parameter.paramID == OSCParameters::POS_Z_ID.getParamID()) {
        zAttachment = std::make_unique<juce::ParameterAttachment>(
            parameter,
            // callback function on parameter change
            [this] (float newValue) {
                this->m_z = newValue;
                this->updateSphericalCoordinates();
            },
            // undo manager
            nullptr);
        zAttachment->sendInitialUpdate();
    }
}

void SphericalSliderBox::updateSphericalCoordinates() {
    if (!activeDrag) {
        float radius, azimuth, elevation;

        radius = sqrtf(powf(m_x, 2) + powf(m_y, 2) + powf(m_z, 2));
        azimuth = atan2f(m_y, m_x) * 180  / (float) M_PI;
        if (radius != 0.f) elevation = asinf(m_z / radius) * 180 / (float) M_PI;
        else elevation = 0.f;

        // std::printf("update spherical from x=%f, y=%f, z=%f, new a=%f, e=%f, d=%f\n", m_x, m_y, m_z, azimuth, elevation, radius);

        apvts.state.getChildWithName("Settings").setProperty(PluginParameters::RADIUS_ID, radius, nullptr);
        apvts.state.getChildWithName("Settings").setProperty(PluginParameters::AZIMUTH_ID, azimuth, nullptr);
        apvts.state.getChildWithName("Settings").setProperty(PluginParameters::ELEVATION_ID, elevation, nullptr);
    }
}

void SphericalSliderBox::sliderValueChanged(juce::Slider* slider) {
    float radius = (float) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::RADIUS_ID);
    float azimuth = (float) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::AZIMUTH_ID);
    float elevation = (float) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::ELEVATION_ID);

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
    m_x = normalizeMetricValue(x);
    float y = limitMetricValue(radius * sinf(azimuth * (float) M_PI / 180) * cosf(elevation * (float) M_PI / 180));
    m_y = normalizeMetricValue(y);
    float z = limitMetricValue(radius * sinf(elevation * (float) M_PI / 180));
    m_z = normalizeMetricValue(z);
    
    // std::printf("update cartesian from a=%f, e=%f, d=%f, new x=%f, y=%f, z=%f\n", azimuth, elevation, radius, x, y, z);
    juce::AudioProcessorParameterWithID *xParam = apvts.getParameter(OSCParameters::POS_X_ID.getParamID());
    juce::AudioProcessorParameterWithID *yParam = apvts.getParameter(OSCParameters::POS_Y_ID.getParamID());
    juce::AudioProcessorParameterWithID *zParam = apvts.getParameter(OSCParameters::POS_Z_ID.getParamID());


    xParam->beginChangeGesture();
    xParam->setValueNotifyingHost(m_x);
    xParam->endChangeGesture();

    yParam->beginChangeGesture();
    yParam->setValueNotifyingHost(m_y);
    yParam->endChangeGesture();

    zParam->beginChangeGesture();
    zParam->setValueNotifyingHost(m_z);
    zParam->endChangeGesture();
}

float SphericalSliderBox::limitMetricValue(float value) {
    if (value > cartesian_coordinate_limit) {
        return cartesian_coordinate_limit;
    } else if (value < -cartesian_coordinate_limit) {
        return -cartesian_coordinate_limit;
    } else {
        return value;
    }
}

float SphericalSliderBox::normalizeMetricValue(float value) {
    return (value + cartesian_coordinate_limit) / (2.f*cartesian_coordinate_limit);
}