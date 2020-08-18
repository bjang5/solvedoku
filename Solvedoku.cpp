#include <iostream>

using namespace std;

// stores the entirety of the puzzle
int sudoku[9][9];	

// represents each number's attributes
struct number {	
	int count = 0;
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

int main() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> sudoku[i][j];
			if (sudoku[i][j] == 1) {
				list[1].count++;
			}
			else if (sudoku[i][j] == 2) {
				list[2].count++;
			}
			else if (sudoku[i][j] == 3) {
				list[3].count++;
			}
			else if (sudoku[i][j] == 4) {
				list[4].count++;
			}
			else if (sudoku[i][j] == 5) {
				list[5].count++;
			}
			else if (sudoku[i][j] == 6) {
				list[6].count++;
			}
			else if (sudoku[i][j] == 7) {
				list[7].count++;
			}
			else if (sudoku[i][j] == 8) {
				list[8].count++;
			}
			else if (sudoku[i][j] == 9) {
				list[9].count++;
			}
		}
	}
	printSudoku();
	return 0;
}
