#include "board.h"
#include "helper.h"
#include "game.h"
#include "data.h"
#include "auth.h"

#include <stdio.h>
#include <string.h>
#include <SDL.h>

extern SDL_Renderer* renderer;
extern struct user playerInfo;
static TTF_Font* font;
static SDL_Color color; 
static SDL_Color white; 
static SDL_Texture* background;
static SDL_Texture* gameTitle;
static SDL_Texture* gameBoard;
static SDL_Texture* playerHistory[5];
static SDL_Rect srcGameTitle;
static SDL_Rect dstGameTitle;
static SDL_Rect dstGameBoard;
static SDL_Rect dstPlayerHistory;
static char buffForPath[512];
char buffForData[2048];
char loadData[5][512];
int isHaveData;

void setBoardVariable(){
    font = TTF_OpenFont("res/font/UbuntuMono-Regular.ttf", 24);
    color.r = 255;
    color.g = 255;
    color.b = 0;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    background = loadTexture(loadSurface("res/image/background.jpg"));
    gameTitle  = loadTexture(loadSurface("res/image/game_title.png"));
    gameBoard  = loadTexture(loadSurface("res/image/bridge.png"));
    srcGameTitle.x = 0;
    srcGameTitle.y = 0;
    srcGameTitle.w = 500;
    srcGameTitle.h = 108; 
    dstGameTitle.x = (WINDOW_WIDTH - 500)/2;
    dstGameTitle.y = 20;
    dstGameTitle.w = 500;
    dstGameTitle.h = 108;
    dstGameBoard.x = (WINDOW_WIDTH-500)/2;
    dstGameBoard.y = 40+dstGameTitle.h;
    dstGameBoard.w = 500;
    dstGameBoard.h = (WINDOW_HEIGHT-(dstGameBoard.y+20));
    dstPlayerHistory.x = (WINDOW_WIDTH-450)/2;
    dstPlayerHistory.y = 50+dstGameTitle.h;
    dstPlayerHistory.w = 450;
    dstPlayerHistory.h = ((WINDOW_HEIGHT-(dstGameBoard.y+30))/5);
    memset(loadData, 0, sizeof(loadData[0][0]) * 5 * 512);
}

void board()
{
    SDL_RenderCopy(renderer, background, NULL, NULL); 
    SDL_RenderCopy(renderer, gameTitle, &srcGameTitle, &dstGameTitle); 
    SDL_RenderCopy(renderer, gameBoard, NULL, &dstGameBoard); 
    if(isHaveData){
        dstPlayerHistory.y = 50+dstGameTitle.h;
        int itr = 0;
        while(itr < (signed int)(sizeof(loadData)/sizeof(loadData[0]))){
            if(!loadData[itr]) break;
            if(loadData[itr][0]){
                playerHistory[itr] = loadTexture(loadTextSurface(font, loadData[itr], &white));
                SDL_RenderCopy(renderer, playerHistory[itr], NULL, &dstPlayerHistory);
                dstPlayerHistory.y += dstGameTitle.h/2;
            }
            itr++;
        }
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(700);
}

void prepareData()
{	
    for(int i = 0; i < (signed int)(sizeof(loadData)/sizeof(loadData[0])); i++)
	strcpy(loadData[i],"");
    sprintf(buffForPath, "data/%d.txt", getID("data/user.txt", playerInfo.username)); 
    getData(buffForPath, buffForData, sizeof(loadData)/sizeof(loadData[0]), 1);  
    int ctr = 0;
    for(int i = 0; i < (signed int)(sizeof(loadData)/sizeof(loadData[0])); i++){	
	while(buffForData[ctr]){
	    if(buffForData[ctr] == '\n'){
		ctr++;
		break;
	    }
	    strcat(loadData[i], (char[2]){buffForData[ctr],0});
	    if(!isHaveData) isHaveData = 1;
	    ctr++;
	}
    } 
}
