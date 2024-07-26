#pragma once
class Filters
{
	static void MovingAverage(double* input, double* output, int avgWidth, int len);
	static void RecursiveMovingAverage(double* input, double* output, int avgWidth, int len);
};

