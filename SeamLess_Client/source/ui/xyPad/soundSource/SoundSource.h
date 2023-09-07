/*
=====================================================================

SoundSource.h
Created: 7 Sep 2021 11:00:00am
Author:  Fares Schulz

=====================================================================
*/

# ifndef SOUND_SOURCE_H
# define SOUND_SOURCE_H

# include <JuceHeader.h>
# include <SeamLess.h>

class SoundSource : public juce::Component {
public:
    SoundSource();

    void paint(juce::Graphics& g) override;
    void resized() override;

    float xPosition=0;
    float yPosition=0;

private:
    juce::ColourGradient gradient;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SoundSource)
};

# endif // SOUND_SOURCE_H