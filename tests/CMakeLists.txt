cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(tests)

set(INC ${CMAKE_SOURCE_DIR}/include/)
set(SRC ${CMAKE_SOURCE_DIR}/src)

# Set variables
set(PROJECT_INCLUDE_PATH
    ${INC}/
    ${INC}/Components
    ${INC}/Core
    ${INC}/Manager
    ${INC}/Physics
    ${INC}/Primitives
)

set(PROJECT_CPP_PATH
    ${SRC}/Core/Shader.cpp
    ${SRC}/Components/Mesh.cpp
    ${SRC}/Components/Vertex.cpp
    ${SRC}/Components/Texture.cpp
    ${SRC}/Components/Texture2D.cpp
    ${SRC}/Components/TextureCubemap.cpp
    ${SRC}/Core/Window.cpp
    ${SRC}/FirstScene.cpp
    ${SRC}/GameElements/*.cpp
    ${SRC}/Player.cpp
    ${SRC}/Renderer.cpp
    ${SRC}/Physics/Gravity.cpp
    ${SRC}/Manager/TextureManager.cpp
    ${SRC}/Manager/ShaderManager.cpp
    ${SRC}/Primitives/Object.cpp
    ${SRC}/Primitives/Cube.cpp
    ${SRC}/Primitives/Sphere.cpp
    ${SRC}/Physics/Collider.cpp
    ${SRC}/Physics/Simplex.cpp
    ${SRC}/Camera.cpp
)

include_directories(${PROJECT_INCLUDE_PATH})
file(GLOB_RECURSE CPPS ${PROJECT_CPP_PATH})

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/tests.cpp
    ${CPPS}
)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE_PATH})