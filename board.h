// board.h file

class Board {
    public:
        Board();                // The constructor sets grid array values and other member fields to zero.
        void play();            // An entire game of 2048 is executed.

        bool moveLeft();        // These four move methods push all squares towards that direction.
        bool moveRight();       // They return false if no squares move, since no new square should
        bool moveUp();          // spawn unless a square has moved. They also combine two squares of the
        bool moveDown();        // same value into one square of doubled value if two are comined.

        bool pushSquares();
        bool combineSquares();
        
        void flipHorizontally();
        void flipDiag();
        void flipAntiDiag();

        void incrementScore(int);
        int boardIsValid();    // This function checks whether there is another move possible, or if the game should end.
        void spawnSquare();     // Randomly selects an open spot in the board and randomly selects 2 or 4 to spawn in that square.
        void clearBoard();      // Sets all values and score back to zero for a new game to be played.
        void printBoard();      // Prints the board and current score.

    private:
        int grid[4][4];         // Holds all values in the board.
        int score;              // Score starts at zero and when two squares combine into one square of doubled value,
                                // the new square's value is added to the score.
        bool keepPlaying;       // User's input for whether they want to quit or not.
};
