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

class InvertibleSlider : public juce::Slider
{
    // TODO does the default con/destructor need to be overwritten?
public:
	double proportionOfLengthToValue (double proportion) {   return m_is_inverted ? juce::Slider::proportionOfLengthToValue(1.0f-proportion) : juce::Slider::proportionOfLengthToValue(proportion) ;}
	double valueToProportionOfLength (double value) {   return m_is_inverted ? 1.0f-(juce::Slider::valueToProportionOfLength(value)): juce::Slider::valueToProportionOfLength(value) ; }
    void setInverted(bool is_inverted){ m_is_inverted = is_inverted;}
private:
    bool m_is_inverted = false;
};

class CostumRotarySlider : public juce::Component {
public:
    CostumRotarySlider(juce::String sliderName);
    ~CostumRotarySlider() override;
    
    void addSliderAttachment(juce::AudioProcessorValueTreeState& state, const juce::String& parameterID);
    void setDoubleClickReturnValue(double valueToSetOnDoubleClick);

    InvertibleSlider slider;

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

