//
//  PluginParameters.hpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#ifndef PluginParameters_h
#define PluginParameters_h

#include <JuceHeader.h>
#include <OSCParameters.h>

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
    HuFo,
    H0104
};

inline juce::String toString(VenueType venueType) {
    switch(venueType)
    {
    case VenueType::TU_Studio: return "TU Studio";
    case VenueType::HuFo: return "HuFo";
    case VenueType::H0104: return "H0104";
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

        GAIN_TOGGLE_ID = "param_gain_toggle",
        SPHERICAL_TOGGLE_ID = "param_spherical_toggle",

        MAIN_CONNECTION_STATUS_ID = "param_main_connection_status";

    inline static const juce::String

        // not automatable Parameters
        RADIUS_NAME = "Radius",
        AZIMUTH_NAME = "Azimuth",
        ELEVATION_NAME = "Elevation",

        GAIN_TOGGLE_LABEL = "Gain",
        SPHERICAL_TOGGLE_LABEL = "Spherical",

        MAIN_CONNECTION_STATUS_NAME = "Main Connection Status";

    inline static const juce::StringArray
    
        // not automatable Parameters
        GRID_CHOICE_LABELS = {"Grid OFF", "Grid \nON \nxyz", (juce::String) juce::CharPointer_UTF8("Grid \nON \n r \xcf\x86 \xce\xb8\t")},
        VENUE_CHOICE_LABELS = {"TU Studio", "HuFo", "H0104"};
    
    static juce::StringArray getPluginParameterList();
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    static juce::StringArray getSettingsList();
    static juce::ValueTree createNotAutomatableValueTree();
    static void clearNotAutomatableValueTree();
    
private:

    inline static juce::StringArray parameterList;
    inline static juce::StringArray settingsList;
    inline static juce::ValueTree notAutomatableParameterValueTree;
};

#endif /* PluginParameters_h */
