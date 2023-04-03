#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SDL2/SDL.h>
#include "texture.h"

#define MAX_CLIPS 12

typedef struct
{
   SDL_Texture *textureSheet;
   SDL_Rect *clips[MAX_CLIPS];
   SDL_Rect *currentClip;
   unsigned int numberOfFrames;
   unsigned int frame;
} animator;

void animator_create(animator *animator, SDL_Texture *textureSheet, unsigned int xPixels, unsigned int yPixels, unsigned int numberOfFrames);
void animator_updateFrame(animator *animator, unsigned int frameRate);
void animator_renderFrame(animator *animator, int x, int y, int width, int height, SDL_Renderer *renderTarget);
void animator_destroy(animator *animator);

#endif
