#pragma once
#include <vector>
class SignalGenerator
{
public:
	SignalGenerator(uint32_t pSampleRate) { sampleRate = pSampleRate; }
	std::vector<double> SquareWave(double frequency, double dutyCycle, double amplitude, double offset);
	std::vector<double> TriangeWave(double frequency, double amplitude, double offset);
	std::vector<double> Sine(double frequency, double amplitude, double offset, double time);
	std::vector<double> RandomNoise(double maxAmplitude, double offset);
	std::vector<double> AM(double carrierFreq, double carrierAmp, double carrierOffset, double signalFreq, double signalAmp);
	std::vector<double> Pulse(double frequency, double amplitude, double tOn, double tOff, double time, double offset);
private:
	uint32_t sampleRate;
};