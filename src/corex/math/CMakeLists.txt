cmake_minimum_required(VERSION 3.14)

add_library(corex-math STATIC
    algebra.cpp
    geometry.cpp
    linear_algebra.cpp
    utils.cpp
    ds/Vec2.cpp
    # So that CLion and IDEs that have CMake integration will know that the
    # header-only files are part of the project.
    ../math.hpp
)