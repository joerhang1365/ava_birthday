#include "container.h"

SDL_Window *window = NULL;
SDL_Renderer *renderTarget = NULL;
SDL_Event event;
SDL_Rect drawingRect;

textBox myText;

animator *x_animator = NULL;
SDL_Texture *x_texture = NULL;

// clock
float frameTime = 0;
int previousTime = 0;
int currentTime = 0;
float deltaTime = 0;

// font
TTF_Font* font = NULL;
SDL_Color color = {40, 230, 60};

// keys
bool x_key = false;

bool running = true;

char *message = "Dear Ava,\n\nIt still amazes me how we came to find each other. You match and pair with me perfectly in all of your incredible ways. I love how you build robots, cook, sing, go to concerts, lifeguard, workout, babysit, and have a wild but fantastic family. You are there for me when I need you and when I am struggling. I do not know where I would be right now without you. It is so funny how we came together. If you had not annoyingly following Bailey around and sat with us for lunch I never would have spoken with you. I will always think about you even when I cannot be with you. Thank you for all the happiness and excitment you give me.\n\nLove, Joseph\n";

int container()
{
   if(initialize() == false)
   {
      return -1;
   }

   printf("%s", message);

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
      window = SDL_CreateWindow("Birtday Time", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
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

   font = TTF_OpenFont("serif.ttf", 12);
   if(font == NULL)
   {
      printf("error creating font\n");
      return false;
   }

   level_load(&templateLevel, renderTarget);
   textBox_load(&myText, "Shine bright today and remeber to have a GOOD TIMES", renderTarget);

   x_animator = (animator*) malloc(sizeof(animator));
   x_texture = texture_load("pressx.png", renderTarget);
   animator_create(x_animator, x_texture, 32, 16, 2);

   return true;
}

void events(SDL_Event *event)
{
   if(event->type == SDL_QUIT)
   {
      running = false;
   }
   else if(event->type == SDL_KEYDOWN)
   {
      if(event->key.keysym.sym == SDLK_x)
      {
         x_key = true;
      }
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
      animator_updateFrame(x_animator, 10);
   }
}

void render()
{
   //Clear screen
   SDL_SetRenderDrawColor(renderTarget, 1.0f, 1.0f, 1.0f, 1.0f);
   SDL_RenderClear(renderTarget);
   SDL_SetRenderDrawColor(renderTarget, 14.0f, 96.0f, 39.0f, 1.0f);

   level_render(templateLevel, renderTarget);
   animator_renderFrame(x_animator, 116 * SCREEN_SCALE, 232 * SCREEN_SCALE, 32 * SCREEN_SCALE, 16 * SCREEN_SCALE, renderTarget);
   if(x_key == true)
   {
      textBox_render(myText, renderTarget);
   }

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

