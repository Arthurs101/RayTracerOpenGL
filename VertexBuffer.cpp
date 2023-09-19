#include "Verterx_Buffer.h"
VertexBuffer::VertexBuffer(GLfloat* vertices, GLsizeiptr size) { //declarar en openGL el buffer
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
VertexBuffer::VertexBuffer(vector<float> vertices) {
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
}
void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
}
void VertexBuffer::Unbind(){
	glBindBuffer(GL_ARRAY_BUFFER, 0);
} 
void VertexBuffer::Delete() {
	glDeleteBuffers(1, &vertexBufferID);
}