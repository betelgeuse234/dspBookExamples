#pragma once
class Transforms
{
	static void InverseDFTOne(double* xx, double* rex, double* imx, int n);
	static void InverseDFTTwo(double* xx, double* rex, double* imx, int n);
	static void DFTCorrelationInput(double* xx, double* rex, double* imx, int n);
	static void DFTCorrelationOutput(double* xx, double* rex, double* imx, int n);

	static void RectToPolar(double* rex, double* imx, double* magx, double* phasex, int n);
	static void PolarToRect(double* rex, double* imx, double* magx, double* phasex, int n);

	static void PhaseUnwrap(double* phasex, double* phasexUnwrap, int n);


};

