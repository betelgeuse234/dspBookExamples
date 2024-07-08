#pragma once
class Convolution
{
public:
	static void InputSideAlgorithm(double* x, double* h, double* y, int lenX, int lenH);
	static void OutputSideAlgorithm(double* x, double* h, double* y, int lenX, int lenH);
	static void FirstDifference(double* x, double* y, int lenX);
	static void RunningSum(double* x, double* y, int lenX);
};

