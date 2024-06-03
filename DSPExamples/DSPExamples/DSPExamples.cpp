// DSPExamples.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Statistics.h"
#include "SignalGenerator.h"
#include "Convolution.h"

int main()
{
    std::vector<double> squareWave = SignalGenerator::SquareWave(1000, .5, 20.0, 0);
    double mean = Statistics::mean(&squareWave[0], static_cast<unsigned int>(squareWave.size()));
    double std_dv = Statistics::std_dev(&squareWave[0], static_cast<unsigned int>(squareWave.size()));

    std::cout << "Square Wave\n" << "Mean = " << mean << "\n" << "Standard Deviation = " << std_dv << "\n";

    std::vector<double> sineWave = SignalGenerator::Sine(1000, 20.0, 0);
    double meanSine = Statistics::mean(&sineWave[0], static_cast<unsigned int>(sineWave.size()));
    double stdDevSine = Statistics::std_dev(&sineWave[0], static_cast<unsigned int>(sineWave.size()));
    std::ofstream output_file("./example.txt");
    std::ostream_iterator<double> output_iterator(output_file, "\n");
    std::copy(sineWave.begin(), sineWave.end(), output_iterator);

    std::vector<double> x = { 0, -1, -1.25, 2, 1.5, 1.5, .75, 0, -.75 };
    std::vector<double> h = { 1, -0.5, -.25, -.1 };
    std::vector<double> y(x.size() + h.size() - 1, 0);
    std::vector<double> y2(x.size() + h.size() - 1, 0);

    Convolution::InputSideAlgorithm(&x[0], &h[0], &y[0], x.size(), h.size());
    Convolution::OutputSideAlgorithm(&x[0], &h[0], &y2[0], x.size(), h.size()); 

    std::cout << "Sine Wave\n" << "Mean = " << meanSine << "\n" << "Standard Deviation = " << stdDevSine << "\n";
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
