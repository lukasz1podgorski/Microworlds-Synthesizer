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

	if (!allowTailOff || !adsr.isActive())
	{
		clearCurrentNote();
	}
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

	adsrParameters.attack = 0.5f;
	adsrParameters.decay = 0.1f;
	adsrParameters.sustain = 0.8f;
	adsrParameters.release = 0.5f;

	adsr.setParameters(adsrParameters);
	
	isPrepared = true;
}

void MicroworldsVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	jassert(isPrepared);

	if (!isVoiceActive())
		return;

	synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
	synthBuffer.clear();

	juce::dsp::AudioBlock<float> audioBlock {synthBuffer};
	osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
	gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

	adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

	for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
	{
		outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

		if (!adsr.isActive())
		{
			clearCurrentNote();
		}
	}
}
