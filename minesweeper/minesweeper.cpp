#include <iostream>

#include "minesweeper.h"
#include "engine.h"

minesweeper::minesweeper(){
    vroom.FPS = 1;

    for (int i=0; i<vroom.ylen; i++){
        for (int u=0; u<vroom.xlen; u++){
            vroom.ekraan[i][u] = ground;
        }
    }
}

void minesweeper::setup(int xt, int yt){
    int xl = 10;
    int yl = 10;
    vroom.initScreen(xl, yl);
    
    int bomb_num = 4;
    for (int i=0; i<bomb_num; i++){
        int xb = rand() % xl;
        int yb = rand() % yl;
        bombs.push_back({xl,yl});
    }
}

void minesweeper::click(int xl, int yl){
    for (int i=0;i<bombs.length();i++){
        if (xl == bombs[i][0] && yl == bombs[i][y]){
            hit = true;
        }
    }
    if (!hit){
        vroom.ekraan[xl][yl] = 'P';
    } else {
        int num = 0;
        for (int i=0;i<bombs.length(); i++){
            for (int x=0;x<3;x++){
                for (int y=0;x<3;x++){
                    if (bombs[i][0] == (x+xl-1) && bombs[i][1] == (y+yl-1)){
                        num = num +1;
                    }
                }
            }
        }
        vroom.ekraan[xl][yl] = num;
        count = count + 1;
    }
}

void minesweeper::flag(int xl, int yl){
    vroom.ekraan[xl][yl] = 'F';
}

void minesweeper::cycle(){
    bool end = false;
    while (!end){
        char* inp << std::cin;
        char* chars = '0';
        char* ints = '0';
        
        for (int i=0;i<strlen(inp)-1;i++){
            if (char(inp[i]) > 47 && char(inp[i]) < 58){
                ints = ints + inp[i];
            } else if (char(inp[i]) > 64 && char(inp[i]) < 90){
                chars = chars + inp[i];
            }
        }
        
        int x = int(chars);
        int y = ints;
        
        if (inp.last() == 'F'){
            flag(x,y);
        } else if (inp.last() == 'B'){
            click(x,y);
        } else {
            std::cout << "error in input";
        }
        
        click(x,y);
        
        if (hit || count > bomb_num){
            end = true;
        }
    }
}