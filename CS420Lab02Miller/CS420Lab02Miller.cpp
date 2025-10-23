// Kayden Miller
//CS420
//Lab 02
//Computing a Histogram of all ASICC characters in a text file using threads

#include <vector>
#include <thread>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <atomic>
#include <array>

#include "HelperFunctions.h"

#define LOCK 1;
#define UNLOCK 0;

using namespace std;

int main(int argc, char* argv[])
{
	int numThreads = thread::hardware_concurrency();
	vector<thread> globalWorkers;

	char* fileData = nullptr;
	size_t fileSize;

	array<int,256> histogram = { 0 };
	array<atomic<bool>, 256> locks = { 0 };

	int sectionSize = 0;
	int startPos = 0;
	bool remainder = false;
	atomic<bool> onRemainder = false;

	fileToMemoryTransfer(argv[1], &fileData, fileSize);

	sectionSize = fileSize / numThreads;

	if (fileSize % numThreads != 0)
		remainder = true;

	//Sequential Search through file
	/*for (int i = 0; i < fileSize; i++)
	{
		histogram[(unsigned char)fileData[i]]++;
	}*/

	//Using a global histogram
	for (int i = 0; i < numThreads; i++)
	{
		globalWorkers.push_back(
			thread([&,startPos]()
				{
					for (int i = startPos; i < (startPos + sectionSize); i++)
					{
						char current = fileData[i];
						while(locks[current] == 1){}

						locks[current] = LOCK;
						histogram[current]++;
						locks[current] = UNLOCK;
					}

					if (remainder && !onRemainder)
					{
						onRemainder = LOCK;
						for (int i = (sectionSize * numThreads); i < fileSize; i++)
						{
							char current = fileData[i];
							while (locks[current] == 1) {}

							locks[current] = LOCK;
							histogram[current]++;
							locks[current] = UNLOCK;
						}
					}
				}));
		startPos+= sectionSize;
	}
	
	for_each(globalWorkers.begin(), globalWorkers.end(),
		[](thread& t) { t.join(); });

	cout << "Run with one global histogram" << endl;
	printHisto(histogram);

	//ready variables for next set of threads
	histogram.fill(0);
	startPos = 0;
	onRemainder = UNLOCK;
	vector<thread> localWorkers;

	//Threads using local histograms
	for (int i = 0; i < numThreads; i++)
	{
		localWorkers.push_back(
			thread([&, startPos]()
				{
					array<int, 256> lHistogram = { 0 };

					for (int i = startPos; i < (startPos + sectionSize); i++)
					{
						lHistogram[fileData[i]]++;
					}

					if (remainder && !onRemainder)
					{
						onRemainder = LOCK;
						for (int i = (sectionSize * numThreads); i < fileSize; i++)
						{
							lHistogram[fileData[i]]++;
						}
					}

					for (int i =0; i<256 ; i++)
					{
						while (locks[i] == 1) {}
						locks[i] = LOCK;
						histogram[i] += lHistogram[i];
						locks[i] = UNLOCK;
					}
					
				}));
		startPos += sectionSize;
	}

	for_each(localWorkers.begin(), localWorkers.end(),
		[](thread& t) { t.join(); });

	cout << "Run with local histograms" << endl;
	printHisto(histogram);


	return 0;
}