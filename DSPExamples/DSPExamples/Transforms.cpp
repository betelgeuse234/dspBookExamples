#include "Transforms.h"
#include <math.h>


// needs to be tested
//L oop through each requency generating the entire length of the sine 
// and cosine waves, and add them to the accumulator signa
void InverseDFTOne(double* xx, double* rex, double* imx, int n)
{
	double pi = 3.14159265; // replace in the future
	// divide frequency domain by n/2 and invert the sign of the imaginary value
	for (int k = 0; k < n / 2; k++)
	{
		rex[k] = rex[k] / (n / 2);
		imx[k] = -imx[k] / (n / 2);
	}

	// deal with special cases for real values 
	rex[0] = rex[0] / 2;
	rex[n / 2] = rex[n / 2] / 2;

	// zero out time domain data
	for (int i = 0; i < n; i++)
	{
		xx[i] = 0;
	}

	for (int k = 0; k < n / 2; k++)
	{
		for (int i = 0; i < n; i++)
		{
			xx[i] = xx[i] + rex[k] * cos(2 * pi * k * i / n);
			xx[i] = xx[i] + imx[k] * sin(2 * pi * k * i / n);
		}
	}
}

// needs to be tested
// Loop through each sample in the time domain, 
// and sum the corresponding samples from each cosine and sine wave
void InverseDFTTwo(double* xx, double* rex, double* imx, int n)
{
	double pi = 3.14159265; // replace in the future
// divide frequency domain by n/2 and invert the sign of the imaginary value
	for (int k = 0; k < n / 2; k++)
	{
		rex[k] = rex[k] / (n / 2);
		imx[k] = -imx[k] / (n / 2);
	}

	// deal with special cases for real values 
	rex[0] = rex[0] / 2;
	rex[n / 2] = rex[n / 2] / 2;

	// zero out time domain data
	for (int i = 0; i < n; i++)
	{
		xx[i] = 0;
	}

	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n/2; k++)
		{
			xx[i] = xx[i] + rex[k] * cos(2 * pi * k * i / n);
			xx[i] = xx[i] + imx[k] * sin(2 * pi * k * i / n);
		}
	}
}

// needs to be tested
void DFTCorrelationInput(double* xx, double* rex, double* imx, int n)
{
	double pi = 3.14159265; // replace in the future

	// zero out frequency domain 
	for (int k = 0; k < n / 2; k++)
	{
		rex[k] = 0;
		imx[k] = 0;
	}

	for (int k = 0; k < n / 2; k++)
	{
		for (int i = 0; i < n; i++)
		{
			rex[k] = rex[k] + xx[i] * cos(2 * pi * k * i / n);
			imx[k] = imx[k] + xx[i] * sin(2 * pi * k * i / n);
		}
	}
}

// needs to be tested
void DFTCorrelationOut(double* xx, double* rex, double* imx, int n)
{
	double pi = 3.14159265; // replace in the future

	// zero out frequency domain 
	for (int k = 0; k < n / 2; k++)
	{
		rex[k] = 0;
		imx[k] = 0;
	}

	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n / 2; k++)
		{
			rex[k] = rex[k] + xx[i] * cos(2 * pi * k * i / n);
			imx[k] = imx[k] + xx[i] * sin(2 * pi * k * i / n);
		}
	}
}

// needs to be tested
void RectToPolar(double* rex, double* imx, double* magx, double* phasex, int n)
{
	double pi = 3.14159265; // replace in the future

	for (int k = 0; k < n; k++)
	{
		magx[k] = sqrt(pow(rex[k], 2) + pow(imx[k], 2));

		if (rex[k] == 0)
		{
			rex[k] = 0.000000000000000001; // prevent divide by 0
		}

		phasex[k] = atan(imx[k] / rex[k]);

		// correct for arctan 
		if (rex[k] < 0 && imx[k] < 0)
		{
			phasex[k] = phasex[k] - pi;
		}

		if (rex[k] < 0 && imx[k] >= 0)
		{
			phasex[k] = phasex[k] + pi;
		}
	}
}

// needs to be tested
void PolarToRect(double* rex, double* imx, double* magx, double* phasex, int n)
{
	double pi = 3.14159265; // replace in the future

	for (int k = 0; k < n; k++)
	{
		rex[k] = magx[k] * cos(phasex[k]);
		imx[k] = magx[k] * sin(phasex[k]);
	}
}

// needs to be tested I'm uncertain about the some potential casting issues when generating the c value
void PhaseUnwrap(double* phasex, double* phasexUnwrap, int n)
{
	double pi = 3.14159265; // replace in the future
	for (int k = 0; k < n; k++)
	{
		int c = static_cast<int>(phasexUnwrap[k - 1] - phasex[k]) / 2 * pi;
		phasexUnwrap[k] = phasex[k] + static_cast<double>(c) * 2.0 * pi;
	}
}