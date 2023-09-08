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

enum class GridType {
    Off,
    Cartesian,
    Spherical
};

enum class VenueType {
    TU_Studio,
    HuFo
};

class PluginParameters {
public:

// Not automatable parameters

    inline static const juce::String
    
        // not automatable Parameters
        GRID_TYPE_ID = "param_grid_type",
        VENUE_TYPE_ID = "param_venue_type";
    
    static juce::StringArray getPluginParameterList();
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    static juce::StringArray getSettingsList();
    static juce::ValueTree createNotAutomatableValueTree();
    static void clearNotAutomatableValueTree(juce::ValueTree notAutomatableParameterValueTree);
    
private:

    inline static juce::StringArray parameterList;
    inline static juce::StringArray settingsList;
};

#endif /* PluginParameters_h */
