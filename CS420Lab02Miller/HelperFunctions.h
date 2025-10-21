#pragma once

//Reads data from file to RAM
void fileToMemoryTransfer(string fileName, char** data, size_t& numOfBytes) {
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

void printHisto(array<int,256>& graph)
{
	for (int i = 0; i < 256; i++)
	{
		cout << i << ": " << graph[i] << endl;
	}
}