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

class OscSender : public juce::OSCSender, private juce::ValueTree::Listener {

public:
    explicit OscSender(juce::AudioProcessorValueTreeState& pluginApvts);
    
    void connectToPort();
    void sendMessage(Source& source, Parameter parameter);
    
private:
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;
    void showConnectionErrorMessage (const juce::String& messageText);

private:
    juce::AudioProcessorValueTreeState& apvts;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscSender)
};

#endif /* OscSender_h */
