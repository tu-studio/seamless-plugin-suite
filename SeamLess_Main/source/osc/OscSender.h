//
//  OscSender.h
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#ifndef OscSender_h
#define OscSender_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>
#include <SourceTree.h>

class OscSender : public juce::OSCSender, private juce::ValueTree::Listener, private juce::HighResolutionTimer {

public:
    explicit OscSender(juce::AudioProcessorValueTreeState& pluginApvts);
    
    void connectToPort();
    void sourceParameterChanged(Source& source, Parameter parameter);
    
private:
    void sendMessage(juce::OSCMessage& message);
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;
    void showConnectionErrorMessage (const juce::String& messageText);
    void hiResTimerCallback() override;

private:
    juce::AudioProcessorValueTreeState& apvts;
    std::queue<juce::OSCMessage> oscMessageStack;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscSender)
};

#endif /* OscSender_h */
