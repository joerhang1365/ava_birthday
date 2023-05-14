#include "level.h"

level templateLevel =
{
   .rows = 16, 
   .columns = 16, 
   .tileSize = 16, 
   .map = {
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', 'f', ' ', ' ', ' ', ' ', 'f', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', 'f', ' ', 'g', 'g', 'g', 'g', ' ', 'f', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', 'g', ' ', ' ', 'g', ' ', ' ', ' ', ' ', ' ', ' ',
      'g', 'g', 'g', 'g', 'g', 'g', 'g', ' ', ' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g',
      ' ', ' ', ' ', ' ', 'f', ' ', 'g', 'g', 'g', 'g', ' ', 'f', ' ', ' ', 'r', ' ',
      ' ', ' ', 'l', ' ', ' ', 'f', ' ', ' ', ' ', ' ', 'f', ' ', ' ', 'r', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w',
      'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w',
      ' ', ' ', 'l', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'l', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'l', ' ',
      },
};


char level_getTile(level level, unsigned int column, unsigned int row)
{
   return level.map[row * level.columns + column];
}

void level_load(level *level, SDL_Renderer *renderTarget)
{
   // flower
   level->animations[0] = (animator*) malloc(sizeof(animator));
   level->textures[0] = texture_load("flower.png", renderTarget);
   animator_create(level->animations[0], level->textures[0], 16, 16, 2);

   // grass
   level->animations[1] = (animator*) malloc(sizeof(animator));
   level->textures[3] = texture_load("grass.png", renderTarget);
   animator_create(level->animations[1], level->textures[3], 16, 16, 4);

   // heart
   level->animations[2] = (animator*) malloc(sizeof(animator));
   level->textures[5] = texture_load("heart.png", renderTarget);
   animator_create(level->animations[2], level->textures[5], 32, 32, 4);

   // water
   level->animations[3] = (animator*) malloc(sizeof(animator));
   level->textures[7] = texture_load("water.png", renderTarget);
   animator_create(level->animations[3], level->textures[7], 16, 16, 4);

   // bigmama
   level->animations[4]  = (animator*) malloc(sizeof(animator));
   level->textures[8] = texture_load("bigmama.png", renderTarget);
   animator_create(level->animations[4], level->textures[8], 32, 32, 2);

   // birthday
   level->textures[1] = texture_load("birthday.png", renderTarget);

   // ground
   level->textures[2] = texture_load("ground.png", renderTarget);

   // wall
   level->textures[4] = texture_load("wall.png", renderTarget);

   // rock
   level->textures[6] = texture_load("rock.png", renderTarget);
}

void level_update(level *level)
{
   animator_updateFrame(level->animations[0], 60);
   animator_updateFrame(level->animations[1], 120);
   animator_updateFrame(level->animations[2], 15);
   animator_updateFrame(level->animations[3], 10);
   animator_updateFrame(level->animations[4], 120);
}

void level_render(level level, SDL_Renderer *renderTarget)
{
   for(int i = 0; i < level.columns; i++)
   {
      for(int j = 0; j < level.rows; j++)
      {
         char currentTile = level_getTile(level, i, j);
         int x = i * level.tileSize * SCREEN_SCALE;
         int y = j * level.tileSize * SCREEN_SCALE;
         int width = level.tileSize * SCREEN_SCALE;
         int height = level.tileSize * SCREEN_SCALE;
         if(currentTile != ' ')
         {
            if(currentTile == 'f')
            { 
                animator_renderFrame(level.animations[0], x, y, width, height, renderTarget);
            }
            else if(currentTile == 'w')
            {
               animator_renderFrame(level.animations[3], x, y, width, height, renderTarget);
            }
            else if(currentTile == 'g')
            {
               SDL_Rect renderRect = {x, y, width, height};
               SDL_RenderCopy(renderTarget, level.textures[2], NULL, &renderRect);
            }
            else if(currentTile == 'r')
            {
               SDL_Rect renderRect = {x, y, width, height};
               SDL_RenderCopy(renderTarget, level.textures[6], NULL, &renderRect);
            }
            else if(currentTile == 'l')
            {
               animator_renderFrame(level.animations[1], x, y, width, height, renderTarget);
            }
            else if(currentTile == 'w')
            {
               SDL_Rect renderRect = {x, y, width, height};
               SDL_RenderCopy(renderTarget, level.textures[4], NULL, &renderRect);
            }
         }
      }
   }
   
   // Birthday sign
   SDL_Rect birthdayRect = {32 * SCREEN_SCALE, 8 * SCREEN_SCALE, 192 * SCREEN_SCALE, 69 * SCREEN_SCALE};
   SDL_RenderCopy(renderTarget, level.textures[1], NULL, &birthdayRect);

   // heart
   animator_renderFrame(level.animations[2], 113 * SCREEN_SCALE, 112 * SCREEN_SCALE, 32 * SCREEN_SCALE, 32 * SCREEN_SCALE, renderTarget);
  
   // bigmama
   animator_renderFrame(level.animations[4], 32 * SCREEN_SCALE, 96 * SCREEN_SCALE, 32 * SCREEN_SCALE, 32 * SCREEN_SCALE, renderTarget);
}
