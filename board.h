#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

int noAvailableThreads = 8;
vector<thread> threads;
string solution;

class Board
{
    string board;
    vector<vector<string>> possibleGridFills;

public:
    Board(string s);

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

    static void BuildBoard(const string &originalBoard, string s, int row, int col, const vector<vector<string>> gridFills, int threadStartRow, int threadStartCol);

    void PrintSolution();
};
