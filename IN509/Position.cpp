//
//  Position.cpp
//  IN509
//
//  Created by Amir on 01/01/2017.
//  Copyright © 2017 sll. All rights reserved.
//
#include "Position.hpp"
#include <time.h>
#include <stdlib.h>

Position::Position(){
    this->x = 0;
    this->y = 0;
}
Position::Position(int x, int y){
    this->x = x;
    this->y = y;
}
int Position::getx(){
    return this->x;
}
int Position::gety(){
    return this->y;
}
void Position::setx(int x){
     this->x = x;
}
void Position::sety(int y){
    this->y = y;
}
//bool Position::equals(Object obj){} surcharge de l'operateur nécessaire afin de comparer des positions
bool Position::isnear(Position p){
    if(this->x == (p.getx()+1))
        return true;
    if(this->x == (p.gety()-1))
        return true;
    if(this->y == (p.gety()+1))
        return true;
    if(this->y == (p.gety()-1))
        return true;
    return false;
}
int Position::alea(int const min, int const max){
    int aleaval;
    srand(time(NULL));
    aleaval = rand()%max+min;
    return aleaval;
}




/*Position Position::generatepos(Terrain tab)           en com car besoin du terrain pas encore dispo
{
    for (int i = 0; i < tab.getFondations().length; i++) {
        for (int j = 0; j < tab.getFondations().length; j++) {
            int x = alea(0,80);
            int y = alea(0,24);
            if(tab.getFondations()[x][y] != Fondations.MURS)
                return new Position(x,y);
        }
    }
    return null;
}*/
