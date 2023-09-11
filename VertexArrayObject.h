#ifndef VERTEXARRAYOBJECT_CLASS_H
#define VERTEXARRAYOBJECT_CLASS_H

#include<glad/glad.h>
#include"Verterx_Buffer.h"
class VertexArrayObject {
public:
	GLuint vaoID;

	VertexArrayObject();
	void linkVtxBuff(VertexBuffer& VBO, GLuint layout); //link a vertex buffer to the vertex array object
	void linkVtxBuff(VertexBuffer& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset); //link a vertex buffer to the vertex array object

	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};


#endif
