#include "MicroworldsVoice.h"

bool MicroworldsVoice::canPlaySound(juce::SynthesiserSound* sound)
{
	return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void MicroworldsVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound,
	int currentPitchWheelPosition)
{

}

void MicroworldsVoice::stopNote(float velocity, bool allowTailOff)
{

}

void MicroworldsVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void MicroworldsVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void MicroworldsVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{

}
