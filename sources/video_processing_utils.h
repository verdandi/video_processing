#ifndef VIDEO_PROCESSING_UTILS_H_
#define VIDEO_PROCESSING_UTILS_H_

/*
 * Вспомогательные функции для автоматического освобождения ресурсов,
 * выделяемых библиотекой libav.
 * developed by: Kuksov Pavel
 * e-mail: aimed.fire@gmail.com
 */

#include <cstdio>

extern "C" {
    #include "libavcodec/avcodec.h"
}

namespace VideoProcessing {

void deleteAVCodec(AVCodec* codec);

void deleteAVCodecContext(AVCodecContext* codecContext);

void deleteAVParser(AVCodecParserContext* parser);

void deleteFile(std::FILE* file);

void deleteAVFrame(AVFrame* frame);

}

#endif /* end of include guard: VIDEO_PROCESSING_UTILS_H_ */

