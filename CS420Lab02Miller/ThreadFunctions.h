#pragma once

#include <array>
#include <atomic>

#define LOCK True
#define UNLOCK False


using namespace std;

void sharedHistogram(array<int,256>& histo, array<atomic<bool>,256>& locks)
{

}
