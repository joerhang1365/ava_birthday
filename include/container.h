#ifndef CONTAINER_H
#define CONTAINER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "surface.h"
#include "texture.h"
#include "animator.h"
#include "level.h"

#define PI 3.14159264

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256
#define SCREEN_SCALE 3
#define MAX_FRAMERATE 60
#define TILE_SIZE 16

extern float frameTime;
extern int previousTime;
extern int currentTime;
extern float deltaTime;

int container();
bool initialize();
void events(SDL_Event *event);
void update();
void render();
void clean();

#endif
