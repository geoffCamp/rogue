all:
	gcc -Wall -pedantic -std=c99 src/main.c src/parse.c src/utility.c src/draw.c src/hero.c -Iinclude -o bin/runMe -lncurses -lm
