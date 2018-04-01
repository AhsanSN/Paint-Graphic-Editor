#ifndef SHAPES_H
#define SHAPES_H
#include <SDL.h>


class Shapes
{
    public:
        Shapes();
        virtual void draw(SDL_Renderer*);
        virtual void inFillrect(SDL_Rect*);

    protected:

    private:
};

#endif // SHAPES_H
