-- premake5.lua
workspace "RoboArena"
   architecture "x64"
   configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "RoboArena"
    location "RoboArena"
    kind "StaticLib" --"ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.location}")

    files {
       "%{prj.location}/src/**.h",
       "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{prj.location}/vendor/spdlog/include",
        "/usr/include/python3.8/"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
