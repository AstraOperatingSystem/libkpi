from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class kpiRecipe(ConanFile):
        name = "kpi"
        version = "0.1.0"
        package_type = "static-library"

        license = "MIT"
        author = "Didas72 <diogocruzdiniz@gmail.com>"
        url="https://github.com/AstraOperatingSystem/libkpi"
        description="Library to handle keypad input"

        settings = "os", "compiler", "build_type", "arch"

        exports_sources = "CMakeLists.txt", "cmake/*", "src/*", "include/*"

        def layout(self):
                cmake_layout(self)

        def generate(self):
                deps = CMakeDeps(self)
                deps.generate()
                tc = CMakeToolchain(self)
                tc.variables["KPI_VERSION"] = self.version
                tc.generate()

        def build(self):
                cmake = CMake(self)
                cmake.configure()
                cmake.build()

        def package(self):
                cmake = CMake(self)
                cmake.install()

        def package_info(self):
                self.cpp_info.set_property("cmake_file_name", "kpi")
                self.cpp_info.set_property("cmake_target_name", "kpi::kpi")
                self.cpp_info.libs = ["kpi"]
