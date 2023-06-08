//
//  CostumSliderComponent.h
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#ifndef CostumSliderComponent_h
#define CostumSliderComponent_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <SliderLookAndFeel.h>

//==============================================================================
//            Rotary Slider
//==============================================================================

class CostumSliderComponent : public juce::Component {
public:
    CostumSliderComponent(juce::String sliderName);
    ~CostumSliderComponent() override;
    
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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CostumSliderComponent)
};

#endif /* CostumSliderComponent_h */

