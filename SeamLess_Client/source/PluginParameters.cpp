//
//  PluginParameters.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "PluginParameters.h"

juce::AudioProcessorValueTreeState::ParameterLayout PluginParameters::createParameterLayout() {
//    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
//    params.push_back(std::make_unique<juce::AudioParameterFloat> (PluginParameters::AED_1_ID,
//                                                                  PluginParameters::AED_1_NAME,
//                                                                  PluginParameters::AED_RANGE,
//                                                                  0.f));
//
//    params.push_back(std::make_unique<juce::AudioParameterFloat> (PluginParameters::AED_2_ID,
//                                                                  PluginParameters::AED_2_NAME,
//                                                                  PluginParameters::AED_RANGE,
//                                                                  0.f));
    
    juce::AudioProcessorValueTreeState::ParameterLayout parameterLayout = SendParameters::createParameterLayout();
    
    if (parameterList.isEmpty()) {
        for (const auto & param : SendParameters::getPluginParameterList()) {
            parameterList.add(param);
        }
    }
    
//    for (const auto & param : params) {
//        parameterLayout.add(param);
//        parameterList.add(parameterList.add(param->getParameterID());
//    }
    
    return parameterLayout;
}

juce::StringArray PluginParameters::getPluginParameterList() {
    return parameterList;
}

juce::ValueTree PluginParameters::createNotAutomatableValueTree()
{
    SendParameters::createNotAutomatableValueTree();
    juce::ValueTree notAutomatableParameterValueTree = SendParameters::getNotAutomatableValueTree().createCopy();
    
//    notAutomatableParameterValueTree.setProperty(The property you want.);
    
    settingsList = SendParameters::getSettingsList();
    
    return notAutomatableParameterValueTree;
}

void PluginParameters::clearNotAutomatableValueTree(juce::ValueTree notAutomatableParameterValueTree) {
    notAutomatableParameterValueTree.removeAllProperties(nullptr);
    SendParameters::clearNotAutomatableValueTree();
}

juce::StringArray PluginParameters::getSettingsList() {
    return settingsList;
}
