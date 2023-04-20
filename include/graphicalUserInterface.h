#ifndef GRAPHICAL_USER_INTERFACE
#define GRAPHICAL_USER_INTERFACE

#include "container.h"

#define MAX_TEXT_WIDTH 20

typedef struct
{
   char message[300];
   unsigned int size;
} textBox;

void textBox_load(textBox *textBox, char *message, SDL_Renderer *renderTarget);
void textBox_render(textBox textBox, SDL_Renderer *renderTarget);

#endif
