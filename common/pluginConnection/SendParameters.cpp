#include "SendParameters.h"

SendParameters::SendParameters() {
    createNotAutomatableValueTree();
}
SendParameters::~SendParameters() {
    clearNotAutomatableValueTree();
}

juce::AudioProcessorValueTreeState::ParameterLayout SendParameters::createParameterLayout() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat> (GAIN_1_ID,
                                                                  GAIN_1_NAME,
                                                                  GAIN_RANGE,
                                                                  0.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat> (GAIN_2_ID,
                                                                  GAIN_2_NAME,
                                                                  GAIN_RANGE,
                                                                  0.f));
                                                                  
    params.push_back(std::make_unique<juce::AudioParameterFloat> (GAIN_3_ID,
                                                                  GAIN_3_NAME,
                                                                  GAIN_RANGE,
                                                                  0.f));

    params.push_back(std::make_unique<juce::AudioParameterFloat> (GAIN_4_ID,
                                                                  GAIN_4_NAME,
                                                                  GAIN_RANGE,
                                                                  0.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat> (POS_X_ID,
                                                                  POS_X_NAME,
                                                                  POS_RANGE,
                                                                  0.f));

    params.push_back(std::make_unique<juce::AudioParameterFloat> (POS_Y_ID,
                                                                  POS_Y_NAME,
                                                                  POS_RANGE,
                                                                  0.f));

    params.push_back(std::make_unique<juce::AudioParameterFloat> (POS_Z_ID,
                                                                  POS_Z_NAME,
                                                                  POS_RANGE,
                                                                  0.f));
    
    if (parameterList.isEmpty()) {
        for (const auto & param : params) {
            parameterList.add(param->getParameterID());
        }

    }
    return { params.begin(), params.end() };
}

juce::StringArray SendParameters::getPluginParameterList() {
    return parameterList;
}

void SendParameters::createNotAutomatableValueTree()
{
    if (! notAutomatableParameterValueTree.isValid()) {
        notAutomatableParameterValueTree = juce::ValueTree("SendParameters");
        notAutomatableParameterValueTree.setProperty(SOURCE_IDX_NAME, juce::var(-1), nullptr);
    }
    
    if (settingsList.isEmpty()) {
        settingsList.add(SOURCE_IDX_NAME);
    }
    
    return;
}

void SendParameters::clearNotAutomatableValueTree() {
    notAutomatableParameterValueTree.removeProperty(SOURCE_IDX_NAME, nullptr);
    if (JUCE_DEBUG) std::cout << "All properties from SendParameters removed." << std::endl;
    notAutomatableParameterValueTree = juce::ValueTree(); // clears the ValueTree so that we are not leaking
    if (JUCE_DEBUG) std::cout << "SendParameters Value Tree to nullptr." << std::endl;
}

juce::StringArray SendParameters::getSettingsList() {
    return settingsList;
}

juce::ValueTree SendParameters::getNotAutomatableValueTree() {
    return notAutomatableParameterValueTree;
}
