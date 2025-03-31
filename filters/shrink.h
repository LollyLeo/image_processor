#pragma once
#include "basefilter.h"
#include <cmath>

class ShrinkFilter : public Filter {
public:
    ShrinkFilter(size_t h, size_t w);
    void Apply(Image& image) const override;
    ~ShrinkFilter() override = default;

private:
    size_t h_;
    size_t w_;
};