#include "modifier.h"
#include <algorithm>  // For std::reverse

Modifier::Modifier(const std::vector<CommandPointer>& commands) {
    filters_.reserve(size(commands));
    for (const auto& command : commands) {
        filters_.push_back(CreateFilter(command));
    }
}

void Modifier::Apply(Image& image) const {
    for (const FilterPointer& filter : filters_) {
        filter->Apply(image);
    }
};