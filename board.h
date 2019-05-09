#pragma once
#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include <mutex>
#include "threadpool.h"

using namespace std;

class Board
{
static string solution;
static mutex mutexSolved;
    string board;
    vector<vector<string>> possibleGridFills;
	ThreadPool* threadPool;
public:
    Board(string s, ThreadPool* tp=0);

    ~Board();

    static bool IsValid(string s, int row, int col);

    string BoardStringToString(const string &data);

    string ToString();

    void CreateGrids(string s, int row, int col, char tryNumber, vector<char> tryNumbers, vector<string> &possibleGrids);

    vector<string> GeneratePossibleGrids(string s, unsigned int gridID);

    void Init(string s);

    const string Data();

    static void PushGrid(string &s, int row, int col, string grid);

    static void PopGrid(const string &originalBoard, string &s, int row, int col);

    static void BuildBoard(const string &originalBoard, string s, int row, int col, const vector<vector<string>> gridFills, int threadID, ThreadPool *tp);

    void PrintSolution();
    static void SetSolved(string sol);
    string GetSolution();
};
