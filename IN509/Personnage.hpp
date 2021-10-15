//
//  Personnage.hpp
//  IN509
//
//  Created by Amir on 01/01/2017.
//  Copyright © 2017 sll. All rights reserved.
//

#ifndef Personnage_hpp
#define Personnage_hpp

#include <stdio.h>
#include <string>
#include "Position.hpp"

class Personnage {
    //Attributs
    protected :
    int vie;
    int dmg;
    int mana;
    int gold;
    const int vieMax = 100;
    const int manaMax = 10;
    const int goldMax = 1000;
    char Symbole;
    std::string nom = "";
    Position *pos;
    //String symbole;
    //Inventaire sac;
    
    //getters
    public:
     int getmana();
     int getvie();
     int getdmg();
     int getgold();
    // Position getpos();
     std::string getnom();
    //setters
    public :
     void setmana(int x);
     void setvie(int x);
     void setdmg(int x);
     void setpos(int x, int y);
    
};

#endif /* Personnage_hpp */
