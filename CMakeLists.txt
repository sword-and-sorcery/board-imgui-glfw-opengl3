cmake_minimum_required(VERSION 2.8.12)
project(sword_and_sorcery)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_definitions("-DIMGUI_IMPL_OPENGL_LOADER_GLEW")

add_executable(board_imgui src/main.cpp
                           src/config.cpp
                           ${CONAN_SRC_DIRS_IMGUI}/bindings/imgui_impl_glfw.cpp
                           ${CONAN_SRC_DIRS_IMGUI}/bindings/imgui_impl_opengl3.cpp)
set_target_properties(board_imgui PROPERTIES CXX_STANDARD 17)
target_include_directories(board_imgui PRIVATE ${CONAN_SRC_DIRS_IMGUI})
target_link_libraries(board_imgui PRIVATE CONAN_PKG::imgui CONAN_PKG::ui-tileset-glfw CONAN_PKG::glew CONAN_PKG::boost)

install(TARGETS board_imgui
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)

