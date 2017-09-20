#include <vector>
#include "engine.h"

#ifndef MINESWEEPER_H
#define MINESWEEPER_H

class minesweeper{
    public:
        engine vroom;
        std::vector<int[2]> bombs;
        bool hit = false;
        int count = 0;
        void click(int, int);
        void flag(int, int);
        void cycle();
        void setup(int, int);
        minesweeper();
        char ground = ' ';
};

#endif