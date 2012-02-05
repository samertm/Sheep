OBJS = sheep.o timer.o button.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LIBS = -lSDL -lSDL_image -lSDL_ttf

sheepgame : $(OBJS)
	$(CC) -o sheepgame $(LFLAGS) $(OBJS) $(LIBS)

main.o : sheep.h sheep.cc timer.h button.h
	$(CC) $(CFLAGS) main.cc $(LIBS)

sheep.o : sheep.h sheep.cc
	$(CC) $(CFLAGS) sheep.cc $(LIBS)

timer.o : timer.h timer.cc
	$(CC) $(CFLAGS) timer.cc -lSDL

button.o : button.h button.cc
	$(CC) $(CFLAGS) button.cc -lSDL -lSDL_image

clean :
	rm $(OBJS) sheepgame
