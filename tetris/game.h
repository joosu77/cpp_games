#include "engine.h"
#include "block.h"

#ifndef GAME_H
#define GAME_H

class game{
    private:
        block tetromino;
        engine vroom;
        int cooldown = 0;
        
        char const static ground = ' ';
        char const static active_piece = 'A';
        char const static passive_piece = 'V';
        
        void brainz();
        void wait(long);
    public:
        game();
        void run();
};

#endif