#ifndef ElementBuffer_CLASS_H
#define ElementBuffer_CLASS_H

#include<glad/glad.h>
#include <vector>
using namespace std;
class ElementBuffer
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	ElementBuffer(GLuint* indices, GLsizeiptr size);
	ElementBuffer(vector<unsigned int> indeices);
	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
};

#endif
