cmake_minimum_required(VERSION 2.8.12)
project(sword_and_sorcery)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_definitions("-DIMGUI_IMPL_OPENGL_LOADER_GLEW")

add_executable(board_imgui src/main.cpp
                           ${CONAN_SRC_DIRS_IMGUI}/bindings/imgui_impl_glfw.cpp
                           ${CONAN_SRC_DIRS_IMGUI}/bindings/imgui_impl_opengl3.cpp)
target_include_directories(board_imgui PRIVATE ${CONAN_SRC_DIRS_IMGUI})
target_link_libraries(board_imgui PRIVATE CONAN_PKG::imgui CONAN_PKG::ui-tileset-glfw CONAN_PKG::glew)
