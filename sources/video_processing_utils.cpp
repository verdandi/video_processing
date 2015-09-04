#include "video_processing_utils.h"

namespace VideoProcessing {

void deleteAVCodec(AVCodec*) {
} //end of void deleteAVCodec()

void deleteAVCodecContext(AVCodecContext* codecContext) {
    avcodec_close(codecContext);
    av_free(codecContext);
} //end of void deleteAVCodecContext()

void deleteAVParser(AVCodecParserContext* parser) {
    av_parser_close(parser);
} //end of void deleteAVParser()

} /* VideoProcessing */
