/* BOARD_H */

#ifndef BOARD_H
#define BOARD_H
// #include "displayBoard.h"

class Board 
{
private:
    char board[8][8];

public:
    virtual ~Board();   
    // void printBoard(char board[8][8]);
    void resetShipBoard(char shipBoard[8][8]);
};

#endif /* BOARD_H */