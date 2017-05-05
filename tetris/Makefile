# Makefile  for "snake" C++ application
#Created by Joosep Näks 27.03.2017

PROG = tetris
CC = g++
CPPFLAGS = -idirafter ../engine/ -Wno-write-strings -std=c++0x
LDFLAGS = -lalleg 
OBJS = tetris_main.o game.o engine.o block.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LDFLAGS)

tetris_main.o: tetris_main.cpp
	$(CC) $(CPPFLAGS) -c tetris_main.cpp

game.o: game.cpp
	$(CC) $(CPPFLAGS) -c game.cpp

engine.o: ../engine/engine.cpp
	$(CC) $(CPPFLAGS) -c ../engine/engine.cpp

block.o: block.cpp
	$(CC) $(CPPFLAGS) -c block.cpp

clean:
	rm -f $(PROG) $(OBJS)
