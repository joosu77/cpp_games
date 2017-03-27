#include <vector>

#ifndef ENGINE_H
#define ENGINE_H

class engine{
    public:
        void getInput();
        void printScreen();
        void initScreen(int, int);	
        
        engine();
        
        static int const NUM_BUTTONS =10;
        bool buttons [NUM_BUTTONS];
        //buttons: x,a,b,y,L,R,<>,<>,select,start
        
        bool joyst;
        
        int xstick;
        int ystick;
        
        int xlen;
        int ylen;
        std::vector < std::vector<char> > ekraan; 
        int score;
        float FPS;
};

#endif