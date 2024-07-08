#include "Convolution.h"

void Convolution::InputSideAlgorithm(double* x, double* h, double* y, int lenX, int lenH){
	for (int i = 0; i < lenX; i++)
	{
		for (int j = 0; j < lenH; j++)
		{
			y[i + j] = y[i + j] + x[i] * h[j];
		}
	}
}

void Convolution::OutputSideAlgorithm(double* x, double* h, double* y, int lenX, int lenH) {
	for (int i = 0; i < (lenX + lenH); i++)
	{
		for (int j = 0; j < lenH; j++)
		{
			if (i - j > 0 && i - j < lenX)
			{
				y[i] = y[i] + x[i-j] * h[j];
			}
			
		}
	}
}

void Convolution::FirstDifference(double* x, double* y, int lenX)
{
	y[0] = 0;
	for (int i = 1; i < lenX; i++)
	{
		y[i] = x[i] - x[i - 1];
	}
}

void Convolution::RunningSum(double* x, double* y, int lenX)
{
	y[0] = x[0];
	for (int i = 1; i < lenX; i++)
	{
		y[i] = x[i] - y[i - 1];
	}
}