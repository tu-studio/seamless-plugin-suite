//
//  SourceTree.cpp
//  SeamLess_Main
//
//  Created by Fares Schulz on 08.06.23.
//

#include "SourceTree.h"

SourceTree::SourceTree(MainServer& m) : mainServer(m) {
    mainServer.addListener(this);
}

SourceTree::~SourceTree() {
    mainServer.removeListener(this);
}

void SourceTree::newPluginConnection(PluginConnection *pluginConnection) {
    for (auto & source : sources) {
        if (pluginConnection == source.pluginConnection) return;
    }
    Source newSource;
    newSource.pluginConnection = pluginConnection;
    sources.push_back(newSource);
    
    std::cout << "SourceTree has new source! N = " << sources.size() << std::endl;
}

void SourceTree::deletedPluginConnection(PluginConnection *pluginConnection) {
    for (unsigned long i = 0; i < sources.size(); i++) {
        if (pluginConnection == sources[i].pluginConnection) sources.erase(sources.begin() + (long) i);
    }
    std::cout << "SourceTree deleted source! N = " << sources.size() << std::endl;
}

void SourceTree::parameterChanged(PluginConnection *pluginConnection, Parameter parameter, float value1, float value2, float value3) {
    for (auto & source : sources) {
        if (pluginConnection == source.pluginConnection) {
            if (parameter == PARAM_SOURCE_IDX) {
                source.sourceIdx = (int) value1;
            }
            else if (parameter == PARAM_POS) {
                source.xPosition = value1;
                source.yPosition = value2;
                source.zPosition = value3;
            } else if (parameter == PARAM_GAIN_1) {
                source.gain1 = value1;
                juce::ignoreUnused(value2);
                juce::ignoreUnused(value3);
            } else if (parameter == PARAM_GAIN_2) {
                source.gain2 = value1;
                juce::ignoreUnused(value2);
                juce::ignoreUnused(value3);
            }
            std::cout << "Parameter changed:" << std::endl;
            std::cout << "Source Index: " << source.sourceIdx << std::endl;
            std::cout << "Position: (" << source.xPosition << ", " << source.yPosition << ", " << source.zPosition << ")" << std::endl;
            std::cout << "Gain 1: " << source.gain1 << std::endl;
            std::cout << "Gain 2: " << source.gain2 << std::endl;
            return;
        }
    }
    std::cout << "Error: Source not in SourceTree!" << std::endl;
}

