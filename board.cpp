#include "board.h"

using namespace std;

Board::Board(string s)
{

    if (s.length() != 81)
    {
        cout << "Wrong string length! Must be 81\n";
    }
    board = s;
    Init(s);
}

Board::~Board()
{
}

bool Board::IsValid(string s, int row, int col)
{
    for (int i = 0; i < 3; i++)
    {
        vector<char> ccv;
        vector<char> cch;
        // One line is 9 chars long
        for (int j = 0; j < 9; j++)
        {
            char cv = s[col * 3 + i + j * 9];
            char ch = s[row * 27 + i * 9 + j];
            if (cv != '0')
            {
                vector<char>::iterator f = find(ccv.begin(), ccv.end(), cv);
                if (f != ccv.end())
                    return false;
                ccv.push_back(cv);
            }

            if (ch != '0')
            {
                vector<char>::iterator f = find(cch.begin(), cch.end(), ch);
                if (f != cch.end())
                    return false;
                cch.push_back(ch);
            }
        }
    }
    return true;
}

string Board::BoardStringToString(const string &data)
{
    string s = "";

    for (int i = 0; i < 81; i++)
    {
        s += data[i];
        if ((i + 1) % 9 == 0)
            s += "\n";
        else
            s += " ";
    }
    return s;
}

string Board::ToString()
{
    return BoardStringToString(Data());
}

void Board::CreateGrids(string s, int row, int col, char tryNumber, vector<char> tryNumbers, vector<string> &possibleGrids)
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            int idx = col * 3 + x + row * 27 + 9 * y;
            if (s[idx] == '0')
            {
                s[idx] = tryNumber;
                if (IsValid(s, row, col))
                {
                    if (tryNumbers.size() == 0)
                    {
                        string grid = "";
                        for (int i = 0; i < 3; i++)
                        {
                            for (int j = 0; j < 3; j++)
                            {
                                grid += s[col * 3 + j + row * 27 + 9 * i];
                            }
                        }
                        possibleGrids.push_back(grid);
                    }
                    else
                    {
                        char nextTryNumber = tryNumbers[tryNumbers.size() - 1];
                        tryNumbers.pop_back();
                        CreateGrids(s, row, col, nextTryNumber, tryNumbers, possibleGrids);
                        tryNumbers.push_back(nextTryNumber);
                    }
                }
                s[idx] = '0';
            }
        }
    }
}

vector<string> Board::GeneratePossibleGrids(string s, unsigned int gridID)
{
    vector<string> grids;
    int gridRow = gridID / 3;
    int gridColumn = gridID % 3;
    vector<char> tryNumbers = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            char c = s[gridColumn * 3 + i + gridRow * 27 + 9 * j];
            if (c != '0')
            {
                tryNumbers.erase(remove(tryNumbers.begin(), tryNumbers.end(), c), tryNumbers.end());
            }
        }
    }

    char first = tryNumbers[tryNumbers.size() - 1];
    tryNumbers.pop_back();
    CreateGrids(s, gridRow, gridColumn, first, tryNumbers, grids);
    cout << "Number of grids: " << grids.size() << '\n';
    return grids;
}

void Board::Init(string s)
{

    for (int i = 0; i < 9; i++)
    {
        vector<string> possibleGrids = GeneratePossibleGrids(s, i);
        possibleGridFills.push_back(possibleGrids);
    }
}

const string Board::Data()
{
    return board;
}

void Board::PushGrid(string &s, int row, int col, string grid)
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            int idx = col * 3 + x + row * 27 + 9 * y;
            s[idx] = grid[x + 3 * y];
        }
    }
}

void Board::PopGrid(const string &originalBoard, string &s, int row, int col)
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            int idx = col * 3 + x + row * 27 + 9 * y;
            s[idx] = originalBoard[idx];
        }
    }
}

void Board::BuildBoard(const string &originalBoard, string s, int row, int col, const vector<vector<string>> gridFills, int threadStartRow, int threadStartCol)
{
    unsigned int noPossibleGrids = gridFills[row * 3 + col].size();
    for (int i = 0; i < noPossibleGrids; i++)
    {
        if (row == 0 && col == 0)
            cout << "Now running " << i << " at the top level\n";
        PushGrid(s, row, col, gridFills[row * 3 + col][i]);
        if (IsValid(s, row, col))
        {
            if (col == 2 && row == 2)
            {
                solution = "DONE! THIS TEXT SHOULD BE THE BOARD REPRESENTATION";
                //solution=BoardStringToString(s.c_str());
                return;
            }
            else
            {
                if (noAvailableThreads > 0)
                {
                    std::thread t(BuildBoard, originalBoard, s, row + (col == 2), (col + 1) % 3, gridFills, row + (col == 2), (col + 1) % 3);
                    t.detach();
                    noAvailableThreads--;
                }
                else
                    BuildBoard(originalBoard, s, row + (col == 2), (col + 1) % 3, gridFills, threadStartRow, threadStartCol);
            }
        }
        PopGrid(originalBoard, s, row, col);
    }
    // Increase thread counter when we return (since this concludes the usage of the thread)
    if (col == threadStartCol && row == threadStartRow)
        noAvailableThreads++;
}

void Board::PrintSolution()
{
    string s = board;
    auto t_start = chrono::high_resolution_clock::now();
    std::thread mainThread(BuildBoard, s.c_str(), s, 0, 0, possibleGridFills, 0, 0);
    noAvailableThreads--;
    mainThread.join();
    auto t_end = chrono::high_resolution_clock::now();
    cout << std::chrono::duration<double, std::milli>(t_end - t_start).count() << " ms\n";
}