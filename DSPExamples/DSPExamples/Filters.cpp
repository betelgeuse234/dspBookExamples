#include "Filters.h"
#include <math.h>


// MOVING AVERAGE FILTER
// This program filters 5000 samples with a 101 point moving
// average filter, resulting in 4900 samples of filtered data.
void Filters::MovingAverage(double* input, double* output, int avgWidth, int len)
{
	for (int i = (avgWidth-1)/2; i < len - (avgWidth-1)/2; i++)
	{
		output[i] = 0;
		for (int j = -(avgWidth-1)/2; j < (avgWidth-1)/2; j++) // centered average not one sided avaerage this only works if avgWidth is and odd number
		{
			output[i] = output[i] + input[i + j];
		}
		output[i] /= avgWidth;
	}
}

// MOVING AVERAGE FILTER IMPLEMENTED BY RECURSION
// This program filters 5000 samples with a 101 point moving
// average filter, resulting in 4900 samples of filtered data.
// A double precision accumulator is used to prevent round-off drift.
void Filters::RecursiveMovingAverage(double* input, double* output, int avgWidth, int len)
{
	double acc = 0.0;

	// first we need to create a sum for the first index of the output
	for (int i = 0; i < avgWidth; i++)
	{
		acc = acc + input[i];
	}

	// I probably need to fiddle with how we are doing this whole index thing so like if avgwidth is 101 then this index would be 50 here however where we need it to be 51 per the book example it is still just 50
	output[(avgWidth - 1) / 2] = acc / avgWidth; // This is supposed to be the first value in the output.

	for (int i = (avgWidth + 1) / 2; i < len - (avgWidth + 1) / 2; i++)
	{
		acc = acc + input[i + (avgWidth - 1) / 2] - input[i - (avgWidth - 1) / 2];
		output[i] = acc / avgWidth;
	}
}

void Filters::LowPassWindowedSinc(double* input, double* output, int dataLen, double* kernal, int kernalLen)
{
	const double FC = 0.14;
	const int M = 100;
	const double PI = 3.14159265;

	// Generate LPF kernal
	for (int i = 0; i < 100; i++)
	{
		if (i - M / 2 == 0)
		{
			kernal[i] = 2 * PI * FC;
		}

		if (i - M / 2 != 0)
		{
			kernal[i] = sin(2 * PI * FC * (i - M / 2)) / (i - M / 2);
		}

		kernal[i] = kernal[i] * (0.54 - 0.46 * cos(2 * PI * i / M));
	}

	// Normalize the LPF kernal for unity gain at DC
	int sum = 0;

	for (int i = 0; i < 100; i++)
	{
		sum = sum + kernal[i];
	}

	for (int i = 0; i < 100; i++)
	{
		kernal[i] = kernal[i] / sum;
	}

	// convolve the input signal and filter kernel
	for (int j = 100; j < 4999; j++)
	{
		output[j] = 0;

		for (int i = 0; i < 100; i++)
		{
			output[j] = output[j] + input[j - i] * kernal[i];
		}
	}
}
