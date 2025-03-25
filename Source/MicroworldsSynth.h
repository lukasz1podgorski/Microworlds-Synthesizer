#pragma once
#include <JuceHeader.h>

class MicroworldsSynth : public juce::SynthesiserSound
{
public:
	bool appliesToNote(int midiNoteNumber) override;
	bool appliesToChannel(int midiChannel) override;
};

