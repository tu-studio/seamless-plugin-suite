//
//  SourceTree.cpp
//  SeamLess_Main
//
//  Created by Fares Schulz on 08.06.23.
//

#include "SourceTree.h"

SourceTree::SourceTree(juce::AudioProcessorValueTreeState& pluginApvts, MainServer& m) : apvts(pluginApvts), mainServer(m) {
    mainServer.addListener(this);
}

SourceTree::~SourceTree() {
    mainServer.removeListener(this);
}

void SourceTree::addListener(Listener* listener) {
    listenerList.add(listener);
}

void SourceTree::removeListener(Listener* listener) {
    listenerList.remove(listener);
}

void SourceTree::newPluginConnection(PluginConnection *pluginConnection) {
    int n_clients = 0;
    for (auto & source : sources) {
        if (source.pluginConnection != nullptr) n_clients++;
        if (pluginConnection == source.pluginConnection) return;
    }

    Source newSource;
    newSource.pluginConnection = pluginConnection;
    sources.push_back(newSource);
    
    setTreePropertyAsync(apvts.state.getChildWithName("Settings"), PluginParameters::NUM_CLIENTS_ID, n_clients + 1);

    #if JUCE_DEBUG
        std::cout << "SourceTree has new client! n_clients = " << n_clients + 1 << std::endl;
    #endif
}

void SourceTree::deletedPluginConnection(PluginConnection *pluginConnection) {
    int n_clients = 0;
    for (auto & source : sources) {
        if (pluginConnection == source.pluginConnection) source.pluginConnection = nullptr;
        if (source.pluginConnection != nullptr) n_clients++;
    }

    setTreePropertyAsync(apvts.state.getChildWithName("Settings"), PluginParameters::NUM_CLIENTS_ID, n_clients);

    #if JUCE_DEBUG
        std::cout << "SourceTree deleted client! n_clients = " << n_clients << std::endl;
    #endif
}

void SourceTree::parameterChanged(PluginConnection *pluginConnection, Parameter parameter, int int_value, float value1, float value2, float value3) {

    // handle parameter changing to a source index of an already existing source
    if (parameter == PARAM_SOURCE_IDX && int_value > 0){
        for (auto & source: sources){
            // TODO ensure that every source index exists only once

            // only change to sources that don't have a pluginConnection and have the same sourceIdx
            if (!(source.pluginConnection == nullptr && source.sourceIdx == int_value)){
                continue;
            }

            // if a compatible source was found, find the old source for this plugin
            for (auto & current_source : sources){
                if (current_source.pluginConnection == pluginConnection){
                    current_source.pluginConnection = nullptr;
                    // TODO do something with old source? maybe delete if nothing changed
                    break;
                }
            }

            // set the new pluginConnection
            source.pluginConnection = pluginConnection;
            // dump the current state of the source to the plugin
            dumpSourceToClientPlugin(source);

            return;
        }
    }
    
    for (auto & source : sources) {
        if (pluginConnection == source.pluginConnection) {
            updateSource(source, parameter, int_value, value1, value2, value3);
            
            listenerList.call([source, parameter, int_value] (Listener& l) {l.sourceParameterChanged(source, parameter, int_value);});
            return;
        }
    }
    std::cout << "Error: Source not in SourceTree!" << std::endl;
}

void SourceTree::parameterChanged(int sourceIndex, Parameter parameter, int int_value, float value1, float value2, float value3){
    for (auto & source : sources) {
        if (sourceIndex == source.sourceIdx) {
            updateSource(source, parameter, int_value, value1, value2, value3);

            // notify clients of changed parametr
            if (source.pluginConnection != nullptr){
                source.pluginConnection->parameterChanged(parameter, int_value, value1, value2, value3);
            } else {
                listenerList.call([source, parameter, int_value] (Listener& l) {l.sourceParameterChanged(source, parameter, int_value);});
            }
            return;
        }
    }

    // if the source did not exist create it, and send out the OSC message
    Source newSource;
    newSource.sourceIdx = sourceIndex;
    updateSource(newSource, parameter, int_value, value1, value2, value3);
    newSource.pluginConnection = nullptr;
    sources.push_back(newSource);
    
    listenerList.call([newSource, parameter, int_value] (Listener& l) {l.sourceParameterChanged(newSource, parameter, int_value);});
}

void SourceTree::dumpSourcesToReceiver(){
    #if JUCE_DEBUG
        std::cout << "Dumping Sources via OSC" << std::endl;
    #endif
    for (auto & source: sources){
        if (source.sourceIdx <= 0) continue;
        listenerList.call([source] (Listener& l) {l.sourceParameterChanged(source, PARAM_POS, 0);});
        for (int i = 0; i < source.nGains; i++){
            listenerList.call([source, i] (Listener& l) {l.sourceParameterChanged(source, PARAM_GAIN, i);});

            source.pluginConnection->parameterChanged(PARAM_GAIN, i, source.gain[i], 0, 0);
        }

    }
}

void SourceTree::updateSource(Source &source, Parameter parameter, int int_value, float value1, float value2, float value3){
    switch (parameter){
    case PARAM_SOURCE_IDX:
        source.sourceIdx = int_value;
        break;

    case PARAM_POS:
        source.xPosition = value1;
        source.yPosition = value2;
        source.zPosition = value3;
        break;

    case PARAM_POS_SINGLE:
        if (int_value == PARAM_POS_SINGLE_X) source.xPosition = value1; 
        else if (int_value == PARAM_POS_SINGLE_Y) source.yPosition = value1; 
        else if (int_value == PARAM_POS_SINGLE_Z) source.zPosition = value1; 
    case PARAM_GAIN:
        if (int_value < source.nGains && int_value >=0)
            source.gain[int_value] = value1;
    default:
        break;
    }
}

void SourceTree::dumpSourceToClientPlugin(Source & source){
    if (source.pluginConnection == nullptr)
        return;
    
    source.pluginConnection->parameterChanged(PARAM_POS, 0, source.xPosition, source.yPosition, source.zPosition);
    for (int i = 0; i < source.nGains; i++)
    {
        source.pluginConnection->parameterChanged(PARAM_GAIN, i, source.gain[i], 0, 0);
    }
    
}


void SourceTree::deletedMainServer() {
    sources.clear();
}

void SourceTree::updateNumClients() {
    setTreePropertyAsync(apvts.state.getChildWithName("Settings"), PluginParameters::NUM_CLIENTS_ID, (int) sources.size());
}

void SourceTree::setTreePropertyAsync(juce::ValueTree tree, const juce::Identifier& propertyName, const juce::var& newValue) {
    (new SetTreePropertyMessage{ tree, propertyName, newValue })->post();
}