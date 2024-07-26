#include "Filters.h"


// MOVING AVERAGE FILTER
// This program filters 5000 samples with a 101 point moving
// average filter, resulting in 4900 samples of filtered data.
void MovingAverage(double* input, double* output, int avgWidth, int len)
{
	for (int i = (avgWidth-1)/2; i < len - (avgWidth-1)/2; i++)
	{
		output[i] = 0;
		for (int j = -(avgWidth-1)/2; j < (avgWidth-1)/2; j++)
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
void RecursiveMovingAverage(double* input, double* output, int avgWidth, int len)
{
	double acc = 0.0;

	for (int i = 0; i < avgWidth; i++)
	{
		acc = acc + input[i];
	}

	// I probably need to fiddle with how we are doing this whole index thing so like if avgwidth is 101 then this index would be 50 here however where we need it to be 51 per the book example it is still just 50
	output[(avgWidth - 1) / 2] = acc / avgWidth;

	for (int i = (avgWidth - 1) / 2; i < len - (avgWidth - 1) / 2; i++)
	{
		acc = acc + input[i + (avgWidth - 1) / 2] - input[i - (avgWidth - 1) / 2];
		output[i] = acc / avgWidth;
	}
}
