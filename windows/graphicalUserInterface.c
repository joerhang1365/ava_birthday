#include "graphicalUserInterface.h"

void textBox_load(textBox *textBox, char *message, SDL_Renderer *renderTarget)
{
   unsigned int index = 0;
   while(message[index] != '\0')
   {
      textBox->message[index] = message[index];
      textBox->size++;
      index++;
   }
}

void textBox_render(textBox textBox, SDL_Renderer *renderTarget)
{
   SDL_Texture *boxTexture = texture_load("textbox.png", renderTarget);
   SDL_Rect boxRect = {32 * SCREEN_SCALE, 182 * SCREEN_SCALE, 192 * SCREEN_SCALE, 64 * SCREEN_SCALE};
   SDL_RenderCopy(renderTarget, boxTexture, NULL, &boxRect);
   SDL_DestroyTexture(boxTexture);

   char line[30];
   unsigned int index = 0;
   unsigned int row = 0;

   while(index < textBox.size)
   {
      for(unsigned int column = 0; column < 30; column++)
      {
         line[column] = textBox.message[index];
         index++;
      }
 
      SDL_Surface *textSurface = TTF_RenderText_Solid(font, line, color);
      SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderTarget, textSurface);
      SDL_FreeSurface(textSurface);
      SDL_Rect textRect = {37 * SCREEN_SCALE, row * 48 + 186 * SCREEN_SCALE, 176 * SCREEN_SCALE, 16 * SCREEN_SCALE};
      SDL_RenderCopy(renderTarget, textTexture, NULL, &textRect);
      SDL_DestroyTexture(textTexture);
      row++;
   }
}
