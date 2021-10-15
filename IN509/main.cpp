#include "Position.hpp"
#include "Personnage.hpp"
#include "Joueur.hpp"
#include "NonJoueur.hpp"
#include <iostream>
#define VIE 100
int main()
{

    Position *p = new Position(25,35);
    Joueur *j = new Joueur("sid",30,40,40,40,40);
    Joueur *j2 = new Joueur("Hamid",10,10,10,10,10);
   // j2->sedeplacer("haut");
    //std::cout<<j2->getposy()<<"\n";
    NonJoueur *m = new NonJoueur("IA",25 , 35, 20, 20, 20,VIE);
   /*
    NonJoueur *m = new NonJoueur("IA",20 , 20, 20, 20, 20);
    std::cout<<m -> alea_direction()<<"\n";
    m->sedeplacer(m->alea_direction());
    std::cout<<"coordonnée x : "<< m->getposx() <<"\n";
    std::cout<<"coordonnée y : "<< m->getposy() <<"\n";*/
    std::string direction = "bas_G";
    float arg1 = j->teta(p, direction, j);
    std::cout << " coordonée avt dé selon x : " <<j -> getposx() << "\n";
    std::cout << " coordonée avt dé selon y : " <<j -> getposy() << "\n";
    j -> sedeplacer(direction);
    std::cout << "nouvelle coordonée selon x : " <<j -> getposx() << "\n";
    std::cout << "nouvelle coordonée selon y : " <<j -> getposy() << "\n";
    //std::cout<< "coordonnée x :" <<j->calcul_vect_jj(j,p)[0]<<"\n";
    //std::cout<< "coordonnée y :" <<j->calcul_vect_jj(j,p)[1]<<"\n";
    //std::cout << "santé avant l'attaque : " << m->getvie() << "\n";
    //std::cout << "santé de l'attaquant avant l'attaque : " << j->getvie() << "\n";
    //j->attaquer(p, j, 90, arg1, direction,m);
    //std::cout << "santé apres l'attaque : " << m->getvie() << "\n";
    //std::cout << "santé de l'attaquant avant l'attaque : " << j->getvie() << "\n";
    return 0;
}
