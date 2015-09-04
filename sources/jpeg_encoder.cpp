#include "jpeg_encoder.h"
#include "video_processing_utils.h"

namespace VideoProcessing {

JPEGEncoder::JPEGEncoder()
            : codec_(avcodec_find_encoder(AV_CODEC_ID_MJPEG), deleteAVCodec),
              codecContext_(avcodec_alloc_context3(codec_.get()), deleteAVCodecContext)
{
    if ( codec_ == nullptr ) {
        throw InternalLibAVError("JPEG codec not found\n");
    } //end of if

    if ( codecContext_ == nullptr ) {
        throw InternalLibAVError("context for JPEG codec not created");
    } //end of if

    codecContext_->bit_rate = DEFAULT_BIT_RATE;
    codecContext_->pix_fmt = DEFAULT_FRAME_FORMAT;
    codecContext_->codec_id = AV_CODEC_ID_MJPEG;
    codecContext_->codec_type = AVMEDIA_TYPE_VIDEO;
    codecContext_->time_base.den = 1;
    codecContext_->time_base.num = DEFAULT_FPS;
} //end of JPEGEncoder::JPEGEncoder()

void JPEGEncoder::encode(std::shared_ptr<AVFrame> frame,
                         std::shared_ptr<AVCodecContext> frameCharacteristics,
                         const std::string& filename) {
    codecContext_->width = frameCharacteristics->width;
    codecContext_->height = frameCharacteristics->height;

    if ( avcodec_open2(codecContext_.get(), codec_.get(), NULL) < 0 ) {
        throw InternalLibAVError("JPEG codec not opened\n");
    }

    AVPacket packet;
    av_init_packet(&packet);

    // требуется для работы функции avcodec_encode_video2()
    packet.data = nullptr;
    packet.size = 0;

    int encodeIsFinished = 0;
    while ( !encodeIsFinished ) {
        int retCode = avcodec_encode_video2(codecContext_.get(), &packet, frame.get(), &encodeIsFinished);
        if ( retCode < 0 ) {
            av_free_packet(&packet);

            throw InternalLibAVError("encoding failed\n");
        } //end of if
    } //end of while

    std::FILE* JPEGFile = fopen(filename.c_str(), "wb");
    fwrite(packet.data, 1, packet.size, JPEGFile);
    fclose(JPEGFile);
    av_free_packet(&packet);
    avcodec_close(codecContext_.get());
} //end of void JPEGEncoder::encode()

} /* VideoProcessing */
