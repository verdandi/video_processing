#include <iostream>

extern "C" {
    #include "libavcodec/avcodec.h"
}

int main( int argc, char *argv[] ) {
    if ( argc == 1 ) {
        std::cout << "Usage: " << argv[0] << " <path to source bitstream>\n";
    } //end of if
    return 0;
} //end of main
