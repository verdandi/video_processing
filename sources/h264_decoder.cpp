#include "h264_decoder.h"

#include <iostream>

namespace VideoProcessing {

H264Decoder::H264Decoder(const std::string& bitstreamPath)
            : codec_(avcodec_find_decoder(AV_CODEC_ID_H264), deleteAVCodec),
              codecContext_(avcodec_alloc_context3(codec_.get()), deleteAVCodecContext),
              parser_(av_parser_init(AV_CODEC_ID_H264), deleteAVParser),
              bitstream_(std::fopen(bitstreamPath.c_str(), "rb"), deleteFile),
              frame_(av_frame_alloc(), deleteAVFrame),
              rawData_(nullptr),
              numberOfReadedBytes_(0)
{
    if ( codec_ == nullptr ) {
        throw InternalLibAVError("h.264 codec not found\n");
    } //end of if

    if ( codecContext_ == nullptr ) {
        throw InternalLibAVError("context for h.264 codec not created");
    } //end of if

    if ( avcodec_open2(codecContext_.get(), codec_.get(), nullptr) < 0 ) {
        throw InternalLibAVError("h.264 codec not opened");
    } //end of if

    if ( parser_ == nullptr ) {
        throw InternalLibAVError("could not init parser");
    } //end of if

    if ( bitstream_ == nullptr ) {
        throw InternalLibAVError("could not open file with bitstream");
    } //end of if
} //end of H264Decoder::H264Decoder()

std::shared_ptr<AVFrame> H264Decoder::decode() {
    AVPacket packet;
    av_init_packet(&packet);

    int decodeIsFinished = 0; // флаг успешного завершения декодирования очередного фрейма
    while ( !std::feof(bitstream_.get()) ) {
        if ( numberOfReadedBytes_ == 0 ) {
            numberOfReadedBytes_ = fread(buffer_, 1, SIZE_OF_BUFFER, bitstream_.get());
            rawData_ = buffer_; //устанавливаем указатель на начало массива с сырыми данными
        }

        int numberOfParsedBytes = av_parser_parse2(parser_.get(), codecContext_.get(),
                                                   &packet.data, &packet.size, rawData_,
                                                   numberOfReadedBytes_, 0, 0, 0);

        if ( packet.size > 0 && numberOfParsedBytes >= 0 ) {
            int numberOfDecodedBytes = avcodec_decode_video2(codecContext_.get(), frame_.get(), &decodeIsFinished, &packet);
            if ( numberOfDecodedBytes < 0 ) {
                throw InternalLibAVError("decoding failed");
            } //end of if

            //если декодирование пакета завершено
            if ( decodeIsFinished == 1 ) {
                av_free_packet(&packet);

                // устанавливаем параметры декодированного кадра
                codecContext_->width = frame_->width;
                codecContext_->height = frame_->height;

                // подготавливаем указатель и счетчик к следующей операции декодирования
                numberOfReadedBytes_ -= numberOfParsedBytes;
                rawData_ += numberOfParsedBytes;

                return std::shared_ptr<AVFrame>(frame_);
            } //end of if
        } //end of if

        // обновляем счетчик и указатель
        numberOfReadedBytes_ -= numberOfParsedBytes;
        rawData_ += numberOfParsedBytes;
    } //end of while

    return std::shared_ptr<AVFrame>(nullptr);
} //end of std::shared_ptr<AVFrame> H264Decoder::decode()

std::shared_ptr<AVCodecContext> H264Decoder::getVideoCharacteristics() const {
    return std::shared_ptr<AVCodecContext>(codecContext_);
} //end of std::shared_ptr<AVCodecContext> H264Decoder::getVideoCharacteristics()

}
