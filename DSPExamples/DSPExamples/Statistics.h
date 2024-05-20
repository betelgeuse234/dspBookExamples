#pragma once

class Statistics {       // The class
public:             // Access specifier
	static double sum(double* data, unsigned int length);
	static double mean(double* data, unsigned int length);
	static double variance(double* data, unsigned int length);
	static double std_dev(double* data, unsigned int length);
	static double running_man(double* data, unsigned int length);
	static double running_std_dev(double* data, unsigned int length);
};
