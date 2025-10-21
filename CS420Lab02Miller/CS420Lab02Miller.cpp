// Kayden Miller, CS420, Lab 02, Computing Histogram using Multithreads

#include <vector>
#include <thread>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "ThreadFunctions.h" 

using namespace std;

void fileToMemoryTransfer(char* fileName, char** data, size_t& numOfBytes);

int main(int argc, char *argv[])
{

	return 0;
}

//Reads data from file to RAM
void fileToMemoryTransfer(char* fileName, char** data, size_t& numOfBytes) {
	streampos begin, end;
	ifstream inFile(fileName, ios::in | ios::binary | ios::ate);
	if (!inFile)
	{
		cerr << "Cannot open " << fileName << endl;
		inFile.close();
		exit(1);
	}
	size_t size = inFile.tellg();
	char* buffer = new char[size];
	inFile.seekg(0, ios::beg);
	inFile.read(buffer, size);
	inFile.close();
	*data = buffer;
	numOfBytes = size;
}
