#ifndef SURFACE_H
#define SURFACE_H

#include <SDL.h>
#include <SDL_image.h>

SDL_Surface *optimizedSurface(char *filePath, SDL_Surface *windowSurface);

#endif
