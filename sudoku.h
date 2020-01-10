#ifndef SUDOKU_H
#define SUDOKU_H

void solveIt(int, int[][10], int, int, int, bool, bool[], int&);
bool checkRow(int , int , int , int num[][10]);
bool checkCol(int , int , int , int num[][10]);
bool checkBox(int , int , int , int num[][10]);
void getPuzzleBoard(int [][10], bool[]);
bool onRowBoxEnd(int, int, int);
bool onRowEnd(int, int, int);
bool onBoxEnd(int, int, int);
bool onRowBoxBegin(int, int, int);
bool onRowBegin(int, int, int);
bool onBoxBegin(int, int, int);
#endif
