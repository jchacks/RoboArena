-- premake5.lua
workspace "RoboArena"
   architecture "x64"
   configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "RoboArena"
    location "RoboArena"
    kind "StaticLib" --"ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files {
       "%{prj.name}/src/**.h",
       "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/vendor/spdlog/include",
        "/usr/include/python3.8/"
    }

    postbuildcommands {
        ("{COPY} %{cfg.buildtarget.relpath} ../PyRoboArena/lib"),
        ("cd ../PyRoboArena && python setup.py build_ext --inplace"),
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
