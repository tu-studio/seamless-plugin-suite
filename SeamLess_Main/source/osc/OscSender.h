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
#include <SourceTree.h>

class OscSender : public juce::OSCSender {
public:
    explicit OscSender();
    
    void sendMessage(Source& source, Parameter parameter);
    
private:
    void showConnectionErrorMessage (const juce::String& messageText);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscSender)
};

#endif /* OscSender_h */
