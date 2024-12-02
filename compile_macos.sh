#!/bin/bash

PROJECT_DIR=$(pwd)
BUILD_DIR="${PROJECT_DIR}/build"

# third-party libraries
GLAD_DIR="/usr/local/include/glad"
GLAD_INCLUDE="${GLAD_DIR}/include"
GLAD_SRC="${GLAD_DIR}/src/glad.c"
GLM_INCLUDE="$(brew --prefix glm)/include"
GLFW_INCLUDE="$(brew --prefix glfw)/include"
GLFW_LIBS="$(brew --prefix glfw)/lib"

ENGINE_PHYSICS_SRC_FILES="engine/physics/rigid_body.cpp"
ENGINE_RENDER_SRC_FILES="engine/render_opengl/render.cpp engine/render_opengl/shader.cpp engine/render_opengl/shapes.cpp"
ENGINE_WINDOW_SRC_FILES="engine/window_glfw/keyboard.cpp engine/window_glfw/window.cpp"
ENGINE_SRC_FILES="engine/engine.cpp ${ENGINE_WINDOW_SRC_FILES} ${ENGINE_RENDER_SRC_FILES} ${ENGINE_PHYSICS_SRC_FILES}"
SRC_FILES="${PROJECT_DIR}/main.cpp ${ENGINE_SRC_FILES} ${GLAD_SRC}"
EXE_NAME="engine"

# Step 2: Create the build directory
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir "$BUILD_DIR"
fi

clang++ -std=c++11 -o "$BUILD_DIR/$EXE_NAME" $SRC_FILES \
    -I$GLFW_INCLUDE -I$GLM_INCLUDE -I$GLAD_INCLUDE -framework OpenGL \
    -L$GLFW_LIBS -lglfw