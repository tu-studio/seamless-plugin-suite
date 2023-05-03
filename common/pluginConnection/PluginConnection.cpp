//
//  PluginConnection.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 03.05.23.
//

#include "PluginConnection.h"

PluginConnection::PluginConnection() : InterprocessConnection(true, 15) {}

PluginConnection::~PluginConnection() {
    disconnect(10);
}

void PluginConnection::connectionMade() {
    std::cout << "Connection estblished!" << std::endl;
}

void PluginConnection::connectionLost() {
    std::cout << "Conection lost!" << std::endl;
    disconnect(10);
}

void PluginConnection::messageReceived(const juce::MemoryBlock& message) {
    std::cout << "Got message!" << std::endl;
}
