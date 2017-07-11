#ifndef CODER_H_
#define CODER_H_

/*
 * developed by: Kuksov Pavel
 * e-mail: aimed.fire@gmail.com
 */

extern "C" {
    #include "libavcodec/avcodec.h"
}

namespace VideoProcessing {

class Coder {
/*
 * Абстрактный класс. Предоставляет интерфейс для всех классов,
 * реализующих функции кодирования/декодирования.
 * Проводит единственную за сессию регистрацию кодеров библиотеки libav
 */
public:
    Coder() {
        static bool isRegistered = false;

        if ( !isRegistered ) {
            avcodec_register_all();
            isRegistered = true;
        } //end of if
    }
};//end of declaration class Coder

}

#endif /* end of include guard: CODER_H_ */

