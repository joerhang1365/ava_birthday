#include "animator.h"

void animator_create(animator *animator, SDL_Texture *textureSheet, unsigned int xPixels, unsigned int yPixels, unsigned int numberOfFrames)
{
   for(int i = 0; i < numberOfFrames; i++)
   {
      animator->clips[i] = malloc(sizeof(SDL_Rect));
      if(animator->clips[i] == NULL)
      {
         printf("error allocting memory for clip %d\n", i);
      }
      animator->clips[i]->x = i * xPixels;
      animator->clips[i]->y = 0;
      animator->clips[i]->w = xPixels;
      animator->clips[i]->h = yPixels;
   }
   animator->textureSheet = textureSheet;
   animator->currentClip = animator->clips[0];
   animator->numberOfFrames = numberOfFrames;
   animator->frame = 0;
}

void animator_updateFrame(animator *animator, unsigned int frameRate)
{
   animator->currentClip = animator->clips[animator->frame / frameRate];
   ++animator->frame;
   if(animator->frame / frameRate > animator->numberOfFrames - 1)
   {
      animator->frame = 0;
   }
}

void animator_renderFrame(animator *animator, int x, int y, int width, int height, SDL_Renderer *renderTarget)
{
   SDL_Rect renderQuad = {x, y, width, height};
   SDL_RenderCopy(renderTarget, animator->textureSheet, animator->currentClip, &renderQuad);
}

void animator_destroy(animator *animator)
{
   for(int i = 0; i < animator->numberOfFrames; i++)
   {
      free(animator->clips[i]);
   }
}
