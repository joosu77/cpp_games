#include "kuubik.h"

int main(){
    kuubik kuubik;
    kuubik.ekraanile("Segamata");
    kuubik.turn('U',true);
    kuubik.turn('R',true);
    //kuubik.turn('R',true);
    //kuubik.turn('R',true);	
    kuubik.ekraanile("Keeratud U, true");
    return 0;
}