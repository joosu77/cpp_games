# Makefile  for "kuubik" C++ application
#Created by Joosep N�ks 27.03.2017

PROG = kuubik
CC = g++
CPPFLAGS = -idirafter ../engine/ -Wno-write-strings -std=c++0x
LDFLAGS = -lalleg 
OBJS = main.o kuubik.o engine.o

all: $(PROG)

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

kuubik.o: kuubik.cpp
	$(CC) $(CPPFLAGS) -c kuubik.cpp

engine.o: ../engine/engine.cpp
	$(CC) $(CPPFLAGS) -c ../engine/engine.cpp

clean:
	rm -f $(PROG) $(OBJS)
