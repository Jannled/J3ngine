#include "Scene.h"

#include "lib/JUtils.h"

#include <stdio.h>
#include <iostream>

#include "lib/Galogen46.h"
#include "lib/cgltf.h"

static void loadGLTF(cgltf_data* data, cgltf_options* options);
static GLuint initArrayBuffer(void* data, GLsizeiptr size, GLenum target, GLint num, GLenum type, GLuint attribute, GLsizei stride, size_t offset);

Scene::Scene()
{

}

Scene::~Scene()
{

}

Camera* Scene::getCamera()
{
	return this->camera;
}

int Scene::loadScene(const char* path)
{
	cgltf_options options = {};
	cgltf_data* data = NULL;
	cgltf_result result = cgltf_parse_file(&options, "models/scene.gltf", &data);

	char npath[1024];
	getWorkingDirectory(npath, 1024);

	std::cout << "Working dir: \"" << path << "\"" << std::endl;

	if (result == cgltf_result_success)
	{
		loadGLTF(data, &options);
		
		cgltf_free(data);
	}
	else
		std::cerr << "Failed to open scene!" << std::endl;
}

const GLenum types[] = {GL_FALSE, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT, GL_FLOAT};

void loadGLTF(cgltf_data* data, cgltf_options* options)
{
	for(int m=0; m<data->meshes_count; m++)
	{
		GLuint VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		for(int p=0; p<data->meshes[m].primitives_count; p++)
		{
			for(int a=0; a<data->meshes[m].primitives[p].attributes_count; a++)
			{
				cgltf_accessor* acc = data->meshes[m].primitives[p].attributes[a].data;

				char path[1024];
				snprintf(path, 1024, "models/%s", acc->buffer_view->buffer->uri);
				cgltf_result result = cgltf_load_buffers(options, data, path);

				if(data->meshes[m].primitives[p].attributes[a].type == cgltf_attribute_type_position)
				{
					initArrayBuffer(
						acc->buffer_view->buffer->data,
						acc->buffer_view->buffer->size,
						GL_ARRAY_BUFFER,
						acc->type,
						types[acc->component_type],
						0, //glGetAttribLocation("aPos")
						acc->buffer_view->stride,
						acc->buffer_view->offset + acc->offset
				);
				}
			}
		}

		glBindVertexArray(0);
	}
}

/**
 * \param data Data to populate the buffer with.
 * \param size Size of the afore mentioned data in bytes.
 * \param target Specifies the target to which the buffer object is bound for glBufferData, for example GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
 * \param num Number of elements per vertex attribute, Must be 1-4 or GL_BGRA.
 * \param type Specifies the datatype of each element in the glVertexAttribPointer call.
 * \param attribute Attribute location on the shader
 * \param stride Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
 * \param offset Offset for the first element in bytes.
 */
GLuint initArrayBuffer(void* data, GLsizeiptr size, GLenum target, GLint num, GLenum type, GLuint attribute, GLsizei stride, size_t offset)
{
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(target, buffer);

	glBufferData(target, size, data, GL_STATIC_DRAW);
	glVertexAttribPointer(attribute, num, type, GL_FALSE, stride, (void*) offset);

	glBindBuffer(target, 0);
}