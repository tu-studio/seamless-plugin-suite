//
//  SourceIndexSelector.h
//  SeamLess_Client
//
//  Created by Fares Schulz on 08.06.23.
//

#ifndef SourceIndexSelector_h
#define SourceIndexSelector_h

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>

class SourceIndexSelector : public juce::Component, private juce::ValueTree::Listener {
public:
    SourceIndexSelector(juce::AudioProcessorValueTreeState &apvts);
    ~SourceIndexSelector() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    void sourceIndexTextChanged();
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;

private:
    juce::AudioProcessorValueTreeState& apvts;

    juce::Label descLabel;
    juce::Label sourceIndexText;
    juce::Label connectionStatusLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceIndexSelector)
};

#endif /* SourceIndexSelector_h */
