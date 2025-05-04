cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(GolfOGL)

set(CMAKE_CXX_STANDARD 17)
set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# Set variables
set(PROJECT_INCLUDE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Components
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Primitives
)

set(PROJECT_CPP_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Primitives/*.cpp
)

# Libs
add_subdirectory(libs)

# .hpp and .cpp files
include_directories(${PROJECT_INCLUDE_PATH})
file(GLOB_RECURSE CPPS ${PROJECT_CPP_PATH})

add_executable(${PROJECT_NAME} ${CPPS})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad glm)


# Checking resources

if (NOT EXISTS ${OUTPUT_DIR}/res)
    add_custom_command(TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}/res
        COMMENT "Creating res direction"
    )
endif()


# Copy res directory in build
add_custom_command(TARGET ${PROJECT_NAME}
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/res
    ${OUTPUT_DIR}/res
    COMMENT "Copying res in building directory"
)