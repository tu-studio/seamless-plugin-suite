//
//  XYPad.h
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 07.09.23.
//

#ifndef XY_PAD_H
#define XY_PAD_H

# include <JuceHeader.h>
# include <SeamLess.h>
# include <PluginParameters.h>
# include "soundSource/SoundSource.h"

class XYPad : public juce::Component {
public:
    XYPad(juce::AudioProcessorValueTreeState& pluginApvts);

    void addParameterAttachment(juce::RangedAudioParameter& parameter);

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;

private:
    juce::Point<int> convertMeterToPixel(float xMeter, float yMeter);
    juce::Point<float> convertPixelToMeter(int xPixel, int yPixel);

private:
    juce::AudioProcessorValueTreeState& apvts;
    SoundSource soundSource;
    int sourceWidthPx = 50;

    float xPosition;
    float yPosition;

    std::unique_ptr<juce::ParameterAttachment> xAttachment;
    std::unique_ptr<juce::ParameterAttachment> yAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XYPad)
};

#endif // XY_PAD_H