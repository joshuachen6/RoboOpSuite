add_requires("glfw", "opengl")
add_requires("imgui v1.91.0-docking", {configs = {glfw = true, opengl3 = true}})
add_requires("implot v0.17")

-- Custom soil2 package definition
package("soil2_lib")
    set_homepage("https://github.com/Jacob-Tate/soil2-cmake")
    set_description("SOIL2 with CMake support")
    add_urls("https://github.com/Jacob-Tate/soil2-cmake.git")
    add_deps("cmake")
    add_syslinks("GL")
    
    on_install(function (package)
        local configs = {"-DBUILD_SHARED_LIBS=OFF"}
        import("package.tools.cmake").install(package, configs)
        os.mkdir(package:installdir("include"))
        os.cp("src/SOIL2/*.h", package:installdir("include"))
    end)
    
    on_test(function (package)
        assert(package:has_cfuncs("SOIL_load_OGL_texture", {includes = "SOIL2.h"}))
    end)
package_end()

add_requires("soil2_lib")

target("RoboOp")
    set_kind("shared")
    set_languages("cxx20")
    add_files("RoboOp/src/**.cpp")
    add_includedirs("RoboOp/include", {public = true})
    add_includedirs("RoboOp/src")

target("RoboOpTest")
    set_kind("binary")
    set_languages("cxx20")
    add_deps("RoboOp")
    add_files("RoboOp/test_src/**.cpp")
    add_includedirs("RoboOp/test_include")

target("RoboOpVisualizer")
    set_kind("binary")
    set_languages("cxx20")
    
    add_deps("RoboOp")
    add_packages("glfw", "opengl", "soil2_lib", "imgui", "implot")
    
    add_includedirs("RoboOpVisualizer/include", "RoboOpVisualizer/font")
    add_files("RoboOpVisualizer/src/**.cpp")
    
    after_build(function (target)
        import("core.project.task")
        os.cp("RoboOpVisualizer/font/fa-solid-900.ttf", target:targetdir())
    end)
