#ifndef CODER_H_
#define CODER_H_

extern "C" {
    #include "libavcodec/avcodec.h"
}

namespace VideoProcessing {

class Coder {
public:
    Coder() {
        static bool isRegistered = false;

        if ( !isRegistered ) {
            avcodec_register_all();
        } //end of if
    }
    virtual ~Coder() = 0;
};//end of declaration class Coder

}

#endif /* end of include guard: CODER_H_ */

