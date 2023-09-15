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

void OSCSender::sourceParameterChanged(Source& source, Parameter parameter) {
    if (source.sourceIdx > 0) {
        if (parameter == PARAM_SOURCE_IDX) {
            juce::OSCMessage oscMessagePosition("/source/pos/xyz", source.sourceIdx, source.xPosition, source.yPosition, source.zPosition);
            juce::OSCMessage oscMessageGain1("/send/gain",source.sourceIdx, 0, source.gain1);
            juce::OSCMessage oscMessageGain2("/send/gain",source.sourceIdx, 1, source.gain2);
            juce::OSCMessage oscMessageGain3("/send/gain",source.sourceIdx, 2, source.gain3);
            juce::OSCMessage oscMessageGain4("/send/gain",source.sourceIdx, 3, source.gain4);
            if ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_INTERVAL_ID) > 0) {
                oscMessageStack.push(oscMessagePosition);
                oscMessageStack.push(oscMessageGain1);
                oscMessageStack.push(oscMessageGain2);
                oscMessageStack.push(oscMessageGain3);
                oscMessageStack.push(oscMessageGain4);
            }
            else {
                sendMessage(oscMessagePosition);
                sendMessage(oscMessageGain1);
                sendMessage(oscMessageGain2);
                sendMessage(oscMessageGain3);
                sendMessage(oscMessageGain4);
            }
            return;
        }
        else {
            juce::OSCMessage oscMessage("/");
            if (parameter == PARAM_POS) {
                oscMessage = juce::OSCMessage("/source/pos/xyz", source.sourceIdx, source.xPosition, source.yPosition, source.zPosition);
            } else if (parameter == PARAM_GAIN_1) {
                oscMessage = juce::OSCMessage("/send/gain",source.sourceIdx, 0, source.gain1);
            } else if (parameter == PARAM_GAIN_2) {
                oscMessage = juce::OSCMessage("/send/gain",source.sourceIdx, 1, source.gain2);
            } else if (parameter == PARAM_GAIN_3) {
                oscMessage = juce::OSCMessage("/send/gain",source.sourceIdx, 2, source.gain3);
            } else if (parameter == PARAM_GAIN_4) {
                oscMessage = juce::OSCMessage("/send/gain",source.sourceIdx, 3, source.gain4);
            }
            if ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_INTERVAL_ID) > 0) {
                oscMessageStack.push(oscMessage);
            }
            else {
                sendMessage(oscMessage);
            }
        }
    }
}

void OSCSender::sendMessage(juce::OSCMessage& message) {
    if (! send(message)) {
        setTreePropertyAsync(apvts.state.getChildWithName("Settings"), PluginParameters::OSC_SEND_STATUS_ID, 0);
    }
}

void OSCSender::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) {
    if (property.toString() == PluginParameters::OSC_SEND_ADRESS_ID || property.toString() == PluginParameters::OSC_SEND_PORT_ID) {
        #if JUCE_DEBUG
            std::cout << "OSC send adress: " << (juce::String) treeWhosePropertyHasChanged.getProperty(PluginParameters::OSC_SEND_ADRESS_ID) << ":" << (int) treeWhosePropertyHasChanged.getProperty(PluginParameters::OSC_SEND_PORT_ID) << std::endl;
        #endif
        disconnectFromPort();
        connectToPort();
    }
    else if (property.toString() == PluginParameters::OSC_SEND_INTERVAL_ID) {
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