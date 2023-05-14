#include "texture.h"

SDL_Texture *texture_load(char *filePath, SDL_Renderer *renderTarget)
{
   SDL_Texture *texture = NULL;
   SDL_Surface *surface = IMG_Load(filePath);
   if(surface == NULL)
   {
      printf("error creating texture surface\n");
   }
   else
   {
      texture = SDL_CreateTextureFromSurface(renderTarget, surface);
      if(texture == NULL)
      {
         printf("error creating texture\n");
      }
   }
   SDL_FreeSurface(surface);

   return texture;
}
