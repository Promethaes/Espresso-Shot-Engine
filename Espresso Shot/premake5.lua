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
      os.getenv("EspressoShotPath").."include/Espresso/**.hpp",
      os.getenv("EspressoShotPath").."include/Espresso/**.cs",
      os.getenv("EspressoShotPath").."Assets/Mesh/**.obj",
      os.getenv("EspressoShotPath").."Assets/Textures/**.png",
      os.getenv("EspressoShotPath").."Assets/Shaders/**.vert",
      os.getenv("EspressoShotPath").."Assets/Shaders/**.frag"
   }
   includedirs{os.getenv("EspressoShotPath").."include/"}

local arch = " "
local config = " "
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
      defines { "DEBUG" }
      symbols "On"
      targetdir (solutionDir .. "/build/" .. arch .. "/Debug")
      config = "/Debug"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      targetdir (solutionDir .. "/build/" .. arch .. "/Release")
      config = "/Release"

   filter {}
      libdirs{os.getenv("EspressoShotPath").."libs/" .. arch .. config,os.getenv("EspressoShotPath").."libs/" .. arch .. config.."/Fmod"}
      config = "\\Release\\"
      os.execute("mkdir " .. "build\\build\\"..arch..config)
      os.execute("XCOPY " .. "libs\\x64\\Debug\\Fmod\\fmod.dll " .."build\\build\\"..arch..config)
      config = "\\Debug\\"
      os.execute("mkdir " .. "build\\build\\"..arch..config)
      os.execute("XCOPY " .. "libs\\x64\\Debug\\Fmod\\fmod.dll " .."build\\build\\"..arch..config)

project "Espresso Shot - Built"
    defines{"PROJECT"}
    kind "ConsoleApp"
    configuration "windows"
        links { "opengl32", "glfw3.lib","fmod_vc.lib","fmodL_vc.lib"}