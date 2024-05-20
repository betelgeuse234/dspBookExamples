#pragma once
#include <vector>
class SignalGenerator
{
public:
	static std::vector<double> SquareWave(double frequency, double dutyCycle, double amplitude, double offset);
	static std::vector<double> TriangeWave(double frequency, double amplitude, double offset);
	static std::vector<double> Sine(double frequency, double amplitude, double offset);
	static std::vector<double> RandomNoise(double maxAmplitude, double offset);
	static std::vector<double> AM(double carrierFreq, double carrierAmp, double carrierOffset, double signalFreq, double signalAmp);

};