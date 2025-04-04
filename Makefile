CC = gcc
TARGET = mandelbrot

$(TARGET): mandelbrot.c
	$(CC) mandelbrot.c -o $(TARGET)

clean:
	rm -rf $(TARGET)

run:$(TARGET)
	./$(TARGET)
