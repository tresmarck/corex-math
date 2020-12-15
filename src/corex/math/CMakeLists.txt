cmake_minimum_required(VERSION 3.14)

add_library(corex-math STATIC
    algebra.cpp
    geometry.cpp
    ds/Vec2.cpp
)