# Board representation
The board is represented by a char array of size ceil(81/2)=41. The most significant 4 bits of the first char represents the upper-left square. The least significant 4 bits of the first char represent the second square on the upper row, counting from left. The most significant 4 bits of the last char represents the lower-right square on the board.
In the solution described below, the board is then treated as 3x3 grids. 

# Solution
1. Read the board to solve
2. Starting with the upper-left grid, generate all possible variations. Take into consideration the clues on the board. Repeat for all 9 grids.
3. 

Build with:
g++ -o sudoku main.cpp board.cpp threadpool.cpp -pthread 
Run with:
./sudoku
