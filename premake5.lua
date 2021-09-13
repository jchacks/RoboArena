-- premake5.lua
workspace "RoboArena"
   architecture "x64"
   configurations { "Debug", "Release", "Python" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


include_directories = {}
include_directories["Python"] = "/usr/include/python3.8/"
include_directories["spdlog"] = "RoboArena//vendor/spdlog/include"
include_directories["stduuid"] = "RoboArena/vendor/stduuid/include"
include_directories["MGSL"] = "RoboArena/vendor/stduuid/gsl"
include_directories["GLFW"] = "RoboArena/vendor/GLFW/include"
include_directories["glm"] = "RoboArena/vendor/glm"

--Include other premake
include "RoboArena/vendor/GLFW"

project "RoboArena"
    location "RoboArena"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    pchheader "rapch.h"

    files {
       "%{prj.location}/src/**.h",
       "%{prj.location}/src/**.cpp"
    }
    defines {
		"_CRT_SECURE_NO_WARNINGS",
	}

    includedirs {
        "%{prj.location}/src",
        "%{include_directories.spdlog}",
        "%{include_directories.stduuid}",
        "%{include_directories.MGSL}",
        "%{include_directories.Python}",
        "%{include_directories.GLFW}",
        "%{include_directories.glm}",
    }

    links {
        "GLFW",
        "GL",
        "dl",
        "pthread"
    }

    filter "configurations:Debug"
        defines { "DEBUG", "RA_ENABLE_ASSERTS" }
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
