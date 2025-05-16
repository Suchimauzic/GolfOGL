cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(GolfOGL)

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
    ${INC}/Manager
    ${INC}/Primitives
)

set(PROJECT_CPP_PATH
    ${SRC}/*.cpp
    ${SRC}/Components/*.cpp
    ${SRC}/Core
    ${SRC}/Manager
    ${SRC}/Primitives/*.cpp
)

# Libs
add_subdirectory(libs)

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