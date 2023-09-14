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
    void disconnectFromPort();
    void sourceParameterChanged(Source& source, Parameter parameter);
    
private:
    void sendMessage(juce::OSCMessage& message);
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;
    void showConnectionErrorMessage (const juce::String& messageText);
    void hiResTimerCallback() override;
    void setTreePropertyAsync(juce::ValueTree tree, const juce::Identifier& propertyName, const juce::var& newValue);

private:
    juce::AudioProcessorValueTreeState& apvts;
    std::queue<juce::OSCMessage> oscMessageStack;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscSender)
};

//==================================================================
// Structure to update ValueTree properties on !message thread!
// https://docs.juce.com/master/classCallbackMessage.html

struct SetTreePropertyMessage : public juce::CallbackMessage
{
    SetTreePropertyMessage(juce::ValueTree tree_, const juce::Identifier& propertyName_, const juce::var& newValue_) :
        tree(tree_),
        propertyName(propertyName_),
        newValue(newValue_)
    {
    }
    
    void messageCallback() override
    {
        tree.setProperty(propertyName, newValue, nullptr);
    }
    
    juce::ValueTree tree;
    const juce::Identifier propertyName;
    const juce::var newValue;
};

#endif /* OscSender_h */
