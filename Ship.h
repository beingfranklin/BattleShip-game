#ifndef SHIP_H
#define SHIP_H
#include <string>
using namespace std;

class Ship
{
private:
    int size,hits;
    string type;
public:
    Ship(int newSize,string newType){
        size=newSize;
        type=newType;
        hits=0;
    }
    bool isSunk(){
        if(hits==size)
            return true;
        return false;
    }
    void hit(){
        if(!isSunk()){
            ++hits;
        }
    }
};

#endif