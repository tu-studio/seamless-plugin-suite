/*
=====================================================================

SeamLess.h
Created: 6 Jun 2023
Author:  Fares Schulz

=====================================================================
*/

/*===================================================================
Configurations for SeamLess Plugin Suite
===================================================================*/

#include <JuceHeader.h>

#ifndef SeamLess_h
#define SeamLess_h

#define DEFAULT_OSC_SEND_ADRESS "127.0.0.1"
#define DEFAULT_OSC_SEND_PORT 9000
// send interval (ms) for outgoing OSC messages
#define DEFAULT_OSC_SEND_INTERVAL 0

#define DEFAULT_OSC_RECEIVE_PORT 9001

//==================================================================

#define IPC_PORT 52713

#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288   /* pi             */
#endif /* M_PI */

const juce::Colour tuStudioPurple      = juce::Colour(0xff8c61b0);
const juce::Colour tuStudioDarkPurple  = juce::Colour(0xff3f2951);
const juce::Colour transparent       = juce::Colour(0x00000000);
const juce::Colour tuStudioNight = juce::Colour(0xff0c0910);
const juce::Colour tuStudioLightLavender      = juce::Colour(0xffd7dae5);
const juce::Colour tuStudioTransparentLightLavender      = juce::Colour(0x55d7dae5);
const juce::Colour tuStudioRed = juce::Colour(0xff6e0e0a);
const juce::Colour tuStudioEbony = juce::Colour(0xff606c64);
const juce::Colour tuStudioTransparentEbony = juce::Colour(0x88606c64);

//==================================================================
// Structure to update ValueTree properties on !message thread!
// https://docs.juce.com/master/classCallbackMessage.html
//==================================================================

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

#endif /* SeamLess_h */