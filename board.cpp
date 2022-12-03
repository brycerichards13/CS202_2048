// Board CPP File
#include<iostream>
#include<cstdlib>
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
            cout << "Enter move (w:up, a:left, s:down, d:left): ";
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

// Notes on print: Using ascii values 205 for horizontal lines, 186 for verticals, and 
// similar "pipe" looking characters. Max number possible in 2048 is 131072, so each
// digit gets 10 spaces; 6 for number, 2 on each side to space it out.
// So, each line is (10*4) + 5 characters long, so 45.
// Height of board is not decided yet :shrug:

// Okay, this looks like shit. Feel free to delete all of it lmao. I'll probably make a separate function
// for each part, cuz this is so confusing to write / read...
void Board::printBoard() {
    char vert = 186;

    cout << "Score: " << score << endl;
    
    // First line is printed.
    cout << (char)201;
    for (int i = 0; i < 43; i++) {
        cout << (char)205;
    }
    cout << (char)187 << endl;

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 1; j++) {
            printf("%c%10c%c%10c%c%10c%c%10c%c\n", vert, ' ', vert, ' ', vert, ' ', vert, ' ', vert);
        }

        for (int j = 0; j < 4; j++) {
            if (grid[i][j] == 0) printf("%10s", " ");
            else printf("%10d" ,grid[i][j]);
        }

        for (int j = 0; j < 1; j++) {
            printf("%c%10c%c%10c%c%10c%c%10c%c\n", vert, ' ', vert, ' ', vert, ' ', vert, ' ', vert);
        }
    }    
    return;
}
