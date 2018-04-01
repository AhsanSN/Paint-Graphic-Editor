#include "Point.h"
#include"SDL.h"
#include<iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

Point::Point() //gives random color
{
    //ctor
    c1 = rand() % 255 ;
   c2 = rand() % 255 ;
   c3 = rand() % 255 ;
   c4 = rand() % 255 ;
}

void Point::draw(SDL_Renderer* gRenderer) //draws
{
    SDL_SetRenderDrawColor( gRenderer, c1, c2, c3, c4 );
    SDL_RenderDrawPoint( gRenderer, xpoint,ypoint);
}

void Point::giveCoods(int xi, int yi) //give coods
{
    xpoint=xi;
    ypoint=yi;
}

