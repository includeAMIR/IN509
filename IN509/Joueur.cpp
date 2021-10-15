//
//  Joueur.cpp
//  IN509
//
//  Created Amir on 01/01/2017.
//  Copyright © 2017 sll. All rights reserved.
//

#include "Joueur.hpp"

/*Joueur::Joueur(Terrain t)         plusieurs choses reste a implemeter avant
{
    this->nom = "Player";
    this->vie = 100;
    this->pos = Position::generatepos(t);
    this->mana = 100;
    this->dmg = 5;
    this->gold = 100;
    this->sac = new Inventaire();
    this->c = new Color(255,255,0);
    this->terrain = t;
    
}*/
Joueur::Joueur(std::string nom,int x,int y,int mana,int dmg,int gold){
    this->nom = nom;
    this->vie = 100;
    this->pos =   new Position( x, y);
    this->mana = mana;
    this->dmg = dmg;
    this->gold = gold;
    
    //this->sac = new Inventaire(); inventaire en attente
}
bool Joueur::isAlive(){
    return alive;
}
void Joueur::setAlive(bool alive){
    this->alive = alive;
}
bool Joueur::isEquiped(){
    return equiped;
}
void Joueur::setEquiped(bool equiped) {
    this->equiped = equiped;
}
int Joueur::getmana(){
    return this->mana;
}
//get
int Joueur::getvie(){ return this->vie;}
int Joueur::getdmg(){ return this->dmg;}
int Joueur::getgold(){ return this->gold;}
//Color Joueur::getColor(){ return this->c;} en attente de color
int Joueur::getposx(){ return pos->getx();}
int Joueur::getposy(){ return pos->gety();}
std::string Joueur::getnom() { return this->nom;}
std::string Joueur::getSymbole() {return symbole;}
//set
void Joueur::setSymbole(std::string symbole) { this->symbole = symbole;}
void Joueur::setmana(int x){ this->mana = x;}
void Joueur::setvie(int x){this->vie = x;}
void Joueur::setdmg(int x){this->dmg = x;}
//void Joueur::setColor(Color c) { this->c = c;} Color en attente
void Joueur::setpos(int x, int y){this->pos = new Position(x,y);}
void Joueur::addgold(int x){this->gold += x;}
//methodes
void Joueur::sedeplacer(std::string direction)
{
    int i = 0;
    while (i<3){
        
        if(direction == "haut" && this->pos->gety() > 0) pos->sety(getposy()+1);
        if(direction == "bas" && this->pos->gety() <= 24) pos->sety(getposy()-1);
        if(direction == "gauche" && this->pos->getx() > 0) pos->setx(getposx()-1);
        if(direction == "droite" && this->pos->getx() <= 80) pos->setx(getposx()+1);
        if(direction == "haut_D" && this->pos->getx() <= 80) {
            pos->setx(getposx()+1);
            pos->sety(getposy()+1);
        }
        if(direction == "haut_G" && this->pos->getx() <= 80) {
            pos->setx(getposx()-1);
            pos->sety(getposy()+1);
        }
        if(direction == "bas_D" && this->pos->getx() <= 80) {
            pos->setx(getposx()+1);
            pos->sety(getposy()-1);
        }
        if(direction == "bas_G" && this->pos->getx() <= 80) {
            pos->setx(getposx()-1);
            pos->sety(getposy()-1);
        }

        i++;
    }
}
bool Joueur::angle_diff(int arg0,int arg1, std::string direction){
    //arg0 et arg1 en degrées
    //arg0 toujours 90 arg1 valeur de retour de la methode teta
    int diff_angle;
    diff_angle = ((((arg0 - arg1) % 360) + 540) % 360) - 180;
    if(direction == "haut"){
        if((diff_angle < 315 && diff_angle < 360) || diff_angle > 45){
            std::cout << "ne peut pas tirer dans cette direction hors angle de tir ";
            return false;
        }
    }
    else if (direction == "droite"){
        if(diff_angle < 45 || diff_angle > 135){
            std::cout << "ne peut pas tirer dans cette direction hors angle de tir ";
            return false;
        }
    }
    else if (direction == "bas"){
        if(diff_angle < 135 || diff_angle > 175){
            std::cout << "ne peut pas tirer dans cette direction hors angle de tir ";
            return false;
        }

    }
    else if (direction == "gauche"){
        if(diff_angle < 175 || diff_angle > 265){
            std::cout << "ne peut pas tirer dans cette direction hors angle de tir ";
            return false;
        }
        
    }

    std::cout << "direction Joueur : " << direction << "\n";
    std::cout << "tir vers le " << direction << " donc possible" << "\n";

    return true;
    
}
/*float Joueur::angle_joueur_clique(Joueur *j1, Position *clique){
    int scalair = (j1 -> getposx() * clique -> getx())+(j1 -> getposy() * clique -> gety());
    float norme_vec_j1 = sqrt(pow(j1->getposx(),2)+ pow(j1->getposy(),2));
    float norme_vec_pos = sqrt(pow(clique->getx(),2)+ pow(clique->gety(),2) );
    float cos_teta = scalair /(norme_vec_j1 * norme_vec_pos);
    float teta_rad = (cos_teta * PI/3)/0.5;
    float teta_deg = (teta_rad * 180)/PI;
    return teta_deg;
}*/
float  Joueur::teta (Position *p,std::string direction, Joueur *j){
    int tabj[2];
    if(direction == "haut"){
        tabj[0] = 0;
        tabj[1] = 10;
        int scalair = (tabj[0] * calcul_vect_jj(j,p)[0])+(tabj[1] * calcul_vect_jj(j, p)[1]);
        float norme_vec_j1 = sqrt(pow(tabj[0],2)+ pow(tabj[1],2));
        float norme_vec_pos = sqrt(pow(calcul_vect_jj(j,p)[0],2)+ pow(calcul_vect_jj(j,p)[1],2));
        float cos_teta = scalair /(norme_vec_j1 * norme_vec_pos);
        float teta_rad = (cos_teta * PI/3)/0.5;
        float teta_deg = (teta_rad * 180)/PI;
        return teta_deg;
    }
    if(direction == "droite"){
        tabj[0] = 10;
        tabj[1] = 0;
        int scalair = (tabj[0] * calcul_vect_jj(j,p)[0])+(tabj[1] * calcul_vect_jj(j, p)[1]);
        float norme_vec_j1 = sqrt(pow(tabj[0],2)+ pow(tabj[1],2));
        float norme_vec_pos = sqrt(pow(calcul_vect_jj(j,p)[0],2)+ pow(calcul_vect_jj(j,p)[1],2));
        float cos_teta = scalair /(norme_vec_j1 * norme_vec_pos);
        float teta_rad = (cos_teta * PI/3)/0.5;
        float teta_deg = (teta_rad * 180)/PI;
        return teta_deg;
    }
    if(direction == "bas"){
        tabj[0] = 0;
        tabj[1] = -10;
        int scalair = (tabj[0] * calcul_vect_jj(j,p)[0])+(tabj[1] * calcul_vect_jj(j, p)[1]);
        float norme_vec_j1 = sqrt(pow(tabj[0],2)+ pow(tabj[1],2));
        float norme_vec_pos = sqrt(pow(calcul_vect_jj(j,p)[0],2)+ pow(calcul_vect_jj(j,p)[1],2));
        float cos_teta = scalair /(norme_vec_j1 * norme_vec_pos);
        float teta_rad = (cos_teta * PI/3)/0.5;
        float teta_deg = (teta_rad * 180)/PI;
        return teta_deg;
    }
    if(direction == "gauche"){
        tabj[0] = -10;
        tabj[1] = 0;
        int scalair = (tabj[0] * calcul_vect_jj(j,p)[0])+(tabj[1] * calcul_vect_jj(j, p)[1]);
        float norme_vec_j1 = sqrt(pow(tabj[0],2)+ pow(tabj[1],2));
        float norme_vec_pos = sqrt(pow(calcul_vect_jj(j,p)[0],2)+ pow(calcul_vect_jj(j,p)[1],2));
        float cos_teta = scalair /(norme_vec_j1 * norme_vec_pos);
        float teta_rad = (cos_teta * PI/3)/0.5;
        float teta_deg = (teta_rad * 180)/PI;
        return teta_deg;
    }
    if(direction == "haut_D"){
        tabj[0] = 5;
        tabj[1] = 5;
        int scalair = (tabj[0] * calcul_vect_jj(j,p)[0])+(tabj[1] * calcul_vect_jj(j, p)[1]);
        float norme_vec_j1 = sqrt(pow(tabj[0],2)+ pow(tabj[1],2));
        float norme_vec_pos = sqrt(pow(calcul_vect_jj(j,p)[0],2)+ pow(calcul_vect_jj(j,p)[1],2));
        float cos_teta = scalair /(norme_vec_j1 * norme_vec_pos);
        float teta_rad = (cos_teta * PI/3)/0.5;
        float teta_deg = (teta_rad * 180)/PI;
        return teta_deg;
    }
    if(direction == "haut_G"){
        tabj[0] = -5;
        tabj[1] = 5;
        int scalair = (tabj[0] * calcul_vect_jj(j,p)[0])+(tabj[1] * calcul_vect_jj(j, p)[1]);
        float norme_vec_j1 = sqrt(pow(tabj[0],2)+ pow(tabj[1],2));
        float norme_vec_pos = sqrt(pow(calcul_vect_jj(j,p)[0],2)+ pow(calcul_vect_jj(j,p)[1],2));
        float cos_teta = scalair /(norme_vec_j1 * norme_vec_pos);
        float teta_rad = (cos_teta * PI/3)/0.5;
        float teta_deg = (teta_rad * 180)/PI;
        return teta_deg;
    }
    if(direction == "bas_D"){
        tabj[0] = 5;
        tabj[1] = -5;
        int scalair = (tabj[0] * calcul_vect_jj(j,p)[0])+(tabj[1] * calcul_vect_jj(j, p)[1]);
        float norme_vec_j1 = sqrt(pow(tabj[0],2)+ pow(tabj[1],2));
        float norme_vec_pos = sqrt(pow(calcul_vect_jj(j,p)[0],2)+ pow(calcul_vect_jj(j,p)[1],2));
        float cos_teta = scalair /(norme_vec_j1 * norme_vec_pos);
        float teta_rad = (cos_teta * PI/3)/0.5;
        float teta_deg = (teta_rad * 180)/PI;
        return teta_deg;
    }
    if(direction == "bas_G"){
        tabj[0] = -5;
        tabj[1] = -5;
        int scalair = (tabj[0] * calcul_vect_jj(j,p)[0])+(tabj[1] * calcul_vect_jj(j, p)[1]);
        float norme_vec_j1 = sqrt(pow(tabj[0],2)+ pow(tabj[1],2));
        float norme_vec_pos = sqrt(pow(calcul_vect_jj(j,p)[0],2)+ pow(calcul_vect_jj(j,p)[1],2));
        float cos_teta = scalair /(norme_vec_j1 * norme_vec_pos);
        float teta_rad = (cos_teta * PI/3)/0.5;
        float teta_deg = (teta_rad * 180)/PI;
        return teta_deg;
    }
}
int * Joueur::calcul_vect_jj(Joueur *j, Position *p){
    int tab[2];
    if(p->getx()>j->getposx() && p->gety()>j->getposy()){
        tab[0] = p->getx() - j->getposx();
        tab[1] = p->gety() - j->getposy();
    }
    else if(p->getx()>j->getposx() && p->gety()<j->getposy()) {
        tab[0] = j->getposx() - p->getx();
        tab[1] = j->getposy() - p->gety();
    }
    else if(p->getx()<j->getposx() && p->gety()>j->getposy()) {
        tab[0] = j->getposx() - p->getx();
        tab[1] = p->gety() - j->getposy();
    }
    else if(p->getx()<j->getposx() && p->gety()<j->getposy()) {
        tab[0] = j->getposx() - p->getx();
        tab[1] = j->getposy() - p->gety();
    }
    return tab;
}
void Joueur::attaquer(Position *p, Joueur *j,float arg0,float arg1,std::string direction, NonJoueur *m){
    int distance = (sqrt(pow((p->getx()-j->getposx()), 2)+ pow(p->gety()-j->getposy(), 2)));
    if((distance<50) && (j-> angle_diff(arg0, arg1, direction) == true)){
        if(( p->getx() == m->getposx() && p->gety() == m->getposy()) && distance < 10){
            m->setvie(getvie()-50);
            j->setvie(getvie()-20);
            std::cout<< "attaque de - 50 !!! \n";
        }
        else if(( p->getx() == m->getposx() && p->gety() == m->getposy()) && distance < 20 && distance > 10){
            m->setvie(getvie()-40);
            j->setvie(getvie()-18);
            std::cout<< "attaque de - 40 !!! \n";
        }
        else if(( p->getx() == m->getposx() && p->gety() == m->getposy()) && distance < 30 && distance > 20){
            m->setvie(getvie()-30);
            j->setvie(getvie()-15);
            std::cout<< "attaque de - 30 !!! \n";
        }
        else if(( p->getx() == m->getposx() && p->gety() == m->getposy()) && distance < 40 && distance > 30){
            m->setvie(getvie()-20);
            j->setvie(getvie()-13);
            std::cout<< "attaque de - 20 !!! \n";
        }
        else if(( p->getx() == m->getposx() && p->gety() == m->getposy()) && distance < 50 && distance > 40){
            m->setvie(getvie()-10);
            j->setvie(getvie()-10);
            std::cout<< "attaque de - 10 !!! \n";
        }
    }
    else{std::cout<<"hors de portée \n"; }
}





