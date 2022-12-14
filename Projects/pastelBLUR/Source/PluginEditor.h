/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PALdata/PALlookandfeel/PAL_LookAndFeel_V1.h"
#include "PALdata/PALdsp/PALdsp.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PastelBLURAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PastelBLURAudioProcessorEditor (PastelBLURAudioProcessor&, AudioProcessorValueTreeState&);
    ~PastelBLURAudioProcessorEditor() override;
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PastelBLURAudioProcessor& audioProcessor;
    AudioProcessorValueTreeState& valueTreeState;
    
    PAL_LookAndFeel_V1 laf;
    
    unsigned int scale = 1;
    
    Font OptimaRegular { Typeface::createSystemTypefaceFor(BinaryData::OPTIMA_TTF,
                                                          BinaryData::OPTIMA_TTFSize) };
    Font OptimaBold { Typeface::createSystemTypefaceFor(BinaryData::OPTIMA_BOLD_TTF,
                                                          BinaryData::OPTIMA_BOLD_TTFSize) };
    
    Slider low_predelaySlider;
    Slider mid_predelaySlider;
    Slider high_predelaySlider;
    Slider low_tankLengthSlider;
    Slider mid_tankLengthSlider;
    Slider high_tankLengthSlider;
    Slider low_tankDecaySlider;
    Slider mid_tankDecaySlider;
    Slider high_tankDecaySlider;
    Slider low_levelSlider;
    Slider mid_levelSlider;
    Slider high_levelSlider;
    Slider outSlider;
    
    std::unique_ptr<SliderAttachment> low_predelayAttachment;
    std::unique_ptr<SliderAttachment> mid_predelayAttachment;
    std::unique_ptr<SliderAttachment> high_predelayAttachment;
    std::unique_ptr<SliderAttachment> low_tankLengthAttachment;
    std::unique_ptr<SliderAttachment> mid_tankLengthAttachment;
    std::unique_ptr<SliderAttachment> high_tankLengthAttachment;
    std::unique_ptr<SliderAttachment> low_tankDecayAttachment;
    std::unique_ptr<SliderAttachment> mid_tankDecayAttachment;
    std::unique_ptr<SliderAttachment> high_tankDecayAttachment;
    std::unique_ptr<SliderAttachment> low_levelAttachment;
    std::unique_ptr<SliderAttachment> mid_levelAttachment;
    std::unique_ptr<SliderAttachment> high_levelAttachment;
    std::unique_ptr<SliderAttachment> outSliderAttachment;
    

    Label low_predelayLabel;
    Label mid_predelayLabel;
    Label high_predelayLabel;
    Label low_tankLengthLabel;
    Label mid_tankLengthLabel;
    Label high_tankLengthLabel;
    Label low_tankDecayLabel;
    Label mid_tankDecayLabel;
    Label high_tankDecayLabel;
    Label low_levelLabel;
    Label mid_levelLabel;
    Label high_levelLabel;
    Label outLabel;
    
    Label titleLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PastelBLURAudioProcessorEditor)
};
