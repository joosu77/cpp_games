#include <chrono>
#include <vector>
#include <allegro.h>
<<<<<<< HEAD
#include <string>
#include <iostream>
=======
>>>>>>> a6e380d... Init

#include "block.h"

block::block(){
    shape_bag[0] = 'I';
    shape_bag[1] = 'L';
    shape_bag[2] = 'J';
    shape_bag[3] = 'S';
    shape_bag[4] = 'Z';
    shape_bag[5] = 'T';
}

std::vector< std::vector<char> > block::create(int xlen, int ylen, std::vector< std::vector<char> > screen){
    xloc = xlen/2;
    yloc = 3;
    xl = xlen;
    yl = ylen;
    
    // valin, mis kujuga tykk on
    using namespace std::chrono;
    auto epoch = high_resolution_clock::from_time_t(0);
    auto now   = high_resolution_clock::now();
    auto seconds = duration_cast<milliseconds>(now - epoch).count();
    shape = shape_bag [seconds%7];
    
    shapeInit();
<<<<<<< HEAD
    fillBlueprint();
=======
>>>>>>> a6e380d... Init
    return drawTetromino(screen, 0, 0);
}

std::vector< std::vector<char> > block::deactivate(std::vector< std::vector<char> > screen){
    return drawTetromino(screen, 0, 1);
}

