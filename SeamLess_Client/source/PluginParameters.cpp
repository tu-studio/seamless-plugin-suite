//
//  PluginParameters.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "PluginParameters.h"

juce::AudioProcessorValueTreeState::ParameterLayout PluginParameters::createParameterLayout() {
    
    juce::AudioProcessorValueTreeState::ParameterLayout parameterLayout = OSCParameters::createParameterLayout();
    
    if (parameterList.isEmpty()) {
        for (const auto & param : OSCParameters::getPluginParameterList()) {
            parameterList.add(param);
        }
    }
    
    return parameterLayout;
}

juce::StringArray PluginParameters::getPluginParameterList() {
    return parameterList;
}

juce::ValueTree PluginParameters::createNotAutomatableValueTree()
{
    if (! notAutomatableParameterValueTree.isValid()) {

        OSCParameters::createNotAutomatableValueTree();
        notAutomatableParameterValueTree = juce::ValueTree("Settings");
        notAutomatableParameterValueTree.copyPropertiesFrom(OSCParameters::getNotAutomatableValueTree(), nullptr);

        notAutomatableParameterValueTree.setProperty(PluginParameters::RADIUS_ID, 0.f, nullptr);
        notAutomatableParameterValueTree.setProperty(PluginParameters::AZIMUTH_ID, 0.f, nullptr);
        notAutomatableParameterValueTree.setProperty(PluginParameters::ELEVATION_ID, 0.f, nullptr);
        
        notAutomatableParameterValueTree.setProperty(PluginParameters::GRID_CHOICE_ID, (int) GridType::Off, nullptr);
        notAutomatableParameterValueTree.setProperty(PluginParameters::VENUE_CHOICE_ID, (int) VenueType::TU_Studio, nullptr);
        notAutomatableParameterValueTree.setProperty(PluginParameters::GAIN_TOGGLE_ID, 1, nullptr);
        notAutomatableParameterValueTree.setProperty(PluginParameters::SPHERICAL_TOGGLE_ID, 0, nullptr);

        notAutomatableParameterValueTree.setProperty(PluginParameters::MAIN_CONNECTION_STATUS_ID, 0, nullptr);
        
    }
    
    if (settingsList.isEmpty()) {
        settingsList = OSCParameters::getSettingsList();
        settingsList.add(PluginParameters::RADIUS_ID);
        settingsList.add(PluginParameters::AZIMUTH_ID);
        settingsList.add(PluginParameters::ELEVATION_ID);
        settingsList.add(PluginParameters::GRID_CHOICE_ID);
        settingsList.add(PluginParameters::VENUE_CHOICE_ID);
        settingsList.add(PluginParameters::GAIN_TOGGLE_ID);
        settingsList.add(PluginParameters::SPHERICAL_TOGGLE_ID);
        settingsList.add(PluginParameters::MAIN_CONNECTION_STATUS_ID);
    }
    
    return notAutomatableParameterValueTree;
}

void PluginParameters::clearNotAutomatableValueTree() {
    notAutomatableParameterValueTree.removeAllProperties(nullptr);
    notAutomatableParameterValueTree = juce::ValueTree();
    OSCParameters::clearNotAutomatableValueTree();
}

juce::StringArray PluginParameters::getSettingsList() {
    return settingsList;
}
