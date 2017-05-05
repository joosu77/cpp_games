#include <iostream>
#include <allegro.h>
#include <unistd.h>

int const NUM_BUTTONS = 10;
bool buttons [NUM_BUTTONS];
//buttons: x, a, b, y, L, R, <>, <>, select, start
 
int xstick = 0;
int ystick = 0;

void getInput();
void printInput();

int main(){
    for (int i=0;i<NUM_BUTTONS;i++){
        buttons[i] = false;
    }
    while (true){
        getInput();
        printInput();
        usleep(1000000);
    }
    return 0;
}

void getInput(){
    poll_joystick();
    for (int i=0;i<NUM_BUTTONS; i++){
        if (joy[0].button[i].b){
            buttons[i] = true;
        } else {
            buttons[i] = false;
        }
    }
   
    xstick = joy[0].stick[0].axis[0].pos;
    ystick = joy[0].stick[0].axis[1].pos;
}

void printInput(){
    for (int i = 0; i<NUM_BUTTONS; i++){
        std::cout << "button" << (i+1) << ": " << buttons[i] << std::endl;
    }
    std::cout << "x axis pos: " << xstick << std::endl;
    std::cout << "y axis pos: " << ystick << std::endl;
   
}