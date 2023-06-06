//
//  OscSender.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "OscSender.h"

OscSender::OscSender(juce::AudioProcessorValueTreeState &apvts, juce::StringArray parameterList) {
    if (! connect ("127.0.0.1", 9001))
        showConnectionErrorMessage ("Error: could not connect to UDP port 9001.");
    for (auto & parameter : parameterList) {
        parameterChanged(parameter, apvts.getRawParameterValue(parameter)->load());
    }
}

void OscSender::parameterChanged(const juce::String &parameterID, float newValue) {
    if (parameterID == PluginParameters::SEND_1_ID.getParamID()) {
        if (! send("/send1", newValue))
            showConnectionErrorMessage("Error: could not send OSC message.");
    }
}

void OscSender::showConnectionErrorMessage (const juce::String& messageText)
  {
      juce::AlertWindow::showMessageBoxAsync (juce::AlertWindow::WarningIcon,
                                              "Connection error",
                                              messageText,
                                              "OK");
  }
