#ifndef PLAYER_H
#define PLAYER_H
// #include "displayBoard.h"

class Player
{
private:
    char shipBoard[8][8];
public:

    virtual ~Player();   
    void displayBoardState(int fireCount, char hitBoard[8][8]);
    void getPlayerName(char &playerName);
    void fireShip(char playerName, char hitBoard[8][8], char shipBoard[8][8], int totalCells);
    bool checkWon(int hitCells, int totalCells); 
};

#endif