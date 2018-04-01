#pragma once
#ifndef POINT_H
#define POINT_H
#include"SDL.h"
#include<Shapes.h>


class Point : public Shapes
{
    public:
        Point();
        void draw(SDL_Renderer*);
        void giveCoods(int ,int);

    protected:

    private:
        int xpoint;
        int ypoint;
        int c1,c2,c3,c4;
};

#endif // POINT_H
