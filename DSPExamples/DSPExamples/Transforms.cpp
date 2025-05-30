#include "Transforms.h"
#include <math.h>


// needs to be tested
//L oop through each requency generating the entire length of the sine 
// and cosine waves, and add them to the accumulator signa
void Transforms::InverseDFTOne(double* xx, double* rex, double* imx, int n)
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
void Transforms::InverseDFTTwo(double* xx, double* rex, double* imx, int n)
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
void Transforms::DFTCorrelationInput(double* xx, double* rex, double* imx, int n)
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
void Transforms::DFTCorrelationOutput(double* xx, double* rex, double* imx, int n)
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



// COMPLEX DFT BY CORRELATION
// Upon entry, N% contains the number of points in the DFT, and
// XR[ ] and XI[ ] contain the real and imaginary parts of the time domain.
// Upon return, REX[ ] and IMX[ ] contain the frequency domain data.
// All signals run from 0 to N%-1.
void Transforms::CplxDFTByCorr(double* xR, double* xI, double* reX, double* imX, int n)
{
	double pi = 3.14159265; // should be using value for pi from library or some common area
	// Zero rex and imx so they can be used as accumulators during correlation
	for (int i = 0; i < n; i++)
	{
		reX[i] = 0;
		imX[i] = 0;
	}

	double sR = 0;
	double sI = 0;
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			sR = cos(2 * pi * k * i / n);
			sI = -sin(2 * pi * k * i / n);
			reX[k] = reX[k] + xR[i] * sR - xI[i] * sI;
			imX[k] = imX[k] + xR[i] * sI + xI[i] * sR;
		}
	}
}



// I need to double checkc everything here to make sure I implemented things with that goto correctly
// THE FAST FOURIER TRANSFORM
// Upon entry, N% contains the number of points in the DFT, REX[ ] and
// IMX[ ] contain the real and imaginary parts of the input. Upon return,
// REX[ ] and IMX[ ] contain the DFT output. All signals run from 0 to N%-1.
void Transforms::FFT(double* reX, double* imX, int n)
{
	double pi = 3.14159265;
	int nm1 = n - 1;
	int nd2 = n / 2; // this probably needs to be a double due to integer devision
	int m = static_cast<int>(log(n) / log(2));
	int j = nd2;


	// Bit reversal sorting
	for (int i = 1; i < n - 2; i++)
	{
		if (i >= j)
		{

		}
		else
		{
			double tr = reX[j];
			double ti = imX[j];
			reX[j] = reX[i];
			imX[j] = imX[i];
			reX[i] = tr;
			imX[i] = ti;
		}

		int k = nd2;

		if (k < j) {
			while (k < j)
			{
				j = j - k;
				k = k / 2;
			}
		}

		j = j + k;
	}

	// Loop for each stage
	for (int l = 1; l < m; l++)
	{
		int le = static_cast<int>(pow(2, l));
		int le2 = le / 2;
		int ur = 1;
		int ui = 0;

		double sr = cos(pi / le2);
		double si = -sin(pi / le2);
		// Loop for each sub DFT
		for (int j = 1; j < le; j++)
		{
			int jm1 = j - 1;

			// Loop for each butterfly
			double tr = 0;
			double ti = 0;
			for (int i = jm1; i < nm1; i += le)
			{
				int ip = i + le2;
				tr = reX[ip] * ur - imX[ip] * ui;
				ti = reX[ip] * ui - imX[ip] * ur;
				reX[ip] = reX[i] - tr;
				imX[ip] = imX[i] - ti;
				reX[i] = reX[i] + tr;
				imX[i] = imX[i] + ti;
			}
			tr = ur;
			ur = tr * sr - ui * si;
			ui = tr * si + ui * sr;
		}
	}
}

