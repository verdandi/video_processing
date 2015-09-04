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

void deleteFile(std::FILE* file) {
    std::fclose(file);
} //end of void deleteFile()

void deleteAVFrame(AVFrame* frame) {
    av_free(frame);
} //end of void deleteAVFrame()

} /* VideoProcessing */
