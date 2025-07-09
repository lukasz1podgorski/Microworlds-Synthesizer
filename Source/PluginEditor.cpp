#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    //juce::ignoreUnused (processorRef);

    setSize (400, 300);

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    attackAttachment = std::make_unique<SliderAttachment>(processorRef.vts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(processorRef.vts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(processorRef.vts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(processorRef.vts, "RELEASE", releaseSlider);

    oscSelectAttachment = std::make_unique<ComboBoxAttachment>(processorRef.vts, "OSC1", oscSelect);

    setSliderParameters(attackSlider);
    setSliderParameters(decaySlider);
    setSliderParameters(sustainSlider);
    setSliderParameters(releaseSlider);

}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);

    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10; // distance between sliders
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() / 2 - padding;
    const auto sliderStartX = 0;
    const auto sliderStartY = bounds.getHeight() / 2 - (sliderHeight / 2);

    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

}

void AudioPluginAudioProcessorEditor::setSliderParameters(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}