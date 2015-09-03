#include "video_processing_utils.h"

namespace VideoProcessing {

void deleteAVCodec(AVCodec*) {
} //end of void deleteAVCodec()

void deleteAVCodecContext(AVCodecContext* codecContext) {
    avcodec_close(codecContext);
    av_free(codecContext);
} //end of void deleteAVCodecContext()

} /* VideoProcessing */
