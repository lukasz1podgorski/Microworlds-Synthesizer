#pragma once
#include <JuceHeader.h>
#include "MicroworldsSynth.h"


class MicroworldsVoice : public juce::SynthesiserVoice
{
public:
	bool canPlaySound(juce::SynthesiserSound* sound) override;
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound,
		int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
	void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
	void updateADSR(const float attack, const float decay, const float sustain, const float release);

private:
	juce::ADSR adsr;
	juce::ADSR::Parameters adsrParameters;
	juce::AudioBuffer<float> synthBuffer;

	juce::dsp::Oscillator<float> osc{ [](float x) { return std::sin(x); } };
	juce::dsp::Gain<float> gain;
	bool isPrepared = false;

	// saw: return x / juce::MathConstants<float>::pi;
	// square: x < 0.0f ? -1.0f : 1.0f;

};

