#pragma once
#include"SDL.h"
#include"Point.h"
#include"Shapes.h"

/** Rect class **/

class Rect : public Shapes
{
public:

    Rect(SDL_Rect);
    virtual void draw(SDL_Renderer*);
    void inFillrect(SDL_Rect);

private:

    SDL_Rect fillRect;
    Point topLeft;
    Point bottomRight;
    int c1;
    int c2;
    int c3;
    int c4;
};
