#include <chrono>
#include <vector>
#include <allegro.h>

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
            
            if (blueprint[y][x]){
                if (y>4 || x>4 || absx>xl || absy>yl || y<0 || x<0 || absx<0 || absy<0){
                    allegro_message("y: %d, x: %d, absy: %d, absx: %d", y, x, absy, absx);
                }
                if (del){
                    screen [absy][absx] = ground;
                } else if (deact){
                    screen [absy][absx] = passive_piece;
                } else {
                    screen [absy][absx] = active_piece;
                }
            }
        }
    }
    return screen;
}

std::vector< std::vector<char> > block::move(int way, std::vector< std::vector<char> > screen){
    drawTetromino(screen, 1, 0);
    if (way == 1 && checker(xloc+1, yloc, screen, 0)){
        xloc = xloc+1;
    } else if (way == 2 && checker(xloc, yloc-1, screen, 0)){
        yloc = yloc-1;
    } else if (way == 3 && checker(xloc-1, yloc, screen, 0)){
        xloc = xloc-1;
    } else if (way == 9 && checker(xloc, yloc, screen, -1)){
        dir = dir-1;
    } else if (way == 11 && checker(xloc, yloc, screen, 1)){
        dir = dir+1;
    } else {
        return std::vector< std::vector<char> > ();
    }
    drawTetromino(screen, 0, 0);
    allegro_message("usfhniusdnf");
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
                /*if (blueprint[y][x] && screen[absy][absx] == passive_piece){
                    return false;
                }*/
            }
        }
    } else if ((dir+deltad)==1 && (xloc+dist_up)<xl &&
    (xloc-dist_down)>=0 && (yloc+dist_right)<yl){
        for (int y=0;y<5;y++){
            for (int x=0;x<5;x++){
                int absx = (xloc+x)-3;
                int absy = (yloc+y)-3;
                /*if (blueprint[x][5-y] && screen[absy][absx] == passive_piece){
                    return false;
                }*/
            }
        }
    } else if ((dir+deltad)==2 && (xloc+dist_left)<xl &&
    (xloc-dist_right)>=0 && (yloc+dist_up)<yl){
        for (int y=0;y<5;y++){
            for (int x=0;x<5;x++){
                int absx = (xloc+x)-3;
                int absy = (yloc+y)-3;
                /*if (blueprint[5-y][5-x] && screen[absy][absx] == passive_piece){
                    return false;
                }*/
            }
        }
    } else if ((dir+deltad)==3 && (xloc+dist_down)<xl &&
    (xloc-dist_up)>=0 && (yloc+dist_left)<yl){
        for (int y=0;y<5;y++){
            for (int x=0;x<5;x++){
                int absx = (xloc+x)-3;
                int absy = (yloc+y)-3;
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
}