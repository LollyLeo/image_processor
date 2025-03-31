#pragma once
#include "basefilter.h"
#include <cmath>

class HorizontalShrinkFilter : public Filter {
public:
    explicit HorizontalShrinkFilter(size_t w);
    void Apply(Image& image) const override;
    ~HorizontalShrinkFilter() override = default;

private:
    size_t w_;
};