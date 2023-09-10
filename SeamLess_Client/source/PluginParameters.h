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
        RADIUS_ID = "param_radius",
        AZIMUTH_ID = "param_azimuth",
        ELEVATION_ID = "param_elevation",

        GRID_CHOICE_ID = "param_grid_choice",
        VENUE_CHOICE_ID = "param_venue_choice",

        CARTESIAN_TOGGLE_ID = "param_cartesian_toggle",
        SPHERICAL_TOGGLE_ID = "param_spherical_toggle";

    inline static const juce::String

        // not automatable Parameters
        RADIUS_NAME = "Radius",
        AZIMUTH_NAME = "Azimuth",
        ELEVATION_NAME = "Elevation",

        CARTESIAN_TOGGLE_LABEL = "Cartesian",
        SPHERICAL_TOGGLE_LABEL = "Spherical";

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
