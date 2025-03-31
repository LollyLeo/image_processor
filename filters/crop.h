#pragma once

#include "basefilter.h"

class CropFilter : public Filter {
private:
    size_t width_;
    size_t height_;

public:
    CropFilter(size_t w, size_t h);
    void Apply(Image& image) const override;
    ~CropFilter() override = default;
};
