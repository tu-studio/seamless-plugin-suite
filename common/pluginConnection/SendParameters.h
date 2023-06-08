//
//  SendParameters.hpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#ifndef SendParameters_h
#define SendParameters_h

#include <JuceHeader.h>

class SendParameters {
public:
    
    SendParameters();
    ~SendParameters();
    
    inline static const juce::ParameterID
        
        GAIN_1_ID = {"param_send_1", 1},
        GAIN_2_ID = {"param_send_2", 1};
    
    inline static const juce::String
        
        GAIN_1_NAME = "Send HOA",
        GAIN_2_NAME = "Send WFS",
    
        // not automatable SendParameters
        SOURCE_IDX_NAME = "Source Index";
    
    static juce::StringArray getPluginParameterList();
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    static void createNotAutomatableValueTree();
    static void clearNotAutomatableValueTree();
    static juce::StringArray getSettingsList();
    static juce::ValueTree getNotAutomatableValueTree();
    
private:
    
    inline static juce::StringArray parameterList;
    inline static juce::StringArray settingsList;
    inline static juce::ValueTree notAutomatableParameterValueTree;
    
    inline static juce::NormalisableRange<float> GAIN_RANGE {0.f, 1.f, 0.01f};
};

#endif /* SendParameters_h */
