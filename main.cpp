#include <string>
#include <iostream>
#include <bitset>
#include <chrono>
#include <thread>
#include <random>
#include <iterator>
#include "board.h"
#include "threadpool.h"

using namespace std;
int maxNoThreads = 3;

static void FindSolution(Board &board)
{
	board.GenerateSolution();
}

template <typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator &g)
{
	uniform_int_distribution<> dis(0, distance(start, end) - 1);
	advance(start, dis(g));
	return start;
}

template <typename Iter>
Iter select_randomly(Iter start, Iter end)
{
	// https://stackoverflow.com/a/16421677
	static random_device rd;
	static mt19937 gen(rd());
	string board = select_randomly(start, end, gen);
}

int main()
{
	const vector<string> boards = {"870090240106520080094000000000340610001206300063075000000000850020051704057060093",
								   "070940520009003007350721090700000000504302806000000002040615089900800200013097040",
								   "609007000100200000070063000700006032040000050980100007000820010000005009000600208",
								   "000801000000000430500000000000070800000000100020030000600000075003400000000200600"};
	ThreadPool tp(maxNoThreads);
	string boardAsText = *select_randomly(boards.begin(), boards.end());
	Board board(boardAsText, &tp);
	auto t_start = chrono::high_resolution_clock::now();
	thread t(FindSolution, ref(board));
	t.detach();
	string ret = board.GetSolution();
	auto t_end = chrono::high_resolution_clock::now();
	cout << std::chrono::duration<double>(t_end - t_start).count() << " ms\n";
	cout << "Solution:\n";
	cout << Board::BoardStringToString(ret) << "\n";
	cout << "Sleep for 5s..\n";
	this_thread::sleep_for(5s);
	cout << "Done!\n";
	return 1;
}
