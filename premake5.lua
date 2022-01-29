-- premake5.lua
workspace "RoboArena"
   architecture "x64"
   configurations { "Debug", "Release", "Python" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


include_directories = {}
include_directories["Python"] = "/usr/local/include/python3.8/"
include_directories["spdlog"] = "RoboArena/vendor/spdlog/include"
include_directories["glm"] = "RoboArena/vendor/glm"

project "RoboArena"
    location "RoboArena"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    pic "On"

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
        "%{include_directories.Python}",
        "%{include_directories.glm}",
    }
    

    links {
        "dl",
        "pthread"
    }
    filter "system:macosx"
        links {"Python.framework"}
        linkoptions {"-F /usr/local/Cellar/python@3.8/3.8.12_1/Frameworks"}
        buildoptions {"-F /usr/local/Cellar/python@3.8/3.8.12_1/Frameworks"}


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
            ("{COPY} %{cfg.buildtarget.relpath} ../PyRoboArena/lib/%{cfg.buildtarget.name}"),
            ("cd ../PyRoboArena && python setup.py build_ext --inplace"),
        }
