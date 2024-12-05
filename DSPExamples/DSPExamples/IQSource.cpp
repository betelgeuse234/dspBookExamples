#include "IQSource.h"
#include <filesystem>
#include<iostream>
#include<fstream>
#include <windows.h>

using namespace std;

IQSource::IQSource()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	cout << std::string(buf) << endl;

	string myText;
	ifstream IQData("..//..//IQRecordings//IQREC-12-05-24-12h46m45s895.iq", ios::in | ios::binary);

	if (!IQData) {
		cout << "Cannot open file!" << endl;
		return;
	}
	
	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(IQData), {});

	data = (Complex*)buffer.data();
	dataLen = buffer.size() / 4;
}