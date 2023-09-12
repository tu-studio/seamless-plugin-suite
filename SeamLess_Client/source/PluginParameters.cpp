//
//  PluginParameters.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "PluginParameters.h"

juce::AudioProcessorValueTreeState::ParameterLayout PluginParameters::createParameterLayout() {
    
    juce::AudioProcessorValueTreeState::ParameterLayout parameterLayout = SendParameters::createParameterLayout();
    
    if (parameterList.isEmpty()) {
        for (const auto & param : SendParameters::getPluginParameterList()) {
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
    SendParameters::createNotAutomatableValueTree();
    juce::ValueTree notAutomatableParameterValueTree = juce::ValueTree("Settings");
    notAutomatableParameterValueTree.copyPropertiesFrom(SendParameters::getNotAutomatableValueTree(), nullptr);
    
    notAutomatableParameterValueTree.setProperty(PluginParameters::RADIUS_ID, 0.f, nullptr);
    notAutomatableParameterValueTree.setProperty(PluginParameters::AZIMUTH_ID, 0.f, nullptr);
    notAutomatableParameterValueTree.setProperty(PluginParameters::ELEVATION_ID, 0.f, nullptr);
    
    notAutomatableParameterValueTree.setProperty(PluginParameters::GRID_CHOICE_ID, (int) GridType::Off, nullptr);
    notAutomatableParameterValueTree.setProperty(PluginParameters::VENUE_CHOICE_ID, (int) VenueType::TU_Studio, nullptr);
    notAutomatableParameterValueTree.setProperty(PluginParameters::GAIN_TOGGLE_ID, 1, nullptr);
    notAutomatableParameterValueTree.setProperty(PluginParameters::SPHERICAL_TOGGLE_ID, 0, nullptr);

    notAutomatableParameterValueTree.setProperty(PluginParameters::MAIN_CONNECTION_STATUS_ID, 0, nullptr);
    
    settingsList = SendParameters::getSettingsList();
    
    return notAutomatableParameterValueTree;
}

void PluginParameters::clearNotAutomatableValueTree(juce::ValueTree notAutomatableParameterValueTree) {
    notAutomatableParameterValueTree.removeAllProperties(nullptr);
    if (JUCE_DEBUG) std::cout << "All properties from PluginParameters removed" << std::endl;
    notAutomatableParameterValueTree = juce::ValueTree();
    SendParameters::clearNotAutomatableValueTree();
}

juce::StringArray PluginParameters::getSettingsList() {
    return settingsList;
}
