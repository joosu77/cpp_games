#include "neural.h"

neural::neural(){
    vroom.FPS = 4;
    
    int xl = 10;
    int yl = 10;
    vroom.initscreen(xl,yl);
    
    for (int i=0; i<vroom.ylen; i++){
        for (int u=0; u<vroom.xlen; u++){
            vroom.ekraan[i][u] = ground;
        }
    }
}