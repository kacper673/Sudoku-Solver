#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <mutex>
class sudoku {
public:

	int tab[9][9];

	struct indexes {
		int x;
		int y;
	}index;

	std::vector<indexes> spaces;
	std::string functionName;

	void exampleSudoku();
	void printSudoku();

	std::mutex m;
	

};
//solving
void findingSpaces(sudoku& toSolve, int tab[9][9]);
bool checkRowsCols(int tab[9][9], int x, int y);
bool checkBoxes(int tab[9][9]);
bool isValid(int tab[9][9]);
void solve(sudoku& toSolve);
//random sudoku
bool hasUniqueSolution(sudoku& toSolve, int tempSudoku[9][9]);
void generateEmpty(sudoku& toSolve);
void generateRand(sudoku& toSolve);

#endif
