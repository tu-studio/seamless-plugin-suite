//
//  PluginParameters.hpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#ifndef PluginParameters_h
#define PluginParameters_h

#include <JuceHeader.h>
#include <SendParameters.h>

class PluginParameters {
public:
    
//    inline static const juce::ParameterID
        
//        add parameter here
    
//    inline static const juce::String
        
//        add parameter here
    
    static juce::StringArray getPluginParameterList();
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    static juce::StringArray getSettingsList();
    static juce::ValueTree createNotAutomatableValueTree();
    static void clearNotAutomatableValueTree(juce::ValueTree notAutomatableParameterValueTree);
    
private:
    
    inline static juce::StringArray parameterList;
    inline static juce::StringArray settingsList;
    
//    inline static juce::NormalisableRange<float> sendRange {0.f, 1.f, 0.01f};
};

#endif /* PluginParameters_h */
