#include <chrono>
#include <iostream>

#include "kuubik.h"
#include "engine.h"

kuubik::kuubik(){
    yl = 12;
    xl = 9;
    vroom.initScreen(xl, yl);
    
    for (int y=0;y<yl;y++){
        for (int x=0;x<xl;x++){
            vroom.ekraan[y][x] = ground;
        }
    }
    
    for (int i=0;i<6;i++){
        std::vector<std::vector<int>> side;
        for (int o=0;o<3;o++){
            std::vector<int> line;
            for (int u=0;u<3;u++){
                line.push_back(i);
            }
            side.push_back(line);
        }
        kuup.push_back(side);
    }
    
}

void kuubik::run(){
    while (true){
        scramble();
        ekraanile();
        lahenda();
        ekraanile();
    }
}

void kuubik::scramble(){
    for (int i=0;i<10;i++){
        using namespace std::chrono;
        auto epoch = high_resolution_clock::from_time_t(0);
        auto now   = high_resolution_clock::now();
        auto seconds = duration_cast<milliseconds>(now - epoch).count();
        long mills = seconds;
        
        std::vector<char> moves;
        moves  = {'U','L','F','R','D','B'};
        turn(moves[mills%6], true);
    }
}

void kuubik::lahenda(){

}

void kuubik::ekraanile(){
    for (int y=0;y<3;y++){
        for (int x=0;x<3;x++){
            vroom.ekraan[y][x+3] = charof(kuup[0][y][x]);
            vroom.ekraan[y+3][x] = charof(kuup[1][y][x]);
            vroom.ekraan[y+3][x+3] = charof(kuup[2][y][x]);
            vroom.ekraan[y+3][x+6] = charof(kuup[3][y][x]);
            vroom.ekraan[y+6][x+3] = charof(kuup[4][y][x]);
            vroom.ekraan[y+9][x+3] = charof(kuup[5][y][x]);
        }
    }

    vroom.printScreen();
}

void kuubik::turn(char macro, bool clock){
    if (clock){
        switch (macro){
            case 'U':
                sideClockwise(0);
            case 'L':
                sideClockwise(1);
            case 'F':
                sideClockwise(2);
            case 'R':
                sideClockwise(3);
            case 'D':
                sideClockwise(4);
            case 'B':
                sideClockwise(5);
        }
    } /*else {
        switch (macro){
        
        }
    }*/
}

