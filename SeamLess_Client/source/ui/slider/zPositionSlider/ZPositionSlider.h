/*
=====================================================================

ZPositionSlider.h
Created: 7 Sep 2021 11:00:00am
Author:  Fares Schulz

=====================================================================
*/

#ifndef Z_POSITION_SLIDER_H
#define Z_POSITION_SLIDER_H

#include <JuceHeader.h>
#include <SeamLess.h>
#include <SliderLookAndFeel.h>
#include <PluginParameters.h>

class ZPositionSlider : public juce::Component {

public:
    ZPositionSlider(juce::AudioProcessorValueTreeState& a);
    ~ZPositionSlider() override;
    
    void addSliderAttachment(juce::AudioProcessorValueTreeState& state, const juce::String& parameterID);
    void setDoubleClickReturnValue(double valueToSetOnDoubleClick);
    
private:
    void resized() override;
    
private:
    SliderLookAndFeel customSliderLookAndFeel;
    juce::Slider slider;
    juce::Label sliderLabel;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
    std::unique_ptr<juce::RangedAudioParameter*> parameter;

    juce::AudioProcessorValueTreeState& apvts;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ZPositionSlider)
};

#endif /* Z_POSITION_SLIDER_H */