#pragma once
#include"SDL.h"
#ifndef LINE_H
#define LINE_H
#include<Shapes.h>

class Line : public Shapes
{
    public:
        Line();
        void draw(SDL_Renderer* );
        void giveCoordinates1(int , int);
        void giveCoordinates2(int , int);
        void ColorDraw(SDL_Renderer*);
    protected:

    private:
        int A;
        int B;
        int C;
        int D;
        int c1;
        int c2;
        int c3;
        int c4;

};

#endif // LINE_H
