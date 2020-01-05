# J3ngine
An OpenGL PBR engine with minimal overhead.

## Status
Im currently designing the base structure for the engine, this is far from being usable.

## Compilation
Run `make` to compile the whole engine.

## About
The engine uses [Galogen](https://galogen.gpfault.net/galogen-web.html) for the [OpenGL](https://www.opengl.org) function calls and a self written library to create the window and [OpenGL](https://www.opengl.org) context.

This engine avoids using [GLFW](https://www.glfw.org) and [GLEW](http://glew.sourceforge.net) as they are some heavy librarys, which are hard to compile.
