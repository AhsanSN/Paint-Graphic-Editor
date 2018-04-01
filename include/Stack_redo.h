#pragma once
#include"Node.h"
#include"Shapes.h"
#include<iostream>
#include <SDL.h>

using namespace std;

class Stack_redo
{
private:
    Node* head;
    Node* tail;
public:
    Stack_redo();
    ~Stack_redo();
    void Push_redo(Shapes*);
    void clearAll_redo();
    Shapes* Pop_redo();
    void Show_redo(SDL_Renderer* gRenderer);
};
