//
//  PluginParameters.hpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#ifndef PluginParameters_h
#define PluginParameters_h

#include <JuceHeader.h>

class PluginParameters {
public:
    
    inline static const juce::ParameterID
        
        SEND_1_ID = {"param_send_1", 1},
        SEND_2_ID = {"param_send_2", 1};
    
    inline static const juce::String
        
        SEND_1_NAME = "Send HOA",
        SEND_2_NAME = "Send WFS";
    
    static juce::StringArray getPluginParameterList();
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
private:
    
    inline static juce::StringArray parameterList;
    
    inline static juce::NormalisableRange<float> sendRange {0.f, 1.f, 0.01f};
};

#endif /* PluginParameters_h */
