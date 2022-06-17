![Teapot image](https://github.com/kgrajda/SGEng/blob/main/static/teapot.png)
# SGEng [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Simple Game Engine in C++20.

## Features

* Separate threads for GLFW event loop processing and game loop,
* Programmable startup, update, draw and destroy stage of the game loop,
* OpenGL and GLFW abstractions,
* Run-time shader reloading,
* Blinn-Phong shading model,
* OBJ file loading,
* Configurable through TOML file,
* Simple key press and mouse button press management.

## Dependencies

* [OpenGL (glad2)](https://gen.glad.sh/) >= 4.5
* [GLFW](https://github.com/glfw/glfw)
* [GLM](https://github.com/g-truc/glm)
* [Assimp](https://github.com/assimp/assimp)
* [Toml++](https://marzer.github.io/tomlplusplus/)
* [Plog](https://github.com/SergiusTheBest/plog)
