-- premake5.lua
workspace "RoboArena"
   architecture "x64"
   configurations { "Debug", "Release", "Python" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "RoboArena"
    location "RoboArena"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    pchheader "rapch.h"

    files {
       "%{prj.location}/src/**.h",
       "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{prj.location}/src",
        "%{prj.location}/vendor/spdlog/include",
        "/usr/include/python3.8/"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter "configurations:Python"
        kind "StaticLib"
        defines { "NDEBUG" }
        optimize "On"

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../PyRoboArena/lib"),
            ("cd ../PyRoboArena && python setup.py build_ext --inplace"),
        }
