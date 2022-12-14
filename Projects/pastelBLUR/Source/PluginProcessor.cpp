/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PastelBLURAudioProcessor::PastelBLURAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
, parameters (*this, nullptr, Identifier ("ReverbExperiments"),{
    
    // PREDELAY LENGTH ===============================================================
    
    std::make_unique<AudioParameterFloat>("low_predelay",
                                          "Low_Predelay",
                                          NormalisableRange<float> (0.001f,   // min
                                                                    5.0f,   // max
                                                                    0.01f), // interval
                                          0.001f), // default
    
    std::make_unique<AudioParameterFloat>("mid_predelay",
                                          "Mid_Predelay",
                                          NormalisableRange<float> (0.001f,   // min
                                                                    5.0f,   // max
                                                                    0.01f), // interval
                                          0.001f), // default
    
    std::make_unique<AudioParameterFloat>("high_predelay",
                                          "High_Predelay",
                                          NormalisableRange<float> (0.001f,   // min
                                                                    5.0f,   // max
                                                                    0.01f), // interval
                                          0.001f), // default
    
    // TANK LENGTH ====================================================================
    
    std::make_unique<AudioParameterFloat>("low_tankLength",
                                          "Low_TankLength",
                                          NormalisableRange<float> (0.5f,   // min
                                                                    5.0f,   // max
                                                                    0.01f), // interval
                                          1.0f), // default
    
    std::make_unique<AudioParameterFloat>("mid_tankLength",
                                          "Mid_TankLength",
                                          NormalisableRange<float> (0.5f,   // min
                                                                    5.0f,   // max
                                                                    0.01f), // interval
                                          1.0f), // default
    
    std::make_unique<AudioParameterFloat>("high_tankLength",
                                          "High_TankLength",
                                          NormalisableRange<float> (0.5f,   // min
                                                                    5.0f,   // max
                                                                    0.01f), // interval
                                          1.0f), // default
    
    // TANK DECAY =====================================================================
    
    std::make_unique<AudioParameterFloat>("low_tankDecay",
                                          "Low_TankDecay",
                                          NormalisableRange<float> (0.0f,   // min
                                                                    0.6f,   // max
                                                                    0.01f), // interval
                                          0.3f), // default
    
    std::make_unique<AudioParameterFloat>("mid_tankDecay",
                                          "Mid_TankDecay",
                                          NormalisableRange<float> (0.0f,   // min
                                                                    0.6f,   // max
                                                                    0.01f), // interval
                                          0.3f), // default
    
    std::make_unique<AudioParameterFloat>("high_tankDecay",
                                          "High_TankDecay",
                                          NormalisableRange<float> (0.0f,   // min
                                                                    0.6f,   // max
                                                                    0.01f), // interval
                                          0.3f), // default
    
    // LEVEL ==========================================================================
    
    std::make_unique<AudioParameterFloat>("low_level",
                                          "Low_Level",
                                          NormalisableRange<float> (0.0f,   // min
                                                                    1.0f,   // max
                                                                    0.01f), // interval
                                          1.0f), // default
    
    std::make_unique<AudioParameterFloat>("mid_level",
                                          "Mid_Level",
                                          NormalisableRange<float> (0.0f,   // min
                                                                    1.0f,   // max
                                                                    0.01f), // interval
                                          1.0f), // default
    
    std::make_unique<AudioParameterFloat>("high_level",
                                          "High_Level",
                                          NormalisableRange<float> (0.0f,   // min
                                                                    1.0f,   // max
                                                                    0.01f), // interval
                                          1.0f), // default
    
    // OUTPUT LEVEL ===================================================================
    
    std::make_unique<AudioParameterFloat>("output",
                                          "Output",
                                          NormalisableRange<float> (0.0f,   // min
                                                                    1.0f,   // max
                                                                    0.01f), // interval
                                          1.0f), // default
})
{
    low_predelayParameter = parameters.getRawParameterValue("low_predelay");
    mid_predelayParameter = parameters.getRawParameterValue("mid_predelay");
    high_predelayParameter = parameters.getRawParameterValue("high_predelay");
    
    low_tankLengthParameter = parameters.getRawParameterValue("low_tankLength");
    mid_tankLengthParameter = parameters.getRawParameterValue("mid_tankLength");
    high_tankLengthParameter = parameters.getRawParameterValue("high_tankLength");
    
    low_tankDecayParameter = parameters.getRawParameterValue("low_tankDecay");
    mid_tankDecayParameter = parameters.getRawParameterValue("mid_tankDecay");
    high_tankDecayParameter = parameters.getRawParameterValue("high_tankDecay");
    
    low_levelParameter = parameters.getRawParameterValue("low_level");
    mid_levelParameter = parameters.getRawParameterValue("mid_level");
    high_levelParameter = parameters.getRawParameterValue("high_level");
    
    outLevelParameter = parameters.getRawParameterValue("output");

}

