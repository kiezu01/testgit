#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>

using namespace std;

void TextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoXY(int column, int line) {
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

char treeKeys[] = {'0', '~', '-', '.', '.', '~', '-', '~', '-', '*', '.', '.', '~', '-', '.', '.', '~', '-', '.', '.', '~', '-', '@', '.', '.', '~', '-', '.', '.', '~', '-', '.', '.', '~', '-'};
int foliageWitch = 70;
const int ROWS = 45;
const int COLS = 200;
const int NRANDOM = 3;
const int NTIMES = 450;
const double WAIT = 200;
const char SNOW = '*';

int randomColor() {
	int colorArr[] = {14, 12, 9, 13};
	int n = sizeof(colorArr) / sizeof(int);
	return colorArr[rand() % n];
}

bool randomStar() {
	return rand() % 200 == 1;
}

void displayTree(char treeMap[ROWS][COLS], int treeMapColor[ROWS][COLS]) {
	int treeKeyCount = sizeof(treeKeys) / sizeof(treeKeys[0]);
	int pfCount = 0;

	TextColor(10);
	for (int i = 0; i < ROWS; i++) {
		if (i < foliageWitch) {
			int r = -1;
			for (int j = i; j < foliageWitch; j++) {
				r++;
				char c;
				if (i < ROWS / 2) {
					if (randomStar()) {
						c = '+';
						TextColor(14);
					} else {
						c = ' ';
					}
				}
				cout << c;
				treeMap[i][r] = c;
				treeMapColor[i][r] = 14;
			}
			int r2 = r;
			for (int j = 0; j < COLS - r2; j++) {
				r++;
				if (j < (2 * i - 1)) {
					char c = treeKeys[pfCount % treeKeyCount];
					int cl = (c == '0' || c == '*' || c == '@') ? randomColor() : 10;
					TextColor(cl);
					cout << c;
					treeMap[i][r] = c;
					treeMapColor[i][r] = cl;
					pfCount++;
				} else {
					char c;
					if (i < ROWS / 2) {
						if (randomStar()) {
							c = '+';
							TextColor(14);
						} else {
							c = ' ';
						}
					}
					cout << c;
					treeMap[i][r] = c;
					treeMapColor[i][r] = 14;
				}
			}
		} else {
			for (int k = 0; k < COLS; k++) {
				cout << ' ';
				treeMap[i][k] = ' ';
			}
			cout << endl;
		}
	}
	TextColor(8);
	for (int k = 0; k < COLS; k++) {
		cout << '_';
	}
}

void plot(char m[ROWS][COLS], int topRow) {
	TextColor(15);
	for (int i = 0; i < ROWS; i++) {
		int row = (topRow + i) % ROWS;
		for (int j = 0; j < COLS; j++) {
			if (m[row][j] == SNOW) {
				gotoXY(j, i);
				cout << m[row][j];
			}
		}
	}
	gotoXY(COLS, ROWS);
}

void clrscr(char treeMap[ROWS][COLS], int treeMapColor[ROWS][COLS], char m[ROWS][COLS], int topRow, int t) {
	for (int i = 0; i < ROWS; i++) {
		int row = (topRow + i) % ROWS;
		for (int j = 0; j < COLS; j++) {
			if (m[row][j] == SNOW) {
				gotoXY(j, i);
				if (t < NTIMES / 2 || treeMap[i][j] == '+') {
					TextColor(treeMapColor[i][j]);
				} else {
					TextColor(15);
				}
				cout << treeMap[i][j];
			}
		}
	}
}

void waitTime(double waitSecs) {
	Sleep(waitSecs);
}

int main() {
	srand(time(NULL));
	TextColor(15);

	int topRow = 0;
	char m[ROWS][COLS] = { ' ' };
	char treeMap[ROWS][COLS] = { ' ' };
	int treeMapColor[ROWS][COLS] = {};

	displayTree(treeMap, treeMapColor);
	Sleep(3000);

	for (int t = 0; t < NTIMES; t++) {
		plot(m, topRow);
		waitTime(WAIT);
		clrscr(treeMap, treeMapColor, m, topRow, t);
		topRow -= 1;
		if (topRow < 0) {
			topRow = ROWS - 1;
		}
		for (int j = 0; j < COLS; j++) {
			m[topRow][j] = ' ';
		}
		for (int r = 0; r < NRANDOM; r++) {
			m[topRow][rand() % COLS] = SNOW;
		}
	}
}

