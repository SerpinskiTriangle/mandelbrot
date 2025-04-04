CC = gcc
TARGET = mandelbrot
LDFLAGS = -lm -lSDL2
CFLAGS = -Wall -Wextra
SDLFLAGS =  $(shell sdl2-config --cflags) $(shell sdl2-config --libs)


$(TARGET): mandelbrot.c
	$(CC) mandelbrot.c -o $(TARGET) $(LDFLAGS) $(CFLAGS) $(SDLFLAGS)

clean:
	rm -rf $(TARGET)

run:$(TARGET)
	./$(TARGET)
