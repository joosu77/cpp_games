# Makefile  for "snake" C++ application
#Created by Joosep Näks 27.03.2017

PROG = snake
CC = g++
CPPFLAGS = -idirafter ../engine/ -Wno-write-strings -std=c++0x
LDFLAGS = -lalleg 
OBJS = snake_main.o game.o engine.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LDFLAGS)

snake_main.o: snake_main.cpp
	$(CC) $(CPPFLAGS) -c snake_main.cpp

game.o: game.cpp
	$(CC) $(CPPFLAGS) -c game.cpp

engine.o: ../engine/engine.cpp
	$(CC) $(CPPFLAGS) -c ../engine/engine.cpp

clean:
	rm -f $(PROG) $(OBJS)
