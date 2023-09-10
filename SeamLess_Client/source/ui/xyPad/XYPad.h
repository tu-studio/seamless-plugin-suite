//
//  XYPad.h
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 07.09.23.
//

#ifndef XY_PAD_H
#define XY_PAD_H

#include <JuceHeader.h>
#include <SeamLess.h>
#include <PluginParameters.h>
#include <SoundSource.h>
#include <CoordinatesLabel.h>
#include <Grid.h>

class XYPad : public juce::Component {
public:
    XYPad(juce::AudioProcessorValueTreeState& pluginApvts);

    void addParameterAttachment(juce::RangedAudioParameter& parameter);

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;

    void setSourceWidthPx(int newSourceWidthPx);

private:
    juce::Point<int> convertMeterToPixel(float xMeter, float yMeter);
    juce::Point<float> convertPixelToMeter(int xPixel, int yPixel);
    void updateSourceWidthPx();
    void paintFraming(juce::Graphics& g);
    void paintSourceShadow(juce::Graphics& g);
    void paintGrid(juce::Graphics& g);

private:
    juce::AudioProcessorValueTreeState& apvts;
    
    SoundSource soundSource;
    int sourceWidthPx;

    float xPosition;
    float yPosition;
    float zPosition;

    Grid grid;

    juce::Path shadowOrigin;
    juce::DropShadow sourceShadow;

    std::unique_ptr<juce::ParameterAttachment> xAttachment;
    std::unique_ptr<juce::ParameterAttachment> yAttachment;
    std::unique_ptr<juce::ParameterAttachment> zAttachment;

    // Coordinates when dragging the sound source
    CoordinatesLabel coordinatesLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XYPad)
};

#endif // XY_PAD_H