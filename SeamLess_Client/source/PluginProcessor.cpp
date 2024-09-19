#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
        apvts (*this, nullptr, juce::Identifier ((std::string) "Parameters_SeamLess_Client"), PluginParameters::createParameterLayout())
{
    for (auto & parameterID : PluginParameters::getPluginParameterList()) {
        apvts.addParameterListener(parameterID, this);
    }
    // A new not automatable value tree is created, since the one in PluginParameters is static and shared between all instances of the plugin
    // Therefore we can get ambiguous behaviour if we don't create a new one for each instance 
    juce::ValueTree newNotAutomatableValueTree = PluginParameters::createNotAutomatableValueTree().createCopy();
    apvts.state.addChild(newNotAutomatableValueTree, 0 , nullptr);
    apvts.state.addListener(this);
    pluginConnection.addListener(this);
    pluginConnection.connect();
    if (!pluginConnection.isConnected()) {
        startTimer(1000);
    }
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
{
    for (auto & parameterID : PluginParameters::getPluginParameterList()) {
        apvts.removeParameterListener(parameterID, this);
    }
    apvts.state.removeListener(this);
    // Remove the shared ValueTree for not automatalbe parameters
    PluginParameters::clearNotAutomatableValueTree();
    // Remove the ValueTree for the plugin
    apvts.state.removeChild(0 , nullptr);
}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String AudioPluginAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);
}

void AudioPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void AudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        juce::ignoreUnused (channelData);
        // ..do something to the data...
    }
}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
{
    return new AudioPluginAudioProcessorEditor (*this, apvts);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
    #if JUCE_DEBUG
        std::cout << xml->toString() << std::endl;
    #endif
}

void AudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr) {
        #if JUCE_DEBUG
            std::cout << xmlState->toString() << std::endl;
        #endif
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
    }
    if (pluginConnection.isConnected()) apvts.state.getChildWithName("Settings").setProperty(PluginParameters::MAIN_CONNECTION_STATUS_ID, 1, nullptr);
    else apvts.state.getChildWithName("Settings").setProperty(PluginParameters::MAIN_CONNECTION_STATUS_ID, 0, nullptr);

    pluginConnection.updateState(apvts, PluginParameters::getPluginParameterList(), PluginParameters::getSettingsList());
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}

void AudioPluginAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue) {
    pluginConnection.parameterChanged(parameterID, newValue);
}

void AudioPluginAudioProcessor::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) {
    pluginConnection.parameterChanged(property.toString(), treeWhosePropertyHasChanged.getProperty(property));
}

void AudioPluginAudioProcessor::timerCallback() {
    if (!pluginConnection.isConnected()) {
        pluginConnection.connect();
    } else {
        stopTimer();
    }
}

void AudioPluginAudioProcessor::forwardMessage(PluginConnection *pluginConnectionThatCalled, const juce::MemoryBlock &memoryBlock) {
    // listener to the pluginConnection from the main plugin
    Message* message = (Message*) memoryBlock.getData();
    Parameter parameter = message->parameter;
    float value1 = message->value1;
    float value2 = message->value2;
    float value3 = message->value3;

    switch (parameter)
    {
    case Parameter::PARAM_POS:
        apvts.getParameter(OSCParameters::POS_X_ID.getParamID())->setValueNotifyingHost(OSCParameters::POS_RANGE.convertTo0to1(value1));
        apvts.getParameter(OSCParameters::POS_Y_ID.getParamID())->setValueNotifyingHost(OSCParameters::POS_RANGE.convertTo0to1(value2));
        apvts.getParameter(OSCParameters::POS_Z_ID.getParamID())->setValueNotifyingHost(OSCParameters::POS_RANGE.convertTo0to1(value3));
        break;
    case Parameter::PARAM_GAIN_1:
        apvts.getParameter(OSCParameters::GAIN_1_ID.getParamID())->setValueNotifyingHost(OSCParameters::GAIN_RANGE.convertTo0to1(value1));
        break;
    case Parameter::PARAM_GAIN_2:
        apvts.getParameter(OSCParameters::GAIN_2_ID.getParamID())->setValueNotifyingHost(OSCParameters::GAIN_RANGE.convertTo0to1(value1));
        break;
    case Parameter::PARAM_GAIN_3:
        apvts.getParameter(OSCParameters::GAIN_3_ID.getParamID())->setValueNotifyingHost(OSCParameters::GAIN_RANGE.convertTo0to1(value1));
        break;
    case Parameter::PARAM_GAIN_4:
        apvts.getParameter(OSCParameters::GAIN_4_ID.getParamID())->setValueNotifyingHost(OSCParameters::GAIN_RANGE.convertTo0to1(value1));
        break;
    case Parameter::PARAM_SOURCE_IDX:
        // we should never get here
        break;
    default:
        break;
    }
}

void AudioPluginAudioProcessor::connected(PluginConnection *pluginConnectionThatCalled) {
    apvts.state.getChildWithName("Settings").setProperty(PluginParameters::MAIN_CONNECTION_STATUS_ID, 1, nullptr);
    pluginConnection.updateState(apvts, PluginParameters::getPluginParameterList(), PluginParameters::getSettingsList());
    stopTimer();
    juce::ignoreUnused(pluginConnectionThatCalled);
}

void AudioPluginAudioProcessor::disconnected(PluginConnection *pluginConnectionThatCalled) {
    juce::ignoreUnused(pluginConnectionThatCalled);
    apvts.state.getChildWithName("Settings").setProperty(PluginParameters::MAIN_CONNECTION_STATUS_ID, 0, nullptr);
    startTimer(1000);
}