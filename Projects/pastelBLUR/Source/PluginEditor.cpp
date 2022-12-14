/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PastelBLURAudioProcessorEditor::PastelBLURAudioProcessorEditor (PastelBLURAudioProcessor& p, AudioProcessorValueTreeState& vts)
: AudioProcessorEditor (&p), audioProcessor (p), valueTreeState (vts)
{
    setSize (550, 425);
    scale = 2; // pixel art assets will be scaled up 2x
    OptimaBold.setHeight(18);
    
    setLookAndFeel(&laf);
    
    // PREDELAY ============
    // slider
    low_predelaySlider.setSliderStyle (Slider::RotaryVerticalDrag);
    low_predelaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    low_predelaySlider.setPopupDisplayEnabled(false, false, this);
    addAndMakeVisible(&low_predelaySlider);
    low_predelayAttachment.reset (new SliderAttachment (valueTreeState, "low_predelay", low_predelaySlider));
    // label
    low_predelayLabel.setJustificationType(juce::Justification::centred);
    low_predelayLabel.setText("delay", NotificationType::dontSendNotification);
    low_predelayLabel.setFont(OptimaBold);
    low_predelayLabel.setColour(Label::textColourId, Colour(0xff63607c));
    addAndMakeVisible(&low_predelayLabel);
    
    // slider
    mid_predelaySlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mid_predelaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mid_predelaySlider.setPopupDisplayEnabled(false, false, this);
    addAndMakeVisible(&mid_predelaySlider);
    mid_predelayAttachment.reset (new SliderAttachment (valueTreeState, "mid_predelay", mid_predelaySlider));
    // label
    mid_predelayLabel.setJustificationType(juce::Justification::centred);
    mid_predelayLabel.setText("delay", NotificationType::dontSendNotification);
    mid_predelayLabel.setFont(OptimaBold);
    mid_predelayLabel.setColour(Label::textColourId, Colour(0xff63607c));
    addAndMakeVisible(&mid_predelayLabel);
    
    // slider
    high_predelaySlider.setSliderStyle (Slider::RotaryVerticalDrag);
    high_predelaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    high_predelaySlider.setPopupDisplayEnabled(false, false, this);
    addAndMakeVisible(&high_predelaySlider);
    high_predelayAttachment.reset (new SliderAttachment (valueTreeState, "high_predelay", high_predelaySlider));
    // label
    high_predelayLabel.setJustificationType(juce::Justification::centred);
    high_predelayLabel.setText("delay", NotificationType::dontSendNotification);
    high_predelayLabel.setFont(OptimaBold);
    high_predelayLabel.setColour(Label::textColourId, Colour(0xff63607c));
    addAndMakeVisible(&high_predelayLabel);
    
    // TANK LENGTH ============
    // slider
    low_tankLengthSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    low_tankLengthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    low_tankLengthSlider.setPopupDisplayEnabled(false, false, this);
    addAndMakeVisible(&low_tankLengthSlider);
    low_predelayAttachment.reset (new SliderAttachment (valueTreeState, "low_tankLength", low_tankLengthSlider));
    // label
    low_tankLengthLabel.setJustificationType(juce::Justification::centred);
    low_tankLengthLabel.setText("size", NotificationType::dontSendNotification);
    low_tankLengthLabel.setFont(OptimaBold);
    low_tankLengthLabel.setColour(Label::textColourId, Colour(0xff63607c));
    addAndMakeVisible(&low_tankLengthLabel);
    
    // slider
    mid_tankLengthSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mid_tankLengthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mid_tankLengthSlider.setPopupDisplayEnabled(false, false, this);
    addAndMakeVisible(&mid_tankLengthSlider);
    mid_predelayAttachment.reset (new SliderAttachment (valueTreeState, "mid_tankLength", mid_tankLengthSlider));
    // label
    mid_tankLengthLabel.setJustificationType(juce::Justification::centred);
    mid_tankLengthLabel.setText("size", NotificationType::dontSendNotification);
    mid_tankLengthLabel.setFont(OptimaBold);
    mid_tankLengthLabel.setColour(Label::textColourId, Colour(0xff63607c));
    addAndMakeVisible(&mid_tankLengthLabel);
    
    // slider
    high_tankLengthSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    high_tankLengthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    high_tankLengthSlider.setPopupDisplayEnabled(false, false, this);
    addAndMakeVisible(&high_tankLengthSlider);
    high_predelayAttachment.reset (new SliderAttachment (valueTreeState, "high_tankLength", high_tankLengthSlider));
    // label
    high_tankLengthLabel.setJustificationType(juce::Justification::centred);
    high_tankLengthLabel.setText("size", NotificationType::dontSendNotification);
    high_tankLengthLabel.setFont(OptimaBold);
    high_tankLengthLabel.setColour(Label::textColourId, Colour(0xff63607c));
    addAndMakeVisible(&high_tankLengthLabel);
    
    
    // TANK DECAY ============
    // slider
    low_tankDecaySlider.setSliderStyle (Slider::RotaryVerticalDrag);
    low_tankDecaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    low_tankDecaySlider.setPopupDisplayEnabled(false, false, this);
    addAndMakeVisible(&low_tankDecaySlider);
    low_tankDecayAttachment.reset (new SliderAttachment (valueTreeState, "low_tankDecay", low_tankDecaySlider));
    // label
    low_tankDecayLabel.setJustificationType(juce::Justification::centred);
    low_tankDecayLabel.setText("blur", NotificationType::dontSendNotification);
    low_tankDecayLabel.setFont(OptimaBold);
    low_tankDecayLabel.setColour(Label::textColourId, Colour(0xff63607c));
    addAndMakeVisible(&low_tankDecayLabel);
    
    // slider
    mid_tankDecaySlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mid_tankDecaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mid_tankDecaySlider.setPopupDisplayEnabled(false, false, this);
    addAndMakeVisible(&mid_tankDecaySlider);
    mid_tankDecayAttachment.reset (new SliderAttachment (valueTreeState, "mid_tankDecay", mid_tankDecaySlider));
    // label
    mid_tankDecayLabel.setJustificationType(juce::Justification::centred);
    mid_tankDecayLabel.setText("blur", NotificationType::dontSendNotification);
    mid_tankDecayLabel.setFont(OptimaBold);
    mid_tankDecayLabel.setColour(Label::textColourId, Colour(0xff63607c));
    addAndMakeVisible(&mid_tankDecayLabel);
    
    // slider
    high_tankDecaySlider.setSliderStyle (Slider::RotaryVerticalDrag);
    high_tankDecaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    high_tankDecaySlider.setPopupDisplayEnabled(false, false, this);
    addAndMakeVisible(&high_tankDecaySlider);
    high_tankDecayAttachment.reset (new SliderAttachment (valueTreeState, "high_tankDecay", high_tankDecaySlider));
    // label
    high_tankDecayLabel.setJustificationType(juce::Justification::centred);
    high_tankDecayLabel.setText("blur", NotificationType::dontSendNotification);
    high_tankDecayLabel.setFont(OptimaBold);
    high_tankDecayLabel.setColour(Label::textColourId, Colour(0xff63607c));
    addAndMakeVisible(&high_tankDecayLabel);
    
    // BAND LEVEL ============
    // slider
    low_levelSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    low_levelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    low_levelSlider.setPopupDisplayEnabled(false, false, this);
    addAndMakeVisible(&low_levelSlider);
    low_levelAttachment.reset (new SliderAttachment (valueTreeState, "low_level", low_levelSlider));
    // label
    low_levelLabel.setJustificationType(juce::Justification::centred);
    low_levelLabel.setText("level", NotificationType::dontSendNotification);
    low_levelLabel.setFont(OptimaBold);
    low_levelLabel.setColour(Label::textColourId, Colour(0xff63607c));
    addAndMakeVisible(&low_levelLabel);
    
    // slider
    mid_levelSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mid_levelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mid_levelSlider.setPopupDisplayEnabled(false, false, this);
    addAndMakeVisible(&mid_levelSlider);
    mid_levelAttachment.reset (new SliderAttachment (valueTreeState, "mid_level", mid_levelSlider));
    // label
    mid_levelLabel.setJustificationType(juce::Justification::centred);
    mid_levelLabel.setText("level", NotificationType::dontSendNotification);
    mid_levelLabel.setFont(OptimaBold);
    mid_levelLabel.setColour(Label::textColourId, Colour(0xff63607c));
    addAndMakeVisible(&mid_levelLabel);
    
    // slider
    high_levelSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    high_levelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    high_levelSlider.setPopupDisplayEnabled(false, false, this);
    addAndMakeVisible(&high_levelSlider);
    high_levelAttachment.reset (new SliderAttachment (valueTreeState, "high_level", high_levelSlider));
    // label
    high_levelLabel.setJustificationType(juce::Justification::centred);
    high_levelLabel.setText("level", NotificationType::dontSendNotification);
    high_levelLabel.setFont(OptimaBold);
    high_levelLabel.setColour(Label::textColourId, Colour(0xff63607c));
    addAndMakeVisible(&high_levelLabel);
    
    // OUTPUT
    // slider
    outSlider.setSliderStyle (Slider::LinearVertical);
    outSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    outSlider.setPopupDisplayEnabled(false, false, this);
    addAndMakeVisible(&outSlider);
    outSliderAttachment.reset (new SliderAttachment (valueTreeState, "output", outSlider));
    // label
    outLabel.setJustificationType(juce::Justification::centred);
    outLabel.setText("OUT", NotificationType::dontSendNotification);
    outLabel.setFont(OptimaBold);
    outLabel.setColour(Label::textColourId, Colour(0xff63607c));
    addAndMakeVisible(&outLabel);
}

