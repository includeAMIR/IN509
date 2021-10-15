//
//  Joueur.hpp
//  IN509
//
//  Created by Amir on 01/01/2017.
//  Copyright © 2017 sll. All rights reserved.
//

#ifndef Joueur_hpp
#define Joueur_hpp

#include <stdio.h>
#include "Personnage.hpp"
#include <string>
#include "Position.hpp"
#include "NonJoueur.hpp"
#include <math.h>
#define PI 3.14159265
class Joueur : public Personnage {
   // public Inventaire sac; Inventaire pas encore pret
protected:
    std::string symbole = "X";
    bool equiped = false;
    bool alive = true;
    Position *pos;
    //Terrain terrain; Terrain en attente
public:
    //Joueur(Terrain t); Terrain en attente
    Joueur(std::string nom,int x,int y,int mana,int dmg,int gold);
    bool isAlive();
    void setAlive(bool alive);
    bool isEquiped();
    void setEquiped(bool equiped);
    
    //getters
    
    int getmana();
    int getvie();
    int getdmg();
    int getgold();
    int getposx();
    int getposy();
    std::string getnom();
    std::string getSymbole();
    
    //seters
    
    void setSymbole(std::string symbole);
    void setmana(int x);
    void setvie(int x);
    void setdmg(int x);
    void setpos(int x, int y);
    void addgold(int x);
    
    //methodes
    
    void sedeplacer(std::string direction);
    bool angle_diff(int arg0, int arg1, std::string direction);
    void attaquer(Position *p, Joueur *j,float arg0,float arg1,std::string direction,NonJoueur *m);
    //void prendre(std::vector<Item> obj); Item en Attente
    void utiliser(int i);
    void manger(int i);
    bool estmort();
    void equip();
    //float angle_joueur_clique(Joueur *j1, Position *clique);
    float teta(Position *clique, std::string direction, Joueur *j);
    int * calcul_vect_jj(Joueur *j, Position *p);
    ~Joueur();
};
#endif /* Joueur_hpp */
