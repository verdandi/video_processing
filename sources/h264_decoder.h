#ifndef H264_DECODER_H_
#define H264_DECODER_H_

#include "coder.h"
#include "video_processing_utils.h"
#include "video_processing_error.h"

/*
 * developed by: Kuksov Pavel
 * e-mail: aimed.fire@gmail.com
 */

#include <memory>

namespace VideoProcessing {

class H264Decoder: public Coder {
/*
 * Декодер видео стандарта h.264
 */
public:
    H264Decoder (const std::string& bitstreamPath);
    //~H264Decoder () {}

    /*
     * Декодировать очередной кадр видео потока.
     * Возвращаемое значение:
     * указатель на декодированный кадр.
     */
    std::shared_ptr<AVFrame> decode();

    /*
     * Функция возвращает указатель на объект AVCodecContext,
     * хранящий характеристики видео потока
     * Возвращаемое значение:
     * указатель на объект AVCodecContext
     */
    std::shared_ptr<AVCodecContext> getVideoCharacteristics() const;

private:
    static const int SIZE_OF_BUFFER = 4096; // размер буфера в байтах. Нужен для удобства и может иметь произвольное значение

    std::unique_ptr<AVCodec, void(*)(AVCodec*)> codec_;
    std::shared_ptr<AVCodecContext> codecContext_;
    std::unique_ptr<AVCodecParserContext, void(*)(AVCodecParserContext*)> parser_;
    std::unique_ptr<std::FILE, void(*)(std::FILE*)> bitstream_;
    std::shared_ptr<AVFrame> frame_;
    uint8_t buffer_[SIZE_OF_BUFFER+FF_INPUT_BUFFER_PADDING_SIZE]; // сюда будем читать из из исходного файла с фидео потоком
    uint8_t* rawData_; // указатель на позицию в массиве buffer, с которой начинаются еще не обработанные данные
    int numberOfReadedBytes_; //количество не обработанных сырых данных в массиве buffer в байтах
};//end of declaration class H264Decoder

}

#endif /* end of include guard: H264_DECODER_H_ */

