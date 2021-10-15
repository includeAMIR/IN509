//
//  NonJoueur.hpp
//  IN509
//
//  Created by Amir on 01/01/2017.
//  Copyright © 2017 sll. All rights reserved.
//

#ifndef NonJoueur_hpp
#define NonJoueur_hpp
#include <iostream>
#include <stdio.h>
#include "Personnage.hpp"
#include <string>
#include "Position.hpp"
#define VIE 100

class NonJoueur : public Personnage{
    private :
    int nbrpnj;
    //Terrain t; Terrain en cours d'implementation
    public :
    //NonJoueur(Terrain t);
    NonJoueur(std::string nom, int x, int y , int dmg, int mana, int gold,int vie);
    int getNbrpnj();
    void setNbrpnj(int nbrpnj);
    //void setSymbole(char c);
    int getmana();
    int getvie();
    int getdmg();
    int getgold();
    //char getSymbole();
    int getposx();
    int getposy();
    std::string getnom();
    void setmana(int x);
    void setvie(int x);
    void setdmg(int x);
    void setpos(int x, int y);
    void sedeplacer(std::string direction);
    // void attaque(Joueur j);
    //void prendre(std::vector<Item> obj); item en attente
    void utiliser(int i);
    void manger(int i);
    bool estmort();
    //void attaquer(Joueur *j);
    std::string alea_direction();
    //void isnear(Joueur *j, NonJoueur *m);
    
};
/*note a moi meme j'ai retiré color penser a le faire dans joueur*/

#endif /* NonJoueur_hpp */
