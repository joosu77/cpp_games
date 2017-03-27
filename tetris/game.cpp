#include <iostream>
#include <allegro.h>
#include <chrono>

#include "game.h"
#include "engine.h"
#include "block.h"

game::game(){
    vroom.FPS = 4;
    
    int xl = 10;
    int yl = 20;
    vroom.initScreen(xl, yl);
    
    for (int i=0; i<vroom.ylen; i++){
        for (int u=0; u<vroom.xlen; u++){
            vroom.ekraan[i][u] = ground;
        }
    }
    
    tetromino.create(xl, yl, vroom.ekraan);
}

void game::run(){
    while (true){
        vroom.getInput();
        brainz();
        vroom.printScreen();
        wait(1000/vroom.FPS);
    }
}

void game::brainz(){
    if (cooldown == 16){
        tetromino.deactivate(vroom.ekraan);
        tetromino.create(vroom.xlen, vroom.ylen, vroom.ekraan);
    }
    bool stopped = false;
    if (vroom.xstick<0){
        std::vector< std::vector<char> > i = tetromino.move(3, vroom.ekraan);
        if (i == std::vector< std::vector<char> > ()){
            stopped = true;
        } else {
            vroom.ekraan = i;
        }
        
    } else if (vroom.xstick>0){
        std::vector< std::vector<char> > i = tetromino.move(1, vroom.ekraan);
        if (i == std::vector< std::vector<char> > ()){
            stopped = true;
        } else {
            vroom.ekraan = i;
        }
    } else if (vroom.ystick>0){
        std::vector< std::vector<char> > i = tetromino.move(2, vroom.ekraan);
        if (i == std::vector< std::vector<char> > ()){
            stopped = true;
        } else {
            vroom.ekraan = i;
        }
    }
    std::vector< std::vector<char> > i = tetromino.move(2, vroom.ekraan);
    if (stopped && i == std::vector< std::vector<char> > ()){
        cooldown++;
    } else {
        cooldown = 0;
        vroom.ekraan = i;
    }

}

void game::wait(long milliSeconds){
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    auto now = high_resolution_clock::now();
    auto interval = duration_cast<milliseconds>(now - start).count();

    while(interval<milliSeconds){
        vroom.getInput();
        brainz();
        usleep(100000);
        now = high_resolution_clock::now();
        interval = duration_cast<milliseconds>(now-start).count();
    }
}