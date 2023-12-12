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

const juce::Colour seamlessBlue      = juce::Colour::fromRGBA(0, 65, 93, 255);
const juce::Colour transparent       = juce::Colour(00000000);
const juce::Colour seamlessLightGrey = juce::Colour(220,220,220);
const juce::Colour seamlessGrey      = juce::Colour(140,140,140);

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

#endif /* SeamLess_h */