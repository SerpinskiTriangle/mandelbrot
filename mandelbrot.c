#include <stdio.h>
#include <complex.h>
#include <assert.h>
#include <SDL.h>




void print_complex(double complex num){
  printf("%.2f + %.2fi\n", creal(num), cimag(num));
}


double complex evaluate(double complex iterable, double complex exponent, double complex point){
  return cpow(iterable, exponent) + point;
}


int color_point(double complex initial_value, double complex exponent, double complex point, int max_iterations){
  assert(max_iterations > 0);

  double complex temp = evaluate(initial_value, exponent, point);

  for (int i = 1; i < max_iterations; i++){
    if (cabs(temp) > 2){
      return 0;
    }

    temp = evaluate(temp, exponent, point);
  }
  
  return 1;
}

void test_pixel(SDL_Renderer **renderer){
  for (int i = 0; i < 100; i++){
    SDL_SetRenderDrawColor(*renderer,255,255,255,255);
    SDL_RenderDrawPoint(*renderer, i, i);
  }
}


double dist(double x, double y){
  return sqrt(pow(x, 2) + pow(y, 2));
}


void color_window(SDL_Renderer **renderer, int window_height, int window_width, double complex initial_value, double complex exponent, int max_iterations, double x_offset, double y_offset, double zoom){
  test_pixel(renderer);


  for (int x = 0; x < window_width; x++){
    for (int y = 0; y < window_height; y++){
      double complex point = (zoom * x + x_offset) + (zoom  * y - y_offset) * I;
      
      if(color_point(initial_value, exponent, point, max_iterations) == 0){
        SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);
        SDL_RenderDrawPoint(*renderer, x, y);
        continue;
      } else {
        SDL_SetRenderDrawColor(*renderer,255,255,255,255);
        SDL_RenderDrawPoint(*renderer, x, y);
      }
    }
  }
}


void start_sdl(const int window_height, const int window_width, SDL_Window** window, SDL_Renderer** renderer){
  SDL_Init(SDL_INIT_VIDEO);
  *window = SDL_CreateWindow("SDL2 Window", 0, 0, window_width, window_height, SDL_WINDOW_SHOWN);
  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

  SDL_SetRenderDrawColor(*renderer,0,0,0,255);
  SDL_RenderClear(*renderer);
}


void stop_sdl(SDL_Window* window, SDL_Renderer* renderer){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}






int main(){
  const Uint8 *keyboardstate;

  const int window_height = 500;
  const int window_width  = 500;

  double window_x = -3; // position of top left corner of window in unit space
  double window_y = 3;

  double zoom = .01; // size of 1 pixel in units

  double move_speed = 50; // pixels per press, per frame

  SDL_Window* window     = NULL;
  SDL_Renderer* renderer = NULL;

  SDL_Event event;

  int running = 1;

  int iterations = 15;

  start_sdl(window_height, window_width, &window, &renderer);
  SDL_RenderPresent(renderer);
    

  while (running){
    color_window(&renderer, window_height, window_width, 0, 2, iterations, window_x, window_y, zoom);
    SDL_RenderPresent(renderer);

    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT){
      break;
    }

    SDL_Delay(16); //milliseconds
    
    keyboardstate = SDL_GetKeyboardState(NULL);

    window_x += (keyboardstate[SDL_SCANCODE_RIGHT] - keyboardstate[SDL_SCANCODE_LEFT]) * zoom * move_speed;
    window_y += (keyboardstate[SDL_SCANCODE_UP] - keyboardstate[SDL_SCANCODE_DOWN])    * zoom * move_speed;

    zoom *= pow(1.01, keyboardstate[SDL_SCANCODE_SPACE] - keyboardstate[SDL_SCANCODE_LSHIFT]);

    iterations += keyboardstate[SDL_SCANCODE_Z] - keyboardstate[SDL_SCANCODE_X];
    printf("%e, %e\r", window_x, window_y);
  }
  

  stop_sdl(window, renderer);

  return 0;
}
