//
//  PluginConnection.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 03.05.23.
//

#include "PluginConnection.h"

PluginConnection::PluginConnection() : InterprocessConnection(true, 15) {
}

PluginConnection::~PluginConnection() {
    disconnect(10);
}

void PluginConnection::addListener(Listener* listener) {
    listenerList.add(listener);
}

void PluginConnection::removeListener(Listener* listener) {
    listenerList.remove(listener);
}

void PluginConnection::connect(juce::AudioProcessorValueTreeState &pluginApvts, juce::StringArray parameterList, juce::StringArray settingsList) {
    connectToSocket("localhost", PORT_NUMBER, 5000);
    if (isConnected()) {
        for (auto & setting : settingsList) {
            parameterChanged(setting, pluginApvts.state.getChild(0).getProperty(setting));
        }
        for (auto & parameter : parameterList) {
            parameterChanged(parameter, pluginApvts.getRawParameterValue(parameter)->load());
        }
    }
}

void PluginConnection::parameterChanged(const juce::String &parameterID, float newValue)
{
    if (isConnected())
    {
        if (parameterID == SendParameters::SOURCE_IDX_NAME) {
            Message message;
            message.parameter = Parameter::PARAM_SOURCE_IDX;
            message.value1 = (float) newValue;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        } else if (parameterID == SendParameters::GAIN_1_ID.getParamID()) {
            Message message;
            message.parameter = Parameter::PARAM_GAIN_1;
            message.value1 = (float) newValue;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        } else if (parameterID ==  SendParameters::GAIN_2_ID.getParamID()) {
            Message message;
            message.parameter = Parameter::PARAM_GAIN_2;
            message.value1 = (float) newValue;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        } else if (parameterID == SendParameters::GAIN_3_ID.getParamID()) {
            Message message;
            message.parameter = Parameter::PARAM_GAIN_3;
            message.value1 = (float) newValue;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        } else if (parameterID == SendParameters::GAIN_4_ID.getParamID()) {
            Message message;
            message.parameter = Parameter::PARAM_GAIN_4;
            message.value1 = (float) newValue;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        } else if (parameterID == SendParameters::POS_X_ID.getParamID()) {
            Message message;
            message.parameter = Parameter::PARAM_POS;
            message.value1 = newValue;
            message.value2 = 99.f;
            message.value3 = 99.f;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        } else if (parameterID == SendParameters::POS_Y_ID.getParamID()) {
            Message message;
            message.parameter = Parameter::PARAM_POS;
            message.value1 = 99.f;
            message.value2 = newValue;
            message.value3 = 99.f;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        } else if (parameterID == SendParameters::POS_Z_ID.getParamID()) {
            Message message;
            message.parameter = Parameter::PARAM_POS;
            message.value1 = 99.f;
            message.value2 = 99.f;
            message.value3 = newValue;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        }
    }
}
    
void PluginConnection::connectionMade() {
    listenerList.call([this] (Listener& l) {l.connected(this);});
    std::cout << "Connection estblished!" << std::endl;
}

void PluginConnection::connectionLost() {
    listenerList.call([this] (Listener& l) {l.disconnected(this);});
    std::cout << "Conection lost!" << std::endl;
}

void PluginConnection::messageReceived(const juce::MemoryBlock& memoryBlock) {
    listenerList.call([this, memoryBlock](Listener& l) {l.forwardMessage(this, memoryBlock);});
}
