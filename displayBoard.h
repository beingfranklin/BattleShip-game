#ifndef DISPLAYBOARD_H
#define DISPLAYBOARD_H

class displayBoard
{
public:
    virtual ~displayBoard();
    virtual void displayBoardState(int fireCount, char hitBoard[8][8]);
};

#endif