PastelBLURAudioProcessorEditor::~PastelBLURAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void PastelBLURAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (Colour(0xffe0d8fb));
    laf.drawBorders(g, getWidth(), getHeight(), 3);
    
    int w = getWidth();
    int h = getHeight();
    
    // variables for calculating positions for box borders
    // (this must be done in Paint because Resize has no access to a Graphics object!)
    int bandGap = h / 50;
    int topMargin = h / 10;
    int bottomMargin = h / 50;
    int leftMargin = h / 5;
    int rightMargin = h / 3.5;
    int centreWidth = w - (leftMargin + rightMargin);
    int centreHeight = h - (topMargin + bottomMargin + bandGap);
    int bandWidth = (centreWidth - (bandGap * 2)) / 3;
    int low_x_border = leftMargin;
    int mid_x_border = leftMargin + bandWidth + bandGap;
    int high_x_border = leftMargin + ((bandWidth + bandGap) * 2);
    
    int vals[3] = {low_x_border, mid_x_border, high_x_border}; // for iteration
    
    for(int i = 0; i < 3; i++) {
        laf.drawBox(g,
                    vals[i], // x
                    topMargin, // y
                    bandWidth, // width
                    centreHeight, // height
                    2, // scale
                    PAL_LookAndFeel_V1::PastelColours::LIGHT_PINK); // fill
    }
    
    g.setColour(Colour(0xff63607c));
    OptimaBold.setHeight(h / 20);
    g.setFont(OptimaBold);
    g.drawFittedText("LOW", low_x_border, topMargin / 2, 100, 10, Justification::topLeft, 1);
    g.drawFittedText("MID", mid_x_border, topMargin / 2, 100, 10, Justification::topLeft, 1);
    g.drawFittedText("HIGH", high_x_border, topMargin / 2, 100, 10, Justification::topLeft, 1);
    g.drawFittedText("OUT", w - (rightMargin / 2) - 10, topMargin + 320, 100, 10, Justification::topLeft, 1);
}

