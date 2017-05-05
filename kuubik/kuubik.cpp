#include <chrono>
#include <iostream>

#include "kuubik.h"
#include "engine.h"

/**
 * Tee kuup ja täida iga külg eri värviga
 **/
kuubik::kuubik(){
    yl = 12;
    xl = 9;
    vroom.initScreen(xl, yl);
    
    // taidab ekraani array tyhjusega
    for (int y=0;y<yl;y++){
        for (int x=0;x<xl;x++){
            vroom.ekraan[y][x] = ground;
        }
    }
    
    // loob kuubi maatriksi
    for (int i=0;i<6;i++){
        for (int o=0;o<3;o++){
            for (int u=0;u<3;u++){
                kuup[i][o][u] = i;
            }
        }
    }
    
    // täida indeksite massiivid
    fillRowID();
}

/**
 *  Trüki kuup, aja saasi ja lahenda
 **/
void kuubik::run(){
    while (true){
        scramble();
        ekraanile("Sassis");
        lahenda();
        ekraanile("Lahendatud");
    }
}

/**
 * Aja kuup sassi
 **/
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

/**
* Keera kuupi niikaua kuni iga külg on ise värvi
*/
void kuubik::lahenda(){

}

void kuubik::ekraanile(char *msg){
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
    std::cout << msg << "\n";

}

void kuubik::turn(char macro, bool clock){
    if (clock){
        switch (macro){
            case 'U':
                sideClockwise(0);
		break;
            case 'L':
                sideClockwise(1);
		break;
            case 'F':
                sideClockwise(2);
		break;
            case 'R':
                sideClockwise(3);
		break;
            case 'D':
                sideClockwise(4);
		break;
            case 'B':
                sideClockwise(5);
		break;
	    default:
		std::cout << "ERROR";
        }
    } /*else {
        switch (macro){
        
        }
    }*/
}

void kuubik::sideClockwise(int side){
    /* transponeeri keeratav kylg */
    {
        int tempSide [3][3];
        for (int i=0;i<3;i++){
            for (int u=0;u<3;u++){
                tempSide[i][u] = kuup[side][2-u][i];
            }
        }
        for (int i=0;i<3;i++){
            for (int u=0;u<3;u++){
                kuup[side][u][i] = tempSide[u][i];
            }
        }
    }

    /* keera küljega piirnev serv */
    
    int tmpSide[3];
    
    // jätame esimese külje meelde
    for (int j = 0; j < 3; j++) {
	tmpSide[j] = *(rowidx[side][j]);
    }
    
    // kopeerime kolmekaupa alustades viimasest
    for (int i=3; i < 12; i+=3) {
	
	for (int j = 0; j < 3; j++) {
		*(rowidx[side][i+j-3]) = *(rowidx[side][i+j]);
		ekraanile("samm");
	}
    }
    
    // kirjutame viimasele külejele meeldejäetud esimese
    for (int j = 0; j < 3; j++) {
	*(rowidx[side][9+j]) = tmpSide[j];
    	ekraanile("samm");
    }
}

void kuubik::fillRowID(){

    int sides[6][4] = {{2,3,5,1},
	{4,2,0,5},
	{4,3,0,1},
	{4,5,0,2},
	{5,3,2,1},
	{0,3,4,1}};
    int dirs [6][4] = {{0,0,2,0},
	{3,3,3,3},
	{0,3,2,1},
	{1,1,1,1},
	{0,2,2,2},
	{0,1,2,3}};

    for(int u=0;u<6;u++){
	std::vector<std::vector<int> > dirTables;

	for (int i=0;i<4;i++){
	    std::vector <int> n;
	    switch (dirs[u][i]){
		case 0:
		    n = {0,0,0,0,1,2};
		    break;
		case 1:
		    n = {0,1,2,2,2,2};
		    break;
		case 2:
		    n = {2,2,2,2,1,0};
		    break;
		case 3:
		    n = {2,1,0,0,0,0};
		    break;
		default:
		    std::cout << "ERROR";
	    }
	    dirTables.push_back(n);
	}
	rowidx[u][0] = &kuup[sides[u][0]][dirTables[0][0]][dirTables[0][3]];
	rowidx[u][1] = &kuup[sides[u][0]][dirTables[0][1]][dirTables[0][4]];
	rowidx[u][2] = &kuup[sides[u][0]][dirTables[0][2]][dirTables[0][5]];
	    
	rowidx[u][3] = &kuup[sides[u][1]][dirTables[1][0]][dirTables[1][3]];
	rowidx[u][4] = &kuup[sides[u][1]][dirTables[1][1]][dirTables[1][4]];
	rowidx[u][5] = &kuup[sides[u][1]][dirTables[1][2]][dirTables[1][5]];
	
	rowidx[u][6] = &kuup[sides[u][2]][dirTables[2][0]][dirTables[2][3]];
	rowidx[u][7] = &kuup[sides[u][2]][dirTables[2][1]][dirTables[2][4]];
	rowidx[u][8] = &kuup[sides[u][2]][dirTables[2][2]][dirTables[2][5]];

	rowidx[u][9] = &kuup[sides[u][3]][dirTables[3][0]][dirTables[3][3]];
	rowidx[u][10] = &kuup[sides[u][3]][dirTables[3][1]][dirTables[3][4]];
	rowidx[u][11] = &kuup[sides[u][3]][dirTables[3][2]][dirTables[3][5]];
    }
}

char kuubik::charof(int num){
    return 48+num;
}