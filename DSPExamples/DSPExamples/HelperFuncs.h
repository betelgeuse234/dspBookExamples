#pragma once
class HelperFuncs
{
public:
	static void NegativeFreqGen(double* reX, double* imx, int n);
	static void RectToPolar(double* rex, double* imx, double* magx, double* phasex, int n);
	static void PolarToRect(double* rex, double* imx, double* magx, double* phasex, int n);

	static void PhaseUnwrap(double* phasex, double* phasexUnwrap, int n);
};

