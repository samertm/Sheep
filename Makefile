OBJS = point.o sheep.o timer.o button.o food.o main.o 
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LIBS = -lSDL -lSDL_image -lSDL_ttf

sheepgame : $(OBJS)
	$(CC) -o sheepgame $(LFLAGS) $(OBJS) $(LIBS)

main.o : sheep.o timer.o button.o point.o
	$(CC) $(CFLAGS) main.cc

food.o : 
	$(CC) $(CFLAGS) food.cc

sheep.o : point.o
	$(CC) $(CFLAGS) sheep.cc $(LIBS)

timer.o :
	$(CC) $(CFLAGS) timer.cc -lSDL

button.o :
	$(CC) $(CFLAGS) button.cc -lSDL -lSDL_image

point.o :
	$(CC) $(CFLAGS) point.cc
