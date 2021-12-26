#include "opening.h"
#include "helper.h"
#include "game.h"

#include <stdio.h>
#include <SDL.h>

extern SDL_Renderer* renderer;
static SDL_Texture* background;

void setOpeningVariable(){
    background = loadTexture(loadSurface("res/image/initial-d.jpg"));
}

void opening()
{
    SDL_RenderCopy(renderer, background, NULL, NULL); 
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/60);
}
