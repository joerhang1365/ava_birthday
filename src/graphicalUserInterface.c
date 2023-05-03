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
   SDL_Texture *boxTexture = texture_load("src/images/textbox.png", renderTarget);
   SDL_Rect boxRect = {32 * SCREEN_SCALE, 182 * SCREEN_SCALE, 192 * SCREEN_SCALE, 64 * SCREEN_SCALE};
   SDL_RenderCopy(renderTarget, boxTexture, NULL, &boxRect);

   char row[MAX_TEXT_WIDTH];
   unsigned int index = 0;
   unsigned int rows = 0;
   unsigned int column = 0;
   while(index < textBox.size)
   {
      while(column < MAX_TEXT_WIDTH)
      {
         row[column] = textBox.message[index];
         column++;
         index++;
      }
      
      SDL_Surface *textSurface = TTF_RenderText_Solid(font, row, color);
      SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderTarget, textSurface);
      SDL_Rect textRect = {37 * SCREEN_SCALE, rows * 48 + 182 * SCREEN_SCALE, 176 * SCREEN_SCALE, 16 * SCREEN_SCALE};
      SDL_RenderCopy(renderTarget, textTexture, NULL, &textRect);
      column = 0;
      rows++;
   }
}
