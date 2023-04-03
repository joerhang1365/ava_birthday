#include "surface.h"

SDL_Surface *optimizedSurface(char *filePath, SDL_Surface *windowSurface)
{
   SDL_Surface *optimizedSurface = NULL;
   SDL_Surface *surface = IMG_Load(filePath);
   if(surface == NULL)
   {
      printf("error creating optimized surface\n");
   }
   else
   {
      optimizedSurface = SDL_ConvertSurface(surface, windowSurface->format, 0);
      if(optimizedSurface == NULL)
      {
         printf("error converting surface\n");
      }
   }
   SDL_FreeSurface(surface);

   return optimizedSurface;
}
