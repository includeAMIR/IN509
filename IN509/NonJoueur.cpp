//
//  NonJoueur.cpp
//  IN509
//
//  Created by Amir on 01/01/2017.
//  Copyright © 2017 sll. All rights reserved.
//

#include "NonJoueur.hpp"
#include <time.h>
/*NonJoueur::NonJoueur(Terrain t){
  terrain en attente
}*/

NonJoueur::NonJoueur(std::string nom, int x, int y , int dmg, int mana, int gold, int vie){
    this->nom = nom;
    this->pos = new Position(x,y);
    this->dmg = dmg;
    this->mana = mana;
    this->gold = gold;
    this->vie = vie;
    //this->Symbole = symbole;
    setNbrpnj(1);
}
int NonJoueur::getNbrpnj(){return nbrpnj;}
void NonJoueur::setNbrpnj(int nbrpnj) { this->nbrpnj = nbrpnj;}
//void NonJoueur::setSymbole(char c) {this->Symbole = c;}
int NonJoueur::getmana() {return this->mana;}
int NonJoueur::getvie() {return this->vie;}
int NonJoueur::getdmg() {return this->dmg;}
int NonJoueur::getgold() {return this->gold;}
//char NonJoueur::getSymbole() { return this->Symbole;}
int NonJoueur::getposx(){ return pos->getx();}
int NonJoueur::getposy(){ return pos->gety();}
std::string NonJoueur::getnom() {return this->nom;}
void NonJoueur::setmana(int x) {this->mana = x;}
void NonJoueur::setvie(int x) {this->vie = x;}
void NonJoueur::setdmg(int x) {    this->dmg = x;}
void NonJoueur::setpos(int x, int y) {this->pos = new Position(x,y);}

std::string NonJoueur::alea_direction(){
    int i = 0;
    std::string direction;

    int nbgen = 0;
    for(i=0; i<4; i++){
        srand(time(NULL));
        nbgen = rand()%4+1;
    }

    switch(nbgen){
        case 1 :
            direction = "haut";
            break;
        case 2 :
            direction = "droite";
            break;
        case 3 :
            direction = "bas";
            break;
        case 4 :
            direction = "gauche";
            break;
        default:
            break;
    }
    return direction;
}
void NonJoueur::sedeplacer(std::string direction){
    if(direction == "haut" && this->pos->gety() > 0) pos->sety(getposy()+3);
    if(direction == "bas" && this->pos->gety() <= 24) pos->sety(getposy()-3);
    if(direction == "gauche" && this->pos->getx() > 0) pos->setx(getposx()-3);
    if(direction == "droite" && this->pos->getx() <= 80) pos->setx(getposx()+3);
    if(this->pos->getx() >= 79) this->pos->setx(getposx()-1);
    if(this->pos->gety() >= 24) this->pos->sety(getposy()-1);
}

void NonJoueur::utiliser(int i) {return;}
void NonJoueur::manger(int i){return;}

bool NonJoueur::estmort()
{    if(this->getvie() <= 0)
        return true;
    return false;
}
/*void NonJoueur::attaquer(Joueur *j){
    j->setvie(getvie()-10);
}*/
/*void NonJoueur::isnear(Joueur *j, NonJoueur *m){
    if((j->getposx() == m -> getposx()&&(j->getposy() == m->getposy()))){
        m -> attaquer(j);
    }
}!
*/

