//
//  OSCSender.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "OSCSender.h"

OSCSender::OSCSender(juce::AudioProcessorValueTreeState& pluginApvts) : apvts(pluginApvts) {
    apvts.state.addListener(this);
}

OSCSender::~OSCSender() {
    stopTimer();
    for (unsigned long i = 0; i < oscMessageStack.size(); i++) {
        sendMessage(oscMessageStack.front());
        oscMessageStack.pop();
    }
    apvts.state.removeListener(this);
}

void OSCSender::connectToPort() {
    juce::String oscSendAdress = apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_ADRESS_ID);
    int oscSendPort = (int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_PORT_ID);

    #if JUCE_DEBUG
        std::cout << "OSC send adress: " << oscSendAdress << ":" << oscSendPort << std::endl;
    #endif

    if (! connect (oscSendAdress, oscSendPort)) {
        apvts.state.getChildWithName("Settings").setProperty(PluginParameters::OSC_SEND_STATUS_ID, 0, nullptr);
    }
    else {
        if ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_INTERVAL_ID) > 0) {
            startTimer((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_INTERVAL_ID));
        }
        apvts.state.getChildWithName("Settings").setProperty(PluginParameters::OSC_SEND_STATUS_ID, 1, nullptr);
    }
}

void OSCSender::disconnectFromPort() {
    stopTimer();
    disconnect();
    apvts.state.getChildWithName("Settings").setProperty(PluginParameters::OSC_SEND_STATUS_ID, 0, nullptr);
}

void OSCSender::sourceParameterChanged(Source& source, Parameter parameter, int index) {
    if (source.sourceIdx <= 0) return;
    
    if (parameter == PARAM_SOURCE_IDX) {
        juce::OSCMessage oscMessagePosition("/source/pos/xyz", source.sourceIdx, source.xPosition, source.yPosition, source.zPosition);
        if ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_INTERVAL_ID) > 0) {
            oscMessageStack.push(oscMessagePosition);
            for (int i = 0; i < source.nGains; i++)
            {
                juce::OSCMessage oscMessageGain("/send/gain",source.sourceIdx, i, source.gain[i]);
                oscMessageStack.push(oscMessageGain);
            }
        }
        else {
            sendMessage(oscMessagePosition);
            for (int i = 0; i < source.nGains; i++)
            {
                juce::OSCMessage oscMessageGain("/send/gain",source.sourceIdx, i, source.gain[i]);
                sendMessage(oscMessageGain);
            }
        }
        return;
    }
    else {
        juce::OSCMessage oscMessage("/");
        if (parameter == PARAM_POS) {
            oscMessage = juce::OSCMessage("/source/pos/xyz", source.sourceIdx, source.xPosition, source.yPosition, source.zPosition);
        } else if (parameter == PARAM_GAIN && index < source.nGains && index >= 0) {
            oscMessage = juce::OSCMessage("/send/gain",source.sourceIdx, index, source.gain[index]);
        } else if (parameter == PARAM_POS_SINGLE){
            // TODO send full position anyways?
            if (index == PARAM_POS_SINGLE_X) oscMessage = juce::OSCMessage("/source/pos/x", source.sourceIdx, source.xPosition);
            else if (index == PARAM_POS_SINGLE_Y) oscMessage = juce::OSCMessage("/source/pos/y", source.sourceIdx, source.yPosition);
            else if (index == PARAM_POS_SINGLE_Z) oscMessage = juce::OSCMessage("/source/pos/z", source.sourceIdx, source.zPosition);  
        } else {
            std::cout << "Invalid OSC Message Type: " << parameter << std::endl;
        }
        if ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_INTERVAL_ID) > 0) {
            oscMessageStack.push(oscMessage);
        }
        else {
            sendMessage(oscMessage);
        }
    }
    
}

void OSCSender::sendMessage(juce::OSCMessage& message) {
    if (! send(message)) {
        setTreePropertyAsync(apvts.state.getChildWithName("Settings"), PluginParameters::OSC_SEND_STATUS_ID, 0);
    }
}

void OSCSender::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) {
    // if (property.toString() == PluginParameters::OSC_SEND_ADRESS_ID || property.toString() == PluginParameters::OSC_SEND_PORT_ID) {
    //     #if JUCE_DEBUG
    //         std::cout << "OSC send adress: " << (juce::String) treeWhosePropertyHasChanged.getProperty(PluginParameters::OSC_SEND_ADRESS_ID) << ":" << (int) treeWhosePropertyHasChanged.getProperty(PluginParameters::OSC_SEND_PORT_ID) << std::endl;
    //     #endif
    //     disconnectFromPort();
    //     connectToPort();
    // }
    // else 
    if (property.toString() == PluginParameters::OSC_SEND_INTERVAL_ID) {
        if ((int) treeWhosePropertyHasChanged.getProperty(property) > 0) {
            stopTimer();
            startTimer((int) treeWhosePropertyHasChanged.getProperty(property));
        } else {
            stopTimer();
            for (unsigned long i = 0; i < oscMessageStack.size(); i++) {
                sendMessage(oscMessageStack.front());
                oscMessageStack.pop();
            }
        }
    }
}

void OSCSender::hiResTimerCallback() {
    if (! oscMessageStack.empty()) {
        sendMessage(oscMessageStack.front());
        oscMessageStack.pop();
    }
}

void OSCSender::setTreePropertyAsync(juce::ValueTree tree, const juce::Identifier& propertyName, const juce::var& newValue) {
    (new SetTreePropertyMessage{ tree, propertyName, newValue })->post();
}

void OSCSender::oscMessageReceived(const juce::OSCMessage& message) {
    juce::OSCMessage newOSCMessage(message);
    if ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_INTERVAL_ID) > 0) {
        oscMessageStack.push(newOSCMessage);
    }
    else {
        sendMessage(newOSCMessage);
    }
}