#include <iostream>
#include <allegro.h>
#include <chrono>

#include "game.h"
#include "engine.h"

game::game(){
	pillx = 1;
	pilly = 1;

	eat = false;
	arrows = true;

	vroom.FPS = 4;
	
	vroom.initScreen(10,10);

	xloc = vroom.xlen/2;
	yloc = vroom.ylen/2;
	direction = 'r';
	// r, d, l, u
    
	// ekraan
	for (int i=0; i<vroom.ylen; i++){
		for (int e=0; e<vroom.xlen; e++){
			vroom.ekraan[i][e] = ground;
		}
	}

	vroom.ekraan[yloc][xloc] = player;
	vroom.ekraan[pilly][pillx] = pill;

	lastx.push_back (xloc);
	lasty.push_back (yloc);
}

void game::run(){
    //menu();
    while (true){
	vroom.getInput();
	brainz();
	move();
	vroom.printScreen();
	std::cout << "hi";
	wait(1000/vroom.FPS);
    }
}

void game::menu(){
    pre = false;
    while (key[KEY_ENTER] != true){
        vroom.getInput();
        brainz();
        move();
        vroom.printScreen();
        std::cout << "PRESS 'ENTER' TO START";
        wait(1000/vroom.FPS);
    }    
    pre = true;
    vroom.score = 0;
}

void game::brainz(){
    if (((vroom.xstick<0) || (vroom.buttons[3]) || (key[KEY_LEFT])) && (direction != 'r')){
        direction = 'l';
    } else if (((vroom.xstick>0) || (vroom.buttons[1]) || (key[KEY_RIGHT])) && (direction != 'l')){
        direction = 'r';
    }
    if (((vroom.ystick<0) || (vroom.buttons[0]) || (key[KEY_UP])) && (direction != 'u')){
        direction = 'd';
    } else if (((vroom.ystick>0) || (vroom.buttons[2]) || (key[KEY_DOWN])) && (direction != 'd')){
        direction = 'u';
    }
    
    if (vroom.buttons[4] && vroom.FPS>0.5){
        vroom.FPS=vroom.FPS-0.5;
    } else if (vroom.buttons[5]) {
        vroom.FPS=vroom.FPS+0.5;
    }

    if (pillx == xloc && pilly == yloc && eat == false){
        vroom.score = vroom.score+1;
        vroom.FPS = vroom.FPS + 0.1;
        eat = true;
    }
}

void game::move(){
    if (!eat){
        bool draw = true;
        for (int i=1; i<lasty.size(); i++){
            if (lasty.front() == lasty[i] && lastx.front() == lastx[i]){
                draw = false;
            }
        }
        if (draw && !(lasty.front() == pilly && lastx.front() == pillx)){
            vroom.ekraan[lasty.front()][lastx.front()] = ground;
        }
         
        lastx.erase(lastx.begin());
        lasty.erase(lasty.begin());
    } else {
	// viimase kaigu jooksul on soodud
        bool gend = false;
        while (!gend){
            // votan aja randomisaarimiseks
            using namespace std::chrono;
            auto epoch = high_resolution_clock::from_time_t(0);
            auto now   = high_resolution_clock::now();
            auto seconds = duration_cast<milliseconds>(now - epoch).count();
            long mills = seconds;
            if (mills>1000){
                mills=mills%1000;
            }
        
            // uue pilli paigutamine
            eat = false;
            if (vroom.score == 1){
                vroom.ekraan[pilly][pillx] = ground;
            } else {
                vroom.ekraan[pilly][pillx] = player;
            }
            pillx = seconds % vroom.xlen;
            pilly = (seconds*(seconds/1000)+1) % vroom.ylen;
            if (vroom.ekraan[pilly][pillx] == ground){
                gend = true;
            }
        }
        vroom.ekraan[pilly][pillx] = pill;
    }
    
    actualMove(direction);
    
    bool surm = false;
    for (int i=0; i<lasty.size(); i++){
        if (yloc == lasty[i] && xloc == lastx[i]){
            surm = true;
        }
    }
    if (surm){
        exit(0);
    }
    
    lastx.push_back(xloc);
    lasty.push_back(yloc);
    vroom.ekraan[yloc][xloc] = player;
}

void game::actualMove(char dir){
    if (pre){
        if (dir == 'u' && yloc<(vroom.ylen-1)){
            yloc = yloc + 1;
        } else if (dir == 'r' && xloc<(vroom.ylen-1)){
            xloc = xloc + 1;
        } else if (dir == 'd' && yloc>0){
            yloc = yloc - 1;
        } else if (dir == 'l' && xloc>0){
            xloc = xloc - 1; 
        } else {
            exit(0);
        }
    } else {
        if (dir == 'u' && yloc<(vroom.ylen-1)){
            yloc = yloc + 1;
        } else if (dir == 'r' && xloc<(vroom.ylen-1)){
            xloc = xloc + 1;
        } else if (dir == 'd' && yloc>0){
            yloc = yloc - 1;
        } else if (dir == 'l' && xloc>0){
            xloc = xloc - 1; 
        } 
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
