#ifndef VIDEO_PROCESSING_UTILS_H_
#define VIDEO_PROCESSING_UTILS_H_

extern "C" {
    #include "libavcodec/avcodec.h"
}

namespace VideoProcessing {

void deleteAVCodec(AVCodec* codec);
void deleteAVCodecContext(AVCodecContext* codecContext);

}

#endif /* end of include guard: VIDEO_PROCESSING_UTILS_H_ */

