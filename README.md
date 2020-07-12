# J3ngine
An OpenGL PBR engine with minimal overhead. Might use it for some games later on.

## Status
Im currently designing the base structure for the engine, this is far from being usable.

## Compilation
The project is compiled with CMake

### Dependencies
- [glm](https://glm.g-truc.net/0.9.9/index.html)
- [stb_image](https://github.com/nothings/stb)
- [Galogen](https://galogen.gpfault.net/galogen-web.html)
- [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)

## About
The engine uses [Galogen](https://galogen.gpfault.net/galogen-web.html) for the [OpenGL](https://www.opengl.org) function calls and a self written library to create the window and [OpenGL](https://www.opengl.org) context.

This engine avoids using [GLFW](https://www.glfw.org) and [GLEW](http://glew.sourceforge.net) as they are some heavy librarys, which are hard to compile.
