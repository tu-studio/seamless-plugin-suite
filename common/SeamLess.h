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

#ifndef SeamLess_h
#define SeamLess_h

#define DEFAULT_OSC_SEND_ADRESS "127.0.0.1"
#define DEFAULT_OSC_SEND_PORT 9000

#define DEFAULT_OSC_RECEIVE_PORT 9001

// send interval (ms) for outgoing OSC messages
#define SEND_INTERVAL 20

//==================================================================

#define IPC_PORT 52713

#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288   /* pi             */
#endif /* M_PI */

const juce::Colour seamlessBlue      = juce::Colour::fromRGBA(0, 65, 93, 255);
const juce::Colour transparent       = juce::Colour(00000000);
const juce::Colour seamlessLightGrey = juce::Colour(220,220,220);
const juce::Colour seamlessGrey      = juce::Colour(140,140,140);

#endif /* SeamLess_h */