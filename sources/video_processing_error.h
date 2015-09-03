#ifndef VIDEO_PROCESSING_ERROR_H_
#define VIDEO_PROCESSING_ERROR_H_

#include <exception>
#include <string>

namespace VideoProcessing {

class VideoProcessingError: public std::exception {
/* класс исключений, используемый в случае общих ошибок в программе.
 * Является корнем иерархии исключений, поэтому достаточно перехватывать
 * исключения этого типа
 */
public:
    VideoProcessingError(const std::string& errorMessage): errorMessage_(errorMessage) {}
    const char* what() const noexcept { return errorMessage_.c_str(); }
private:
    std::string errorMessage_;
};

class InternalLibAVError: public VideoProcessingError {
/*
 * Тип исключений для внутренних ошибок в библиотеке libav
 */
public:
    InternalLibAVError(const std::string& errorMessage): VideoProcessingError(errorMessage) {}
};

}

#endif /* end of include guard: VIDEO_PROCESSING_ERROR_H_ */

