//
//  Position.hpp
//  IN509
//
//  Created by Amir on 01/01/2017.
//  Copyright © 2017 sll. All rights reserved.
//

#ifndef Position_hpp
#define Position_hpp

#include <stdio.h>
class Position{
private:
    int x;
    int y;
public:
    Position();
    Position(int x, int y);
    int getx();
    int gety();
    void setx(int a);
    void sety(int b);
    //bool equals(Object obj);
    bool isnear(Position p);
    //static Position generatepos(Terrain tab);
    static int alea(int const min, int const max);
    //static Position generatepos(Terrain tab);
    
};

#endif /* Position_hpp */
