#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 60);
    addAndMakeVisible(attackSlider);

    setSize (400, 300);

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    attackAttachment = std::make_unique<SliderAttachment>(processorRef.vts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(processorRef.vts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(processorRef.vts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(processorRef.vts, "RELEASE", releaseSlider);

    oscSelectAttachment = std::make_unique<ComboBoxAttachment>(processorRef.vts, "OSC1", oscSelect);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    
}
