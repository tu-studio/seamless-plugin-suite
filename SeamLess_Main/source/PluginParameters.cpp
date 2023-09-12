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
    OSCParameters::createNotAutomatableValueTree();
    juce::ValueTree notAutomatableParameterValueTree = juce::ValueTree("Settings");
    notAutomatableParameterValueTree.copyPropertiesFrom(OSCParameters::getNotAutomatableValueTree(), nullptr);
    
    notAutomatableParameterValueTree.setProperty(PluginParameters::OSC_SEND_ADRESS_ID, PluginParameters::OSC_SEND_ADRESS_INITIAL, nullptr);
    notAutomatableParameterValueTree.setProperty(PluginParameters::OSC_SEND_PORT_ID, PluginParameters::OSC_SEND_PORT_INITIAL, nullptr);
    notAutomatableParameterValueTree.setProperty(PluginParameters::OSC_RECEIVE_PORT_ID, PluginParameters::OSC_RECEIVE_PORT_INITIAL, nullptr);
    
    notAutomatableParameterValueTree.setProperty(PluginParameters::NUM_CLIENTS_ID, 0, nullptr);
    
    settingsList = OSCParameters::getSettingsList();
    
    return notAutomatableParameterValueTree;
}

void PluginParameters::clearNotAutomatableValueTree(juce::ValueTree notAutomatableParameterValueTree) {
    notAutomatableParameterValueTree.removeAllProperties(nullptr);
    if (JUCE_DEBUG) std::cout << "All properties from PluginParameters removed" << std::endl;
    notAutomatableParameterValueTree = juce::ValueTree();
    OSCParameters::clearNotAutomatableValueTree();
}

juce::StringArray PluginParameters::getSettingsList() {
    return settingsList;
}