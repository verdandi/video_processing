#include <iostream>
#include <sstream>
#include <cstring>

#include "h264_decoder.h"
#include "jpeg_encoder.h"

int main(int argc, char *argv[]) {
    if ( argc < 2 ) {
        std::cout << "Usage: " << argv[0] << " <-b=<path to source bitstream>> [-n=<number of frame>] [-p=<path to dir>]\n";
        return 0;
    } //end of if

    std::string path = "./"; // директория куда надо сохранить .jpeg файл
    std::string filePath = "";
    int frameNumber = 0;

    for ( int i = 1; i < argc; ++i ) {
        if ( std::strncmp("-b=", argv[i], 3) == 0 ) {
            filePath = std::string(argv[i]+3);
        } //end of if

        if ( std::strncmp("-p=", argv[i], 3) == 0 ) {
            path = std::string(argv[i]+3);
        } //end of if

        if ( std::strncmp("-n=", argv[i], 3) == 0 ) {
            frameNumber = std::atoi(argv[i]+3);
        } //end of if
    } //end of for

    if ( filePath == "" ) {
        std::cout << "path to source bitstream not defined\n";
        std::cout << "Usage: " << argv[0] << " <-b=<path to source bitstream>> [-n=<number of frame>] [-p=<path to dir>]\n";
        return 0;
    } //end of if

   try {
        VideoProcessing::H264Decoder decoder(filePath);
        VideoProcessing::JPEGEncoder encoder;

        int frameCount = 0;
        for ( auto i = decoder.decode(); i != nullptr; i = decoder.decode() ) {
            ++frameCount;

            if ( frameNumber == 0 || frameCount == frameNumber ) {
                std::ostringstream filename;
                filename << path << "/frame" << frameCount << ".jpeg";
                encoder.encode(i, decoder.getVideoCharacteristics(), filename.str());
            } //end of if
        } //end of for
    } catch(const VideoProcessing::VideoProcessingError& error) {
        std::cerr << "ERROR: " << error.what() << "\n";
    }

    return 0;
} //end of main
