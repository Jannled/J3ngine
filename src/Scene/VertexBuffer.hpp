#ifndef J3_VERTEXBUFFER_H
#define J3_VERTEXBUFFER_H

#include "Galogen46.h"

namespace J3
{
	typedef struct VertexBuffer
    {
        GLvoid* data; /**< Pointer to an element array */
        size_t dataLength; /**< Number of elements in the array */
        GLenum type; /**< Type of elements in the array, see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml */
        GLuint attribIndex; /**< Index of the vertex attribute in the ShaderProgram */
        GLint vecDim = 3; /**< Amount of elements per vector */
        GLsizei stride = 0; /**< Space between vectors */
        GLvoid* offset = (void*) 0; /**< Offset in the vertex buffer */
        GLuint ID = 0; /**< OpenGL buffer handle */
    } VertexBuffer;
}

#endif // J3_VERTEXBUFFER_H