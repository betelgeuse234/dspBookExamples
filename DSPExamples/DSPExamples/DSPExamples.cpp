// DSPExamples.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Statistics.h"
#include "SignalGenerator.h"
#include "Convolution.h"
#include "Filters.h"
#include "ipp.h"
#include "IQSource.h"
#include "Transforms.h"

void ippsFFT(Ipp64f* src, Ipp64f* dst, int fftSize)
{
    ippInit(); // Initialize Ipps to use optimal libs for our hardware
    //Set the size
    //const int N = 128;
    const int order = (int)(log((double)fftSize) / log(2.0));

    // Spec and working buffers
    IppsFFTSpec_R_64f* pFFTSpec = 0;
    Ipp8u* pFFTSpecBuf, * pFFTInitBuf, * pFFTWorkBuf;


    // Query to get buffer sizes
    int sizeFFTSpec, sizeFFTInitBuf, sizeFFTWorkBuf;
    ippsFFTGetSize_R_64f(order, IPP_FFT_NODIV_BY_ANY,
        ippAlgHintAccurate, &sizeFFTSpec, &sizeFFTInitBuf, &sizeFFTWorkBuf);

    // Alloc FFT buffers
    pFFTSpecBuf = ippsMalloc_8u(sizeFFTSpec);
    pFFTInitBuf = ippsMalloc_8u(sizeFFTInitBuf);
    pFFTWorkBuf = ippsMalloc_8u(sizeFFTWorkBuf);

    // Initialize FFT
    ippsFFTInit_R_64f(&pFFTSpec, order, IPP_FFT_NODIV_BY_ANY,
        ippAlgHintAccurate, pFFTSpecBuf, pFFTInitBuf);
    if (pFFTInitBuf) ippFree(pFFTInitBuf);

    ippsFFTFwd_RToPerm_64f(src, dst, pFFTSpec, pFFTWorkBuf);
}

int main()
{
    //IQSource datasource;
    //std::vector<Complex> iqData;
    //iqData.resize(4096);
    //datasource.GetIQData(&iqData[0], 4096);
    
    uint32_t sampleRate = 1000000; // 1MSPS
    SignalGenerator sigGen(sampleRate);
    std::vector<double> squareWave = sigGen.SquareWave(1000, .5, 20.0, 0);
    double mean = Statistics::mean(&squareWave[0], static_cast<unsigned int>(squareWave.size()));
    double std_dv = Statistics::std_dev(&squareWave[0], static_cast<unsigned int>(squareWave.size()));

    double pulseFreq = 100.0e3;
    double timePerSample = 1.0 / (double)sampleRate;
    double numSamples = 2048;
    double time = numSamples * timePerSample;
    std::vector<double> pulse = sigGen.Pulse(pulseFreq, 1.0, 80.0e-6, 40.0e-6, time, 0);

    std::ofstream pulse_file("./pulse.csv");
    for (int i = 0; i < pulse.size(); i++)
    {
        pulse_file << pulse[i] << "\n";
    }
    pulse_file.close();

    std::cout << "Square Wave\n" << "Mean = " << mean << "\n" << "Standard Deviation = " << std_dv << "\n";

    std::vector<double> sineWave = sigGen.Sine(1000, 20.0, 0, 1);
    double meanSine = Statistics::mean(&sineWave[0], static_cast<unsigned int>(sineWave.size()));
    double stdDevSine = Statistics::std_dev(&sineWave[0], static_cast<unsigned int>(sineWave.size()));
    std::ofstream output_file("./example.txt");
    std::ostream_iterator<double> output_iterator(output_file, "\n");
    std::copy(sineWave.begin(), sineWave.end(), output_iterator);

    std::vector<double> x = { 0, -1, -1.25, 2, 1.5, 1.5, .75, 0, -.75 };
    std::vector<double> h = { 1, -0.5, -.25, -.1 };
    std::vector<double> y(static_cast<int>(x.size() + h.size() - 1), 0);
    std::vector<double> y2(static_cast<int>(x.size() + h.size() - 1), 0);

    Convolution::InputSideAlgorithm(&x[0], &h[0], &y[0], static_cast<int>(x.size()), static_cast<int>(h.size()));
    Convolution::OutputSideAlgorithm(&x[0], &h[0], &y2[0], static_cast<int>(x.size()), static_cast<int>(h.size()));

    std::cout << "Sine Wave\n" << "Mean = " << meanSine << "\n" << "Standard Deviation = " << stdDevSine << "\n";


    std::vector<double> sine1 = sigGen.Sine(100e3, 1.0, 0, 1);
    std::vector<double> sine2 = sigGen.Sine(200e3, 1.0, 0, 1);
    std::vector<double> sine3 = sigGen.Sine(400e3, 1.0, 0, 1);
    std::vector<double> noise = sigGen.RandomNoise(0.01, 0);

    std::vector<double> summedWave;
    std::vector<double> outputWave;
    std::vector<double> outputFFT;

    for (int i = 0; i < sine1.size(); i++)
    {
        double tempVal = sine1[i] + sine2[i] + sine3[i] + noise[i];
        summedWave.push_back(tempVal);
    }

    outputWave.resize(summedWave.size());

    int avgWidth = 41;
    Filters::MovingAverage(&summedWave[0], &outputWave[0], avgWidth, static_cast<int>(summedWave.size()));

    // Print out filtering results
    std::ofstream filter_file("./filterResults.csv");
    for (int i = 0; i < 10240; i++)
    {
        filter_file << sine1[i] << "," << sine2[i] << "," << sine3[i] << "," << noise[i] << "," << summedWave[i] << "," << outputWave[i] << "\n";
    }
    filter_file.close();


    // This does not work I'm not sure why
    int fftSize = 2048;
    Ipp64f* ippsSrc = static_cast<Ipp64f*>(&sine1[0]);
    Ipp64f* ippsDst = ippsMalloc_64f(fftSize);    // Allocate complex buffers
    Ipp64f* magnitude = ippsMalloc_64f(fftSize/2);    // Allocate complex buffers
    ippsFFT(ippsSrc, ippsDst, fftSize);  
    // print out FFT results
    
    std::ofstream fft_file("./fftResults.csv");
    for (int i = 0; i < fftSize; i+=2)
    {
        magnitude[i / 2] = sqrt(pow(ippsDst[i], 2) + pow(ippsDst[i + 1], 2));
        fft_file << magnitude[i / 2] << "\n";
    }
    fft_file.close();

    int fftLen = 2048;
    std::vector<double> rex(fftLen/2, 0.0);
    std::vector<double> imx(fftLen/2, 0.0);
    std::vector<double> mag(fftLen / 2, 0.0);
    Transforms::RealFFT(sine2.data(), imx.data(), fftLen/2);

    std::ofstream pulse_fft_file("pulse_fft.csv");
    for (int i = 0; i < fftLen/2; i+=2)
    {
        mag[i] = sqrt(pow(sine2[i], 2) + pow(imx[i], 2));
        pulse_fft_file << mag[i] << "\n";
    }
    pulse_fft_file.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
