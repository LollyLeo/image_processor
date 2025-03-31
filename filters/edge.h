#pragma once

#include "basefilter.h"
#include "gray.h"
#include "../window.h"

class EdgeDetectionFilter : public Filter {
public:
    explicit EdgeDetectionFilter(double threshold);
    void Apply(Image& image) const override;
    ~EdgeDetectionFilter() override = default;

private:
    static const std::vector<double> MATRIX;
    double threshold_;
};