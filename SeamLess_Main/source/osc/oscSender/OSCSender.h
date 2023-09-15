//
//  OSCSender.h
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#ifndef OSCSender_h
#define OSCSender_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>
#include <SourceTree.h>

class OSCSender : public juce::OSCSender, private juce::ValueTree::Listener, public juce::OSCReceiver::Listener<juce::OSCReceiver::RealtimeCallback>, private juce::HighResolutionTimer {

public:
    explicit OSCSender(juce::AudioProcessorValueTreeState& pluginApvts);
    ~OSCSender() override;
    
    void connectToPort();
    void disconnectFromPort();
    void sourceParameterChanged(Source& source, Parameter parameter);
    
private:
    void sendMessage(juce::OSCMessage& message);
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;
    void hiResTimerCallback() override;
    void setTreePropertyAsync(juce::ValueTree tree, const juce::Identifier& propertyName, const juce::var& newValue);
    void oscMessageReceived(const juce::OSCMessage& message) override;

private:
    juce::AudioProcessorValueTreeState& apvts;
    std::queue<juce::OSCMessage> oscMessageStack;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OSCSender)
};

#endif /* OSCSender_h */
