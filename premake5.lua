-- premake5.lua
workspace "RoboArena"
   architecture "x64"
   configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "RoboArena"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")

    files {
       "src/**.h",
       "src/**.cpp"
    }

    includedirs {
        "vendor/spdlog/include",
        "/usr/include/python3.8/"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
