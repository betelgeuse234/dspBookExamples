#include "HelperFuncs.h"
#include <math.h>

// This subroutine creates the complex frequency domain from the real frequency domain.
// Upon entry to this subroutine, N% contains the number of points in the signals, and
// REX[ ] and IMX[ ] contain the real frequency domain in samples 0 to N%/2.
// On return, REX[ ] and IMX[ ] contain the complex frequency domain in samples 0 to N%-1.
void NegativeFreqGen(double* reX, double* imX, int n)
{
	for (int i = n / 2 + 1; i < n; i++)
	{
		reX[i] = reX[n - i];
		imX[i] = -imX[n - i];
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
		int c = static_cast<int>(phasexUnwrap[k - 1] - phasex[k] / 2 * pi);
		phasexUnwrap[k] = phasex[k] + static_cast<double>(c * 2.0 * pi);
	}
}
