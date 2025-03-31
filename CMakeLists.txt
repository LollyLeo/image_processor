cmake_minimum_required(VERSION 3.10)
project(image_processor)
set(CMAKE_CXX_STANDARD 17)  # Force C++17 (or 14/20, whichever worked before)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    image_processor
    main.cpp
    parser.cpp
    pixel.cpp
    image.cpp
    window.cpp
    bmp.cpp
    image_wrapper.cpp
    image_processor.cpp
    fabric.cpp
    filters/modifier.cpp
    filters/negative.cpp
    filters/crop.cpp
    filters/gray.cpp
    filters/sharp.cpp
    filters/edge.cpp
    filters/balance.cpp
    filters/vshrink.cpp
    filters/hshrink.cpp
    filters/shrink.cpp
)