#include <chrono>

#include "randgen.h"

randgen::randgen(){
    using namespace std::chrono;
    auto epoch = high_resolution_clock::from_time_t(0);
    auto now   = high_resolution_clock::now();
    auto seconds = duration_cast<milliseconds>(now - epoch).count();
    seed = seconds;
}

randgen::gitrandom(){

}