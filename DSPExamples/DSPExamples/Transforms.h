#pragma once
class Transforms
{
	static void InverseDFTOne(double* xx, double* rex, double* imx, int n);
	static void InverseDFTTwo(double* xx, double* rex, double* imx, int n);
	static void DFTCorrelationInput(double* xx, double* rex, double* imx, int n);
	static void DFTCorrelationOutput(double* xx, double* rex, double* imx, int n);

	static void CplxDFTByCorr(double* xR, double* xI, double* reX, double* imX, int n);

	static void FFT(double* reX, double imX, int n);
	static void InverseFFT(double* reX, double imX, int n);
	static void RealInverseFFT(double* reX, double imX, int n);
	static void RealFFT(double* reX, double imX, int n);
};

