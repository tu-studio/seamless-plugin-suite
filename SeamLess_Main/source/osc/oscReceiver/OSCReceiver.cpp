//
//  OSCReceiver.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "OSCReceiver.h"

OSCReceiver::OSCReceiver(juce::AudioProcessorValueTreeState& pluginApvts) : apvts(pluginApvts) {
    apvts.state.addListener(this);
}

void OSCReceiver::connectToPort() {
    int oscReceivePort = (int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_RECEIVE_PORT_ID);

    #if JUCE_DEBUG
        std::cout << "OSC receive port: " << oscReceivePort << std::endl;
    #endif

    if (! connect (oscReceivePort)) {
        apvts.state.getChild(0).setProperty(PluginParameters::OSC_RECEIVE_STATUS_ID, 0, nullptr);
    }
    else {
        apvts.state.getChild(0).setProperty(PluginParameters::OSC_RECEIVE_STATUS_ID, 1, nullptr);
    }
}

void OSCReceiver::disconnectFromPort() {
    disconnect();
    apvts.state.getChild(0).setProperty(PluginParameters::OSC_RECEIVE_STATUS_ID, 0, nullptr);
}

void OSCReceiver::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) {
    if (property.toString() == PluginParameters::OSC_RECEIVE_PORT_ID) {
        disconnectFromPort();
        connectToPort();
    }
    juce::ignoreUnused(treeWhosePropertyHasChanged);
}