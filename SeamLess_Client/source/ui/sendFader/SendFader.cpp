//
//  SendFader.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "SendFader.h"

SendFader::SendFader(juce::AudioProcessorValueTreeState &parameters) : parameters(parameters) {
    send1Slider.addSliderAttachment(parameters, PluginParameters::SEND_1_ID.getParamID());
    send1Slider.setDoubleClickReturnValue(0.f);
    addAndMakeVisible(send1Slider);
}

void SendFader::resized() {
    auto area = getLocalBounds();
    send1Slider.setBounds(area);
}
