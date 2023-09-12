//
//  CostumRotarySlider.h
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#ifndef CostumRotarySlider_h
#define CostumRotarySlider_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <SliderLookAndFeel.h>

//==============================================================================
//            Rotary Slider
//==============================================================================

class CostumRotarySlider : public juce::Component {
public:
    CostumRotarySlider(juce::String sliderName);
    ~CostumRotarySlider() override;
    
    void addSliderAttachment(juce::AudioProcessorValueTreeState& state, const juce::String& parameterID);
    void setDoubleClickReturnValue(double valueToSetOnDoubleClick);

    juce::Slider slider;

private:
    void paint(juce::Graphics& g) override;
    void resized() override;
    
private:
    SliderLookAndFeel customSliderLookAndFeel;
    juce::Label sliderLabel;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
    std::unique_ptr<juce::RangedAudioParameter*> parameter;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CostumRotarySlider)
};

#endif /* CostumRotarySlider_h */

