defines{"GLOBAL"}

workspace "Espresso Shot - Built"
   defines{"WORKSPACE"}
   configurations { "Debug", "Release" }
   platforms {"x32","x64"}
   location "build/"
   language "C++"
   cppdialect "C++17"
   files{"src/**.cpp","src/**.c","./include/Espresso/**.h"}
   includedirs{"include/"}

local arch = " "
   filter { "platforms:x32" }
      system "Windows"
      architecture "x32"
      defines {"Win32"}
      arch = "x32"

   filter { "platforms:x64" }
      system "Windows"
      architecture "x64"
      defines {"Win64"}
      arch = "x64"

   filter "configurations:Debug"
      libdirs{"libs/" .. arch .. "/Debug"}
      targetdir ("build/" .. arch .. "/Debug")
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      libdirs{"libs/".. arch .. "/Release"}
      targetdir ("build/" .. arch .. "/Release")
      defines { "NDEBUG" }
      optimize "On"

project "Espresso Shot - Built"
    defines{"PROJECT"}
    kind "ConsoleApp"
    configuration "windows"
        links { "opengl32", "glfw3.lib"}