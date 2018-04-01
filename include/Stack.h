#pragma once
#include"Node.h"
#include"Shapes.h"
#include<iostream>
#include <SDL.h>

using namespace std;

class Stack
{
private:
    Node* head;
    Node* tail;
    int arrayLength = 0;
public:
    Stack();
    ~Stack();
    void Push(Shapes*);
    void clearAll();
    int length();
    void swap(int , int);
    Shapes* Pop();
    void Show(SDL_Renderer* gRenderer);
};
