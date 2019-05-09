#include <string>
#include <iostream>
#include <bitset>
#include <chrono>
#include <thread>
#include "board.h"
#include "threadpool.h"

using namespace std;
int maxNoThreads=3;
ostream& operator<<(ostream& os, Board& board)
{
	return os << board.ToString();
}

static void FindSolution(Board board)
{
	board.PrintSolution();
}

int main()
{
	string board1="870090240106520080094000000000340610001206300063075000000000850020051704057060093";
	string board2="070940520009003007350721090700000000504302806000000002040615089900800200013097040";
	string board3="609007000100200000070063000700006032040000050980100007000820010000005009000600208";
	string board4="000801000000000430500000000000070800000000100020030000600000075003400000000200600";
	ThreadPool tp(maxNoThreads);
	Board board(board4,&tp);
	auto t_start = chrono::high_resolution_clock::now();
	//thread t(FindSolution, board);
	//t.detach();
	string ret=board.GetSolution();
	auto t_end = chrono::high_resolution_clock::now();
	cout << std::chrono::duration<double>(t_end-t_start).count() << " ms\n";
	cout << "Sleep for 5s..\n";
	this_thread::sleep_for(5s);
	cout << "Done!\n";	
	return 0;
}
