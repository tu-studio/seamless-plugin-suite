//
//  GainSliderBox.h
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#ifndef GainSliderBox_h
#define GainSliderBox_h

#include <JuceHeader.h>
#include <PluginParameters.h>
#include <CostumRotarySlider.h>


class GainSliderBox : public juce::Component {
public:
    GainSliderBox(juce::AudioProcessorValueTreeState& apvts);
    void paint(juce::Graphics& g) override;
    void resized() override;
    
private:
    CostumRotarySlider gain1Slider {"HOA"};
    CostumRotarySlider gain2Slider {"WFS"};
    CostumRotarySlider gain3Slider {"Reverb"};
    CostumRotarySlider gain4Slider {"LFE"};
    
    juce::AudioProcessorValueTreeState& apvts;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainSliderBox)
};

#endif /* GainSliderBox_h */
