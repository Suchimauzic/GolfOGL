cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(GolfOGL)

set(CMAKE_CXX_STANDARD 17)

# Set variables
set(PROJECT_INCLUDE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Objects
)

set(PROJECT_CPP_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Objects/*.cpp
)

# Libs
add_subdirectory(libs)

# .hpp and .cpp files
include_directories(${PROJECT_INCLUDE_PATH})
file(GLOB_RECURSE CPPS ${PROJECT_CPP_PATH})

add_executable(${PROJECT_NAME} ${CPPS})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad glm)


# Checking resources

if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/res/shaders/shader.vert OR NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/res/shaders/shader.frag)
    add_custom_command(TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/res
        COMMENT "Creating res direction"
    )
endif()

# Copy res directory in build
add_custom_command(TARGET ${PROJECT_NAME}
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/res
    ${CMAKE_CURRENT_BINARY_DIR}/res
    COMMENT "Copying res in building directory"
)