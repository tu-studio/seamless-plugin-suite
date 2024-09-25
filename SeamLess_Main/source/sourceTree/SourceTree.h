//
//  SourceTree.hpp
//  SeamLess_Main
//
//  Created by Fares Schulz on 08.06.23.
//

#ifndef SourceTree_h
#define SourceTree_h

#include <JuceHeader.h>
#include <PluginParameters.h>
#include <SeamLess.h>
#include <MainServer.h>

struct Source {
    int sourceIdx = -1;
    float xPosition;
    float yPosition;
    float zPosition;
    float gain[4] = {0, 0, 0, 0};
    int nGains = 4;
    PluginConnection* pluginConnection;
};

class SourceTree: private MainServer::Listener
{
public:
    SourceTree(juce::AudioProcessorValueTreeState& pluginApvts, MainServer& m);
    ~SourceTree();
    
    class Listener {
    public:
        virtual void sourceParameterChanged(Source source, Parameter parameter, int index) = 0;
    };
    void addListener(Listener *);
    void removeListener(Listener *);
    void updateNumClients();
    
    /// @brief handles parameters that were changed in the main plugin, for example by a received OSC message 
    /// @param sourceIndex source index of the updated source
    /// @param parameter parameter that was changed
    /// @param int_value renderer_idx if parameter=PARAM_GAIN or coordinate_idx if parameter=PARAM_POS_SINGLE
    /// @param value1 first value used for the update
    /// @param value2 second value used for the update
    /// @param value3 third value used for the update
    void parameterChanged(int sourceIndex, Parameter parameter, int int_value, float value1, float value2, float value3);

    /// @brief Sends the current state of all sources to the current osc receiver
    void dumpSourcesToReceiver();
    
private:
    void newPluginConnection(PluginConnection* pluginConnection) override;
    void deletedPluginConnection(PluginConnection* pluginConnection) override;
    void parameterChanged(PluginConnection* pluginConnection, Parameter parameter, int int_value, float value1, float value2, float value3) override;
    void deletedMainServer() override;
    void setTreePropertyAsync(juce::ValueTree tree, const juce::Identifier& propertyName, const juce::var& newValue);
    void updateSource(Source &source, Parameter parameter, int int_value, float value1, float value2, float value3);
    
    /// @brief Sends the current state of a source to its pluginConnection
    /// @param source 
    void dumpSourceToClientPlugin(Source &source);


    
private:
    juce::AudioProcessorValueTreeState& apvts;
    MainServer& mainServer;
    std::vector<Source> sources;
    
    juce::ListenerList<Listener> listenerList;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SourceTree)
};

#endif /* SourceTree_h */
