#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <stb.h>

#include"Shader.h"
#include"VertexArrayObject.h"
#include"Verterx_Buffer.h"
#include"ElementBuffer.h"
#include"Texture.h"
#include "Sphere.cpp"


const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates
// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	0.5f, 1.0f
};


// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};




int main()
{
	// Initialize GLFW
	glfwInit();



	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "Raytracer", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	Sphere sphere(2.0f, {0.0f,0.0f,0.0f},{0.0f,0.0f,1.0f});
	GLfloat* sphereV = sphere.getVertices();

	GLuint* sphereI = sphere.getIndices();
	//VertexBuffer vbo(vertices, sizeof(vertices));

	////cargar shaders
	Shader shader("obj.vert","obj.frag");
	////cargar vertex buffers y vertex array buffers
	VertexArrayObject vao;
	vao.Bind();

	VertexBuffer vbo(sphereV, sphere.getVerticesSize());
	ElementBuffer ebo(sphereI, sphere.getIndicesSize());

	vao.linkVtxBuff(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); //position coordinates on layer 0
	vao.linkVtxBuff(vbo, 1, 3,GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // color coordinates on layer 1
	vao.linkVtxBuff(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); //texture coordinates on layer 2
	////unbind para evitar modificaciones futuras
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
	
	//scale uniform
	GLuint uniformID = glGetUniformLocation(shader.shaderID, "scale");

	//declare the texture
	Texture popCat("obama.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shader, "tex0", 0);

	//Variables that help the rotation of the pyramid
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.2f, 0.0f, 0.4f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shader.Activate();

		// Simple timer
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		//// Initializes matrices so they are not the null matrix
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// Assigns different transformations to each matrix
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -8.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		// Outputs the matrices into the Vertex Shader
		int modelLoc = glGetUniformLocation(shader.shaderID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shader.shaderID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shader.shaderID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


		//set the scale to be 20% bigger
		glUniform1f(uniformID,0.2f);
		//hacer bind de la textura para aplicarlo
		popCat.Bind();
		//// Bind the VAO so OpenGL knows to use it
		vao.Bind();
		//// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sphere.getIndicesSize(), GL_UNSIGNED_INT,0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}


	//eliminar vbo,vao
	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	//popCat.Delete();
	shader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}