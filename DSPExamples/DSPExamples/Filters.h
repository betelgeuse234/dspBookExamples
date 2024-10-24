#pragma once
class Filters
{
public:
	static void MovingAverage(double* input, double* output, int avgWidth, int len);
	static void RecursiveMovingAverage(double* input, double* output, int avgWidth, int len);
	static void LowPassWindowedSinc(double* input, double* output, int dataLen, double* kernal, int kernalLen);
};

