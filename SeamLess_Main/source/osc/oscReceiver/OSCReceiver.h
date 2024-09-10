//
//  OSCReceiver.h
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#ifndef OSCReceiver_h
#define OSCReceiver_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>
#include <SourceTree.h>

class OSCReceiver : public juce::OSCReceiver, private juce::ValueTree::Listener {

public:
    explicit OSCReceiver(juce::AudioProcessorValueTreeState& pluginApvts);
    ~OSCReceiver() override;
    
    void connectToPort();
    void disconnectFromPort();
    
private:
    void sendMessage(juce::OSCMessage& message);
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;

private:
    juce::AudioProcessorValueTreeState& apvts;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OSCReceiver)
};

#endif /* OSCReceiver_h */
