#include "DFT.h"

void InverseDFT(IQ* iqData, double* timeData, int timeNumData)
{
	for (int i = 0; i  < (timeNumData / 2); i++)
	{
		iqData[i].I = iqData[i].I / timeNumData / 2;
		iqData[i].Q = iqData[i].Q / timeNumData / 2;
	}

	iqData[0].I = iqData[0].I / 2;
	iqData[timeNumData/2].I = iqData[timeNumData/2].I / 2;

	iqData[0].Q = iqData[0].Q / 2;
	iqData[timeNumData / 2].Q = iqData[timeNumData / 2].Q / 2;

	for (int i = 0; i < timeNumData / 2; i++)
	{
		for (int j = 0; j < timeNumData; j++)
		{

		}
	}
}
