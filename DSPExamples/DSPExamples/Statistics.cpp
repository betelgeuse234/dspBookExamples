#include "Statistics.h"
#include <cmath>
#include <vector>

double Statistics::sum(double* data, unsigned int length)
{
	double sum = 0;

	for (unsigned int i = 0; i < length; i++)
	{
		sum += data[i];
	}

	return sum;
}

double Statistics::sumOfSquares(double* data, unsigned int length)
{
	double sum = 0;

	for (unsigned int i = 0; i < length; i++)
	{
		sum += data[i] * data[i];
	}

	return sum;
}

double Statistics::mean(double* data, unsigned int length)
{
	double mean = sum(data, length) / length;
	return mean;
}

double Statistics::variance(double* data, unsigned int length)
{
	double mu = mean(data, length);
	double variance = 0;
	for (unsigned int i = 0; i < length; i++)
	{
		double tmpNum = data[i] - mu;
		variance += tmpNum * tmpNum;
	}
	variance /= length - 1;
	return variance;
}

double Statistics::std_dev(double* data, unsigned int length)
{
	double std_dev = sqrt(variance(data, length));
	return std_dev;
}

double Statistics::running_mean(double* data, unsigned int length)
{
	double sum = 0;
	double sumOfSquares = 0;
	unsigned int n = 0;
	double mean = 0;

	for (n; n < length; n++)
	{
		sum += data[n];
		mean = sum / n;
	}

	return mean;
}

double Statistics::running_std_dev(double* data, unsigned int length)
{
	double sum = 0;
	double sumOfSquares = 0;
	unsigned int n = 0;
	double std_dev = 0;

	for (n; n < length; n++)
	{
		sum += data[n];
		sumOfSquares += data[n] * data[n];
		if (n == 1)
		{
			std_dev = 0;
		}
		else
		{
			std_dev = sqrt(((sumOfSquares - pow(sum, 2)) / n) / n - 1);
		}
	}

	return std_dev;
}

void Statistics::histogram(unsigned int* data, unsigned int dataLength, unsigned int* histData)
{
	for (unsigned int i = 0; i < dataLength; i++)
	{
		histData[data[i]] += 1;
	}
}

double Statistics::histMean(unsigned int* histData, unsigned int histLength)
{
	double mean = 0;
	for (unsigned int i = 0; i < histLength; i++)
	{
		mean += static_cast<double>(i * histData[i]);
	}
	
	mean = mean / histLength;
	return mean;
}

double Statistics::histStdDev(unsigned int* histData, unsigned int histLength, double mean)
{
	double variance = 0;
	double stdDev = 0;
	for (unsigned int i = 0; i < histLength; i++)
	{
		variance += histData[i] * pow(2,(i - mean));
	}
	variance /= (histLength - 1);
	stdDev = sqrt(variance);
	return stdDev;
}

void Statistics::binnedHistogram(double* data, unsigned int dataLength, unsigned int* histData, unsigned int numBins)
{
	for (unsigned int i = 0; i < dataLength; i++)
	{
		unsigned int binNum = static_cast<unsigned int>(data[i] * numBins); // I believe this needs to be changed. I don't think it will give us the bins we want. We probably want some scale information
		histData[binNum] += 1;
	}
}