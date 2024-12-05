#include "Filters.h"
#include "Transforms.h"
#include <math.h>
#include <cstring>


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


// Converts an aliased len point impulse response into an M+1 point filter kernal
// Generalized version of Table 17-1 from The Scientist and Engineer's Guide to Digital Signal Processing
void Filters::CustomFilterDesign(double* impulse, double* filter, int len, int M)
{
	// perform additional validation of M 
	if (M < len)
	{
		double PI = 3.14159265;	// at some time replace this with a value that is used eveywhere

		int index = 0;

		// Shift (rotate) the signal M/2 points to the right
		for (int i = 0; i < len; i++)
		{
			index = i + M / 2;
			if (index > len)
			{
				index = index - (len + 1); // is this the aliasing part?
			}

			filter[index] = impulse[i];
		}

		// Truncate and window the signal
		for (int i = 0;i < len; i++)
		{
			if (i > M) // truncate
			{
				filter[i] = 0;
			}
			else if (i <= M) // window
			{
				filter[i] = filter[i] * (0.54 - 0.46 * cos(2 * PI * i / M));
			}
		}
	}

}

// Need to validate this still
void Filters::FFTConvolution(double* input, int inLen, double* output, double* kernel, int kernelLen, int fftLen)
{
	int sigChunkLen = (fftLen - kernelLen) + 1;
	int olapLen = fftLen - sigChunkLen;
	double* xx = new double[fftLen - 1];
	double* rex = new double[fftLen / 2];
	double* imx = new double[fftLen / 2];
	double* refr = new double[fftLen / 2];
	double* imfr = new double[fftLen / 2];
	double* olap = new double[olapLen];

	// zero array holding overlap samples
	for (int i = 0; i < olapLen; i++)
	{
		olap[i] = 0;
	}

	// load filter kernel into x
	for (int i = 0; i < fftLen - 1; i++)
	{
		if (i > kernelLen)
		{
			xx[i] = 0.0;
		}
		else
		{
			xx[i] = kernel[i];
		}
	}

	// FFT filter kernel into rex[] and imx[]
	Transforms::RealFFT(xx, imx, fftLen - 1);
	
	// Save frequency response in REFR[] and IMFR[]
	for (int i = 0; i < fftLen / 2; i++)
	{
		rex[i] = xx[i];
		refr[i] = rex[i];
		imfr[i] = imx[i];
	}

	for (int i = 0; i < inLen/fftLen; i++)
	{
		// Mythical subroutine to load the next input segment into  xx
		for (int j = 0; j < fftLen - 1; j++)
		{
			xx[i] = input[i + j];
		}

		// Mythical FFT subroutine xx -> rex & imx
		Transforms::RealFFT(xx, imx, fftLen - 1); // might not need to subtract 1 for len here

		// Save frequency response in REFR[] and IMFR[]
		for (int j = 0; j < fftLen / 2; j++)
		{
			double temp = xx[j] * refr[j] - imx[j] * imfr[j];
			imx[j] = xx[j] * imfr[j] + imx[j] * refr[j];
			xx[j] = temp;
		}

		// Mythical IFFT subroutine
		Transforms::InverseFFT(xx, imx, fftLen - 1); // might not need to subtract 1 for len here

		// add the last segment's overlap to this segment
		for (int j = 0; j < olapLen; j++)
		{
			xx[j] = xx[j] + olap[j];
		}

		// save the samples that will overlap the next segment
		for (int j = fftLen - olapLen; j < fftLen; j++)
		{
			olap[j - (fftLen - olapLen)] = xx[j];
		}

		// Mythical subroutine to output the 625 samples stored in xx[0] - xx[624]
		std::memcpy(&output[i*fftLen], &xx[0], sizeof(double)* (fftLen - olapLen));
	}
	// Mythical subroutin to output all 399 samples in OLAP
	std::memcpy(&output[inLen-1], &olap[0], sizeof(double) * olapLen);
}
