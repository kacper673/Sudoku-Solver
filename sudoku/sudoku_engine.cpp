#include "sudoku.h"
#include <vector>


void sudoku::exampleSudoku() {

   
    int exampleValue[] = {
        5, 3, 0, 0, 7, 0, 0, 1, 2,
        6, 0, 0, 1, 9, 5, 0, 4, 0,
        0, 9, 8, 0, 0, 2, 0, 6, 0,
        8, 0, 9, 0, 6, 0, 4, 0, 3,
        0, 0, 0, 8, 5, 0, 0, 0, 1,
        7, 0, 0, 9, 2, 0, 8, 0, 6,
        0, 6, 1, 0, 0, 0, 2, 8, 0,
        0, 0, 0, 4, 1, 9, 0, 0, 5,
        3, 0, 5, 0, 0, 0, 0, 7, 9
    };

    int k = 0;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (k >= 81) break;
            tab[i][j] = exampleValue[k];
            k++;
        }
    }

}

void sudoku::printSudoku() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << tab[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void findingSpaces(sudoku& toSolve, int tab[9][9]) {
    toSolve.spaces.clear();
    //znajdywanie pustych miejsc

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (tab[i][j] == 0) {
                toSolve.index.x = i;
                toSolve.index.y = j;
                toSolve.spaces.push_back(toSolve.index);
            }
        }
    }
}
bool checkRowsCols(int tab[9][9], int x, int y) {

    //sprawdzenie dla wiersza (iteruje przez kolumny)
    for (int j = 0; j < 9; j++) {
        if (tab[x][y] == tab[x][j] && y != j && tab[x][y] != 0) {
            //std::cout << "Wartosci w wierszu sie powtarzaja dla: x = " << x << " y = " << y << " oraz x = " << x << " y = " << j <<" wartosc to: "<<toSolve.tab[x][j]<< std::endl;
            //std::cout << "Wartosci powtarzaja sie w wierszu: " << x << std::endl;
            return false;
        }
    }
  
    //sprawdznie dla kolumny (iteruje przez wiersze)
    for (int i = 0; i < 9; i++) {
        if (tab[x][y] == tab[i][y] && x != i && tab[x][y] != 0) {
            //std::cout << "Wartosci w kolumnie sie powtarzaja dla: x = " << x << " y = " << y << " oraz x = " << i << " y = " << y <<" wartosc to: " << toSolve.tab[i][y] << std::endl;
           // std::cout << "Wartosci powtarzaja sie w kolumnie: " << y << std::endl;
            return false;
        }
    }
    return true;
}

bool checkBoxes(int tab[9][9]) {
    int beginRow = 0;
    int beginCol = 0;
    int n = 0;
    
    for (int beginRow = 0; beginRow < 9; beginRow += 3) {
        for (int beginCol = 0; beginCol < 9; beginCol += 3) {
            for (int susVal = 1; susVal < 10; susVal++) {
                n = 0;
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (tab[beginRow + i][beginCol + j] == susVal) {
                            n++;
                        }
                        if (n == 2) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}


bool isValid(int tab[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!checkRowsCols(tab, i, j)) {
                return false;
            }
        }
    }

    if (!checkBoxes(tab)) { return false; };
    

    return true;

}

void solve(sudoku& toSolve) {
    auto it = toSolve.spaces.begin();
    
    while (it != toSolve.spaces.end()) {
        if (toSolve.tab[it->x][it->y] == 0) {
            std::lock_guard<std::mutex> lock(toSolve.m);
            toSolve.tab[it->x][it->y] = 1;
           // std::cout << "Na miejscu (" << it->x << ", " << it->y << ")" << " wstawilem liczbe " << toSolve.tab[it->x][it->y] << std::endl;
        }
        else {
            std::lock_guard<std::mutex> lock(toSolve.m);
            toSolve.tab[it->x][it->y]++;
            //std::cout << "Na miejscu (" << it->x << ", " << it->y << ")" << " wstawilem liczbe " << toSolve.tab[it->x][it->y] << std::endl;
        }

        if (toSolve.functionName == "UI") { std::this_thread::sleep_for(std::chrono::milliseconds(2)); }

        if (toSolve.tab[it->x][it->y] > 9) {
            std::lock_guard<std::mutex> lock(toSolve.m);
            toSolve.tab[it->x][it->y] = 0;
            if (it == toSolve.spaces.begin()) {
                //std::cout << "Sudoku nie rozwiazywalne" << std::endl;
                return;
            }
            it--;
            continue;
        }

        if (isValid(toSolve.tab)) { it++; };
    }
    std::cout << std::endl;
    std::cout << "Sudoku has been solved" << std::endl;
}

bool hasUniqueSolution(sudoku& toSolve,int tempSudoku[9][9]) {
    
    
    auto it = toSolve.spaces.begin();
    int solutions_num = 0;
    while (it != toSolve.spaces.end()) {

        tempSudoku[it->x][it->y]++;
       // std::cout << "Na miejscu (" << it->x << ", " << it->y << ")" << " wstawilem liczbe " << tempSudoku[it->x][it->y] << std::endl;

        if (tempSudoku[it->x][it->y] > 9) {
            tempSudoku[it->x][it->y] = 0;
            if (it == toSolve.spaces.begin() && toSolve.spaces.size() == 1) {
                return true;
            }
            if (it == toSolve.spaces.begin()) {
                //std::cout << "Sudoku nie rozwiazywalne" << std::endl;
                return true;
            }
            it--;
            continue;
        }

        bool valid = isValid(tempSudoku); 

        if (valid) { it++; }
        if (valid && it == toSolve.spaces.end()) {
            solutions_num++;
            if (solutions_num > 2) {
                //std::cout << "Ilosc rozwiazan "<<solutions_num<< std::endl; 
                return false;
            }
                it--;
                continue;
            
        } 
    }
    std::cout <<"Ilosc rozwiazan: "<< solutions_num << std::endl; 
    return true;
}

void generateEmpty(sudoku& toSolve) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            toSolve.tab[i][j] = 0;

            //std::cout << toSolve.tab[i][j] << std::endl;

        }
    }
}

void generateRand(sudoku& toSolve) {
    srand(time(nullptr));
    int number_of_spaces = rand() % 11 + 20;
    int x, y;
    int tempValue = 0;
    int removed = 0;
    int tempSudoku[9][9];

    generateEmpty(toSolve);
    findingSpaces(toSolve, toSolve.tab);
    solve(toSolve);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            tempSudoku[i][j] = toSolve.tab[i][j];
        }
    }
    findingSpaces(toSolve, tempSudoku);
    
    toSolve.printSudoku();
    std::cout << std::endl;

    while (removed < number_of_spaces) {
        x = rand() % 9;
        y = rand() % 9;

        if (toSolve.tab[x][y] != 0) {
            tempValue = toSolve.tab[x][y];
            toSolve.tab[x][y] = 0;
            tempSudoku[x][y] = 0;


            findingSpaces(toSolve, tempSudoku); 
            std::cout << std::endl;
            if (hasUniqueSolution(toSolve, tempSudoku)) {
                removed++;
            }

            else {
                toSolve.tab[x][y] = tempValue;
                tempSudoku[x][y] = tempValue;
            }
        }
    }
    std::cout << "Random Sudoku " << std::endl;
    toSolve.printSudoku();
}