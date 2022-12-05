// Board CPP File
#include<iostream>
#include<cstdlib>
#include <sstream>
#include "board.h"
using namespace std;

/*
Notation: [row][column]
so [1][2] is located at:
0 0 0 0
0 0 1 0
0 0 0 0
0 0 0 0
*/

void printTopLine();
void printEmptyLine();
void printMiddleLine();
void printBottomLine();

Board::Board() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            grid[i][j] = 0;
        }
    }

    srand(time(0));
    score = 0;
    keepPlaying = false;
}

void Board::play() {
    char input;
    bool badInput;
    spawnSquare();
    printBoard();

    while(boardIsValid()) {
        badInput = 1;

        while(badInput) {
            badInput = 0;
            cout << "Enter move (w:up, a:left, s:down, d:right): ";
            cin >> input;
            cout << endl;

            switch(input) {
                case 'w':
                    moveUp();
                break;
                case 'a':
                    moveLeft();
                break;
                case 's':
                    moveDown();
                break;
                case 'd':
                    moveRight();
                break;
                default:
                    cout << "Invalid input." << endl;
                    badInput = 1;
                break;
            }
        }
        spawnSquare();
        printBoard();
    }
}

// to merge, push everything to side, merge, then push again.

bool Board::moveLeft() {    
    for (int i = 0; i < 4; i++) {
        // Shift 1
        for (int j = 2; j >= 0; j--) {
            if (grid[i][j] == 0) {
                grid[i][j] = grid[i][j+1];  // Shift left once if zero to left of square.
                grid[i][j+1] = 0;

                if (j > 0 && grid[i][j-1] == 0) {   // Shifts left a second time in 2002 case.
                    grid[i][j-1] = grid[i][j];
                    grid[i][j] = 0;
                } 
            }
        }

        // Merge / shift if zero.
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i][j+1]) {
                grid[i][j] *= 2;
                grid[i][j+1] = 0;
                incrementScore(grid[i][j]);
            }
            else if (grid[i][j] == 0 && grid[i][j+1] != 0) {
                grid[i][j] = grid[i][j+1];
                grid[i][j+1] = 0;
            }
        }

        // Shift again
        for (int j = 2; j >= 0; j--) {
            if (grid[i][j] == 0) {
                grid[i][j] = grid[i][j+1];
                grid[i][j+1] = 0;
            }
        }
    }
    return 0;
}

bool Board::moveRight() {
    return 0;
}

bool Board::moveUp() {
    return 0;
}

bool Board::moveDown() {
    return 0;
}

void Board::incrementScore(int val) {
    score += val;
}

bool Board::boardIsValid() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (grid[i][j] == 0) {
                return 1;
            }
        }
    }

    // Now check that no squares can merge.
    // Start with horizontals.
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == grid[i][j+1]) return 1;
        } 
    }

    // Check verticals.
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (grid[i][j] == grid[i+1][j]) return 1;
        }
    }

    return 0;
}

void Board::spawnSquare() {
    int randIndex = rand() % 16;
    int val = rand() % 10;

    // randIndex holds randon number 0-15. If slot is not blank, index is incremented until open spot.
    // spawnSquare is always run with at least one open slot since play() checks board at the end of each turn.
    while (grid[randIndex / 4][randIndex % 4] != 0) {
        randIndex = rand() % 16;
    }

    if (val > 0) val = 2;
    else val = 4;

    grid[randIndex / 4][randIndex % 4] = val;
    return;
}

void Board::clearBoard() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            grid[i][j] = 0;
        }
    }

    return;
}

// Rewrote the print board function
// Uses seperate helper functions to print each individual row
// The printf statement finds the number of characters-
//  using string streams
void Board::printBoard() {
    printTopLine();
    for(int i = 0; i < 4; i++)
    {
        printEmptyLine();
        for(int j = 0; j < 4; j++)
        {
            cout << (char)186;
            stringstream ss;
            ss >> grid[i][j];
            ss.seekg(0, ios::end);
            int size = ss.tellg();
            printf("%*d%*s",5-(size/2),grid[i][j],5-size/2,"");
        }
        cout << (char)186 << endl;
        printEmptyLine();
        if(i != 3)
        {
            printMiddleLine();
        }
    }
    printBottomLine();
    cout << endl;
    return;
}

void printTopLine() {
    cout << (char)201;
    for(int j = 0; j < 10; j++)
    {
        cout << (char)205;
    }

    for(int i = 0; i < 3; i++)
    {
        cout << (char)203;
        for(int j = 0; j < 10; j++)
        {
            cout << (char)205;
        }
    }
    cout << (char)187 << endl;
}

void printEmptyLine() {
    for(int i = 0; i < 4; i++)
    {
        cout << (char)186;
        cout << "          ";
    }
    cout << (char)186 << endl;
}

void printMiddleLine() {
    cout << (char)204;
    for(int j = 0; j < 10; j++)
    {
        cout << (char)205;
    }

    for(int i = 0; i < 3; i++)
    {
        cout << (char)206;
        for(int j = 0; j < 10; j++)
        {
            cout << (char)205;
        }
    }
    cout << (char)185 << endl;
}

void printBottomLine() {
    cout << (char)200;
    for(int j = 0; j < 10; j++)
    {
        cout << (char)205;
    }

    for(int i = 0; i < 3; i++)
    {
        cout << (char)202;
        for(int j = 0; j < 10; j++)
        {
            cout << (char)205;
        }
    }
    cout << (char)188 << endl;
}