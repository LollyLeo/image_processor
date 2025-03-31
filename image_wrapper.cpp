#include "image_wrapper.h"
ImageWrapper::ImageWrapper(Image image, BitMapFileHeader fheader, BitMapInfoHeader imheader)
    : image_(image), fheader_(fheader), imheader_(imheader) {
}

ImageWrapper ImageWrapper::ReadBmp(const std::string& file_path) {
    BinaryReader br(file_path);
    BitMapFileHeader fheader;
    BitMapInfoHeader imheader;
    br >> fheader;
    br >> imheader;

    CheckCorrectness(fheader, imheader);
    using bmp_consts::BytesPerPixel;
    int32_t padding = static_cast<int32_t>((4 - (imheader.biWidth * BytesPerPixel) % 4) % 4);
    br.GoTo(fheader.bfOffBits);
    uint32_t big_w = imheader.biWidth;
    uint32_t big_h = imheader.biHeight;

    std::vector<std::vector<Pixel>> pixels(big_h);
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    for (uint32_t h = 0; h < big_h; ++h) {
        pixels.back().reserve(big_w);
        for (uint32_t w = 0; w < big_w; ++w) {
            br >> blue;
            br >> green;
            br >> red;
            pixels[big_h - h - 1].emplace_back(Pixel(static_cast<double>(static_cast<int>(red)) / MaxColorValue,
                                                     static_cast<double>(static_cast<int>(green)) / MaxColorValue,
                                                     static_cast<double>(static_cast<int>(blue)) / MaxColorValue));
        }
        br.Ignore(padding);
    }
    return ImageWrapper(Image(pixels), fheader, imheader);
}

void ImageWrapper::SelfApply(const Modifier& m) {
    m.Apply(image_);
    imheader_.biHeight = static_cast<int32_t>(size(image_.pixels));  // errors from static cast?
    if (size(image_.pixels) == 0) {
        throw std::runtime_error("Unable to comprehend an empty image.");
    }
    imheader_.biWidth = static_cast<int32_t>(size(image_.pixels[0]));  // errors from static cast?
}

void ImageWrapper::SelfWrite(const std::string& output_path) {
    BinaryWriter writer(output_path);

    // Write the BitMapFileHeader
    writer << fheader_;

    // Write the BitMapInfoHeader
    writer << imheader_;
    // Calculate padding size (BMP rows are aligned to 4 bytes)
    const int32_t width = imheader_.biWidth;
    const int32_t height = imheader_.biHeight;
    const int32_t row_size = (width * 3 + 3) & ~3;  // Each pixel is 3 bytes (RGB), aligned to 4 bytes
    const int32_t padding_size = row_size - (width * 3);

    // Write the pixel data
    for (int32_t y = height - 1; y >= 0; --y) {
        for (int32_t x = 0; x < width; ++x) {
            // Write the pixel (assuming Image provides a method to access pixel data)
            const auto& pixel = image_.pixels[y][x];
            writer << static_cast<uint8_t>(pixel.blue * MaxColorValue)
                   << static_cast<uint8_t>(pixel.green * MaxColorValue)
                   << static_cast<uint8_t>(pixel.red * MaxColorValue);
        }
        // Write padding at the end of each row
        writer.WritePadding(padding_size);
    }

    if (!writer.IsGood()) {
        throw std::runtime_error("Failed to write image data to file: " + output_path);
    }
}