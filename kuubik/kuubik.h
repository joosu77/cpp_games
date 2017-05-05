#include <vector>
#include "engine.h"

#ifndef KUUBIK_H
#define KUUBIK_H

class kuubik{
    private:
        engine vroom;
        int xl;
        int yl;
        const char ground = ' ';
        
        void scramble();
        void lahenda();
        void sideClockwise(int);
        void fillRowID();
        char charof(int);

	// kuubi värvide kirjeldus kus dimensioonid on järgmised
	// 1 -- kuubi külg
	// 2 -- rida vastaval küljel
	// 3 -- veerg vastavas reas
	// massiivi salvestava väärtus on ruudu värv vahemikus 0-5
	int kuup[6][3][3];
	// indeks kus on pointerid igat külge ääristavatele kleepsudele
	int* rowidx[6][12];

    public:
        void ekraanile(char *);
        kuubik();
        void run();
        void turn(char, bool);
};

#endif