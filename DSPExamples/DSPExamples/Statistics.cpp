#include "Statistics.h"
#include <cmath>

double Statistics::sum(double* data, unsigned int length)
{
	double sum = 0;

	for (unsigned int i = 0; i < length; i++)
	{
		sum += data[i];
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

double Statistics::running_man(double* data, unsigned int length)
{
	return 0.0;
}

double Statistics::running_std_dev(double* data, unsigned int length)
{
	return 0.0;
}
