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


class OscSender : public juce::OSCSender {
public:
    explicit OscSender(juce::AudioProcessorValueTreeState &apvts, juce::StringArray parameterList);
    
    void parameterChanged(const juce::String &parameterID, float newValue);
    
private:
    void showConnectionErrorMessage (const juce::String& messageText);
};

#endif /* OscSender_h */

