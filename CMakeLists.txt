cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(LabyrinthOGL)

set(CMAKE_CXX_STANDARD 17)
set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

set(INC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Set variables
set(PROJECT_INCLUDE_PATH
    ${INC}/
    ${INC}/Components
    ${INC}/Core
    ${INC}/GameElements
    ${INC}/Manager
    ${INC}/Physics
    ${INC}/Primitives
)

set(PROJECT_CPP_PATH
    ${SRC}/*.cpp
    ${SRC}/Components/*.cpp
    ${SRC}/Core/*.cpp
    ${INC}/GameElements/*.cpp
    ${SRC}/Manager/*.cpp
    ${SRC}/Physics/*.cpp
    ${SRC}/Primitives/*.cpp
)

# For creating tests
set(PROJECT_UNIT_TEST TRUE CACHE BOOL "For creating unit-tests")

# Libs
add_subdirectory(libs)

if (PROJECT_UNIT_TEST)
    cmake_policy(SET CMP0079 NEW)
    add_subdirectory(tests)
endif()

# .hpp and .cpp files
include_directories(${PROJECT_INCLUDE_PATH})
file(GLOB_RECURSE CPPS ${PROJECT_CPP_PATH})

add_executable(${PROJECT_NAME} ${CPPS})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad glm stb_image)


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


# For tests
if (PROJECT_UNIT_TEST)
    target_link_libraries(tests PRIVATE glad glfw glm stb_image gtest gtest_main)
endif()


# Debug and Release definitions
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE BUILD_TYPE_DEBUG)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE BUILD_TYPE_RELEASE)
endif()