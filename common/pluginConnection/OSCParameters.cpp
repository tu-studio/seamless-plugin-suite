#include "OSCParameters.h"

OSCParameters::OSCParameters() {
    createNotAutomatableValueTree();
}
OSCParameters::~OSCParameters() {
    clearNotAutomatableValueTree();
}

juce::AudioProcessorValueTreeState::ParameterLayout OSCParameters::createParameterLayout() {
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

juce::StringArray OSCParameters::getPluginParameterList() {
    return parameterList;
}

void OSCParameters::createNotAutomatableValueTree()
{
    if (! notAutomatableParameterValueTree.isValid()) {
        notAutomatableParameterValueTree = juce::ValueTree("OSCParameters");
        notAutomatableParameterValueTree.setProperty(SOURCE_IDX_ID, SOURCE_IDX_INITIAL, nullptr);
    }
    
    if (settingsList.isEmpty()) {
        settingsList.add(SOURCE_IDX_ID);
    }
    
    return;
}

void OSCParameters::clearNotAutomatableValueTree() {
    notAutomatableParameterValueTree.removeProperty(SOURCE_IDX_ID, nullptr);
    notAutomatableParameterValueTree = juce::ValueTree(); // clears the ValueTree so that we are not leaking
}

juce::StringArray OSCParameters::getSettingsList() {
    return settingsList;
}

juce::ValueTree OSCParameters::getNotAutomatableValueTree() {
    return notAutomatableParameterValueTree;
}
