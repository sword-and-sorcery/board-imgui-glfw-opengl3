from conans import ConanFile, CMake


class BoardImgui(ConanFile):
    name = "ui-board-imgui-glfw-opengl3"
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
        # self.requires("glfw/3.2.1@bincrafters/stable")
        # self.requires("rapidxml/1.13@bincrafters/stable")
        # self.requires("boost_filesystem/1.69.0@bincrafters/stable")
        # self.requires("stb/20180214@conan/stable")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.install()
