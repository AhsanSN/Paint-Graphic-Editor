#include "Line.h"
#include<iostream>
#include <time.h>
#include <cstdlib>

using namespace std;
Line::Line() //gives a random color
{
    //ctor
   c1 = rand() % 255 ;
   c2 = rand() % 255 ;
   c3 = rand() % 255 ;
   c4 = rand() % 255 ;
}

void Line::draw(SDL_Renderer* gRenderer) //draws
{
    SDL_SetRenderDrawColor( gRenderer, c1, c2, c3, c4 );
    SDL_RenderDrawLine( gRenderer, A, B,C, D);
}

void Line::giveCoordinates1(int Ai , int Bi) //starting coods
{
    A = Ai;
    B = Bi;
}

void Line::giveCoordinates2(int Ci , int Di) //ending coods
{
    C = Ci;
    D = Di;
}
