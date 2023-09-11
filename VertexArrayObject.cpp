#include "VertexArrayObject.h"
VertexArrayObject::VertexArrayObject() {
	glGenVertexArrays(1, &vaoID);
};
void VertexArrayObject::linkVtxBuff(VertexBuffer& VBO, GLuint layout) {
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
};
void VertexArrayObject::linkVtxBuff(VertexBuffer& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
};
void  VertexArrayObject::Bind() {
	glBindVertexArray(vaoID);
}
// Unbinds the VAO
void  VertexArrayObject::Unbind() {
	glBindVertexArray(0);
}
// Deletes the VAO
void VertexArrayObject::Delete() {
	glDeleteVertexArrays(1, &vaoID);
}