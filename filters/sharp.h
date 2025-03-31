#pragma once

#include "basefilter.h"
#include <vector>

#include "../window.h"
class SharpFilter : public Filter {
public:
    SharpFilter();
    void Apply(Image& image) const override;
    ~SharpFilter() override = default;

private:
    static const std::vector<double> MATRIX;
};