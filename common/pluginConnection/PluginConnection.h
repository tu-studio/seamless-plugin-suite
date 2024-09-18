//
//  PluginConnection.h
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 03.05.23.
//

#ifndef PluginConnection_h
#define PluginConnection_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <OSCParameters.h>

class PluginConnection;

enum Parameter {
    PARAM_SOURCE_IDX,
    PARAM_POS,
    PARAM_GAIN_1,
    PARAM_GAIN_2,
    PARAM_GAIN_3,
    PARAM_GAIN_4
};

struct Message {
    Parameter parameter;
    float value1 = 99.f; // used also for source IDX – unique identifier for client is the plugin connection
    float value2 = 99.f; // only used for PARAM_POS
    float value3 = 99.f; // only used for PARAM_POS
};

class PluginConnection : public juce::InterprocessConnection
{
public:
    class Listener {
    public:
        virtual void forwardMessage(PluginConnection* pluginConnection, const juce::MemoryBlock& memoryBlock) = 0; // pure virtual function
        virtual void disconnected(PluginConnection* pluginConnection) = 0; // pure virtual function
        virtual void connected(PluginConnection* pluginConnection) = 0; 
    };
    void addListener(Listener *);
    void removeListener(Listener *);
    
    PluginConnection();
    ~PluginConnection() override;
    void connect();
    void updateState(juce::AudioProcessorValueTreeState& apvts, juce::StringArray parameterList, juce::StringArray settingsList);
    void parameterChanged(const juce::String &parameterID, float newValue);
    
private:
    void connectionMade() override;
    void connectionLost() override;
    void messageReceived(const juce::MemoryBlock& message) override;

private:
    juce::ListenerList<Listener> listenerList;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginConnection)
};

#endif /* PluginConnection_h */
