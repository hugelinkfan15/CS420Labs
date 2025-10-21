// Kayden Miller, CS420, Lab 02, Computing Histogram using Multithreads

#include <vector>
#include <thread>
#include <iostream>
#include <algorithm>>

using namespace std;

void func()
{
	cout << "**Inside thread" << this_thread::get_id() << "!" << endl;
}

int main()
{
	int numthreads = thread::hardware_concurrency();
	vector<thread> workers;

	cout << "This computer has " << numthreads << " threads." << endl;

	for (int i = 0; i < numthreads; i++)
		workers.push_back(thread(func));

	for_each(workers.begin(),workers.end(),[](thread& t){t.join();});

	return 0;
}
