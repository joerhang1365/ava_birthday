#ifndef SURFACE_H
#define SURFACE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface *optimizedSurface(char *filePath, SDL_Surface *windowSurface);

#endif
