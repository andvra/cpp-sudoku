#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <mutex>
#include "threadpool.h"

using namespace std;

class Board
{
    string solution;
    mutex mutexSolved;
    string board;
    vector<vector<string>> possibleGridFills;
    ThreadPool *threadPool;

public:
    Board(string s, ThreadPool *tp = 0);

    ~Board();

    bool IsValid(string s, int row, int col);

    string BoardStringToString(const string &data);

    string ToString();

    void CreateGrids(string s, int row, int col, char tryNumber, vector<char> tryNumbers, vector<string> &possibleGrids);

    vector<string> GeneratePossibleGrids(string s, unsigned int gridID);

    void Init(string s);

    const string Data();

    void GenerateSolution();
    void SetSolved(string sol);
    string GetSolution();
};
