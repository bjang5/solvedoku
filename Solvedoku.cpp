#include <iostream>

using namespace std;

// stores the entirety of the puzzle
int sudoku[9][9];	

// represents each number's attributes
struct number {	
	int count = 0;

	// true equates to filled position, false equates to empty position
	bool row [9] = {false, false,false,false,false,false,false,false,false};
	bool column [9] = {false, false,false,false,false,false,false,false,false};
	bool box [9] = {false, false,false,false,false,false,false,false,false};
};

// list every number, indexed from 1-9
number list[10];

void printNum(int num) {
	for (int i = 0; i < 9; i++) {
		cout << "Row " << i+1 << ": " << list[num].row[i] << endl;
		cout << "Column " << i+1 << ": " << list[num].row[i] << endl;
		cout << "Box " << i+1 << ": " << list[num].row[i] << endl;
	}
}

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
void solver(int num, int boxNum) {
	/*cout << num << " " << boxNum << endl;*/
	bool miniBox[3][3];
	// initialization of miniBox
	for (int boxIs = 0; boxIs < 3; boxIs++) {
		for (int sboxJ = 0; sboxJ < 3; sboxJ++) {
			miniBox[boxIs][sboxJ] = false;
		}
	}

	if (!(list[num].box[boxNum])) {
		for (int r = (boxNum/3)*3; r <= (boxNum/3)*3+2; r++) {
			for (int c = (boxNum%3)*3; c <= (boxNum%3)*3+2; c++) {
				if(list[num].row[r]==true){
					miniBox[r%3][c%3] = true;
				} else if(list[num].column[c]==true){
					miniBox[r%3][c%3] = true; 
				} else if(sudoku[r][c]!=0) {
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
			sudoku[rCoordinate + (boxNum/3)*3][cCoordinate + (boxNum%3)*3] = num;
			list[num].count++;
			list[num].row[rCoordinate + (boxNum/3)*3] = true;
			list[num].column[cCoordinate + (boxNum%3)*3] = true;
			list[num].box[boxNum] = true;
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

				if(i>=0&&i<=2&&j>=0&&j<=2){
					list[sudoku[i][j]].box[0] = true;
				} else if(j>2&&j<=5&&i>=0&&i<=2){
					list[sudoku[i][j]].box[1] = true;
				} else if(j>5&&j<=8&&i>=0&&i<=2){
					list[sudoku[i][j]].box[2] = true;
				}else if(j>=0&&j<=2&&i>2&&i<=5){
					list[sudoku[i][j]].box[3] = true;
				}else if(j>2&&j<=5&&i>2&&i<=5){
					list[sudoku[i][j]].box[4] = true;
				}else if(j>5&&j<=8&&i>2&&i<=5){
					list[sudoku[i][j]].box[5] = true;
				}else if(j>=0&&j<=2&&i>5&&i<=8){
					list[sudoku[i][j]].box[6] = true;
				}else if(j>2&&j<=5&&i>5&&i<=8){
					list[sudoku[i][j]].box[7] = true;
				}else if(j>5&&j<=8&&i>5&&i<=8){
					list[sudoku[i][j]].box[8] = true;
				}
			}
		}
	}

	//check box number values
	for(int i = 0; i < 9; i++){
		for (int num = 1; num <=9; num++){
			cout << "Number: " << num ; 
			cout << " Box Number: " << i << " is " << list[num].box[i] << endl;
		}
	}

	// before solve
	printSudoku();
	
	for (int i = 0; i < 1000; i++){
		for (int num = 1; num <= 9; num++) {
				for (int box = 0; box < 9; box++) {
					solver(num,box);
			}
		}
	}

	cout << endl << endl << endl;
	// after solve
	printSudoku();

	//check box number values
	for(int i = 0; i < 9; i++){
		for (int num = 1; num <=9; num++){
			cout << "Number: " << num ; 
			cout << " Box Number: " << i << " is " << list[num].box[i] << endl;
		}
	}

	return 0;
}


/*TEST
5 3 4 6 7 8 9 1 2 6 7 2 1 9 5 0 4 8 0 9 8 3 4 0 5 6 7 8 5 9 7 6 1 4 2 3 0 2 6 8 0 3 7 9 1 7 1 3 9 2 4 8 5 0 9 6 1 5 3 7 2 8 4 2 8 0 4 1 9 6 3 5 3 4 5 2 0 6 1 7 0

0 8 0 0 0 0 2 0 0 0 0 0 0 8 4 0 9 0 0 0 6 3 2 0 0 1 0 0 9 7 0 0 0 0 8 0 8 0 0 9 0 3 0 0 2 0 1 0 0 0 0 9 5 0 0 7 0 0 4 5 8 0 0 0 3 0 7 1 0 0 0 0 0 0 8 0 0 0 0 4 0
*/

