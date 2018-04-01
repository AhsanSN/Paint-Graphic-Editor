#include"Stack.h"
#include <iostream>
#include<SDL.h>
#include<Shapes.h>
#include<Rect.h>
//taken from LMS
//data type changed to Shapes* as it stores the addresses of shapes, instead of int
Stack::Stack()
{
    head = NULL;
    tail = NULL;

}

Stack::~Stack()
{
    while(head != NULL)
    {
        Node* temp = head;
        head = head->next;
        temp->data;
        delete temp;
    }
}

void Stack::Push(Shapes* val)
{
    arrayLength++;
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

Shapes* Stack::Pop()
{
    Shapes* val=NULL;

    if(head != NULL)
    {
        Node* temp = tail;
        val = temp->data;
        tail = tail->prev;
        if(head!=NULL)
        {
            tail->next = NULL;
        }
        delete temp;
        temp = NULL;
    }
    return val;
}

void Stack::Show(SDL_Renderer* gRenderer) //displays all shapes
{
    Node* temp = head;
    while(temp!=NULL)
    {
        cout<<"1";
        (temp->data)->draw(gRenderer);
        temp = temp->next;
        SDL_RenderPresent(gRenderer);
    }
    cout<<""<<endl;

}

int Stack::length() //gives length of stack
{
    return arrayLength;
}

void Stack::clearAll()
{
    Node* temp = head;
    while(temp!=NULL)
    {
        Stack::Pop();
        temp = temp->next;
    }
}


void Stack::swap(int i, int j)
{
    if(head == NULL) return;

    // Get ith node
    Node* node_i = head;
    int node_cnt = 0;
    while(1)
    {
        if(node_cnt == i) break;
        if(node_i == NULL) return;
        node_i = node_i->next;
        node_cnt++;
    }

    // Get jth node
    Node* node_j = head;
    node_cnt = 0;
    while(1)
    {
        if(node_cnt == j) break;
        if(node_j == NULL) return;
        node_j = node_j->next;
        node_cnt++;
    }

    // Swap values of nodes
    Shapes* temp = node_i->data;
    node_i->data = node_j->data;
    node_j->data = temp;
}

