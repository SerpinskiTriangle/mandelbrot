#include <stdio.h>
#include <complex.h>
#include <assert.h>
#include <SDL.h>




void print_complex(double complex num){
  printf("%.2f + %.2fi\n", creal(num), cimag(num));
}
double complex evaluate(double complex point, double complex exponent, double complex constant){
  return cpow(point, exponent) + constant;
}


double complex iterate(double complex point, double complex exponent, double complex constant, int iterations){ 
  //recustion would be possible and cool but it's not good practice
  assert(iterations > 0);

  double complex temp = evaluate(point, exponent, constant);

  for (int i = 1; i < iterations; i++){
    temp = evaluate(temp, exponent, constant);
  }

  return temp;
}


int color_point(double complex point, double complex exponent, double complex constant, int max_iterations){
  assert(max_iterations > 0);

  double complex temp = evaluate(point, exponent, constant);

  for (int i = 1; i < max_iterations; i++){
    if (creal(temp) > 2 || cimag(temp) > 2){
      return 0;
    }

    temp = evaluate(temp, exponent, constant);
  }
  
  return 1;
}


void start_sdl(){
  SDL_Event event;
  int running;

  const int window_width = 800;
  const int window_height = 800;
  
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("SDL2 Window", 0, 0, window_height, window_width, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderClear(renderer);
}


void stop_sdl(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}


int main(){
  start_sdl();

  SDL_RenderPresent(renderer);
  SDL_Delay(2000); //milliseconds

  stop_sdl();

  return 0;
}
