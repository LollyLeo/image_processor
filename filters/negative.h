#pragma once
#include "basefilter.h"

class NegativeFilter : public Filter {
public:
    NegativeFilter();
    void Apply(Image& image) const override;
    ~NegativeFilter() override = default;
};