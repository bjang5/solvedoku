#include <iostream>
#include <vector>

using namespace std;

struct sudoku {
	int matrix[9][9];
	bool solved = false;
};

sudoku original;


// returns false if incomplete
bool checkComplete(){
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (original.matrix[i][j]==0)
				return false;
		}
	}
	return true;
}

// prints the sudoku puzzle
void printSudoku() {
	cout << endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << original.matrix[i][j] << " ";

			// starts at 0, need to shift over by 1. 
			// Add column symbol after every three numbers, %3 returns 0 when (j+1) is a multiple of 3
			// ! inverts it
			if (!((j+1)%3) && j != 8) {	
				cout << "| ";
			}
		}
		if (!((i+1)%3) && i != 8) {
			cout << "\n" << "_____________________";
		}
		cout << endl;		
	}
}


// gives the box # (0-9) for row i, column j
int giveBox(int i, int j ){
	if(i>=0&&i<=2&&j>=0&&j<=2){
					return 0;
				} else if(j>2&&j<=5&&i>=0&&i<=2){
					return 1;
				} else if(j>5&&j<=8&&i>=0&&i<=2){
					return 2;
				}else if(j>=0&&j<=2&&i>2&&i<=5){
					return 3;
				}else if(j>2&&j<=5&&i>2&&i<=5){
					return 4;
				}else if(j>5&&j<=8&&i>2&&i<=5){
					return 5;
				}else if(j>=0&&j<=2&&i>5&&i<=8){
					return 6;
				}else if(j>2&&j<=5&&i>5&&i<=8){
					return 7;
				}else {
					return 8;
				}
}

// returns true if we can put into original[i][j] without breaking sudoku rules
bool validInput(int num, int i, int j){
	// box coordinates of row i, column j
	int boxNum = giveBox(i, j);

	for (int k = 0; k < 9; k++){
		if(original.matrix[i][k] == num)
			return false;
	}

	for (int k = 0; k < 9; k++){
		if(original.matrix[k][j] == num)
			return false;
	}

	for(int boxRow = (boxNum/3)*3; boxRow <= (boxNum/3)*3+2; boxRow++){
		for (int boxCol = (boxNum%3)*3; boxCol <= (boxNum%3)*3+2; boxCol++){
			if(original.matrix[boxRow][boxCol] == num)
				return false;
		}
	}
	return true;
}


// finds the next empty spot in sudoku, returns false when no more empty spots
// uses &row and &col to alter the values inputted into the function
bool findEmpty(int &row, int &col){
	for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (original.matrix[row][col] == 0)
                return true;
    return false;
}


// uses recursion to try different values, stops when no more empty spots
bool backTrack(){
	int row, col;
	// stops backTrack() once sudoku puzzle is completed
	if(findEmpty(row, col) == false){
		return true;
	} else {
		// attempts to try numbers 1-9
		for(int num = 1; num <= 9; num++){
			// inserts num into sudoku if within rules
			if(validInput(num, row, col)){
				original.matrix[row][col] = num;
		
				// recursively calls itself, ends when sudoku is complete
				if(backTrack()){
					return true;
				}

				// if backTrack is invalid, replaces the tried number with 0 and tries the next num
				original.matrix[row][col] = 0;
			}				
		}
			
	}
	return false;
}

int main() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> original.matrix[i][j];
		}
	}


	// before solve
	printSudoku();

	// solving algorithm
	backTrack();

	cout << endl << endl << endl;

	// after solve
	printSudoku();

	return 0;
}


/*TEST
5 3 4 6 7 8 9 1 2 6 7 2 1 9 5 0 4 8 0 9 8 3 4 0 5 6 7 8 5 9 7 6 1 4 2 3 0 2 6 8 0 3 7 9 1 7 1 3 9 2 4 8 5 0 9 6 1 5 3 7 2 8 4 2 8 0 4 1 9 6 3 5 3 4 5 2 0 6 1 7 0

0 8 0 0 0 0 2 0 0 0 0 0 0 8 4 0 9 0 0 0 6 3 2 0 0 1 0 0 9 7 0 0 0 0 8 0 8 0 0 9 0 3 0 0 2 0 1 0 0 0 0 9 5 0 0 7 0 0 4 5 8 0 0 0 3 0 7 1 0 0 0 0 0 0 8 0 0 0 0 4 0

9 2 0 8 1 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 2 6 5 0 0 0 5 0 8 4 0 2 0 0 0 0 4 0 0 0 0 6 8 0 0 9 0 0 3 8 2 0 4 0 3 4 0 0 0 0 0 2 0 8 0 0 2 3 0 7 9 0 0 0 0 0 0 5 0 8 

9 0 1 2 0 0 0 0 6 0 6 0 0 8 0 0 0 4 0 0 0 0 0 4 0 0 3 7 0 0 0 0 1 0 0 5 0 0 5 0 4 0 6 0 0 3 0 0 5 0 0 0 0 8 2 0 0 4 0 0 0 0 0 6 0 0 0 5 0 0 9 0 4 0 0 0 0 7 8 0 1
*/
