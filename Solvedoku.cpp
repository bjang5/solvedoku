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

void solver(int num) {
	for (int b = 0; b < 9; b++) {
		if (!list[num].box[b]) {
			for (int r = b/3; r <= b/3+2; r++) {
				for (int c = (b%3)*3; c <= (b%3)*3+2; c++) {
					
				}
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
				if () {

				}
			}
		}
	}
	printSudoku();
	return 0;
}
