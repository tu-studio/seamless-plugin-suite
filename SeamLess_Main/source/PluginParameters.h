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
#include <SeamLess.h>

class PluginParameters {
public:

// Not automatable parameters

    inline static const juce::String
    
        // not automatable Parameters
        OSC_SEND_ADRESS_ID = "param_osc_send_adress",
        OSC_SEND_PORT_ID = "param_osc_send_port",
        OSC_SEND_INTERVAL_ID = "param_osc_send_interval",
        OSC_SEND_STATUS_ID = "param_osc_send_status",

        OSC_RECEIVE_PORT_ID = "param_osc_receive_port",
        OSC_RECEIVE_STATUS_ID = "param_osc_receive_status",

        NUM_CLIENTS_ID = "param_num_clients";

    inline static const juce::String

        OSC_SEND_ADRESS_INITIAL = DEFAULT_OSC_SEND_ADRESS,
        OSC_SEND_PORT_INITIAL = (juce::String) DEFAULT_OSC_SEND_PORT,
        OSC_SEND_INTERVAL_INITIAL = (juce::String) DEFAULT_OSC_SEND_INTERVAL,
        OSC_SEND_STATUS_INITIAL = "0",

        OSC_RECEIVE_PORT_INITIAL = (juce::String) DEFAULT_OSC_RECEIVE_PORT,
        OSC_RECEIVE_STATUS_INITIAL = "0",

        NUM_CLIENTS_INITIAL = "0";
    
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