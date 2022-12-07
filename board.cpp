// Board CPP File
#include<iostream>
#include<cstdlib>
#include <sstream>
#include <stdlib.h>
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
void pushSquares();

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
    bool keepPlaying = false;
    spawnSquare();
    printBoard();

    while(boardIsValid() == 1 || boardIsValid() == 2) 
    {
        if(boardIsValid() == 2 && keepPlaying == false)
        {
            char keepPlayingInput;
            cout << "YOU WIN! Would you like to keep playing?";
            while(keepPlayingInput != 'T' || keepPlayingInput != 'F')
            {
                cin >> keepPlayingInput;
            }
            if(keepPlayingInput == 'T')
            {
                keepPlaying == true;
            }
            else if(keepPlayingInput == 'F')
            {
                exit(0);
            }
        }
        badInput = 1;
        bool movedBool = false;
        while(badInput || movedBool == false) {
            badInput = 0;
            cout << "Enter move (w:up, a:left, s:down, d:right): ";
            cin >> input;
            cout << endl;

            switch(input) {
                case 'w':
                    movedBool = moveUp();
                    break;
                case 'a':
                    movedBool = moveLeft();
                    break;
                case 's':
                    movedBool = moveDown();
                    break;
                case 'd':
                    movedBool = moveRight();
                    break;
                default:
                    cout << "Invalid input." << endl;
                    badInput = 1;
                    break;
            }
            if(movedBool == false)
            {
                printBoard();
            }
        }
        //cout << flush;
        //system("CLS");
        spawnSquare();
        printBoard();
    }
    cout << "You lost!";
}

// to merge, push everything to side, merge, then push again.

bool Board::moveLeft() {
    int i = 0;
    i += pushSquares();
    i += combineSquares();
    i += pushSquares();
    if(i > 0)
    {
        return true;
    }
    return false;
}

bool Board::moveRight() {
    bool movedBool;
    flipHorizontally();
    movedBool = moveLeft();
    flipHorizontally();
    return movedBool;
}

bool Board::moveUp() {
    bool movedBool;
    flipDiag();
    movedBool = moveLeft();
    flipDiag();
    return movedBool;
}

bool Board::moveDown() {
    //VV --This also works the same, not important but I thought it was interesting-- VV
    // flipHorizontally();
    // flipDiag();
    // flipHorizontally();
    // moveLeft();
    // flipHorizontally();
    // flipDiag();
    // flipHorizontally();
    bool movedBool;
    flipAntiDiag();
    movedBool = moveLeft();
    flipAntiDiag();
    return movedBool;
}

void Board::incrementScore(int val) {
    score += val;
}

int Board::boardIsValid() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (grid[i][j] == 2048)
            {
                return 2;
            }
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
            if (grid[i][j] == grid[i+1][j]) return 1;
        } 
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
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
    cout << "Score : " << score << endl;
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

bool Board::pushSquares() {
    bool moveBool = false;
    for (int i = 0; i < 4; i++)
    {
        int firstEmptyPos = 0;
        for (int j = 0; j < 4; j++)
        {
            if(grid[i][j] != 0)
            {
                if(firstEmptyPos != j)
                {
                    grid[i][firstEmptyPos] = grid[i][j];
                    grid[i][j] = 0;
                    moveBool = true;
                }
                firstEmptyPos++;
            }
        }
    }
    return moveBool;
}

bool Board::combineSquares(){
    bool moveBool = false;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(grid[i][j] == grid[i][j+1] && grid[i][j] != 0)
            {
                grid[i][j] = grid[i][j] * 2;
                grid[i][j+1] = 0;
                moveBool = true;
                incrementScore(grid[i][j]);
            }
        }
    }
    return moveBool;
}

void Board::flipHorizontally(){
    int tempGrid[4][4];
    for(int i = 0; i < 4; i++)
    {
        int reverseJ = 3;
        for(int j = 0; j < 2; j++)
        {
            tempGrid[i][reverseJ] = grid[i][reverseJ];
            grid[i][reverseJ] = grid[i][j];
            grid[i][j] = tempGrid[i][reverseJ];
            reverseJ--;
            //cout << "j " << j << endl;
        }
    }
}

void Board::flipDiag(){
    int tempGrid[4][4];
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            tempGrid[i][j] = grid[j][i];
        }
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            grid[i][j] = tempGrid[i][j];
        }
    }
}

void Board::flipAntiDiag(){
    int tempGrid[4][4];
    int reverseJ = 3; 
    for(int i = 0; i < 4; i++)
    {
        int reverseI = 3;
        for(int j = 0; j < 4; j++)
        {
            tempGrid[i][j] = grid[reverseI][reverseJ];
            reverseI--;
        }
        reverseJ--;
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            grid[i][j] = tempGrid[i][j];
        }
    }
}