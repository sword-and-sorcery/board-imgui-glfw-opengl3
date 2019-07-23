cmake_minimum_required(VERSION 2.8.12)
project(sword_and_sorcery)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_definitions("-DIMGUI_IMPL_OPENGL_LOADER_GLEW")

add_executable(board_imgui src/main.cpp
                           src/config.cpp
                           bindings/imgui_impl_glfw.cpp
                           bindings/imgui_impl_opengl3.cpp
                           src/draw_glfw_opengl3.cpp
                           src/draw_glfw_opengl3.h)
set_target_properties(board_imgui PROPERTIES CXX_STANDARD 17)
target_link_libraries(board_imgui PRIVATE CONAN_PKG::ui-tileset-glfw CONAN_PKG::ui-board_game CONAN_PKG::imgui CONAN_PKG::glew CONAN_PKG::boost)
target_include_directories(
        board_imgui PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(TARGETS board_imgui
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)