void PastelBLURAudioProcessorEditor::resized()
{
    int w = getWidth();
    int h = getHeight();
    scale = 2; // to change how large knobs / sliders appear
    
    // sizes of art assets
    int knobSize = 30;
    int sliderHeight = 102;
    int sliderWidth = 16;
    int textWidth = 100;
    
    // variables for calculating screen placement
    // (all based on ratios to allow resizing)
    int bandGap = h / 50; // space between band boxes
    // margins
    int topMargin = h / 10;
    int bottomMargin = h / 50;
    int leftMargin = h / 5;
    int rightMargin = h / 3.5;
    int centreWidth = w - (leftMargin + rightMargin); // width of plugin (minus margins)
    int centreHeight = h - (topMargin + bottomMargin + bandGap); // height of plugin (minus margins)
    int bandWidth = (centreWidth - (bandGap * 2)) / 3; // width of band boxes
    // band x positions
    int low_x_border = leftMargin;
    int mid_x_border = leftMargin + bandWidth + bandGap;
    int high_x_border = leftMargin + ((bandWidth + bandGap) * 2);
    int knobBorderXOffset = (bandWidth - (knobSize * scale)) / 2; // space between band border and knob
    // knob x positions
    int low_x = low_x_border + knobBorderXOffset;
    int mid_x = mid_x_border + knobBorderXOffset;
    int high_x = high_x_border + knobBorderXOffset;
    int knobAndTextHeight = centreHeight / 4.1; // height of knob and label together
    // knob y positions
    int predelay_y = topMargin + (bandGap * 1.5);
    int tankLength_y = predelay_y + knobAndTextHeight;
    int tankDecay_y = tankLength_y + knobAndTextHeight;
    int level_y = tankDecay_y + knobAndTextHeight;
    int paramLabelOffset = (knobSize * scale) + (h / 150); // how far below slider is label drawn
    

    // SLIDERS ===========================================================
    
    // PREDELAY
    low_predelaySlider.setSize(knobSize * scale, knobSize * scale);
    low_predelaySlider.setBounds(low_x,
                                 predelay_y,
                                 low_predelaySlider.getWidth(),
                                 low_predelaySlider.getHeight());
    
    mid_predelaySlider.setSize(knobSize * scale, knobSize * scale);
    mid_predelaySlider.setBounds(mid_x,
                                 predelay_y,
                                 mid_predelaySlider.getWidth(),
                                 mid_predelaySlider.getHeight());

    high_predelaySlider.setSize(knobSize * scale, knobSize * scale);
    high_predelaySlider.setBounds(high_x,
                                 predelay_y,
                                 high_predelaySlider.getWidth(),
                                 high_predelaySlider.getHeight());
    
    // TANK LENGTH
    low_tankLengthSlider.setSize(knobSize * scale, knobSize * scale);
    low_tankLengthSlider.setBounds(low_x,
                                   tankLength_y,
                                   low_tankLengthSlider.getWidth(),
                                   low_tankLengthSlider.getHeight());
    
    mid_tankLengthSlider.setSize(knobSize * scale, knobSize * scale);
    mid_tankLengthSlider.setBounds(mid_x,
                                   tankLength_y,
                                   mid_tankLengthSlider.getWidth(),
                                   mid_tankLengthSlider.getHeight());

    high_tankLengthSlider.setSize(knobSize * scale, knobSize * scale);
    high_tankLengthSlider.setBounds(high_x,
                                   tankLength_y,
                                   high_tankLengthSlider.getWidth(),
                                   high_tankLengthSlider.getHeight());
    
    // TANK DECAY
    low_tankDecaySlider.setSize(knobSize * scale, knobSize * scale);
    low_tankDecaySlider.setBounds(low_x,
                                 tankDecay_y,
                                  low_tankDecaySlider.getWidth(),
                                  low_tankDecaySlider.getHeight());
    
    mid_tankDecaySlider.setSize(knobSize * scale, knobSize * scale);
    mid_tankDecaySlider.setBounds(mid_x,
                                 tankDecay_y,
                                  mid_tankDecaySlider.getWidth(),
                                  mid_tankDecaySlider.getHeight());
    
    high_tankDecaySlider.setSize(knobSize * scale, knobSize * scale);
    high_tankDecaySlider.setBounds(high_x,
                                 tankDecay_y,
                                  high_tankDecaySlider.getWidth(),
                                  high_tankDecaySlider.getHeight());
    
    // LEVEL
    low_levelSlider.setSize(knobSize * scale, knobSize * scale);
    low_levelSlider.setBounds(low_x,
                              level_y,
                              low_levelSlider.getWidth(),
                              low_levelSlider.getHeight());
    
    mid_levelSlider.setSize(knobSize * scale, knobSize * scale);
    mid_levelSlider.setBounds(mid_x,
                              level_y,
                              mid_levelSlider.getWidth(),
                              mid_levelSlider.getHeight());
    
    high_levelSlider.setSize(knobSize * scale, knobSize * scale);
    high_levelSlider.setBounds(high_x,
                              level_y,
                              high_levelSlider.getWidth(),
                              high_levelSlider.getHeight());
    
    // OUTPUT SLIDER
    outSlider.setSize(sliderWidth * 3, sliderHeight * 3);
    outSlider.setBounds(w - ((rightMargin / 2) + (outSlider.getWidth() / 2)),
                        topMargin,
                        outSlider.getWidth(),
                        outSlider.getHeight());
    
    // LABELS ===================================================================
    
    // PREDELAY
    low_predelayLabel.setSize(textWidth, low_predelayLabel.getFont().getHeight());
    low_predelayLabel.setBounds(low_x - (knobSize / 2),
                                predelay_y + paramLabelOffset,
                                low_predelayLabel.getWidth(),
                                low_predelayLabel.getHeight());
    
    mid_predelayLabel.setSize(textWidth, mid_predelayLabel.getFont().getHeight());
    mid_predelayLabel.setBounds(mid_x - (knobSize / 2),
                                predelay_y + paramLabelOffset,
                                mid_predelayLabel.getWidth(),
                                mid_predelayLabel.getHeight());
    
    high_predelayLabel.setSize(textWidth, high_predelayLabel.getFont().getHeight());
    high_predelayLabel.setBounds(high_x - (knobSize / 2),
                                predelay_y + paramLabelOffset,
                                 high_predelayLabel.getWidth(),
                                 high_predelayLabel.getHeight());
    
    // TANK LENGTH
    low_tankLengthLabel.setSize(textWidth, low_tankLengthLabel.getFont().getHeight());
    low_tankLengthLabel.setBounds(low_x - (knobSize / 2),
                                tankLength_y + paramLabelOffset,
                                  low_tankLengthLabel.getWidth(),
                                  low_tankLengthLabel.getHeight());
    
    mid_tankLengthLabel.setSize(textWidth, mid_tankLengthLabel.getFont().getHeight());
    mid_tankLengthLabel.setBounds(mid_x - (knobSize / 2),
                                  tankLength_y + paramLabelOffset,
                                  mid_tankLengthLabel.getWidth(),
                                  mid_tankLengthLabel.getHeight());
    
    high_tankLengthLabel.setSize(textWidth, high_tankLengthLabel.getFont().getHeight());
    high_tankLengthLabel.setBounds(high_x - (knobSize / 2),
                                   tankLength_y + paramLabelOffset,
                                   high_tankLengthLabel.getWidth(),
                                   high_tankLengthLabel.getHeight());
    
    // TANK DECAY
    low_tankDecayLabel.setSize(textWidth, low_tankDecayLabel.getFont().getHeight());
    low_tankDecayLabel.setBounds(low_x - (knobSize / 2),
                                tankDecay_y + paramLabelOffset,
                                 low_tankDecayLabel.getWidth(),
                                 low_tankDecayLabel.getHeight());
    
    mid_tankDecayLabel.setSize(textWidth, mid_tankDecayLabel.getFont().getHeight());
    mid_tankDecayLabel.setBounds(mid_x - (knobSize / 2),
                                 tankDecay_y + paramLabelOffset,
                                 mid_tankDecayLabel.getWidth(),
                                 mid_tankDecayLabel.getHeight());
    
    high_tankDecayLabel.setSize(textWidth, high_tankDecayLabel.getFont().getHeight());
    high_tankDecayLabel.setBounds(high_x - (knobSize / 2),
                                  tankDecay_y + paramLabelOffset,
                                  high_tankDecayLabel.getWidth(),
                                  high_tankDecayLabel.getHeight());
    
    // LEVEL
    low_levelLabel.setSize(textWidth, low_levelLabel.getFont().getHeight());
    low_levelLabel.setBounds(low_x - (knobSize / 2),
                             level_y + paramLabelOffset,
                             low_levelLabel.getWidth(),
                             low_levelLabel.getHeight());
    
    mid_levelLabel.setSize(textWidth, mid_levelLabel.getFont().getHeight());
    mid_levelLabel.setBounds(mid_x - (knobSize / 2),
                             level_y + paramLabelOffset,
                             mid_levelLabel.getWidth(),
                             mid_levelLabel.getHeight());
    
    high_levelLabel.setSize(textWidth, high_levelLabel.getFont().getHeight());
    high_levelLabel.setBounds(high_x - (knobSize / 2),
                              level_y + paramLabelOffset,
                              high_levelLabel.getWidth(),
                              high_levelLabel.getHeight());
    
}
