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


int main(){
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;
  int running;

  const int window_width;
  const int window_height;
  
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(window_width,window_height,0,&window,&renderer);

  
  double complex point = 2.0;
  double complex exponent = 2.0;
  double complex constant = -1.0;

  double complex result = iterate(point, exponent, constant, 5);

  print_complex(result);
  return 0;
}
