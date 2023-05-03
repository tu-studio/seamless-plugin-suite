//
//  MainServer.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 03.05.23.
//

#include "MainServer.h"

MainServer::MainServer() : InterprocessConnectionServer() {}

MainServer::~MainServer() {
    stop();
    for (unsigned long i = 0; i < mainConnections.size(); i++) {
        delete mainConnections[i];
    }
}

PluginConnection* MainServer::createConnectionObject() {
    PluginConnection* newClientConnection = new PluginConnection;
    mainConnections.push_back(newClientConnection);

    std::cout << "Main plugin received new connection! N=" << mainConnections.size() << std::endl;
    
    return newClientConnection;
}
