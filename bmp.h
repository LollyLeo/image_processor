#pragma once
#include <string>
#include "image.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "filters/modifier.h"
#include <cstdint>  // For fixed-width integer types

namespace swap_endian_useless {
const uint32_t N_255 = 0x000000FF;
const uint32_t N_65280 = 0x0000FF00;
const uint32_t N_16711680 = 0x00FF0000;
const uint32_t N_4278190080 = 0xFF000000;
const uint32_t BITS_PER_BYTE = 8;
const uint32_t THREE_BY_EUGHT = 24;
}  // namespace swap_endian_useless

uint32_t SwapEndian(uint32_t value);

namespace bmp_consts {
// BMP file type identifier ("BM")
constexpr uint16_t BmpFileType = 0x4D42;

// Size of the BITMAPFILEHEADER structure
constexpr size_t BitmapFileHeaderSize = 14;

// Size of the BITMAPINFOHEADER structure
constexpr size_t BitmapInfoHeaderSize = 40;

// Minimum offset to pixel data (BITMAPFILEHEADER + BITMAPINFOHEADER)
constexpr size_t MinPixelDataOffset = BitmapFileHeaderSize + BitmapInfoHeaderSize;

// 24-bit BMP format
constexpr uint16_t BitsPerPixel24Bit = 24;

// No compression
constexpr uint32_t BiRgb = 0;

// No color table for 24-bit BMP
constexpr uint32_t NoColorTable = 0;

// Bytes per pixel for 24-bit BMP
constexpr size_t BytesPerPixel = 3;
}  // namespace bmp_consts

#pragma pack(push, 1)  // Ensure no padding is added between struct members

struct BitMapFileHeader {
    uint16_t bfType;       // File type, must be "BM" (0x4D42)
    uint32_t bfSize;       // Size of the file in bytes
    uint16_t bfReserved1;  // Reserved, must be 0
    uint16_t bfReserved2;  // Reserved, must be 0
    uint32_t bfOffBits;    // Offset to the start of pixel data
};

struct BitMapInfoHeader {
    uint32_t biSize;          // Size of this header (40 bytes)
    int32_t biWidth;          // Width of the bitmap in pixels
    int32_t biHeight;         // Height of the bitmap in pixels
    uint16_t biPlanes;        // Number of color planes (must be 1)
    uint16_t biBitCount;      // Bits per pixel (1, 4, 8, 16, 24, or 32)
    uint32_t biCompression;   // Compression method (0 for uncompressed)
    uint32_t biSizeImage;     // Size of the raw bitmap data (including padding)
    int32_t biXPelsPerMeter;  // Horizontal resolution (pixels per meter)
    int32_t biYPelsPerMeter;  // Vertical resolution (pixels per meter)
    uint32_t biClrUsed;       // Number of colors in the color palette
    uint32_t biClrImportant;  // Number of important colors used (0 means all)
};

#pragma pack(pop)  // Restore default packing

void CheckCorrectness(const BitMapFileHeader& fheader, const BitMapInfoHeader& imheader);

class BinaryReader {
public:
    explicit BinaryReader(const std::string& file_path) : file_stream_(file_path, std::ios::binary) {
        if (!file_stream_) {
            throw std::runtime_error("Failed to open the input file: " + file_path);
        }
    }

    ~BinaryReader() {
        if (file_stream_.is_open()) {
            file_stream_.close();
        }
    }

    template <typename T>
    BinaryReader& operator>>(T& variable) {
        if (!file_stream_.read(reinterpret_cast<char*>(&variable), sizeof(T))) {
            throw std::runtime_error("Failed to read from file");
        }
        return *this;
    }

    bool IsGood() const {
        return file_stream_.good();
    }

    void GoTo(uint32_t b) {  // b = bfOffBits
        file_stream_.seekg(b, std::ios::beg);
    }

    void Ignore(int32_t count) {
        file_stream_.ignore(count);
    }

private:
    std::ifstream file_stream_;
};

class BinaryWriter {
public:
    explicit BinaryWriter(const std::string& file_path) : file_stream_(file_path, std::ios::binary) {
        if (!file_stream_) {
            throw std::runtime_error("Failed to open the output file: " + file_path);
        }
    }

    ~BinaryWriter() {
        if (file_stream_.is_open()) {
            file_stream_.close();
        }
    }

    template <typename T>
    BinaryWriter& operator<<(const T& value) {
        if (!file_stream_.write(reinterpret_cast<const char*>(&value), sizeof(T))) {
            throw std::runtime_error("Failed to write to file");
        }
        return *this;
    }

    bool IsGood() const {
        return file_stream_.good();
    }
    void GoTo(uint32_t b) {  // b = bfOffBits
        file_stream_.seekp(b, std::ios::beg);
    }
    void WritePadding(int32_t count, uint8_t padding_value = 0x00) {
        std::vector<uint8_t> padding(count, padding_value);
        if (!file_stream_.write(reinterpret_cast<const char*>(padding.data()), count)) {
            throw std::runtime_error("Failed to write padding to file");
        }
    }

private:
    std::ofstream file_stream_;
};
