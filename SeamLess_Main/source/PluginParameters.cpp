//
//  PluginParameters.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "PluginParameters.h"

juce::AudioProcessorValueTreeState::ParameterLayout PluginParameters::createParameterLayout() {
    
    // For now we have no automatable parameters in the Main Plugin
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    if (parameterList.isEmpty()) {
        for (const auto & param : params) {
            parameterList.add(param->getParameterID());
        }
    }
    
    return { params.begin(), params.end() };
}

juce::StringArray PluginParameters::getPluginParameterList() {
    return parameterList;
}

juce::ValueTree PluginParameters::createNotAutomatableValueTree()
{
    // No need to create a copy from the OSCParameters notAutomatableParameterValueTree
    if (! notAutomatableParameterValueTree.isValid()) {
        notAutomatableParameterValueTree = juce::ValueTree("Settings");
        
        notAutomatableParameterValueTree.setProperty(OSC_SEND_ADRESS_ID, OSC_SEND_ADRESS_INITIAL, nullptr);
        notAutomatableParameterValueTree.setProperty(OSC_SEND_PORT_ID, OSC_SEND_PORT_INITIAL, nullptr);
        notAutomatableParameterValueTree.setProperty(OSC_SEND_INTERVAL_ID, OSC_SEND_INTERVAL_INITIAL, nullptr);
        
        notAutomatableParameterValueTree.setProperty(OSC_RECEIVE_PORT_ID, OSC_RECEIVE_PORT_INITIAL, nullptr);
        
        notAutomatableParameterValueTree.setProperty(NUM_CLIENTS_ID, NUM_CLIENTS_INITIAL, nullptr);
    }
    
    if (settingsList.isEmpty()) {
        settingsList.add(OSC_SEND_ADRESS_ID);
        settingsList.add(OSC_SEND_PORT_ID);
        settingsList.add(OSC_SEND_INTERVAL_ID);
        settingsList.add(OSC_RECEIVE_PORT_ID);
        settingsList.add(NUM_CLIENTS_ID);
    }
    
    return notAutomatableParameterValueTree;
}

void PluginParameters::clearNotAutomatableValueTree() {
    notAutomatableParameterValueTree.removeAllProperties(nullptr);
    notAutomatableParameterValueTree = juce::ValueTree();
}

juce::StringArray PluginParameters::getSettingsList() {
    return settingsList;
}