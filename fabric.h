#pragma once

#include "filters/filter_names.h"
#include "parser.h"
#include <map>
#include <string>
// std::set<std::string> filter_flags = {"-crop", "-gs", "-neg", "-sharp", "-edge", "-blur"};

enum FilterType {
    CROP,
    GRAYSCALE,
    NEGATIVE,
    SHARPENING,
    EDGE_DETECTION,
    BLUR,
    COLORBALANCE,
    VERTICALSHRINKING,
    HORIZONTALSHRINKING,
    SHRINKING
};

const std::map<std::string, FilterType> FILTER_MAP = {{"-crop", FilterType::CROP},
                                                      {"-gs", FilterType::GRAYSCALE},
                                                      {"-neg", FilterType::NEGATIVE},
                                                      {"-sharp", FilterType::SHARPENING},
                                                      {"-edge", FilterType::EDGE_DETECTION},
                                                      {"-blur", FilterType::BLUR},
                                                      {"-cb", FilterType::COLORBALANCE},
                                                      {"-vshrink", FilterType::VERTICALSHRINKING},
                                                      {"-hshrink", FilterType::HORIZONTALSHRINKING},
                                                      {"-shrink", FilterType::SHRINKING}};

FilterPointer CreateFilter(CommandPointer cp);