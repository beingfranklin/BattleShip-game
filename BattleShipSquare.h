#ifndef BATTLESHIPSQUARE_H
#define BATTLESHIPSQUARE_H
#include "Ship.h"

class BattleShipSquare
{
private:
    Ship* ship;
    bool isFired;
public:
    BattleShipSquare(){
        ship = NULL;
        isFired = false;
    }
    void reset(){
        ship = NULL;
        isFired = false;
    } 
    bool addShip(Ship* newShip){
        ship=newShip;
        return true;
    }
    char getStatus(){
        if(ship == nullptr){
            if (isFired==true)
                return 'M';
            return 'E';
        }
        else{
            if (isFired==true)
                return 'H';
            return 'S';
        }
    }

    void fire(){
         if(ship == nullptr && !isFired){
             isFired=true;
         }
    }
};

#endif