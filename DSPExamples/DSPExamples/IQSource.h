#pragma once
#include <vector>
#include <complex>

struct Complex{
	uint16_t real;
	uint16_t imag;
};

class IQSource
{
public:
	IQSource();
private:
	Complex* data;
	int dataLen;
};

