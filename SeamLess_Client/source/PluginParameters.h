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

inline juce::String toString(GridType gridType) {
    switch(gridType)
    {
    case GridType::Off: return "Grid OFF";
    case GridType::Cartesian: return "Grid \nON \nxyz";
    case GridType::Spherical: return juce::CharPointer_UTF8("Grid \nON \n r \xcf\x86 \xce\xb8\t");
    default: return "";
    }
}

enum class VenueType {
    TU_Studio,
    HuFo
};

inline juce::String toString(VenueType venueType) {
    switch(venueType)
    {
    case VenueType::TU_Studio: return "TU Studio";
    case VenueType::HuFo: return "HuFo";
    default: return "";
    }
}

class PluginParameters {
public:

// Not automatable parameters

    inline static const juce::String
    
        // not automatable Parameters
        GRID_CHOICE_ID = "param_grid_type",
        VENUE_CHOICE_ID = "param_venue_type";

    inline static const juce::StringArray
    
        // not automatable Parameters
        GRID_CHOICE_LABELS = {"Grid OFF", "Grid \nON \nxyz", (juce::String) juce::CharPointer_UTF8("Grid \nON \n r \xcf\x86 \xce\xb8\t")},
        VENUE_CHOICE_LABELS = {"TU Studio", "HuFo"};
    
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
