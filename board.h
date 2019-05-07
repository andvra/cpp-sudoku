#include <string>
#include <vector>
#include <algorithm>

using  namespace std;

class Board
{
    char board[81];
    vector<string> possibleGridFills[9];
public:
    Board(string s)
    {
        if(s.length()!=81) {
            cout << "Wrong string length! Must be 81\n";
        }
        for(int i=0; i<81; i++)
            board[i]=s.c_str()[i];
        Init(s);
    }

    ~Board()
    {
    }

    bool IsValid(string s, int row, int col)
    {
        for(int i=0; i<3; i++)
        {
            vector<char> ccv;
            vector<char> cch;
            // One line is 9 chars long
            for(int j=0; j<9; j++)
            {
                char cv=s[col*3+i+j*9];
                char ch=s[row*27+i*9+j];
                if(cv!='0')
                {
                    vector<char>::iterator f=find(ccv.begin(),ccv.end(),cv);
                    if (f!=ccv.end())
                        return false;
                    ccv.push_back(cv);
                }

                if(ch!='0')
                {
                    vector<char>::iterator f=find(cch.begin(),cch.end(),ch);
                    if(f!=cch.end())
                        return false;
                    cch.push_back(ch);
                }
            }
        }
        return true;

    }

    string BoardStringToString(const char* data)
    {
        string s = "";

        for(int i=0; i<81; i++) {
            s+=data[i];
            if((i+1)%9==0)
                s+="\n";
            else
                s+=" ";
        }
        return s;
    }

    string ToString()
    {
        return BoardStringToString(Data());
    }
    void Asd(string s, int row, int col, char tryNumber, vector<char> tryNumbers, vector<string>& possibleGrids)
    {
        for(int x=0; x<3; x++)
        {
            for(int y=0; y<3; y++)
            {
                int idx=col*3+x+row*27+9*y;
                if(s[idx]=='0')
                {
                    s[idx]=tryNumber;
                    if(IsValid(s,row,col))
                    {
                        if(tryNumbers.size()==0)
                        {
                            string grid="";
                            for(int i=0; i<3; i++)
                            {
                                for(int j=0; j<3; j++)
                                {
                                    grid+=s[col*3+j+row*27+9*i];
                                }
                            }
                            possibleGrids.push_back(grid);
                        }
                        else
                        {
                            char nextTryNumber=tryNumbers[tryNumbers.size()-1];
                            tryNumbers.pop_back();
                            Asd(s,row,col,nextTryNumber,tryNumbers, possibleGrids);
                            tryNumbers.push_back(nextTryNumber);
                        }
                    }
                    s[idx]='0';
                }
            }
        }
    }

    vector<string> GeneratePossibleGrids(string s, unsigned int gridID)
    {
        vector<string> grids;
        int gridRow=gridID/3;
        int gridColumn=gridID%3;
        vector<char> tryNumbers= {'1','2','3','4','5','6','7','8','9'};
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                char c=s[gridColumn*3+i+gridRow*27+9*j];
                if(c!='0')
                {
                    tryNumbers.erase(remove(tryNumbers.begin(),tryNumbers.end(),c),tryNumbers.end());
                }
            }
        }

        char first=tryNumbers[tryNumbers.size()-1];
        tryNumbers.pop_back();
        Asd(s,gridRow,gridColumn,first,tryNumbers,grids);
        cout << "Number of grids: " << grids.size() << '\n';
        return grids;
    }

    void Init(string s)
    {
        for(int i=0; i<9; i++)
        {
            vector<string> possibleGrids = GeneratePossibleGrids(s,i);
            possibleGridFills[i]=possibleGrids;
        }
    }

    const char* Data()
    {
        return board;
    }

    void PushGrid(string& s, int row, int col, string grid)
    {
        for(int x=0; x<3; x++)
        {
            for(int y=0; y<3; y++)
            {
                int idx = col*3+x+row*27+9*y;
                s[idx]=grid[x+3*y];
            }
        }
    }

    void PopGrid(string& s, int row, int col)
    {
        for(int x=0; x<3; x++)
        {
            for(int y=0; y<3; y++)
            {
                int idx = col*3+x+row*27+9*y;
                s[idx]=board[idx];
            }
        }
    }

    string BuildBoard(string s, int row, int col)
    {
	   unsigned int noPossibleGrids=possibleGridFills[row*3+col].size();
	   unsigned int oneTenth=noPossibleGrids/100;
        for(int i=0; i<noPossibleGrids; i++)
        {
		if(row==0&&col==0)
		cout << "Now running " << i << " at the top level\n";
            //if(row==0 && col==0 && (i%oneTenth)==0)
	//	    cout << "Now running grid " << i << " out of " << noPossibleGrids << " at the top level\n";
		PushGrid(s,row,col,possibleGridFills[row*3+col][i]);
            if(IsValid(s,row,col))
            {
                if(col==2 && row==2)
                {
                    return BoardStringToString(s.c_str());
                }
                else
                {   
			string ret =BuildBoard(s,row+(col==2),(col+1)%3);
			if (ret!="")
				return ret;
                }
            }
            PopGrid(s,row,col);
        }
	return "";
    }

    void PrintSolution()
    {
        string s = board;
        string ret = BuildBoard(s,0,0);
	if(ret=="")
		cout << "No solution found\n";
	else
		cout << ret << "\n";
    }
};

