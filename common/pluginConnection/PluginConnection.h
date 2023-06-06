//
//  PluginConnection.h
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 03.05.23.
//

#ifndef PluginConnection_h
#define PluginConnection_h

#include <JuceHeader.h>
#include "../SeamLess.h"

class PluginConnection : public juce::InterprocessConnection
{
public:
    PluginConnection();
    ~PluginConnection() override;
    void sendMessageToMain(juce::String messageType, juce::String message);
    
private:
    void connectionMade() override;
    void connectionLost() override;
    void messageReceived(const juce::MemoryBlock& message) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginConnection)
};

#endif /* PluginConnection_h */
