#include <algorithm>
#include <iostream>
#include "threadpool.h"

ThreadPool::ThreadPool(int maxNumberOfThreads)
{
	maxThreadCount=maxNumberOfThreads;
	cnt=0;
}

ThreadPool::~ThreadPool()
{
}

int ThreadPool::GetID()
{
	//cout << "Running Get\n";
	int ret=0;
	mtx.lock();
	if(ids.size()<maxThreadCount)
	{
		ret=(++cnt);
		ids.push_back(ret);
		//string s="Got ID " + to_string(ret)+"\n";
		//cout << s;
	}
	mtx.unlock();
	//string s= "Got ID " + to_string(ret)+"\n";
	//cout << s;
	return ret;
}

void ThreadPool::Release(int id)
{
	string s="Running release for ID " + to_string(id) + "\n";
	//cout << s;
	mtx.lock();
	vector<int>::iterator pos=find(ids.begin(),ids.end(),id);
	if(pos!=ids.end())
	{
		ids.erase(pos);
		//s= "Removed ID " + to_string(id) + ". Length: " + to_string(ids.size()) + "\n";
		//cout << s;
	}
	mtx.unlock();
	//cout << "Done running release\n";
}
