#include <algorithm>
#include <iostream>
#include "threadpool.h"

ThreadPool::ThreadPool(int maxNumberOfThreads)
{
	maxThreadCount = maxNumberOfThreads;
	cnt = 0;
}

ThreadPool::~ThreadPool()
{
}

int ThreadPool::GetID()
{
	int ret = 0;
	mtx.lock();
	if (ids.size() < maxThreadCount)
	{
		ret = (++cnt);
		ids.push_back(ret);
	}
	mtx.unlock();
	return ret;
}

void ThreadPool::Release(int id)
{
	string s = "Running release for ID " + to_string(id) + "\n";
	mtx.lock();
	vector<int>::iterator pos = find(ids.begin(), ids.end(), id);
	if (pos != ids.end())
	{
		ids.erase(pos);
	}
	mtx.unlock();
	;
}
