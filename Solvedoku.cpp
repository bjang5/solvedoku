#include <iostream>
#include <vector>

using namespace std;

int repCounter = 0;
int btIter = 0;

// represents each number's attributes
struct number {	
	int count = 0;

	// true equates to filled position, false equates to empty position
	bool row [9] = {false,false,false,false,false,false,false,false,false};
	bool column [9] = {false,false,false,false,false,false,false,false,false};
	bool box [9] = {false,false,false,false,false,false,false,false,false};
};

struct sudoku {
	int matrix[9][9];
	number list[10];
};

sudoku sudokuVect[1000];	


void printNum(int num) {
	for (int i = 0; i < 9; i++) {
		cout << "Row " << i+1 << ": " << sudokuVect[0].list[num].row[i] << endl;
		cout << "Column " << i+1 << ": " << sudokuVect[0].list[num].row[i] << endl;
		cout << "Box " << i+1 << ": " << sudokuVect[0].list[num].row[i] << endl;
	}
}

bool checkComplete(){
	for (int i = 1; i <= 9; i++){
		if (sudokuVect[btIter].list[i].count!=9){
			return false;
		}
	}
	return true;
}

void printSudoku() {
	cout << endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << sudokuVect[btIter].matrix[i][j] << " ";

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

// solves the puzzle by boxes, num is current number to be solved for, guess = true if number is being guessed, false if only spot available
// returns true if value is inserted, INCLUDING guesses
bool initSolver(int num, int boxNum, bool guess) {
	bool miniBox[3][3];
	// initialization of miniBox
	for (int boxIs = 0; boxIs < 3; boxIs++) {
		for (int sboxJ = 0; sboxJ < 3; sboxJ++) {
			miniBox[boxIs][sboxJ] = false;
		}
	}

	if (!(sudokuVect[btIter].list[num].box[boxNum])) {
		for (int r = (boxNum/3)*3; r <= (boxNum/3)*3+2; r++) {
			for (int c = (boxNum%3)*3; c <= (boxNum%3)*3+2; c++) {
				if(sudokuVect[btIter].list[num].row[r]==true){
					miniBox[r%3][c%3] = true;
				} else if(sudokuVect[btIter].list[num].column[c]==true){
					miniBox[r%3][c%3] = true; 
				} else if(sudokuVect[btIter].matrix[r][c]!=0) {
					miniBox[r%3][c%3] = true;
				}
				
			}
		}
		
		int counter = 0;
		int rCoordinate = -1;
		int cCoordinate = -1;
		for(int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				if (miniBox[i][j] == false){
					counter++;
					rCoordinate = i;
					cCoordinate = j;
					if (guess) {
						sudokuVect[btIter].matrix[rCoordinate + (boxNum/3)*3][cCoordinate + (boxNum%3)*3] = num;
						sudokuVect[btIter].list[num].count++;
						sudokuVect[btIter].list[num].row[rCoordinate + (boxNum/3)*3] = true;
						sudokuVect[btIter].list[num].column[cCoordinate + (boxNum%3)*3] = true;
						sudokuVect[btIter].list[num].box[boxNum] = true;
						return true;
					}
				}
			}
		}
		// insert value if only one possible spot
		if (counter == 1){
			sudokuVect[btIter].matrix[rCoordinate + (boxNum/3)*3][cCoordinate + (boxNum%3)*3] = num;
			sudokuVect[btIter].list[num].count++;
			sudokuVect[btIter].list[num].row[rCoordinate + (boxNum/3)*3] = true;
			sudokuVect[btIter].list[num].column[cCoordinate + (boxNum%3)*3] = true;
			sudokuVect[btIter].list[num].box[boxNum] = true;
			return true;
		}
		return false;
	}
	return false;
}

void backTrack(int gNum, int gBoxNum){
	btIter++;
	// copies content from previous sudoku into new sudoku
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			sudokuVect[btIter].matrix[i][j] = sudokuVect[btIter-1].matrix[i][j];
		}
	}
	for (int k = 1; k < 10; k++) {
		sudokuVect[btIter].list[k].count = sudokuVect[btIter-1].list[k].count;
		for (int l = 0; l < 9; l++) {
			sudokuVect[btIter].list[k].row[l] = sudokuVect[btIter-1].list[k].row[l];
			sudokuVect[btIter].list[k].column[l] = sudokuVect[btIter-1].list[k].column[l];
			sudokuVect[btIter].list[k].box[l] = sudokuVect[btIter-1].list[k].box[l];
		}
	}

	while (!initSolver(gNum, gBoxNum, true)) {
		gNum++;
		if (gNum == 10) {
			gBoxNum++;
			gNum = 1;
		}
	}
	while (repCounter < 10){
		for (int num = 1; num <= 9 && repCounter < 10; num++) {
			repCounter++;
			for (int box = 0; box < 9; box++) {
				if (initSolver(num, box, false)) {
					repCounter = 0;
				}
			}
		}
	}
	if (checkComplete()) {
		cout << "Yay!" << endl;
	}
	else {
		backTrack(gNum, gBoxNum);
	}
	return;
}

int main() {
	// initializes sudokuVect
	for(sudoku s : sudokuVect){
		for(int k = 0; k < 9; k++){
			for(int l = 0; l < 9; l++){
				s.matrix[k][l] = 0;
			}
		}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> sudokuVect[0].matrix[i][j];
			if(sudokuVect[0].matrix[i][j] != 0){
				sudokuVect[0].list[sudokuVect[0].matrix[i][j]].count++;
				sudokuVect[0].list[sudokuVect[0].matrix[i][j]].row[i] = true;
				sudokuVect[0].list[sudokuVect[0].matrix[i][j]].column[j] = true;

				if(i>=0&&i<=2&&j>=0&&j<=2){
					sudokuVect[0].list[sudokuVect[0].matrix[i][j]].box[0] = true;
				} else if(j>2&&j<=5&&i>=0&&i<=2){
					sudokuVect[0].list[sudokuVect[0].matrix[i][j]].box[1] = true;
				} else if(j>5&&j<=8&&i>=0&&i<=2){
					sudokuVect[0].list[sudokuVect[0].matrix[i][j]].box[2] = true;
				}else if(j>=0&&j<=2&&i>2&&i<=5){
					sudokuVect[0].list[sudokuVect[0].matrix[i][j]].box[3] = true;
				}else if(j>2&&j<=5&&i>2&&i<=5){
					sudokuVect[0].list[sudokuVect[0].matrix[i][j]].box[4] = true;
				}else if(j>5&&j<=8&&i>2&&i<=5){
					sudokuVect[0].list[sudokuVect[0].matrix[i][j]].box[5] = true;
				}else if(j>=0&&j<=2&&i>5&&i<=8){
					sudokuVect[0].list[sudokuVect[0].matrix[i][j]].box[6] = true;
				}else if(j>2&&j<=5&&i>5&&i<=8){
					sudokuVect[0].list[sudokuVect[0].matrix[i][j]].box[7] = true;
				}else if(j>5&&j<=8&&i>5&&i<=8){
					sudokuVect[0].list[sudokuVect[0].matrix[i][j]].box[8] = true;
				}
			}
		}
	}

	// before solve
	printSudoku();
	
	while (repCounter < 10){
		for (int num = 1; num <= 9 && repCounter < 10; num++) {
			repCounter++;
			for (int box = 0; box < 9; box++) {
				if (initSolver(num, box, false)) {
					repCounter = 0;
				}
			}
		}
	}

	if (!checkComplete()) {
		backTrack(1,0);
	}

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
