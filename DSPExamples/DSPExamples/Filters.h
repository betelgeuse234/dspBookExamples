#pragma once
class Filters
{
public:
	static void MovingAverage(double* input, double* output, int avgWidth, int len);
	static void RecursiveMovingAverage(double* input, double* output, int avgWidth, int len);
	static void LowPassWindowedSinc(double* input, double* output, int dataLen, double* kernal, int kernalLen);
	static void CustomFilterDesign(double* impulse, double* filter, int len, int M);
	static void FFTConvolution(double* input, int inLen, double* output, double* kernel, int kernelLen, int fftLen);
};

