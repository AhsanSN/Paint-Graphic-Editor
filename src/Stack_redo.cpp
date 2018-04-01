#include"Stack_redo.h"
#include <iostream>
#include<SDL.h>
#include<Shapes.h>
#include<Rect.h>
//same code as of Stacks
Stack_redo::Stack_redo()
{
    head = NULL;
    tail = NULL;

}

Stack_redo::~Stack_redo()
{
    while(head != NULL)
    {
        Node* temp = head;
        head = head->next;
        temp->data;
        delete temp;
    }
}

void Stack_redo::Push_redo(Shapes* val)
{
    if (head == NULL)
    {
        head = new Node;
        head->data = val;
        head->next = NULL;
        head->prev = NULL;
        tail=head;

    }
    else
    {
        tail->next = new Node;
        tail->next->data = val;
        tail->next->next = NULL;
        tail->next->prev = tail;
        tail = tail->next;
    }
}

Shapes* Stack_redo::Pop_redo()
{
    SDL_Rect fillRect;
    Shapes* rect = NULL;
    rect = new Rect(fillRect);
    Shapes* val=rect;
    if(head != NULL)
    {
        Node* temp = tail;
        val = tail->data;
        tail = tail->prev;

        if(head!=NULL)
        {
            head->prev = NULL;
        }
        delete temp;
    }
    return val;
}

void Stack_redo::Show_redo(SDL_Renderer* gRenderer)
{
    Node* temp = head;
    while(temp!=NULL)
    {
        (temp->data)->draw(gRenderer);
        temp = temp->next;
    }
}

void Stack_redo::clearAll_redo()
{
    Node* temp = head;
    while(temp!=NULL)
    {
        Stack_redo::Pop_redo();
        temp = temp->next;
    }
}
