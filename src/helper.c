#include "helper.h"
#include "game.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

SDL_Surface* loadTextSurface(TTF_Font* font, const char* text, SDL_Color* color)
{
    return TTF_RenderText_Solid(font, text, *color);
}

SDL_Surface* loadSurface(const char* path)
{
    SDL_Surface* image = IMG_Load(path);

    if(!image){
        printf("IMG Error : %s\n", IMG_GetError());
        SDL_FreeSurface(image);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    return image;
}

SDL_Surface* clearBackground(SDL_Surface* surface, SDL_Color* color)
{
    Uint32 rgb = SDL_MapRGB(surface->format, color->r, color->g, color->b);
    SDL_SetColorKey(surface, SDL_TRUE, rgb);
    return surface;
}

SDL_Texture* loadTexture(SDL_Surface* surface)
{
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if(!texture){
        printf("SDL2 Error : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
    
    return texture;
}
