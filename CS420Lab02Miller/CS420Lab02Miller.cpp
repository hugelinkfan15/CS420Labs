// Kayden Miller, CS420, Lab 02, Computing Histogram using Multithreads

#include <vector>
#include <thread>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "ThreadFunctions.h" 
#include "HelperFunctions.h"

using namespace std;

int main(int argc, char* argv[])
{
	char* fileData = nullptr;
	size_t fileSize;
	array<int,256> histogram = { 0 };
	fileToMemoryTransfer(argv[1], &fileData, fileSize);

	for (int i = 0; i < fileSize; i ++) 
	{
		histogram[fileData[i]]++;
	}

	printHisto(histogram);


	return 0;
}