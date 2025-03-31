#pragma once
#include "basefilter.h"
#include <cmath>

class VerticalShrinkFilter : public Filter {
public:
    explicit VerticalShrinkFilter(size_t w);
    void Apply(Image& image) const override;
    ~VerticalShrinkFilter() override = default;

private:
    size_t h_;
};