
#pragma once
#include<iostream>
#include"Shapes.h"
using namespace std;

struct Node
{
    Shapes* data;
    Node* next;
    Node* prev;
};

