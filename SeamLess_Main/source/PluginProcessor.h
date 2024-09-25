#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <SeamLess.h>
#include <PluginParameters.h>
#include <MainServer.h>
#include <SourceTree.h>
#include <OSCSender.h>
#include <OSCReceiver.h>

//==============================================================================
class AudioPluginAudioProcessor  : public juce::AudioProcessor, private juce::ValueTree::Listener, private SourceTree::Listener, juce::OSCReceiver::Listener<juce::OSCReceiver::MessageLoopCallback>
{
public:
    //==============================================================================
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    OSCReceiver& getOSCReceiverRef();

private:
    void sourceParameterChanged(Source source, Parameter parameter, int index) override;
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;
    void oscMessageReceived (const juce::OSCMessage &message) override;

    //==============================================================================
private:
    juce::AudioProcessorValueTreeState apvts;

    MainServer mainServer;
    SourceTree sourceTree;
    OSCSender oscSender;
    OSCReceiver oscReceiver;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)
};