void kuubik::sideClockwise(int side){
    /* transponeeri keeratav k�lg */
    for (int i=0;i<3;i++){
        int temp = kuup[side][1][0];
        kuup[side][0][0] = kuup[side][2][0];
        kuup[side][1][0] = kuup[side][2][1];
        kuup[side][2][0] = kuup[side][2][2];
        kuup[side][2][1] = kuup[side][1][2];
        kuup[side][2][2] = kuup[side][0][2];
        kuup[side][1][2] = kuup[side][0][1];
        kuup[side][0][2] = kuup[side][0][0];
        kuup[side][0][1] = temp;
    }
    
    std::vector<int> sides (4);
    std::vector<int> dirs (4);
    
    switch (side){
        case 0:
            sides = {2,3,5,1};
            dirs = {0,0,2,0};
            break;
        case 1:
            sides = {4,2,0,5};
            dirs = {3,3,3,3};
            break;
        case 2:
            sides = {4,3,0,1};
            dirs = {0,3,2,1};
            break;
        case 3:
            sides = {4,5,0,2};
            dirs = {1,1,1,1};
            break;
        case 4:
            sides = {5,3,2,1};
            dirs = {0,2,2,2};
            break;
        case 5:
            sides = {0,3,4,1};
            dirs = {0,1,2,3};
            break;
        default:
            std::cout << "ERROR" << std::endl;
    }
    /*
    {
        int* tmp [3];
        int g;
        for (int i=0;i<3;i++){
            tmp[i] = &g;
            a[i] = &g;
            b[i] = &g;
            c[i] = &g;
            d[i] = &g;
        }
    }
    fillABC(sides, dirs);
    
    //std::vector<int*> tmp (3);
    int* tmp [3];
    
    for (int i=0;i<3;i++){
        //std::cout << i << std::endl << a[0] << std::endl << a[1] << std::endl << tmp[0] << std::endl << tmp[1] << std::endl;
        *tmp[i] = *a[i];
        std::cout << *a[i] << std::endl << std::endl;
        *a[i] = *b[i];
        *b[i] = *c[i];
        *c[i] = *d[i];
        *d[i] = *tmp[i];
    }
    */
    std::vector<std::vector<int> > dirTables;
    for (int i=0;i<4;i++){
        std::vector <int> n;
        switch (dirs[i]){
            case 0:
                n = {0,0,0,0,1,2};
            case 1:
                n = {0,1,2,2,2,2};
            case 2:
                n = {2,2,2,2,1,0};
            case 3:
                n = {2,1,0,0,0,0};
        }
        dirTables.push_back(n);
    }
    int tmp[3];
    tmp[0] = kuup[sides[0]][dirTables[0][0]][dirTables[0][3]];
    tmp[1] = kuup[sides[0]][dirTables[0][1]][dirTables[0][4]];
    tmp[2] = kuup[sides[0]][dirTables[0][2]][dirTables[0][5]];
    ekraanile();
    
    kuup[sides[0]][dirTables[0][0]][dirTables[0][3]] = kuup[sides[1]][dirTables[1][0]][dirTables[1][3]];
    kuup[sides[0]][dirTables[0][1]][dirTables[0][4]] = kuup[sides[1]][dirTables[1][1]][dirTables[1][4]];
    kuup[sides[0]][dirTables[0][2]][dirTables[0][5]] = kuup[sides[1]][dirTables[1][2]][dirTables[1][5]];
    ekraanile();
    
    kuup[sides[1]][dirTables[1][0]][dirTables[1][3]] = kuup[sides[2]][dirTables[2][0]][dirTables[2][3]];
    kuup[sides[1]][dirTables[1][1]][dirTables[1][4]] = kuup[sides[2]][dirTables[2][1]][dirTables[2][4]];
    kuup[sides[1]][dirTables[1][2]][dirTables[1][5]] = kuup[sides[2]][dirTables[2][2]][dirTables[2][5]];
    ekraanile();
    
    kuup[sides[2]][dirTables[2][0]][dirTables[2][3]] = kuup[sides[2]][dirTables[3][0]][dirTables[3][3]];
    kuup[sides[2]][dirTables[2][1]][dirTables[2][4]] = kuup[sides[2]][dirTables[3][1]][dirTables[3][4]];
    kuup[sides[2]][dirTables[2][2]][dirTables[2][5]] = kuup[sides[2]][dirTables[3][2]][dirTables[3][5]];
    ekraanile();
    
    kuup[sides[2]][dirTables[3][0]][dirTables[3][3]] = tmp[0];
    kuup[sides[2]][dirTables[3][1]][dirTables[3][4]] = tmp[1];
    kuup[sides[2]][dirTables[3][2]][dirTables[3][5]] = tmp[2];
    ekraanile();
}

void kuubik::fillABC(std::vector<int> sides, std::vector<int> dirs){
    std::vector<std::vector<int> > dirTables;

    for (int i=0;i<4;i++){
        std::vector <int> n;
        switch (dirs[i]){
            case 0:
                n = {0,0,0,0,1,2};
            case 1:
                n = {0,1,2,2,2,2};
            case 2:
                n = {2,2,2,2,1,0};
            case 3:
                n = {2,1,0,0,0,0};
        }
        dirTables.push_back(n);
    }
    a[0] = &kuup[sides[0]][dirTables[0][0]][dirTables[0][3]];
    a[1] = &kuup[sides[0]][dirTables[0][1]][dirTables[0][4]];
    a[2] = &kuup[sides[0]][dirTables[0][2]][dirTables[0][5]];
    
    b[0] = &kuup[sides[1]][dirTables[1][0]][dirTables[1][3]];
    b[1] = &kuup[sides[1]][dirTables[1][1]][dirTables[1][4]];
    b[2] = &kuup[sides[1]][dirTables[1][2]][dirTables[1][5]];
    
    c[0] = &kuup[sides[2]][dirTables[2][0]][dirTables[2][3]];
    c[1] = &kuup[sides[2]][dirTables[2][1]][dirTables[2][4]];
    c[2] = &kuup[sides[2]][dirTables[2][2]][dirTables[2][5]];
    
    d[0] = &kuup[sides[2]][dirTables[3][0]][dirTables[3][3]];
    d[1] = &kuup[sides[2]][dirTables[3][1]][dirTables[3][4]];
    d[2] = &kuup[sides[2]][dirTables[3][2]][dirTables[3][5]];
}

char kuubik::charof(int num){
    return 48+num;
}