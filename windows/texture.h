#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>

SDL_Texture *texture_load(char *filePath, SDL_Renderer *renderTarget);

#endif
