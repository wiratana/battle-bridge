#include "game.h"
#include "opening.h"
#include "auth.h"
#include "gameplay.h"
#include "board.h"

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// window
SDL_Window* window = NULL; 
SDL_Renderer* renderer = NULL;

// core variable
int exitProgram = 0;
int currentPage = 0;
int doesInput   = 0;

extern int selectedOption;
extern int selectedForm;
extern int currentProcess;
extern char inputUsername[100];
extern char inputPassword[100];
extern char authError[255];
extern SDL_Rect dstTank;
extern struct player player;
extern struct bullet bullet;
extern int isFire;

void game()
{
    initEngine();
    initVariable();
    while(!exitProgram){
        SDL_RenderClear(renderer);
        switch(currentPage){
            case 0:
                opening();
                break;
            case 1:
                auth();
                break;
            case 2:
                gameplay();
                break;
	    case 3:
		board();
		break;
            default:
                break;
        }
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
    setOpeningVariable();
    setAuthVariable();
    setGameplayVariable();
    setBoardVariable();
}

void updateLogic()
{
    updateGameplayVariable();
}

void controlHandling()
{
    SDL_Event event;

    SDL_StartTextInput();
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
            { 
                doesInput = 1;
                switch(event.key.keysym.sym){
                    case SDLK_RETURN:
                        if(currentPage == 0)
                            currentPage++;
                        else
                        if(currentPage == 1 && currentProcess == 0)
                            currentProcess++;
                        else
                        if(currentPage == 1 && currentProcess == 1)
                           authProcess(); 
			else
			if(currentPage == 3)
			    currentPage = 0;
                        break;             
                    case SDLK_UP:
                        if(currentPage == 1) 
                            selectedOption = (selectedOption <= 0) ? 1 : selectedOption - 1;
                        if(currentPage == 2 && dstTank.y > 1) 
                            dstTank.y -= player.speed;
                        break;
                    case SDLK_DOWN:
                        if(currentPage == 1)
                            selectedOption = (selectedOption+1)%2;
                        if(currentPage == 2 && dstTank.y < WINDOW_HEIGHT - dstTank.h)
                            dstTank.y += player.speed;
                        break;
                    case SDLK_SPACE:
                        if(currentPage == 2 && bullet.status == 0){
                           bullet.status = 1;
                           isFire = 1;
                        }
                        break;
                    case SDLK_TAB:
                        if(currentPage == 1) 
                            selectedForm = (selectedForm+1)%2;
                        break;
                    case SDLK_BACKSPACE:
                        if(currentPage == 1){
                            if(selectedForm == 0 && strlen(inputUsername) > 0)
                                inputUsername[strlen(inputUsername)-1] = '\0';
                            if(selectedForm == 1 && strlen(inputPassword) > 0)
                                inputPassword[strlen(inputPassword)-1] = '\0';
                        }
                        break;
                    default:
                        break;
                }
                break;
            }
            case SDL_TEXTINPUT:
                if(currentPage == 1) {
                    if(selectedForm == 0 && strlen(inputUsername) < 30)
                        strcat(inputUsername, event.text.text);
                    if(selectedForm == 1 && strlen(inputPassword) < 30)
                        strcat(inputPassword, event.text.text);
                }
                break;
            case SDL_QUIT:
                exitProgram = 1;
                break;
            default:
                break;
        }
    }
    SDL_StopTextInput();
}
