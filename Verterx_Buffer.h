#ifndef VERTEXBUFFER_CLASS_H
#define VERTEXBUFFER_CLASS_H
#include <glad/glad.h>
class VertexBuffer {
public:
	GLuint vertexBufferID; //unsigned int de id de referencia
	VertexBuffer(GLfloat* vertices , GLsizeiptr size);
	void Bind(); //hacer binding del vertex buffer para que opengl lo use
	void Unbind(); //desvincular del hilo de ejecución
	void Delete(); //destruir buffers
};
#endif