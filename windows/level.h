#ifndef LEVEL_H
#define LEVEL_H

#include "container.h"

typedef struct
{
   unsigned int rows;
   unsigned int columns;
   unsigned int tileSize;
   animator *animations[5];
   SDL_Texture *textures[9];
   char map[256];
} level;

/*
 * f = flower
 * r = rock
 * g = ground
 * l = grass
 */

extern level templateLevel;

char level_getTile(level level, unsigned int column, unsigned int row);
void level_load(level *level, SDL_Renderer *renderTarget);
void level_update(level *level);
void level_render(level level, SDL_Renderer *renderTarget);

#endif
