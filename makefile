CC=gcc
CFLAGS=-std=c17 -g -I./include
LDFLAGS=-lm -lSDL2 -lSDL2_image -lSDL2_ttf
PROJECT_NAME=run

SOURCE_FILES=$(wildcard src/*.c)

build: main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROJECT_NAME) main.c $(SOURCE_FILES)

clean:
	rm -f $(PROJECT_NAME)
