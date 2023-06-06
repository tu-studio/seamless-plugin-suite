//
//  SendFader.h
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#ifndef SendFader_h
#define SendFader_h

#include <JuceHeader.h>
#include <PluginParameters.h>
#include <CostumSliderComponent.h>


class SendFader : public juce::Component {
public:
    SendFader(juce::AudioProcessorValueTreeState& parameters);
    void resized() override;
    void parameterChanged(const juce::String &parameterID, float newValue);
    
private:
    CostumSliderComponent send1Slider {"HOA"};
    CostumSliderComponent send2Slider {"WFS"};
    
    juce::AudioProcessorValueTreeState& parameters;
};

#endif /* SendFader_h */
