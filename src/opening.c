#include "opening.h"
#include "helper.h"
#include "game.h"

#include <stdio.h>
#include <SDL.h>

extern SDL_Renderer* renderer;
static TTF_Font* font;
static SDL_Color color; 
static SDL_Color white; 
static SDL_Texture* background;
static SDL_Texture* gameTitle;
static SDL_Texture* clickEnter;
static SDL_Rect srcGameTitle;
static SDL_Rect dstGameTitle;
static SDL_Rect dstClickEnter;

int blink = 0;

void setOpeningVariable(){
    font = TTF_OpenFont("res/font/UbuntuMono-Regular.ttf", 24);
    color.r = 255;
    color.g = 255;
    color.b = 0;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    background = loadTexture(loadSurface("res/image/background.jpg"));
    gameTitle  = loadTexture(loadSurface("res/image/game_title.png"));
    srcGameTitle.x = 0;
    srcGameTitle.y = 0;
    srcGameTitle.w = 500;
    srcGameTitle.h = 108; 
    dstGameTitle.x = (WINDOW_WIDTH - 500)/2;
    dstGameTitle.y = 20;
    dstGameTitle.w = 500;
    dstGameTitle.h = 108;
    dstClickEnter.x = (WINDOW_WIDTH - 400)/2;
    dstClickEnter.y = (WINDOW_HEIGHT - 150);
    dstClickEnter.w = 400;
    dstClickEnter.h = 50;
}

void opening()
{
    clickEnter = loadTexture(loadTextSurface(font,"Click Enter To Start!", (blink?&white:&color)));
    SDL_RenderCopy(renderer, background, NULL, NULL); 
    SDL_RenderCopy(renderer, gameTitle, &srcGameTitle, &dstGameTitle); 
    SDL_RenderCopy(renderer, clickEnter, NULL, &dstClickEnter); 
    SDL_RenderPresent(renderer);
    SDL_Delay(700);
    blink = (blink+1)%2;
}