// INVERSE FAST FOURIER TRANSFORM SUBROUTINE
// Upon entry, N% contains the number of points in the IDFT, REX[ ] and
// IMX[ ] contain the real and imaginary parts of the complex frequency domain.
// Upon return, REX[ ] and IMX[ ] contain the complex time domain.
// All signals run from 0 to N%-1
void Transforms::InverseFFT(double* reX, double* imX, int n)
{
	// Change sign of 
	for (int k = 0; k < n - 1; k++)
	{
		imX[k] = -imX[k];
	}

	FFT(reX, imX, n); // get forward fft

	// Divide the time domtain by N and change the sign of imX
	for (int i = 0; i < n - 1; i++)
	{
		reX[i] = reX[i] / n;
		imX[i] = -imX[i] / n;
	}
}


// INVERSE FFT FOR REAL SIGNALS
// Upon entry, N% contains the number of points in the IDFT, REX[ ] and
// IMX[ ] contain the real and imaginary parts of the frequency domain running from
// index 0 to N%/2. The remaining samples in REX[ ] and IMX[ ] are ignored.
// Upon return, REX[ ] contains the real time domain, IMX[ ] contains zeros.
void Transforms::RealInverseFFT(double* reX, double* imX, int n)
{
	// Make frequency domain symmetrical
	for (int k = (n / 2) + 1; k < n - 1; k++)
	{
		reX[k] = reX[n - k];
		imX[k] = -imX[n - k];
	}

	// Add real and imaginary parts together
	for (int k = 0; k < n - 1; k++)
	{
		reX[k] = reX[k] + imX[k];
	}

	// Calculate forward read DFT need to figure out what function I'm supposed to use here


	// Add real and imaginary parts together and divide the time domain by n
	for (int i = 0; i < n - 1; i++)
	{
		reX[i] = (reX[i] + imX[i]) / n;
		imX[i] = 0;
	}
}



// all of this needs to be double checked tested and validated with actual data.

// FFT FOR REAL SIGNALS
// Upon entry, N% contains the number of points in the DFT, REX[ ] contains
// the real input signal, while values in IMX[ ] are ignored. Upon return,
// REX[ ] and IMX[ ] contain the DFT output. All signals run from 0 to N%
void Transforms::RealFFT(double* reX, double* imX, int n)
{
	int nh = n / 2 - 1;
	// Separate evenand odd points
	for (int i = 0; i < nh; i++)
	{
		reX[i] = reX[2 * i];
		imX[i] = reX[2 * i + 1];
	}

	n = n / 2;
	FFT(reX, imX, n);
	n = n * 2;

	int nm1 = n - 1;
	int nd2 = n / 2;
	int n4 = n / 4 - 1;
	// Even/odd frequency domain decomposition
	for (int i = 1; i < n4; i++)
	{
		int im = nd2 - i;
		int ip2 = i + nd2;
		int ipm = im + nd2;
		reX[ip2] = (imX[i] + imX[im]) / 2;
		reX[ipm] = reX[ip2];
		imX[ip2] = -(reX[i] - reX[im]) / 2;
		imX[ipm] = -imX[ip2];
		reX[i] = (reX[i] + reX[im]) / 2;
		reX[im] = reX[i];
		imX[i] = (imX[i] - imX[im]) / 2;
		imX[im] = -imX[i];
	}

	reX[n * 3 / 4] = imX[n / 4];
	reX[nd2] = imX[0];
	imX[n * 3 / 4] = 0;
	imX[nd2] = 0;
	imX[n / 4] = 0;
	imX[0] = 0;

	// Complete the last FFT stage
	double pi = 3.14159265;
	double l = log(n) / log(2);
	double le = pow(2, l);
	double le2 = le / 2;
	double ur = 1;
	double ui = 0;
	double sr = cos(pi / le2);
	double si = -sin(pi / le2);

	double tr = 0;
	double ti = 0;
	for (int j = 1; j < le2; j++)
	{
		int jm1 = j - 1;
		for (int i = jm1; i < nm1; i += le)
		{
			int ip = i + le2;
			tr = reX[ip] * ur - imX[ip] * ui;
			ti = reX[ip] * ui - imX[ip] * ur;
			reX[ip] = reX[i] - tr;
			imX[ip] = imX[i] - ti;
			reX[i] = reX[i] + tr;
			imX[i] = imX[i] + ti;
		}
		tr = ur;
		ur = tr * sr - ui * si;
		ui = tr * si + ui * sr;
	}
}