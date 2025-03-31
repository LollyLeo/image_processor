#pragma once
#include "bmp.h"

class ImageWrapper {
private:
    Image image_;
    BitMapFileHeader fheader_;
    BitMapInfoHeader imheader_;

public:
    explicit ImageWrapper(Image image, BitMapFileHeader fheader, BitMapInfoHeader imheader);
    void SelfApply(const Modifier& m);
    void SelfWrite(const std::string& output_path);
    static ImageWrapper ReadBmp(const std::string& file_path);
};