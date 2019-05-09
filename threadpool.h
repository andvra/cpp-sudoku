#pragma once
#include <thread>
#include <vector>
#include <tuple>
#include <mutex>

using namespace std;

class ThreadPool
{
vector<int> ids;
int maxThreadCount;
int cnt;
mutex mtx;
public:
    ThreadPool(int maxNumberOfThreads);
    ~ThreadPool();
	int GetID();
	void Release(int id);
};
