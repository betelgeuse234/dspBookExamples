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
	void GetIQData(Complex* dest, int len);
private:
	Complex* data;
	int dataLen;
};

