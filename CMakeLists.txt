cmake_minimum_required(VERSION 3.20)
project(CoreFall)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.3
)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glm)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/glad.c
        src/LoadShader.cpp
        src/LoadShader.h
        src/meshes/Triangle.cpp
        src/meshes/Triangle.h
        src/meshes/Cube.cpp
        src/meshes/Cube.h
        src/meshes/Tetrahedron.cpp
        src/meshes/Tetrahedron.h
        src/meshes/Icosahedron.cpp
        src/meshes/Icosahedron.h
        src/meshes/Mesh.cpp
        src/meshes/Mesh.h
        src/meshes/Octahedron.cpp
        src/meshes/Octahedron.h
        src/meshes/Sphere.cpp
        src/meshes/Sphere.h
        src/Camera.cpp
        src/Camera.h
        src/Material.cpp
        src/Material.h
        src/meshes/Torus.cpp
        src/meshes/Torus.h
        src/meshes/Loaded.cpp
        src/meshes/Loaded.h
        src/object/Object.cpp
        src/object/Object.h
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw opengl32)
elseif (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)
endif()

#target_link_libraries(${PROJECT_NAME} PRIVATE glfw opengl32 glm::glm)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/textures
)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/models
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/models
)