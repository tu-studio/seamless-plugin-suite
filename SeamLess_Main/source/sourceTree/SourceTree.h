//
//  SourceTree.hpp
//  SeamLess_Main
//
//  Created by Fares Schulz on 08.06.23.
//

#ifndef SourceTree_h
#define SourceTree_h

#include <JuceHeader.h>
#include <MainServer.h>

struct Source {
    int sourceIdx;
    float xPosition;
    float yPosition;
    float zPosition;
    float gain1;
    float gain2;
    PluginConnection* pluginConnection;
};

class SourceTree: private MainServer::Listener
{
public:
    SourceTree(MainServer& m);
    ~SourceTree();
    
private:
    void newPluginConnection(PluginConnection* pluginConnection) override;
    void deletedPluginConnection(PluginConnection* pluginConnection) override;
    void parameterChanged(PluginConnection* pluginConnection, Parameter parameter, float value1, float value2, float value3) override;
    void deletedMainServer();
    
private:
    MainServer& mainServer;
    std::vector<Source> sources;
};

#endif /* SourceTree_h */
