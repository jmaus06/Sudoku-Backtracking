//Sudoku Solver by Joel
//1/9/20

#include <iostream>
#include "sudoku.h"
using std::cout; using std::cin; using std::endl;

//main program

int main() {
	bool solved = false;
	int curCube = 1;
	int number[10][10];
	int row = 1;
	int col = 1;
	int box = 1;
	bool noChangeIt[82];	
	int tempvar = 1;
	int count = 1;
	
	//initialization of variables to be put into the functions
	for (tempvar = 1; tempvar <= 81; ++tempvar) //set noChangeIt to false for each 
		noChangeIt[tempvar] = false;

	for (int temp1 = 1; temp1 <= 9; ++temp1) {
		for (int temp2 = 1; temp2 <= 9; ++temp2) //assign values to 0
			number[temp1][temp2] = 0;
	}
	
	cout << "\nSudoku Solver by Joel\n\n";
	cout << "_______________________\n\n";
	cout << "When entering numbers, make sure to put a space \n";
	cout << "between each number.\n";
	
	getPuzzleBoard(number,noChangeIt); //user inputs initial state
	
	solveIt(curCube, number, row, col, box, solved, noChangeIt, count); //solve function
	cout << "SOLVED!!!\n\n";
	cout << endl << "It took " << count << " tries.\n";
	system("pause");
} //end of main function

void solveIt(int currentCube, int num[][10], int ro, int co, int bo, bool solvedIt, bool noChange[], int& countIt) {
	do {	
		//if the cube meets all requirements, go forward
		if (checkRow(ro, co, bo, num) && checkCol(ro, co, bo, num)  && checkBox(ro,co,bo,num)) { 			
			
				do { //do at least once, but keep going if restricted number

					if (onRowBoxEnd(ro, co, currentCube)) { //at end of row and box			
						++ro;
						co = 1;
						++bo;
						++currentCube;
						if (noChange[currentCube] == false)  //start new space at 1
							num[ro][co] = 1;						
					}
					else if (onRowEnd(ro, co, currentCube)) { //at end of row
						++ro;
						co = 1;
						bo -= 2;
						++currentCube;
						if (noChange[currentCube] == false)  //start new space at 1
							num[ro][co] = 1;						
					}
					else if (onBoxEnd(ro, co, currentCube)) { //at end of box
						++co;
						++bo;
						++currentCube;
						if (noChange[currentCube] == false)  //start new space at 1
							num[ro][co] = 1;						
					}
					else {												
						++co;
						++currentCube;						
						if (noChange[currentCube] == false) //start new space at 1
							num[ro][co] = 1;						
					}

				} while (noChange[currentCube] == true);
					//repeat until currentCube is NOT restricted
		}

		else {    //if it does NOT meet requirements	
				
				if ((num[ro][co] < 9) && (noChange[currentCube] == false))   //if less than 9
					++num[ro][co];    //increase by one 
				else {
					bool keepgoingback = true; //cannot increase currentCube

				do {						 
					while (keepgoingback == true) { //until currentCube less than 9

						if (onRowBoxBegin(ro, co, currentCube)) { //at beginning of row and box
							if (noChange[currentCube] == false) 
								num[ro][co] = 0; //resets before advancing
							
								--ro;
								co = 9;
								--bo;
								--currentCube;	
							//once moved to new space, test new space
							if ((noChange[currentCube] == false) && (num[ro][co] < 9)) { 
								++num[ro][co]; //start new space at next one
								keepgoingback = false;
							}
							else if ((noChange[currentCube] == false) && (num[ro][co] == 9))
								keepgoingback = true;

						}	
						else if (onRowBegin(ro, co, currentCube)) { //at beginning of row
							if (noChange[currentCube] == false) //resets cube before advancing
								num[ro][co] = 0;
							
								--ro;
								co = 9;
								bo += 2;
								--currentCube;
							//once moved to new space, test new space
							if ((noChange[currentCube] == false) && (num[ro][co] < 9)) { 
									++num[ro][co];
									keepgoingback = false;
								}
							else if ((noChange[currentCube] == false) && (num[ro][co] == 9))
									keepgoingback = true;
							}
						else if (onBoxBegin(ro, co, currentCube)) { //at beginning of box
							if (noChange[currentCube] == false) //resets cube before advancing
								num[ro][co] = 0;
							
								--co;
								--bo;
								--currentCube;
							//once moved to new space, test new space
							if ((noChange[currentCube] == false) && (num[ro][co] < 9)) { 
								++num[ro][co];
								keepgoingback = false;
							}
							else if ((noChange[currentCube] == false) && (num[ro][co] == 9))
									keepgoingback = true;
							}
						else {
							if (noChange[currentCube] == false) //resets cube before advancing
								num[ro][co] = 0;
								--co;
								--currentCube;
							if ((noChange[currentCube] == false) && (num[ro][co] < 9)) { 
								++num[ro][co];
								keepgoingback = false;
							}
							else if ((noChange[currentCube] == false) && (num[ro][co] == 9))
								keepgoingback = true;
						}
					} //end of keepgoingback loop
				} while (noChange[currentCube] == true);

				}
		}
		++countIt; //tracks total tries
	} while (currentCube <= 81);

	cout << endl;
	for (int tempx = 1; tempx <= 9; ++tempx) {  //display grid when solved
			for (int tempy = 1; tempy <= 9; ++tempy) 
				cout << num[tempx][tempy] << " ";			
			cout << endl;
	}
		cout << endl;		
		solvedIt = true;
}

