#include "crop.h"

CropFilter::CropFilter(size_t w, size_t h) : width_(w), height_(h) {
    if (w == 0 || h == 0) {
        throw std::invalid_argument("Crop must have non-zero parameters.");
    }
}

void CropFilter::Apply(Image& image) const {
    if (size(image.pixels) > height_) {
        image.pixels.resize(height_);
    }
    // potential issue: no pixels[0]
    if (size(image.pixels[0]) > width_) {
        for (auto& row : image.pixels) {
            row.resize(width_);
        }
    }
}