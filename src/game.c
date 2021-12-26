#include "game.h"
#include "opening.h"

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// window
SDL_Window* window = NULL; 
SDL_Renderer* renderer = NULL;

// core variable
int exitProgram = 0;

void game()
{
    initEngine();
    initVariable();
    while(!exitProgram){
        opening();
        controlHandling();
        updateLogic();
    }
}

void initEngine()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf("SDL2 Error: %s\n", SDL_GetError());
        exit(1);
    }

    if(!IMG_Init(IMG_INIT_JPG) && !IMG_Init(IMG_INIT_PNG)) {
        printf("SDL2_Image Error: %s\n", IMG_GetError());
        exit(1);
    }

    if(TTF_Init() < 0) {
        printf("SDL2_TTF Error: %s\n", TTF_GetError());
        exit(1);
    }
    
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if(!window) {
        printf("SDL2 Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    } 

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!renderer) {
        printf("SDL2 Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
}

void initVariable()
{

}

void updateLogic()
{

}

void controlHandling()
{
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                exitProgram = 1;
                break;
            default:
                break;
        }
    }
}
