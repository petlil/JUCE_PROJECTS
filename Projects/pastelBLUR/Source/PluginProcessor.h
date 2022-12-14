/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PALdata/PALdsp/PALdsp.h"
#include "PALrev.h"

//==============================================================================
/**
*/
class PastelBLURAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    PastelBLURAudioProcessor();
    ~PastelBLURAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

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

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PastelBLURAudioProcessor)
    
    PALrev revHigh;
    PALrev revMid;
    PALrev revLow;
    
    // low band
    LPF lpfLow_L {LPF::BIQUAD, 500.0f, 1.0f};
    LPF lpfLow_R {LPF::BIQUAD, 500.0f, 1.0f};
    // middle band
    LPF lpfMid_L {LPF::BIQUAD, 5000.0f, 1.0f};
    LPF lpfMid_R {LPF::BIQUAD, 5000.0f, 1.0f};
    HPF hpfMid_L {HPF::BIQUAD, 500, 1.0f};
    HPF hpfMid_R {HPF::BIQUAD, 500, 1.0f};
    // high band
    HPF hpfHigh_L {HPF::BIQUAD, 5000.0f, 1.0f};
    HPF hpfHigh_R {HPF::BIQUAD, 5000.0f, 1.0f};
    
    AudioProcessorValueTreeState parameters;
    std::atomic<float>* low_predelayParameter = nullptr;
    std::atomic<float>* low_tankLengthParameter  = nullptr;
    std::atomic<float>* low_tankDecayParameter = nullptr;
    std::atomic<float>* low_levelParameter = nullptr;
    
    std::atomic<float>* mid_predelayParameter = nullptr;
    std::atomic<float>* mid_tankLengthParameter  = nullptr;
    std::atomic<float>* mid_tankDecayParameter = nullptr;
    std::atomic<float>* mid_levelParameter = nullptr;
    
    std::atomic<float>* high_predelayParameter = nullptr;
    std::atomic<float>* high_tankLengthParameter  = nullptr;
    std::atomic<float>* high_tankDecayParameter = nullptr;
    std::atomic<float>* high_levelParameter = nullptr;
    
    std::atomic<float>* outLevelParameter = nullptr;
};
