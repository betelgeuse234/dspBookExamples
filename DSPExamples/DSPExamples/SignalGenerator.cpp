#define _USE_MATH_DEFINES
#include <cmath>
#include "SignalGenerator.h"

std::vector<double> SignalGenerator::SquareWave(double frequency, double dutyCycle, double amplitude, double offset)
{   
    
    double sampleRate = 1000000;    // We are going to assume a sample rate of 1MHz
    double sampleLen = 1;           //1s of samples
    double numSamples = sampleRate * sampleLen;
    double period = 1 / frequency;
    double samplesHigh = sampleRate * period * dutyCycle;
    double samplesLow = sampleRate * period * (1 - dutyCycle);
    double highVal = amplitude / 2 + offset;
    double lowVal = -1 * (amplitude / 2) + offset;

    std::vector<double> data;

    while (data.size() < numSamples)
    {
        for (int high = 0; high < samplesHigh && data.size() <= numSamples; high++)
        {
            data.push_back(highVal);
        }

        for (int low = 0; low < samplesLow && data.size() <= numSamples; low++)
        {
            data.push_back(lowVal);
        }
    }

	return data;
}

std::vector<double> SignalGenerator::TriangeWave(double frequency, double amplitude, double offset)
{
    std::vector<double> data;
    return data;
}

std::vector<double> SignalGenerator::Sine(double frequency, double amplitude, double offset)
{
    double sampleRate = 1000000; // We are going to assume a sample rate of 1MHz
    double period = 1 / frequency;
    double sampleLen = 1;           //1s of samples
    double numSamples = sampleRate * sampleLen;
    double samplesPerPeriod = sampleRate * period;
    double angle = 0.0; 
    std::vector<double> data;

    for (int i = 0; i < numSamples; i++)
    {
        double pointY = amplitude / 2 * sin(angle) + offset;
        data.push_back(pointY);
        angle += (2 * M_PI) / samplesPerPeriod;
    }
    return data;
}

std::vector<double> SignalGenerator::RandomNoise(double maxAmplitude, double offset)
{
    std::vector<double> data;
    return data;
}

std::vector<double> SignalGenerator::AM(double carrierFreq, double carrierAmp, double carrierOffset, double signalFreq, double signalAmp)
{
    std::vector<double> data;
    return data;
}