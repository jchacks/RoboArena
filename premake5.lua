-- premake5.lua
workspace "RoboArena"
   architecture "x64"
   configurations { "Debug", "Release" }

project "RoboArena"
   kind "SharedLib"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "**.h", "**.cpp" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
