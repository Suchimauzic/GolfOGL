cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(stb_image)

add_library(${PROJECT_NAME} stb_image.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include/)