#include <string>
#include <vector>

#ifndef BLOCK_H
#define BLOCK_H

class block{
    public:
        char shape;
        // dir - paripaeva (0 - yles, 1 paremale)
        int dir = 0;
        
        int dist_up;
        int dist_down;
        int dist_right;
        int dist_left;
        int blueprint [5][5];
        int xloc;
        int yloc;
        int xl;
        int yl;
        
        block();
        std::vector< std::vector<char> > create(int, int, std::vector< std::vector<char> >);
        std::vector< std::vector<char> > deactivate(std::vector< std::vector<char> >);
        std::vector< std::vector<char> > move(int, std::vector< std::vector<char> >);
        void shapeInit();
        bool checker(int, int, std::vector< std::vector<char> >, int);
        void fillBlueprint();
        std::vector< std::vector<char> > drawTetromino(std::vector< std::vector<char> >, bool, bool);
    private:
        const static char active_piece = 'A';
        const static char passive_piece = 'V';
        const static char ground = ' ';
         
        std::string metaBlueprint;
        char shape_bag [6];
};

#endif