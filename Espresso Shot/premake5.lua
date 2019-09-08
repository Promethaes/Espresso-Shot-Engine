defines{"GLOBAL"}

local solutionDir = "build/"
workspace "Espresso Shot - Built"
   defines{"_CRT_SECURE_NO_WARNINGS"}
   defines{"WORKSPACE"}
   configurations { "Debug", "Release" }
   platforms {"x32","x64","x86"}
   location (solutionDir)
   language "C++"
   cppdialect "C++17"
   files{
      os.getenv("EspressoShotPath").."src/**.cpp",
      os.getenv("EspressoShotPath").."src/**.c",
      os.getenv("EspressoShotPath").."include/Espresso/**.h",
      os.getenv("EspressoShotPath").."Assets/Mesh/**.obj",
      os.getenv("EspressoShotPath").."Assets/Textures/**.png",
      os.getenv("EspressoShotPath").."Assets/Shaders/**.vert",
      os.getenv("EspressoShotPath").."Assets/Shaders/**.frag"
   }
   includedirs{os.getenv("EspressoShotPath").."include/"}

local arch = " "
   filter { "platforms:x32" }
      system "Windows"
      architecture "x32"
      defines {"Win32"}
      arch = "x32"
   filter { "platforms:x86" }
      system "Windows"
      architecture "x86"
      defines {"Win86"}
      arch = "x86"
   filter { "platforms:x64" }
      system "Windows"
      architecture "x64"
      defines {"Win64"}
      arch = "x64"

   filter "configurations:Debug"
      libdirs{os.getenv("EspressoShotPath").."libs/" .. arch .. "/Debug"}
      targetdir (solutionDir .. "/build/" .. arch .. "/Debug")
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      libdirs{os.getenv("EspressoShotPath").."libs/".. arch .. "/Release"}
      targetdir (solutionDir .. "/build/" .. arch .. "/Release")
      defines { "NDEBUG" }
      optimize "On"

project "Espresso Shot - Built"
    defines{"PROJECT"}
    kind "ConsoleApp"
    configuration "windows"
        links { "opengl32", "glfw3.lib"}