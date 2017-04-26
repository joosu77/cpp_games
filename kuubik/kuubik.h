#include <vector>
#include "engine.h"

#ifndef KUUBIK_H
#define KUUBIK_H

class kuubik{
    private:
        engine vroom;
        int xl;
        int yl;
        std::vector<std::vector<std::vector<int> > > kuup;
        const char ground = ' ';
        
        void scramble();
        void lahenda();
        void sideClockwise(int);
        void fillABC(std::vector<int>, std::vector<int>);
        char charof(int);
        
        int* turnLines [6][12];
        
        /*
        std::vector<int*> a;
        std::vector<int*> b;
        std::vector<int*> c;
        std::vector<int*> d;
        */
        int* a [3];
        int* b [3];
        int* c [3];
        int* d [3];
    public:
        void ekraanile();
        kuubik();
        void run();
        void turn(char, bool);
};

#endif