#ifndef JPEG_ENCODER_H_
#define JPEG_ENCODER_H_

/*
 * developed by: Kuksov Pavel
 * e-mail: aimed.fire@gmail.com
 */

#include "coder.h"
#include "video_processing_error.h"

#include <memory>

namespace VideoProcessing {

class JPEGEncoder: public Coder {
/*
 * Кодировщик видео кадров в файл стандарта JPEG.
 * Предполагается, что на вход подаются кадры в формате YUVJ420P.
 * Битрейт устанавливается в значение 100000 бит/c.
 * Значение fps принимается равным 25.
 */
public:
    JPEGEncoder ();

    /*
     * Функция кодирует входной кадр в файл c именем <filename> в стандарте JPEG.
     * Принимаемые параметры:
     * - frame - входной  кадр видео
     * - frameCharacteristics - характеристики входного кадра
     * - filename - путь к файл куда будут сохранен результат успешного кодирования
     */
    void encode(std::shared_ptr<AVFrame> frame, std::shared_ptr<AVCodecContext> frameCharacteristics, const std::string& filename);
private:
    static const AVPixelFormat DEFAULT_FRAME_FORMAT = PIX_FMT_YUVJ420P;
    static const int DEFAULT_BIT_RATE = 100000;
    static const int DEFAULT_FPS = 25;

    std::unique_ptr<AVCodec, void(*)(AVCodec*)> codec_;
    std::shared_ptr<AVCodecContext> codecContext_;
};//end of declaration class JPEGEncoder

} /* VideoProcessing */

#endif /* end of include guard: JPEG_ENCODER_H_ */
