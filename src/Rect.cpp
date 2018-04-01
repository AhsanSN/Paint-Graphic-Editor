#include"Rect.h"
#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;
Rect::Rect(SDL_Rect rect) //gives random color
{
    //srand (time(NULL));
srand (time(NULL));
    c1 = rand() % 255 ;
   c2 = rand() % 255 ;
   c3 = rand() % 255 ;
   c4 = rand() % 255 ;
    this->fillRect = rect;
}

void Rect::inFillrect(SDL_Rect rect) //take coods
{
    this->fillRect = rect;
}

/** Draws the rectangle **/
void Rect::draw(SDL_Renderer* gRenderer) //draws
{
    SDL_SetRenderDrawColor( gRenderer, c1, c2, c3, c4 );
    SDL_RenderFillRect( gRenderer, &fillRect );
}

