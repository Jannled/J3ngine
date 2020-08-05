#include "Window.hpp"

#include <stdio.h>

void J3Window::MessageCallback(
				GLenum source,
				 GLenum type,
				 GLuint id,
				 GLenum severity,
				 GLsizei length,
				 const GLchar* message,
				 const void* userParam
)
{
	const char *mseverity;
	switch(severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:
			mseverity = "[HIGH]"; break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			mseverity = "[Medium]"; break;
		case GL_DEBUG_SEVERITY_LOW:
			mseverity = "[Low]"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			mseverity = "[Note]"; break;
		default:
			mseverity = "[???]"; break;
	}

	const char *mtype;
	switch(type)
	{
		case GL_DEBUG_TYPE_ERROR:
			mtype = "DEBUG_TYPE_ERROR"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			mtype = "DEBUG_TYPE_DEPRECATED_BEHAVIOR"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			mtype = "DEBUG_TYPE_UNDEFINED_BEHAVIOR"; break;
		case GL_DEBUG_TYPE_PORTABILITY:
			mtype = "DEBUG_TYPE_PORTABILITY"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			mtype = "DEBUG_TYPE_PERFORMANCE"; break;
		case GL_DEBUG_TYPE_MARKER:
			mtype = "DEBUG_TYPE_MARKER"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			mtype = "DEBUG_TYPE_PUSH_GROUP"; break;
		case GL_DEBUG_TYPE_POP_GROUP:
			mtype = "DEBUG_TYPE_POP_GROUP"; break;
		case GL_DEBUG_TYPE_OTHER:
			mtype = "DEBUG_TYPE_OTHER"; break;
		default:
			mtype = "???"; break;
	}

	const char* msource;
	switch(source)
	{
		case GL_DEBUG_SOURCE_API:
			msource = "DEBUG_SOURCE_API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			msource = "DEBUG_SOURCE_WINDOW_SYSTEM"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			msource = "DEBUG_SOURCE_SHADER_COMPILER"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			msource = "DEBUG_SOURCE_THIRD_PARTY"; break;
		case GL_DEBUG_SOURCE_APPLICATION:
			msource = "DEBUG_SOURCE_APPLICATION"; break;
		case GL_DEBUG_SOURCE_OTHER:
			msource = "DEBUG_SOURCE_OTHER"; break;
		default:
			msource = "???"; break;
	}

	fprintf(stderr, "[OpenGL]%s %s by %s: %s\n", mseverity, mtype, msource, message);
}