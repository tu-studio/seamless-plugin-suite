//
//  MainServer.h
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 03.05.23.
//

#ifndef MainServer_h
#define MainServer_h

#include <JuceHeader.h>
#include "PluginConnection.h"

class MainServer : public juce::InterprocessConnectionServer
{
public:
    MainServer();
    ~MainServer() override;
    
private:
    PluginConnection* createConnectionObject() override;
    std::vector<PluginConnection*> mainConnections;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainServer)
};

#endif /* MainServer_h */
