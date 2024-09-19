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
    for (auto & source : sources) {
        if (pluginConnection == source.pluginConnection) return;
    }
    // TODO check here somehow if the source already exists
    Source newSource;
    newSource.pluginConnection = pluginConnection;
    sources.push_back(newSource);
    
    // TODO when sources without connections are added, this would be false
    setTreePropertyAsync(apvts.state.getChildWithName("Settings"), PluginParameters::NUM_CLIENTS_ID, (int) sources.size());

    #if JUCE_DEBUG
        std::cout << "SourceTree has new source! N = " << sources.size() << std::endl;
    #endif
}

void SourceTree::deletedPluginConnection(PluginConnection *pluginConnection) {
    for (unsigned long i = 0; i < sources.size(); i++) {
        if (pluginConnection == sources[i].pluginConnection) sources.erase(sources.begin() + (long) i);
    }

    setTreePropertyAsync(apvts.state.getChildWithName("Settings"), PluginParameters::NUM_CLIENTS_ID, (int) sources.size());

    #if JUCE_DEBUG
        std::cout << "SourceTree deleted source! N = " << sources.size() << std::endl;
    #endif
}

void SourceTree::parameterChanged(PluginConnection *pluginConnection, Parameter parameter, float value1, float value2, float value3) {
    for (auto & source : sources) {
        if (pluginConnection == source.pluginConnection) {
            updateSource(source, parameter, value1, value2, value3);
            
            listenerList.call([source, parameter] (Listener& l) {l.sourceParameterChanged(source, parameter);});
            return;
        }
    }
    std::cout << "Error: Source not in SourceTree!" << std::endl;
}

void SourceTree::parameterChanged(int sourceIndex, Parameter parameter, float value1, float value2, float value3){
    for (auto & source : sources) {
        if (sourceIndex == source.sourceIdx) {
            updateSource(source, parameter, value1, value2, value3);

            // notify clients of changed parametr
            if (source.pluginConnection != nullptr){
                source.pluginConnection->parameterChanged(parameter, value1, value2, value3);
            } else {
                listenerList.call([source, parameter] (Listener& l) {l.sourceParameterChanged(source, parameter);});
            }
            return;
        }
    }

    // if the source did not exist create it, and send out the OSC message
    Source newSource;
    newSource.sourceIdx = sourceIndex;
    updateSource(newSource, parameter, value1, value2, value3);
    newSource.pluginConnection = nullptr;
    sources.push_back(newSource);
    
    listenerList.call([newSource, parameter] (Listener& l) {l.sourceParameterChanged(newSource, parameter);});
    std::cout << "Error: Source not in SourceTree!" << std::endl;
}

void SourceTree::updateSource(Source &source, Parameter parameter, float value1, float value2, float value3){
    if (parameter == PARAM_SOURCE_IDX) {
        source.sourceIdx = (int) value1;
    } else if (parameter == PARAM_POS) {
        if (value1 != 99.f) source.xPosition = value1;
        if (value2 != 99.f) source.yPosition = value2;
        if (value3 != 99.f) source.zPosition = value3;
    } else if (parameter == PARAM_GAIN_1) {
        source.gain1 = value1;
        juce::ignoreUnused(value2);
        juce::ignoreUnused(value3);
    } else if (parameter == PARAM_GAIN_2) {
        source.gain2 = value1;
        juce::ignoreUnused(value2);
        juce::ignoreUnused(value3);
    } else if (parameter == PARAM_GAIN_3) {
        source.gain3 = value1;
        juce::ignoreUnused(value2);
        juce::ignoreUnused(value3);
    } else if (parameter == PARAM_GAIN_4) {
        source.gain4 = value1;
        juce::ignoreUnused(value2);
        juce::ignoreUnused(value3);
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