//
//  SendFader.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "SendFader.h"

SendFader::SendFader(juce::AudioProcessorValueTreeState &a) : apvts(a) {
    gain1Slider.addSliderAttachment(apvts, SendParameters::GAIN_1_ID.getParamID());
    gain1Slider.setDoubleClickReturnValue(0.f);
    addAndMakeVisible(gain1Slider);
    gain2Slider.addSliderAttachment(apvts, SendParameters::GAIN_2_ID.getParamID());
    gain2Slider.setDoubleClickReturnValue(0.f);
    addAndMakeVisible(gain2Slider);
}

void SendFader::resized() {
    auto area = getLocalBounds();
    gain1Slider.setBounds(0, 0, area.getWidth()/2, area.getHeight());
    gain2Slider.setBounds(area.getWidth()/2, 0, area.getWidth()/2, area.getHeight());
}
