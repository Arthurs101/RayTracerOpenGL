//this if is to avoid opening or declaring more than once the class from the header
#ifndef SHADER_ClASS_H
#define SHADER_ClASS_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cerrno>


std::string read_file_instructions(const char* filename);  //funcion para leer los datos de los archivos
class Shader {
public:
	GLuint shaderID;
	//constructor que necesita de los archivos con las instrucciones de los sahders para opengl
	Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
	void Activate();
	void Delete();

};

#endif