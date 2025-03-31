#pragma once
#include "basefilter.h"

namespace gray_scale_consts {
constexpr double RedK = 0.299;
constexpr double GreenK = 0.587;
constexpr double BlueK = 0.114;
}  // namespace gray_scale_consts

class GrayScaleFilter : public Filter {
public:
    GrayScaleFilter();
    void Apply(Image& image) const override;
    ~GrayScaleFilter() override = default;
};