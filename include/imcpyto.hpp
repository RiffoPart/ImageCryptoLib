#ifndef _IMCRYPTO_HPP_
#define _IMCRYPTO_HPP_


#include <stdint.h>
#include <opencv2/opencv.hpp>
#include <ostream>
#include <fstream>
#include <functional>

cv::Vec3b insetInColor(cv::Vec3b color, uchar ch);
uchar getChFromColor(cv::Vec3b color);

std::ostream& operator<<(std::ostream& cout, const cv::Vec3b& color);

int32_t getSeed(const std::string& string_key);

void cryptFile(std::string image_path, std::string text_path, uint32_t key, std::string out);

void decryptFile(std::string image_path, uint32_t key, std::string out);

cv::Mat cryptText(cv::Mat img, std::string data, uint32_t key);
std::string decryptText(cv::Mat img, uint32_t key);

//----

using insert_callback = std::function<cv::Vec3b(cv::Vec3b, uchar)>;
namespace base_callback {
    cv::Vec3b CH2RGB323(cv::Vec3b colorOfPixel, uchar ch);
    // cv::Vec3b CH2RGB332(cv::Vec3b colorOfPixel, uchar ch);
    // cv::Vec3b CH2RGB233(cv::Vec3b colorOfPixel, uchar ch);
};

class Cryptor {
private:
    insert_callback _callback;
    int32_t _seed;

public:
    Cryptor(const int32_t& seed, insert_callback callback);

    Cryptor(const Cryptor&) = delete;
    Cryptor(const Cryptor&&) = delete;
    ~Cryptor() = default;

    void setSeed(const int32_t& seed);
    void setInsertCallback(insert_callback callback);

    cv::Mat crypt(cv::Mat sourceMat, const char* buf, const uint32_t size);
};

#endif //_IMCRYPTO_HPP_