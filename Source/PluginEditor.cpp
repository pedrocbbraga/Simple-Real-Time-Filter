/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RAMTeCHSimpleDigitalFilterAudioProcessorEditor::RAMTeCHSimpleDigitalFilterAudioProcessorEditor (RAMTeCHSimpleDigitalFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    /* ----------- DIST SLIDER A ----------- */
    lowpassSlider.setSliderStyle (juce::Slider::LinearHorizontal);
    lowpassSlider.setRange (0.0, 24000.0, 1.0);
    lowpassSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::whitesmoke);
    lowpassSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    lowpassSlider.setPopupDisplayEnabled (true, false, this);
    lowpassSlider.setTextValueSuffix (" Cutoff");
    lowpassSlider.addListener(this);
    lowpassSlider.setBounds (100, 100, 200, 200);
    addAndMakeVisible (&lowpassSlider);
}

RAMTeCHSimpleDigitalFilterAudioProcessorEditor::~RAMTeCHSimpleDigitalFilterAudioProcessorEditor()
{
}

//==============================================================================
void RAMTeCHSimpleDigitalFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Simple Digital Lowpass Filter", getLocalBounds(), juce::Justification::centred, 1);
}

void RAMTeCHSimpleDigitalFilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void RAMTeCHSimpleDigitalFilterAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &lowpassSlider)
    {
        audioProcessor.cutoffFreq = lowpassSlider.getValue();
        
        audioProcessor.a = audioProcessor.cutoffFreq / (audioProcessor.cutoffFreq + audioProcessor.sampleRate);
    }
}
