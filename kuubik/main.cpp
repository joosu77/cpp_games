#include "kuubik.h"

int main(){
    kuubik kuubik;
    kuubik.ekraanile("Segamata");
    /*for(int i=0;i<6;i++){
    kuubik.turn('R',true);
    kuubik.turn('U',true);
    kuubik.turn('R',false);
    kuubik.turn('U',false);
    }*/
    kuubik.turn('L',true);
    kuubik.turn('D',false);
    kuubik.turn('B',false);
    //kuubik.scramble();
    kuubik.ekraanile("Keeratud U, true");
    return 0;
}