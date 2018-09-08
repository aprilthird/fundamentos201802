#pragma once
#include <vector>

using namespace std;

class IOManager
{
public:
	IOManager();
	~IOManager();
	static bool readFileToBuffer(string filePath, vector<unsigned char>& buffer);
};

