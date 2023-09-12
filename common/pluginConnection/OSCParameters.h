//
//  OSCParameters.h
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#ifndef OSCParameters_h
#define OSCParameters_h

#include <JuceHeader.h>

class OSCParameters {
public:
    
    OSCParameters();
    ~OSCParameters();
    
    inline static const juce::ParameterID
        
        GAIN_1_ID = {"param_gain_1", 1},
        GAIN_2_ID = {"param_gain_2", 1},
        GAIN_3_ID = {"param_gain_3", 1},
        GAIN_4_ID = {"param_gain_4", 1},
        POS_X_ID = {"param_pos_x", 1},
        POS_Y_ID = {"param_pos_y", 1},
        POS_Z_ID = {"param_pos_z", 1};

    inline static const juce::String

        // not automatable OSCParameters
        SOURCE_IDX_ID = "param_source_idx";
    
    inline static const juce::String
        
        GAIN_1_NAME = "HOA Gain",
        GAIN_2_NAME = "WFS Gain",
        GAIN_3_NAME = "Reverb Gain",
        GAIN_4_NAME = "LFE Gain",
        POS_X_NAME = "X Position",
        POS_Y_NAME = "Y Position",
        POS_Z_NAME = "Z Position";
    
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
    inline static juce::NormalisableRange<float> POS_RANGE {-10.f, 10.f, 0.01f};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OSCParameters)
};

#endif /* OSCParameters_h */
