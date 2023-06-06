//
//  PluginParameters.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "PluginParameters.h"

juce::AudioProcessorValueTreeState::ParameterLayout PluginParameters::createParameterLayout() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat> (SEND_1_ID,
                                                                  SEND_1_NAME,
                                                                  sendRange,
                                                                  0.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat> (SEND_2_ID,
                                                                  SEND_2_NAME,
                                                                  sendRange,
                                                                  0.f));
    
    for (const auto & param : params) {
        parameterList.add(param->getParameterID());
    }

    return { params.begin(), params.end() };
}

juce::StringArray PluginParameters::getPluginParameterList() {
    return parameterList;
}
