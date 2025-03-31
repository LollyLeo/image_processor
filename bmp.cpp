#include "bmp.h"

void CheckCorrectness(const BitMapFileHeader& fheader, const BitMapInfoHeader& imheader) {
    using bmp_consts::BiRgb;
    using bmp_consts::BitmapFileHeaderSize;
    using bmp_consts::BitmapInfoHeaderSize;
    using bmp_consts::BitsPerPixel24Bit;
    using bmp_consts::BmpFileType;
    // using bmp_consts::BytesPerPixel;
    using bmp_consts::MinPixelDataOffset;
    using bmp_consts::NoColorTable;

    // Check file type
    if (fheader.bfType != BmpFileType) {
        throw std::runtime_error("Invalid BMP file: File type must be 'BM'.");
    }

    // Check header sizes
    if (imheader.biSize != BitmapInfoHeaderSize) {
        throw std::runtime_error("Invalid BMP file: BITMAPINFOHEADER size must be 40 bytes.");
    }

    if (fheader.bfOffBits < MinPixelDataOffset) {
        throw std::runtime_error("Invalid BMP file: Pixel data offset is too small.");
    }

    // Check for 24-bit color
    if (imheader.biBitCount != BitsPerPixel24Bit) {
        throw std::runtime_error("Invalid BMP file: Only 24-bit BMP files are supported.");
    }

    // Check for no color table
    if (imheader.biClrUsed != NoColorTable) {
        throw std::runtime_error("Invalid BMP file: Color table is not supported for 24-bit BMP.");
    }

    // Check for no compression
    if (imheader.biCompression != BiRgb) {
        throw std::runtime_error("Invalid BMP file: Compression is not supported.");
    }
}