std::vector< std::vector<char> > block::drawTetromino(std::vector< std::vector<char> > screen, bool del, bool deact){
    for (int y=0;y<5;y++){
        for (int x=0;x<5;x++){
            int absx = (xloc+x)-3;
            int absy = (yloc+y)-3;
<<<<<<< HEAD
            bool print = false;
            if (dir == 0 && blueprint[y][x]){
                //allegro_message("er");
                print = true;
            } else if (dir == 1 && blueprint[5-x][y]){
                print = true;
            } else if (dir == 2 && blueprint[5-y][5-x]){
                print = true;
            } else if (dir == 3 && blueprint[x][5-y]){
                print = true;
            }
            if (print){
                if (y>4 || x>4 || absx>=xl || absy>=yl || y<0 || x<0 || absx<0 || absy<0){
                    allegro_message("y: %d, x: %d, absy: %d, absx: %d, dir: %d, yloc: %d", y, x, absy, absx, dir, yloc);
=======
            
            if (blueprint[y][x]){
                if (y>4 || x>4 || absx>xl || absy>yl || y<0 || x<0 || absx<0 || absy<0){
                    allegro_message("y: %d, x: %d, absy: %d, absx: %d", y, x, absy, absx);
>>>>>>> a6e380d... Init
                }
                if (del){
                    screen [absy][absx] = ground;
                } else if (deact){
                    screen [absy][absx] = passive_piece;
                } else {
<<<<<<< HEAD
                    //allegro_message("absy: %d, yloc: %d", absy, yloc);
=======
>>>>>>> a6e380d... Init
                    screen [absy][absx] = active_piece;
                }
            }
        }
    }
<<<<<<< HEAD
    //allegro_message("ender");
=======
>>>>>>> a6e380d... Init
    return screen;
}

std::vector< std::vector<char> > block::move(int way, std::vector< std::vector<char> > screen){
<<<<<<< HEAD
    screen = drawTetromino(screen, 1, 0);
    if (way == 1 && checker(xloc+1, yloc, screen, 0)){
        xloc = xloc+1;
    } else if (way == 2 && checker(xloc, yloc+1, screen, 0)){
        yloc = yloc+1;
        allegro_message("yloc: %d", yloc);
=======
    drawTetromino(screen, 1, 0);
    if (way == 1 && checker(xloc+1, yloc, screen, 0)){
        xloc = xloc+1;
    } else if (way == 2 && checker(xloc, yloc-1, screen, 0)){
        yloc = yloc-1;
>>>>>>> a6e380d... Init
    } else if (way == 3 && checker(xloc-1, yloc, screen, 0)){
        xloc = xloc-1;
    } else if (way == 9 && checker(xloc, yloc, screen, -1)){
        dir = dir-1;
    } else if (way == 11 && checker(xloc, yloc, screen, 1)){
        dir = dir+1;
    } else {
        return std::vector< std::vector<char> > ();
    }
<<<<<<< HEAD
    //drawTetromino(screen, 0, 0);
    //allegro_message("usfhniusdnf");
    screen = drawTetromino(screen, 0,0);
    
    
    
=======
    drawTetromino(screen, 0, 0);
    allegro_message("usfhniusdnf");
>>>>>>> a6e380d... Init
    return screen;
}

void block::shapeInit(){
    switch(shape) {
        case 'I':
            dist_up = 1;
            dist_down = 2;
            dist_right = 0;
            dist_left = 0;
    
            metaBlueprint = "00000 00100 00100 00100 00100";
            break;
        case 'L':
            dist_up = 1;
            dist_down = 1;
            dist_right = 1;
            dist_left = 0;
    
            metaBlueprint = "00000 00100 00100 00110 00000";
            break;
        case 'J':
            dist_up = 1;
            dist_down = 1;
            dist_right = 0;
            dist_left = 1;
    
            metaBlueprint = "00000 00100 00100 01100 00000";
            break;
        case 'S':
            dist_up = 0;
            dist_down = 1;
            dist_right = 1;
            dist_left = 1;
    
            metaBlueprint = "00000 00000 00110 01100 00000";
            break;
        case 'Z':
            dist_up = 0;
            dist_down = 1;
            dist_right = 1;
            dist_left = 1;
    
            metaBlueprint = "00000 00000 01100 00110 00000";
            break;
        case 'T':
            dist_up = 0;
            dist_down = 1;
            dist_right = 1;
            dist_left = 1;
    
            metaBlueprint = "00000 00000 01110 00100 00000";
            break;
    }
}

bool block::checker(int nxloc, int xyloc, std::vector< std::vector<char> > screen, int deltad){
    if ((dir+deltad)==0 && (xloc+dist_right)<xl &&
    (xloc-dist_left)>=0 && (yloc+dist_down)<yl){
        for (int y=0;y<5;y++){
            for (int x=0;x<5;x++){
                int absx = (xloc+x)-3;
                int absy = (yloc+y)-3;
<<<<<<< HEAD
                if (blueprint[y][x] && screen[absy][absx] != passive_piece){
                    return true;
                }
=======
                /*if (blueprint[y][x] && screen[absy][absx] == passive_piece){
                    return false;
                }*/
>>>>>>> a6e380d... Init
            }
        }
    } else if ((dir+deltad)==1 && (xloc+dist_up)<xl &&
    (xloc-dist_down)>=0 && (yloc+dist_right)<yl){
        for (int y=0;y<5;y++){
            for (int x=0;x<5;x++){
                int absx = (xloc+x)-3;
                int absy = (yloc+y)-3;
<<<<<<< HEAD
                if (blueprint[5-x][y] && screen[absy][absx] != passive_piece){
                    return true;
                }
=======
                /*if (blueprint[x][5-y] && screen[absy][absx] == passive_piece){
                    return false;
                }*/
>>>>>>> a6e380d... Init
            }
        }
    } else if ((dir+deltad)==2 && (xloc+dist_left)<xl &&
    (xloc-dist_right)>=0 && (yloc+dist_up)<yl){
        for (int y=0;y<5;y++){
            for (int x=0;x<5;x++){
                int absx = (xloc+x)-3;
                int absy = (yloc+y)-3;
<<<<<<< HEAD
                if (blueprint[5-y][5-x] && screen[absy][absx] != passive_piece){
                    return true;
                }
=======
                /*if (blueprint[5-y][5-x] && screen[absy][absx] == passive_piece){
                    return false;
                }*/
>>>>>>> a6e380d... Init
            }
        }
    } else if ((dir+deltad)==3 && (xloc+dist_down)<xl &&
    (xloc-dist_up)>=0 && (yloc+dist_left)<yl){
        for (int y=0;y<5;y++){
            for (int x=0;x<5;x++){
                int absx = (xloc+x)-3;
                int absy = (yloc+y)-3;
<<<<<<< HEAD
                if (blueprint[x][5-y] && screen[absy][absx] != passive_piece){
                    return true;
                }
            }
        }
    }
    return false;
}

void block::fillBlueprint(){
    /*allegro_message("sdfuigsdivgsdovbfcxukyvg");
    
    std::vector<char> a;
    for (int i=0;i<35;i++){
        a.push_back(metaBlueprint[i]);
    }
    for (int i=0;i<35;i++){
        allegro_message(&a[i]);
    }
    std::vector<char> tmpstr;
    tmpstr.push_back(' ');
    */
    for (int y=0;y<5;y++){
        for (int x=0;x<5;x++){
            /*if (metaBlueprint[y*6+x] == 1){
                blueprint[y][x] = true;
            } else {
                blueprint[y][x] = false;
            }*/
            blueprint[y][x] = metaBlueprint[y*6+x];
            //allegro_message(&metaBlueprint[y*6+x]);
            //tmpstr.push_back(metaBlueprint[y*6+x]);
        }
        //tmpstr.push_back(' ');
    }
    //for(int i=0;i<10;i++){
        //allegro_message(&tmpstr[i]);
    //}
    allegro_message("dist_up: %d, dist_down: %d", dist_up, dist_down);
=======
                /*if (blueprint[5-x][5-y] && screen[absy][absx] == passive_piece){
                    return false;
                }*/
            }
        }
    }
    return true;
}

void block::fillBlueprint(){
    for (int y=0;y<5;y++){
        for (int x=0;x<5;x++){
            blueprint[y][x] = metaBlueprint[y*6+x];
        }
    }
>>>>>>> a6e380d... Init
}