import os
from conans import ConanFile, CMake


class BoardImgui(ConanFile):
    name = "ui-board-imgui"
    version = "0.0"

    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False]}
    default_options = {"shared": False}

    generators = "cmake"

    scm = {"type": "git",
           "url": "auto",
           "revision": "auto"}

    def requirements(self):
        self.requires("imgui/1.69@bincrafters/stable")
        self.requires("glew/2.1.0@bincrafters/stable")
        
        self.requires("ui-board_game/0.0@sword/sorcery")
        self.requires("ui-tileset-glfw/0.0@sword/sorcery")
        self.requires("boost/1.69.0@conan/stable")

    def imports(self):
        self.copy("imgui_impl_glfw*", src="misc/bindings", dst="bindings", root_package="imgui")
        self.copy("imgui_impl_opengl3*", src="misc/bindings", dst="bindings", root_package="imgui")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.install()

    def package(self):
        self.copy("LICENSE", dst="licenses")
