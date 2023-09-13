//
//  OscSender.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "OscSender.h"

OscSender::OscSender(juce::AudioProcessorValueTreeState& pluginApvts) : apvts(pluginApvts) {
    apvts.state.addListener(this);
}

void OscSender::connectToPort() {
    juce::String oscSendAdress = apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_ADRESS_ID);
    int oscSendPort = (int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_PORT_ID);

    #if JUCE_DEBUG
        std::cout << "OSC send adress: " << oscSendAdress << ":" << oscSendPort << std::endl;
    #endif

    if (! connect (oscSendAdress, oscSendPort))
        showConnectionErrorMessage ("Error: could not connect to UDP port.");
    else {
        if ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_INTERVAL_ID) > 0) {
            startTimer((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_INTERVAL_ID));
        }
    }
    
}

void OscSender::sourceParameterChanged(Source& source, Parameter parameter) {
    if (source.sourceIdx > 0) {
        if (parameter == PARAM_SOURCE_IDX) {
            juce::OSCMessage oscMessagePosition("/source/pos/xyz", source.sourceIdx, source.xPosition, source.yPosition, source.zPosition);
            juce::OSCMessage oscMessageGain1("/send/gain",source.sourceIdx, 0, source.gain1);
            juce::OSCMessage oscMessageGain2("/send/gain",source.sourceIdx, 1, source.gain2);
            juce::OSCMessage oscMessageGain3("/send/gain",source.sourceIdx, 2, source.gain3);
            juce::OSCMessage oscMessageGain4("/send/gain",source.sourceIdx, 3, source.gain4);
            if ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_INTERVAL_ID) != 0) {
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
            if ((int) apvts.state.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_INTERVAL_ID) != 0) {
                oscMessageStack.push(oscMessage);
            }
            else {
                sendMessage(oscMessage);
            }
        }
    }
}

void OscSender::sendMessage(juce::OSCMessage& message) {
    if (! send(message))
        showConnectionErrorMessage("Error: could not send OSC message.");
}

void OscSender::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) {
    if (property.toString() == PluginParameters::OSC_SEND_ADRESS_ID || property.toString() == PluginParameters::OSC_SEND_PORT_ID) {
        juce::String oscSendAdress = treeWhosePropertyHasChanged.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_ADRESS_ID);
        int oscSendPort = (int) treeWhosePropertyHasChanged.getChildWithName("Settings").getProperty(PluginParameters::OSC_SEND_PORT_ID);
        disconnect();
        if (! connect (oscSendAdress, oscSendPort))
            showConnectionErrorMessage ("Error: could not connect to UDP port.");
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

void OscSender::showConnectionErrorMessage (const juce::String& messageText) {
      juce::AlertWindow::showMessageBoxAsync (juce::AlertWindow::WarningIcon,
                                              "Connection error",
                                              messageText,
                                              "OK");
}

void OscSender::hiResTimerCallback() {
    if (! oscMessageStack.empty()) {
        sendMessage(oscMessageStack.front());
        oscMessageStack.pop();
    }
}