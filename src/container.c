#include "container.h"

SDL_Window *window = NULL;
SDL_Renderer *renderTarget = NULL;
SDL_Event event;
SDL_Rect drawingRect;

textBox myText;

// clock
float frameTime = 0;
int previousTime = 0;
int currentTime = 0;
float deltaTime = 0;

// font
TTF_Font* font = NULL;
SDL_Color color = {40, 190, 60};

bool running = true;

int container()
{
   if(initialize() == false)
   {
      return -1;
   }

   while(running)
   {
      while(SDL_PollEvent(&event) != 0)
      {
         events(&event);
      }
      update();
      render();
   }
   clean();

   return 0;
}

bool initialize()
{
   // window
   if(SDL_Init(SDL_INIT_VIDEO) > 0)
   {
      printf("video initialization error\n");
      return false;
   }
   else
   {
      window = SDL_CreateWindow("It's Ya Birthday Baby", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            SCREEN_WIDTH * SCREEN_SCALE, SCREEN_HEIGHT * SCREEN_SCALE, SDL_WINDOW_SHOWN);
      if(window == NULL)
      {
         printf("window creation error\n");
         return false;
      }
   }

   // renderer
   renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

   // image flags
   int imageFlags = IMG_INIT_PNG | IMG_INIT_JPG;
   if(!(IMG_Init(imageFlags) & imageFlags))
   {
      printf("error unknown image type\n");
   }

   // initialize ttf
   if(TTF_Init() == -1)
   {
      printf("error initializing ttf\n");
      return false;
   }

   font = TTF_OpenFont("src/fonts/serif.ttf", 12);
   if(font == NULL)
   {
      printf("error creating font\n");
      return false;
   }

   level_load(&templateLevel, renderTarget);
   textBox_load(&myText, "What is going on? Where can I get one of those?", renderTarget);

   return true;
}

void events(SDL_Event *event)
{
   if(event->type == SDL_QUIT)
   {
      running = false;
   }
}

void update()
{
   // sets framerate
   previousTime = currentTime;
   currentTime = SDL_GetTicks();
   deltaTime = (currentTime - previousTime) / 1000.0f;

   frameTime += deltaTime;
   if(frameTime >= (float) 1 / MAX_FRAMERATE)
   {
      frameTime = 0;
      // add things here
      level_update(&templateLevel);
   }
}

void render()
{
   //Clear screen
   SDL_SetRenderDrawColor(renderTarget, 1.0f, 1.0f, 1.0f, 1.0f);
   SDL_RenderClear(renderTarget);
   SDL_SetRenderDrawColor(renderTarget, 14.0f, 96.0f, 39.0f, 1.0f);

   level_render(templateLevel, renderTarget);
   textBox_render(myText, renderTarget);

   // pixel grid lines
   SDL_SetRenderDrawColor(renderTarget, 1.0f, 1.0f, 1.0f, 1.0f);
   for(int i = 0; i < SCREEN_HEIGHT * SCREEN_SCALE; i += SCREEN_SCALE)
   {
      SDL_RenderDrawLine(renderTarget, 0, i, SCREEN_WIDTH * SCREEN_SCALE, i);
   }

   for(int i = 0; i < SCREEN_WIDTH * SCREEN_SCALE; i += SCREEN_SCALE)
   {
      SDL_RenderDrawLine(renderTarget, i, 0, i, SCREEN_HEIGHT * SCREEN_SCALE);
   }

   SDL_RenderPresent(renderTarget);
}

void clean()
{
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderTarget);
   window = NULL;
   renderTarget = NULL;
   IMG_Quit();
   SDL_Quit();
}