bool checkRow(int row, int col, int box, int num[][10]) { //see if number exists in row	
	for (int x = 1; x <= 9; ++x) {
		//if current space matches ANY space
		if (num[row][col] == num[x][col])
			if (row!=x)
				return false;		
	}
	return true;
}


bool checkCol(int row, int col, int box, int num[][10]) { //see if number exists in column
	for (int x = 1; x <= 9; ++x) {
		//if current space matches ANY space
		if (num[row][col] == num[row][x]) 
			if(col!=x)
				return false;		
	}
	return true;
}

bool checkBox(int row, int col, int box, int num[][10]) {	
	switch (box) { //checks if the spot is safe 
	case 1:
		for (int x = 1; x <= 3; ++x) {
			for (int y = 1; y <= 3; ++y) {
				if (num[row][col] == num[x][y]) 
					if ((row != x) && (col != y))
					return false;
			}
		}
		return true;
		break;

	case 2:
		for (int x = 1; x <= 3; ++x) {
			for (int y = 4; y <= 6; ++y) {
				if (num[row][col] == num[x][y]) 
					if ((row != x) && (col != y))
						return false;					
			}
		}
		return true;
		break;

	case 3:
		for (int x = 1; x <= 3; ++x) {
			for (int y = 7; y <= 9; ++y) {
				if (num[row][col] == num[x][y]) 
					if ((row != x) && (col != y))
						return false;				
			}
		}
		return true;
		break;

	case 4:
		for (int x = 4; x <= 6; ++x) {
			for (int y = 1; y <= 3; ++y) {
				if (num[row][col] == num[x][y]) 
					if ((row != x) && (col != y))
						return false;
			}
		}
		return true;
		break;

	case 5:
		for (int x = 4; x <= 6; ++x) {
			for (int y = 4; y <= 6; ++y) {
				if (num[row][col] == num[x][y]) 
					if ((row != x) && (col != y))
						return false;
			}
		}
		return true;
		break;

	case 6:
		for (int x = 4; x <= 6; ++x) {
			for (int y = 7; y <= 9; ++y) {
				if (num[row][col] == num[x][y]) 
					if ((row != x) && (col != y))
						return false;
			}
		}
		return true;
		break;

	case 7:
		for (int x = 7; x <= 9; ++x) {
			for (int y = 1; y <= 3; ++y) {
				if (num[row][col] == num[x][y]) 
					if ((row != x) && (col != y))
						return false;
			}
		}
		return true;
		break;

	case 8:
		for (int x = 7; x <= 9; ++x) {
			for (int y = 4; y <= 6; ++y) {
				if (num[row][col] == num[x][y]) 
					if ((row != x) && (col != y))
						return false;
			}
		}
		return true;
		break;

	case 9:
		for (int x = 7; x <= 9; ++x) {
			for (int y = 7; y <= 9; ++y) {
				if (num[row][col] == num[x][y]) 
					if ((row != x) && (col != y))
						return false;
			}
		}
		return true;
		break;
	}
}

bool onRowBoxEnd(int row, int col, int currentCube) { //end of row and box
	if ((currentCube % 27) == 0)
		return true;
	else
		return false;
}

bool onRowEnd(int row, int col, int currentCube) { //end of row only
	if ((currentCube % 9) == 0)
		return true;
	else
		return false;
}
bool onBoxEnd(int row, int col, int currentCube) { //end of current box
	if ((currentCube % 3) == 0)
		return true;
	else
		return false;
}
bool onRowBoxBegin(int row, int col, int currentCube) { //beginning of row and box
	if (((currentCube-1) % 27) == 0)
		return true;
	else
		return false;

}
bool onRowBegin(int row, int col, int currentCube) { //beginning of row only
	if (col == 1)
		return true;
	else
		return false;

}
bool onBoxBegin(int row, int col, int currentCube) { //beginning of box
	if ((currentCube - 1) % 3 == 0)
		return true;
	else
		return false;

}
void getPuzzleBoard(int num[][10], bool noChange[]) { //get initial values from user
	int x;
	int y;
	int curSpace = 1;
	for (x = 1; x <= 9; ++x) {
		cout << "Enter numbers from row "<< x <<".\n";
		for (y = 1; y <= 9; ++y) {
			cin >> num[x][y];		
			if (num[x][y] > 0)
				noChange[curSpace] = true; 
			else
				noChange[curSpace] = false; //if a number is entered, restrict space
			
			++curSpace;
		}
	}
	cout << "\nThe puzzle has been entered.\n";
	system("pause");	
}
