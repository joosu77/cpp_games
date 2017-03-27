#include <iostream>
#include <allegro.h>
#include <unistd.h>
#include <vector>
#include <time.h>
#include <ctime>
#include <chrono>

int const NUM_BUTTONS = 10;
bool buttons [NUM_BUTTONS] = {false, false, false, false, false, false, false, false, false, false};
//buttons: x, a, b, y, L, R, <>, <>, select, start
bool arrows = true;
bool joyst = true;

int xstick = 0;
int ystick = 0;

int const xlen = 10;
int const ylen = 10;
char ekraan[ylen][xlen];

int xloc = xlen/2;
int yloc = ylen/2;
std::vector <int> lastx;
std::vector <int> lasty;
char direction = 'r';
// r, d, l, u

int score = 0;
int pillx = 1;
int pilly = 1;

bool eat = false;

float FPS = 4;

char const ground = ' ';
char const player = 'M';
char const pill = 'p';

void getInput();
void printScreen();
void brainz();
void move();
void custom_init();
void wait(long);

int main(void){
    custom_init();
    
    while (true){
        getInput();
        brainz();
        move();
        printScreen();
        wait(1000/FPS);
    }
}

void custom_init(){
    // allegro
    allegro_init();
    /*if (install_joystick(JOY_TYPE_AUTODETECT) == 0){
        install_keyboard();
        joyst = false;
    }*/
    install_joystick(JOY_TYPE_AUTODETECT);
    set_gfx_mode(GFX_SAFE, 10,10,10,10);
    
    // ekraan
    for (int i=0; i<ylen; i++){
        for (int e=0; e<xlen; e++){
            ekraan[i][e] = ground;
        }
    }
    
    ekraan[yloc][xloc] = player;
    ekraan[pilly][pillx] = pill;
    
    lastx.push_back (xloc);
    lasty.push_back (yloc);
}

void brainz(){
    if (joyst){
        if (arrows){
            if (xstick<0 && (direction != 'r')){
                direction = 'l';
            } else if (xstick>0 && (direction != 'l')){
                direction = 'r';
            }
            if (ystick<0 && (direction != 'u')){
                direction = 'd';
            } else if (ystick>0 && (direction != 'd')){
                direction = 'u';
            }
        } else {
            if (buttons[0] && (direction != 'u')){
                direction = 'd';
            } else if (buttons[2] && (direction != 'd')){
                direction = 'u';
            }
            if (buttons[1] && (direction != 'l')){
                direction = 'r';
            } else if (buttons[3] && (direction != 'r')){
                direction = 'l';
            }
        }
        if (buttons[4] && FPS>0.5){
            FPS=FPS-0.5;
        } else if (buttons[5]) {
            FPS=FPS+0.5;
        }
        if (buttons[8]){
            arrows = true;
        } else if (buttons[9]){
            arrows = false;
        }
    } else {
        if (key[KEY_UP] && (direction != 'u')){
                direction = 'd';
            } else if (key[KEY_DOWN] && (direction != 'd')){
                direction = 'u';
            }
            if (key[KEY_RIGHT] && (direction != 'l')){
                direction = 'r';
            } else if (key[KEY_LEFT] && (direction != 'r')){
                direction = 'l';
            }
    }
    if (pillx == xloc && pilly == yloc && eat == false){
        score = score+1;
        FPS = FPS + 0.1;
        eat = true;
    }
}

void printScreen(){
    for (int i=0;i<50;i++){
        std::cout << std::endl;
    }
    
    std::cout << " SCORE: " << score << "     FPS: " << FPS << std::endl;
    
    for (int u=0; u<(xlen*2+2); u++){
        std::cout << "-";
    }
    std::cout << std::endl;
    
    for (int i=0; i<ylen; i++){
        std::cout << "|";
        for (int e=0; e<xlen; e++){
            std::cout << ekraan[i][e] << " ";
        }
        std::cout << "|";
        std::cout << std::endl;
    }
    for (int u=0; u<(xlen*2+2); u++){
        std::cout << "-";
    }
    std::cout << std::endl << std::endl << std::endl;
}

void move(){
    if (!eat){
        bool draw = true;
        for (int i=1; i<lasty.size(); i++){
            if (lasty.front() == lasty[i] && lastx.front() == lastx[i]){
                draw = false;
            }
        }
        if (draw && !(lasty.front() == pilly && lastx.front() == pillx)){
            ekraan[lasty.front()][lastx.front()] = ground;
        }
         
        lastx.erase(lastx.begin());
        lasty.erase(lasty.begin());
    } else {
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
            if (score == 1){
                ekraan[pilly][pillx] = ground;
            } else {
                ekraan[pilly][pillx] = player;
            }
            pillx = seconds % xlen;
            pilly = (seconds*(seconds/1000)+1) % ylen;
            if (ekraan[pilly][pillx] == ground){
                gend = true;
            }
        }
        ekraan[pilly][pillx] = pill;
    }
    if (direction == 'u' && yloc<(ylen-1)){
        yloc = yloc + 1;
    } else if (direction == 'r' && xloc<(ylen-1)){
        xloc = xloc + 1;
    } else if (direction == 'd' && yloc>0){
        yloc = yloc - 1;
    } else if (direction == 'l' && xloc>0){
        xloc = xloc - 1; 
    } else {
        exit(0);
    }
    
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
    ekraan[yloc][xloc] = player;
}

void getInput(){
    if (joyst){
        poll_joystick();
        for (int i=0;i<NUM_BUTTONS; i++){
            if (joy[0].button[i].b){
                buttons[i] = true;
            } else {
                buttons[i] = false;
            }
        }
    } else {
        poll_keyboard();
    }
    
    xstick = joy[0].stick[0].axis[0].pos;
    ystick = joy[0].stick[0].axis[1].pos;
}

void wait(long milliSeconds){
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    auto now = high_resolution_clock::now();
    auto interval = duration_cast<milliseconds>(now - start).count();

    while(interval<milliSeconds){
        getInput();
        brainz();
        usleep(100000);
        now = high_resolution_clock::now();
        interval = duration_cast<milliseconds>(now-start).count();
    }
}

END_OF_MAIN()