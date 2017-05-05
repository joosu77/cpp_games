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
        
        void turnSide(int,bool);
        void fillRowID();
        char charof(int);

	// kuubi v�rvide kirjeldus kus dimensioonid on j�rgmised
	// 1 -- kuubi k�lg
	// 2 -- rida vastaval k�ljel
	// 3 -- veerg vastavas reas
	// massiivi salvestava v��rtus on ruudu v�rv vahemikus 0-5
	int kuup[6][3][3];
	// indeks kus on pointerid igat k�lge ��ristavatele kleepsudele
	int * rowidx[6][12];
        
        /*
        std::vector<int*> a;
        std::vector<int*> b;
        std::vector<int*> c;
        std::vector<int*> d;
        */
        int* a [3];
        int* b [3];
        int* c [3];
        int* d [3];
    public:
        void ekraanile(char*);
        
    kuubik();
        void run();
        void turn(char, bool);
        void scramble();
        void lahenda();
};

#endif