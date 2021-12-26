#ifndef HELPER_H
#define HELPER_H
#include <SDL.h>
#include <SDL_ttf.h>

SDL_Surface* loadTextSurface(TTF_Font* font, const char* text, SDL_Color* color);
SDL_Surface* loadSurface(const char* path);
SDL_Surface* clearBackground(SDL_Surface* surface, SDL_Color* color);
SDL_Texture* loadTexture(SDL_Surface* surface);

#endif
