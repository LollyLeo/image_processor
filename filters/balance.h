#pragma once
#include "basefilter.h"

class ColorBalanceFilter : public Filter {
public:
    explicit ColorBalanceFilter();
    void Apply(Image& image) const override;
    ~ColorBalanceFilter() override = default;
};