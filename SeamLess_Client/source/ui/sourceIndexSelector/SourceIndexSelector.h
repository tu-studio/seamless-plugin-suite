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
#include <SendParameters.h>

class SourceIndexSelector : public juce::Component {
public:
    SourceIndexSelector(juce::AudioProcessorValueTreeState &apvts);
    ~SourceIndexSelector() override;
    
    void resized() override;

private:
    void sourceIndexTextChanged();

private:
    juce::AudioProcessorValueTreeState& apvts;

    juce::Label descLabel;
    juce::Label sourceIndexText;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceIndexSelector)
};

#endif /* SourceIndexSelector_h */
