# Welcome to Espresso Shot Engine!

Welcome to Espresso Shot engine, an aptly named 3D Game Engine that features *just* what you need including OpenGL, supports .obj loading, image loading (using stb_image), and features Scenes and Game Objects. More to come!
# Building Espresso Shot
### Note:
Currently, only windows is supported.

### Building
Espresso Shot must be built using premake5 or higher, which can be found in the External Dependencies folder or  here: [https://github.com/premake/premake-core/releases](https://github.com/premake/premake-core/releases)

Open up a terminal (or command prompt), navigate to where premake5.exe is located, and use this command:
###
	...\External Dependencies\Premake> .\premake5 --file="...\Espresso Shot\premake5.lua" vs2019
Be sure to swap out the "..." with the path to the cloned repo.