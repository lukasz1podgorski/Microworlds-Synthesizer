#include "MicroworldsVoice.h"

bool MicroworldsVoice::canPlaySound(juce::SynthesiserSound* sound)
{
	return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void MicroworldsVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound,
	int currentPitchWheelPosition)
{
	osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
	adsr.noteOn();
}

void MicroworldsVoice::stopNote(float velocity, bool allowTailOff)
{
	adsr.noteOff();
}

void MicroworldsVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void MicroworldsVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void MicroworldsVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
	adsr.setSampleRate(sampleRate);

	juce::dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock;
	spec.sampleRate = sampleRate;
	spec.numChannels = outputChannels;

	osc.prepare(spec);
	gain.prepare(spec);

	gain.setGainLinear(0.01f);
	
	isPrepared = true;
}

void MicroworldsVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	jassert(isPrepared);

	juce::dsp::AudioBlock<float> audioBlock {outputBuffer};
	osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
	gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

	adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}
