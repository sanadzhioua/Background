prog: main.o back.o
	gcc main.o back.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

main.o: main.c back.h
	gcc -c main.c

back.o: back.c back.h
	gcc -c back.c

