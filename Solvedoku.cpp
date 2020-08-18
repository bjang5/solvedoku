#include <iostream>

using namespace std;

// stores the entirety of the puzzle
int sudoku[9][9];	

// represents each number's attributes
struct number {	
	int count = 0;

	// true equates to filled position, false equates to empty position
	bool row [9];
	bool column [9];
	bool box [9];
};

// list every number, indexed from 1-9
number list[10];


bool checkComplete(){
	for (int i = 1; i <= 9; i++){
		if (list[i].count!=9){
			return false;
		}
	}
	return true;
}

void printSudoku() {
	cout << endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << sudoku[i][j] << " ";

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

// solves the sudoku puzzle by boxes
void solver(int num) {
	for (int b = 0; b < 9; b++) {
		bool miniBox[3][3];
		if (!list[num].box[b]) {
			for (int r = (b/3)*3; r <= (b/3)*3+2; r++) {
				for (int c = (b%3)*3; c <= (b%3)*3+2; c++) {
					if(list[num].row[r]==true){
						miniBox[r%3][c%3] = true; 
					}
					if(list[num].column[r]==true){
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
					}
				}
			}
			// insert value if only one possible spot
			if (counter == 1){
				sudoku[rCoordinate + (b/3)*3][cCoordinate + (b%3)*3] = num;
				list[num].count++;
				list[num].row[rCoordinate + (b/3)*3] = true;
				list[num].column[cCoordinate + (b%3)*3] = true;
				list[num].box[b] = true;
			}	
		}
	}
}

int main() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> sudoku[i][j];
			if(sudoku[i][j] != 0){
				list[sudoku[i][j]].count++;
				list[sudoku[i][j]].row[i] = true;
				list[sudoku[i][j]].column[j] = true;
			}
		}
	}
	printSudoku();
	return 0;
}
