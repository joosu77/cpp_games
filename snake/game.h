#include <vector>
#include "engine.h"

#ifndef GAME_H
#define GAME_H

class game{
    private:
        void brainz();
        void move();
        void wait(long);
        
        engine vroom;
        
	int xloc;
	int yloc;
	std::vector <int> lastx;
	std::vector <int> lasty;
	char direction;
	// r, d, l, u

	int pillx;
	int pilly;

	bool eat;
	bool arrows;

	static char const ground = ' ';
	static char const player = 'M';
	static char const pill = 'p';	
    public:
    	game();
        void run();
};

#endif