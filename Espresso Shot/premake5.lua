defines{"GLOBAL"}

workspace "Espresso Shot - Built"
   defines{"WORKSPACE"}
   configurations { "Debug", "Release" }
   platforms {"x32","x64"}
   location "build/"
   language "C++"
   files{"src/**.cpp","src/**.c","./include/Espresso/**.h"}
   libdirs{"libs"}
   includedirs{"include/"}

   filter "configurations:Debug"
      targetdir ("build/Debug")
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      targetdir ("build/Release")
      defines { "NDEBUG" }
      optimize "On"

   filter { "platforms:x32" }
      system "Windows"
      architecture "x32"

   filter { "platforms:x64" }
      system "Windows"
      architecture "x64"

project "Espresso Shot - Built"
    defines{"PROJECT"}
    kind "ConsoleApp"
    configuration "windows"
        links { "opengl32", "glfw3.lib"}