PastelBLURAudioProcessor::~PastelBLURAudioProcessor()
{
}

//==============================================================================
const juce::String PastelBLURAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PastelBLURAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PastelBLURAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PastelBLURAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PastelBLURAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PastelBLURAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PastelBLURAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PastelBLURAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PastelBLURAudioProcessor::getProgramName (int index)
{
    return {};
}

void PastelBLURAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PastelBLURAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PastelBLURAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PastelBLURAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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
#endif

void PastelBLURAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // predelay lengths
    revLow.setPredelayLength(*low_predelayParameter);
    revMid.setPredelayLength(*mid_predelayParameter);
    revHigh.setPredelayLength(*high_predelayParameter);
    
    // tank lengths
    revLow.setTankLengthFactor(*low_tankLengthParameter);
    revMid.setTankLengthFactor(*mid_tankLengthParameter);
    revHigh.setTankLengthFactor(*high_tankLengthParameter);
    
    // tank decays
    revLow.setTankDecay(*low_tankDecayParameter);
    revMid.setTankDecay(*mid_tankDecayParameter);
    revHigh.setTankDecay(*high_tankDecayParameter);
    
    // band levels
    revLow.setLevel(*low_levelParameter);
    revMid.setLevel(*mid_levelParameter);
    revHigh.setLevel(*high_levelParameter);

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto* dataL = buffer.getWritePointer(0);
    auto* dataR = buffer.getWritePointer(1);
    float outputs[2] = {0.0f, 0.0f}; // set aside memory for reverbs to return L and R float values
    float highOutL = 0.0f, highOutR = 0.0f, midOutL = 0.0f, midOutR = 0.0f, lowOutL = 0.0f, lowOutR = 0.0f;
    
    // main loop
    for(int i = 0; i < buffer.getNumSamples(); i++) {
        float samp = (dataL[i] + dataR[i]) * 0.5;
    
        revLow.processSample(samp, outputs);
        lowOutL = lpfLow_L.processSample(outputs[0]);
        lowOutR = lpfLow_R.processSample(outputs[1]);
        
        revMid.processSample(samp, outputs);
        midOutL = lpfMid_L.processSample(hpfMid_L.processSample(outputs[0]));
        midOutR = lpfMid_R.processSample(hpfMid_R.processSample(outputs[1]));
        
        revHigh.processSample(samp, outputs);
        highOutL = hpfHigh_L.processSample(outputs[0]);
        highOutR = hpfHigh_R.processSample(outputs[1]);
        
        dataL[i] = (lowOutL + midOutL + highOutL) * *outLevelParameter;
        dataR[i] = (lowOutR + midOutR + highOutR) * *outLevelParameter;

    }
}

//==============================================================================
bool PastelBLURAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PastelBLURAudioProcessor::createEditor()
{
    return new PastelBLURAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void PastelBLURAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PastelBLURAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PastelBLURAudioProcessor();
}
