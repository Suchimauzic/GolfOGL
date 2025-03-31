cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(GolfProject)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

file(GLOB CPPS src/*.cpp)

add_executable(${PROJECT_NAME} ${CPPS})