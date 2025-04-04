CC = gcc
TARGET = mandelbrot
LDFLAGS = -lm
CFLAGS = -Wall -Wextra

$(TARGET): mandelbrot.c
	$(CC) mandelbrot.c -o $(TARGET) $(LDFLAGS) $(CFLAGS)

clean:
	rm -rf $(TARGET)

run:$(TARGET)
	./$(TARGET)
