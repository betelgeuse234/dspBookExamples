#pragma once

class Statistics {       // The class
public:             // Access specifier
	static double sum(double* data, unsigned int length);
	static double sumOfSquares(double* data, unsigned int length);
	static double mean(double* data, unsigned int length);
	static double variance(double* data, unsigned int length);
	static double std_dev(double* data, unsigned int length);
	static double running_mean(double* data, unsigned int length);
	static double running_std_dev(double* data, unsigned int length);
	static void histogram(unsigned int* data, unsigned int dataLength, unsigned int* histData);
	static double histMean(unsigned int* histData, unsigned int histLength);
	static double histStdDev(unsigned int* histData, unsigned int histLength, double mean);
	static void binnedHistogram(double* data, unsigned int dataLength, unsigned int* histData, unsigned int numBins);
};
