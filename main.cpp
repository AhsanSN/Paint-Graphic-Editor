#include <SDL.h>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <iostream>
#include"Rect.h"
#include"Line.h"
#include"Stack.h"
#include"Stack_redo.h"
#define fps 60

/*

Important notes:
- the whole main program (main.cpp)is divided into three parts. these three parts are 90% same,except the shape that
they are creating.
- a linked list is used to store shapes
- a linked list (stack_redo) is used to store the redo and the undo elements
- you may find me adding and subtracting some constants to variables, such as length of stack. this is to adjust so that the program
can run properly
*/

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};
//
bool init();
bool loadMedia();
void close();
void redoArrayFunction();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool init() //same code as given
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            }
        }
    }
    return success;
}

bool loadMedia() //same code as given
{
    bool success = true;
    return success;
}

void close() //same code as given //both stacks have been deallocated int he main function in the end
{
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    //Quit SDL subsystems

    SDL_Quit();
}

int main( int argc, char* args[] )
{
    Shapes* swapUpDown[100]; //used to store the shapes that are sent up and down
    srand (time(NULL));
    Uint32 starting_tick;
    Stack stk;
    Stack_redo stkRedo;
    int shapesInStack=0;
    int redoArrayLength=0;
    int redoNumber=0;
    //Start linePermission SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        if( !loadMedia() )  //Load media
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            bool quit = false;  //Main loop controller
            int swapIndex=0; //
            int swapInitialIndex=0; // position of last element in swapstack
            Shapes* swapIndexShape;
            SDL_Event e;        //Event handler that takes care of all events
            bool mouseClicked = false;
            bool allowUp = false;
            SDL_Rect fillRect;
            bool rectanglePermission=false; //rectangle
            bool linePermission = false; //line
            bool swapPermission = true;
            bool pointPermission = false; //point
            //for coordinates
            int oldx ;
            int oldy ;
            int x, y ;
            int lineoldx, lineoldy;
            int linex, liney;
            //creating objects
            Shapes* rect = NULL;
            Line* line = NULL;
            Point* point = NULL;
            rectanglePermission = true;
            rect = new Rect(fillRect);
            line = new Line();
            point = new Point();
            point->giveCoods(0,0); //creates the first point

            stk.Push(point);
            stk.Show(gRenderer);
            shapesInStack++;

            while( !quit )
            {
                while( SDL_PollEvent( &e ) != 0 )
                {

                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    else
                    {
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( gRenderer );
                        rectanglePermission = true;
                        while(!quit)
                        {
                            starting_tick = SDL_GetTicks(); // used to decrease the frame rate to ensure smooth running of program
                            //Handle events on queue
                            while (rectanglePermission ==true) // loop for rectangle. same is done for line and point
                            {
                                starting_tick = SDL_GetTicks();
                                while( SDL_PollEvent( &e ) != 0 )
                                {
                                    //User requests quit
                                    if( e.type == SDL_QUIT )
                                    {
                                        quit = true;
                                        rectanglePermission = false;
                                    }
                                    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
                                    {
                                        SDL_GetMouseState( &x, &y );

                                        if(e.type ==  SDL_MOUSEMOTION)
                                        {
                                            if(mouseClicked == true)
                                                fillRect = { oldx, oldy, x - oldx, y - oldy };
                                            rect->inFillrect(&fillRect); //send the coordinates
                                        }
                                        if(e.type == SDL_MOUSEBUTTONDOWN)
                                        {
                                            if (e.button.button == SDL_BUTTON_LEFT)
                                            {
                                                if(mouseClicked == false)
                                                {
                                                    mouseClicked = true;
                                                    oldx = x;
                                                    oldy = y;
                                                }
                                            }
                                        }
                                        if(e.type == SDL_MOUSEBUTTONUP)
                                        {
                                            if (e.button.button == SDL_BUTTON_LEFT) //draws
                                            {
                                                rect = new Rect(fillRect);
                                                mouseClicked = false;
                                                stk.Push(rect);
                                                shapesInStack++;
                                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                                SDL_RenderClear( gRenderer );
                                                stk.Show(gRenderer); //draws all the shapes
                                            }
                                            if (e.button.button == SDL_BUTTON_RIGHT) //undo
                                            {
                                                if (shapesInStack > 1)
                                                {
                                                    shapesInStack--;
                                                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                                    SDL_RenderClear( gRenderer );
                                                    stkRedo.Push_redo(stk.Pop());
                                                    redoArrayLength ++;
                                                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                                    SDL_RenderClear( gRenderer );
                                                    stk.Show(gRenderer);
                                                }
                                            }
                                            if (e.button.button == SDL_BUTTON_MIDDLE) //redo
                                            {
                                                if (redoNumber-1 <= redoArrayLength+1)
                                                {
                                                    (stkRedo.Pop_redo())->draw(gRenderer);
                                                    redoNumber = redoNumber+1;
                                                    redoArrayLength = redoArrayLength -1;
                                                }
                                            }
                                        }
                                    }
                                }
                                SDL_RenderPresent( gRenderer );
                                switch( e.key.keysym.sym ) // get the keyboard inputs
                                {
                                case SDLK_p:
                                {
                                    rectanglePermission = false;
                                    pointPermission = true;
                                    break;
                                }
                                case SDLK_l:
                                {
                                    rectanglePermission = false;
                                    linePermission = true;
                                    break;
                                }
                                case SDLK_DOWN:
                                {
                                    if (e.type == SDL_KEYUP)
                                    {
                                        allowUp = true;
                                        swapPermission = true;
                                    }
                                    if (e.type == SDL_KEYDOWN)
                                    {
                                        if (swapPermission ==true)
                                        {
                                            if (swapIndex==0)
                                            {
                                                swapInitialIndex=stk.length()-1;
                                            }
                                            if ((stk.length())-2>swapIndex)
                                            {
                                                stk.swap(swapInitialIndex-1,swapInitialIndex);
                                                swapIndex++;
                                                swapInitialIndex--;
                                            }
                                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                            SDL_RenderClear( gRenderer );
                                            stk.Show(gRenderer);
                                            swapPermission = false;
                                            break;
                                        }
                                    }
                                }

                                case SDLK_UP:
                                {
                                    if (allowUp == true)
                                    {
                                        if (e.type == SDL_KEYUP)
                                        {
                                            swapPermission = true;
                                        }
                                        if (e.type == SDL_KEYDOWN)
                                        {
                                            if (swapPermission ==true)
                                            {
                                                if (swapIndex==0)
                                                {
                                                    swapInitialIndex=stk.length()-1;
                                                }
                                                if ((stk.length()-1)>swapIndex)
                                                {
                                                    stk.swap(swapInitialIndex+1,swapInitialIndex);
                                                    swapIndex--;
                                                    swapInitialIndex++;
                                                }
                                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                                SDL_RenderClear( gRenderer );
                                                stk.Show(gRenderer);
                                                swapPermission = false;
                                                break;
                                            }
                                        }
                                    }
                                }

                                }
                                if((500/fps)> SDL_GetTicks() - starting_tick) //decreasing frame rate
                                {
                                    SDL_Delay(500/fps - (SDL_GetTicks() - starting_tick ));
                                }

                            }

                            while (linePermission ==true)
                            {
                                starting_tick = SDL_GetTicks();
                                while( SDL_PollEvent( &e ) != 0 )
                                {
                                    //User requests quit
                                    if( e.type == SDL_QUIT )
                                    {
                                        quit = true;
                                        linePermission = false;
                                    }
                                    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
                                    {
                                        SDL_GetMouseState( &linex, &liney );
                                        if(e.type ==  SDL_MOUSEMOTION)
                                        {
                                            swapPermission = true;
                                            if(mouseClicked == true)
                                                line->giveCoordinates2(linex, liney);
                                        }
                                        if(e.type == SDL_MOUSEBUTTONDOWN)
                                        {
                                            if (e.button.button == SDL_BUTTON_LEFT)
                                            {
                                                if(mouseClicked == false)
                                                {
                                                    mouseClicked = true;
                                                    lineoldx = linex;
                                                    lineoldy = liney;
                                                    line->giveCoordinates1(lineoldx,lineoldy);
                                                }
                                            }
                                        }
                                        if(e.type == SDL_MOUSEBUTTONUP)
                                        {
                                            if (e.button.button == SDL_BUTTON_LEFT)
                                            {
                                                mouseClicked = false;
                                                line = new Line();
                                                line->draw(gRenderer);
                                                stk.Push(line);
                                                shapesInStack++;
                                                stk.Show(gRenderer);
                                            }
                                            if (e.button.button == SDL_BUTTON_RIGHT)
                                            {
                                                if (shapesInStack > 1)
                                                {
                                                    shapesInStack--;
                                                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                                    SDL_RenderClear(gRenderer );
                                                    stkRedo.Push_redo(stk.Pop());
                                                    redoArrayLength++;
                                                    stk.Show(gRenderer);
                                                }
                                            }
                                            if (e.button.button == SDL_BUTTON_MIDDLE)
                                            {
                                                if (redoNumber-1 <= redoArrayLength+1)
                                                {
                                                    (stkRedo.Pop_redo())->draw(gRenderer);
                                                    redoNumber = redoNumber+1;
                                                    redoArrayLength = redoArrayLength -1;
                                                }
                                            }
                                        }
                                    }
                                }
                                SDL_RenderPresent( gRenderer );
                                switch( e.key.keysym.sym )
                                {
                                    if (e.type == SDL_KEYDOWN)
                                    {
                                    case SDLK_p:
                                        linePermission = false;
                                        pointPermission = true;
                                        break;
                                    case SDLK_r:
                                        linePermission = false;
                                        rectanglePermission = true;
                                        break;
                                    case SDLK_DOWN:
                                    {
                                        if (e.type == SDL_KEYUP)
                                        {
                                            allowUp = true;
                                            swapPermission = true;
                                        }
                                        if (e.type == SDL_KEYDOWN)
                                        {
                                            if (swapPermission ==true)
                                            {
                                                if (swapIndex==0)
                                                {
                                                    swapInitialIndex=stk.length()-1;
                                                }
                                                if ((stk.length())-2>swapIndex)
                                                {
                                                    stk.swap(swapInitialIndex-1,swapInitialIndex);
                                                    //stk.swap(stk.length()-1,stk.length());
                                                    swapIndex++;
                                                    swapInitialIndex--;
                                                }
                                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                                SDL_RenderClear( gRenderer );
                                                stk.Show(gRenderer);
                                                swapPermission = false;
                                                break;
                                            }
                                        }
                                    }


                                    case SDLK_UP:
                                    {
                                        if (allowUp == true)
                                        {
                                            if (e.type == SDL_KEYUP)
                                            {
                                                swapPermission = true;
                                            }
                                            if (e.type == SDL_KEYDOWN)
                                            {
                                                if (swapPermission ==true)
                                                {
                                                    if (swapIndex==0)
                                                    {
                                                        swapInitialIndex=stk.length()-1;
                                                    }
                                                    if ((stk.length()-1)>swapIndex)
                                                    {
                                                        stk.swap(swapInitialIndex+1,swapInitialIndex);
                                                        swapIndex--;
                                                        swapInitialIndex++;
                                                    }
                                                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                                    SDL_RenderClear( gRenderer );
                                                    stk.Show(gRenderer);
                                                    swapPermission = false;
                                                    break;
                                                }
                                            }
                                        }
                                    }

                                }
                                }
                                SDL_RenderPresent( gRenderer ); //tempor
                                if((500/fps)> SDL_GetTicks() - starting_tick) //decreasing frame rate
                                {
                                    SDL_Delay(500/fps - (SDL_GetTicks() - starting_tick ));
                                }
                            }
                            while (pointPermission ==true)
                            {
                                while( SDL_PollEvent( &e ) != 0 )
                                {
                                    //User requests quit
                                    if( e.type == SDL_QUIT )
                                    {
                                        quit = true;
                                        pointPermission = false;
                                    }

                                    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
                                    {
                                        SDL_GetMouseState( &x, &y );

                                        if(e.type == SDL_MOUSEBUTTONDOWN)
                                        {
                                            if (e.button.button == SDL_BUTTON_LEFT)
                                            {
                                                if(mouseClicked == false)
                                                {
                                                    mouseClicked = true;
                                                    oldx = x;
                                                    oldy = y;
                                                }
                                            }
                                        }
                                        if(e.type == SDL_MOUSEBUTTONUP)
                                        {
                                            if (e.button.button == SDL_BUTTON_LEFT)
                                            {
                                                mouseClicked = false;
                                                point = new Point();
                                                point->giveCoods(oldx,oldy);
                                                stk.Push(point);
                                                stk.Show(gRenderer);
                                                shapesInStack++;
                                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                                point->draw(gRenderer);
                                            }
                                            if (e.button.button == SDL_BUTTON_RIGHT)
                                            {
                                                if (shapesInStack > 1)
                                                {
                                                    shapesInStack--;
                                                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                                    SDL_RenderClear( gRenderer );
                                                    redoArrayLength++;
                                                    stkRedo.Push_redo(stk.Pop());
                                                    stk.Show(gRenderer);
                                                }
                                            }
                                            if (e.button.button == SDL_BUTTON_MIDDLE)
                                            {
                                                if (redoNumber-1 <= redoArrayLength+1)
                                                {
                                                    (stkRedo.Pop_redo())->draw(gRenderer);
                                                    redoNumber = redoNumber+1;
                                                    redoArrayLength = redoArrayLength -1;
                                                }
                                            }
                                        }
                                    }
                                }
                                SDL_RenderPresent( gRenderer );
                                switch( e.key.keysym.sym )
                                {
                                    if (e.type == SDL_KEYDOWN)
                                    {
                                    case SDLK_l:
                                        pointPermission = false;
                                        linePermission = true;
                                        break;
                                    case SDLK_r:
                                        pointPermission = false;
                                        rectanglePermission = true;
                                        break;
                                    case SDLK_DOWN:
                                    {
                                        if (e.type == SDL_KEYUP)
                                        {
                                            allowUp = true;
                                            swapPermission = true;
                                        }
                                        if (e.type == SDL_KEYDOWN)
                                        {
                                            if (swapPermission ==true)
                                            {
                                                if (swapIndex==0)
                                                {
                                                    swapInitialIndex=stk.length()-1;
                                                }
                                                if ((stk.length())-2>swapIndex)
                                                {
                                                    stk.swap(swapInitialIndex-1,swapInitialIndex);
                                                    swapIndex++;
                                                    swapInitialIndex--;
                                                }
                                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                                SDL_RenderClear( gRenderer );
                                                stk.Show(gRenderer);
                                                swapPermission = false;
                                                break;
                                            }
                                        }
                                    }


                                    case SDLK_UP:
                                    {
                                        if (allowUp == true)
                                        {
                                            if (e.type == SDL_KEYUP)
                                            {
                                                swapPermission = true;
                                            }
                                            if (e.type == SDL_KEYDOWN)
                                            {
                                                if (swapPermission ==true)
                                                {
                                                    if (swapIndex==0)
                                                    {
                                                        swapInitialIndex=stk.length()-1;
                                                    }
                                                    if ((stk.length()-1)>swapIndex)
                                                    {
                                                        stk.swap(swapInitialIndex+1,swapInitialIndex);
                                                        swapIndex--;
                                                        swapInitialIndex++;
                                                    }
                                                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                                    SDL_RenderClear( gRenderer );
                                                    stk.Show(gRenderer);
                                                    swapPermission = false;
                                                    break;
                                                }
                                            }
                                        }
                                    }

                                    }
                                }
                                if((500/fps)> SDL_GetTicks() - starting_tick) //decreasing frame rate
                                {
                                    SDL_Delay(500/fps - (SDL_GetTicks() - starting_tick ));
                                }
                            }
                            if((500/fps)> SDL_GetTicks() - starting_tick) //decreasing frame rate
                            {
                                SDL_Delay(500/fps - (SDL_GetTicks() - starting_tick ));
                            }
                        }
                    }
                }
            }
        }
    }
    stk.clearAll();
    stk.~Stack(); //destructor /deallocates stack
    stkRedo.~Stack_redo();//destructor /deallocates stack
    close();
    return 0;
}




