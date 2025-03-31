cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(GolfProject)

set(CMAKE_CXX_STANDARD 17)

# Libs
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

option(GLFW_BUILD_WAYLAND TRUE)

# subdirectory
add_subdirectory(libs/glfw)
add_subdirectory(libs/glad)
add_subdirectory(libs/glm)

# .hpp and .cpp files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
file(GLOB CPPS src/*.cpp)

add_executable(${PROJECT_NAME} ${CPPS})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad glm)