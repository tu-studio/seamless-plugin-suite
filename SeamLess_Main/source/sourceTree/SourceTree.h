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
    void parameterChanged(int sourceIndex, Parameter parameter, int int_value, float value1, float value2, float value3);
    
private:
    void newPluginConnection(PluginConnection* pluginConnection) override;
    void deletedPluginConnection(PluginConnection* pluginConnection) override;
    void parameterChanged(PluginConnection* pluginConnection, Parameter parameter, int int_value, float value1, float value2, float value3) override;
    void deletedMainServer() override;
    void setTreePropertyAsync(juce::ValueTree tree, const juce::Identifier& propertyName, const juce::var& newValue);
    void updateSource(Source &source, Parameter parameter, int int_value, float value1, float value2, float value3);
    
private:
    juce::AudioProcessorValueTreeState& apvts;
    MainServer& mainServer;
    std::vector<Source> sources;
    
    juce::ListenerList<Listener> listenerList;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SourceTree)
};

#endif /* SourceTree_h */
