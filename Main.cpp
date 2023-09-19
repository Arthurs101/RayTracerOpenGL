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

#include<vector>

const unsigned int width = 800;
const unsigned int height = 800;


// Create an array of sphere properties
struct SphereProperties {
	float radius;
	std::vector<float> color;
	glm::vec3 position;
};


int main()
{
	std::vector<SphereProperties> spheres;

	// Add spheres to the array
	// body
	spheres.push_back({ 1.5f, {0.9f, 0.9f, 1.0f}, glm::vec3(0.0f, 2.0f, 0.0f) });
	spheres.push_back({ 1.0f, {0.9f, 0.9f, 1.0f}, glm::vec3(0.0f, 4.0f, 0.0f) });
	spheres.push_back({ 0.8f, {0.9f, 0.9f, 1.0f}, glm::vec3(0.0f, 5.0f, 0.0f) });
	//nose
	spheres.push_back({0.1f, {1.0f, 0.5f, 0.0f}, glm::vec3(0.0f, 4.7, 4.0f) });
	//buttons
	//face
	spheres.push_back({ 0.08f, {0.63f, 0.51f, 0.38f}, glm::vec3(-0.2f, 4.9f, 4.0f) });
	spheres.push_back({ 0.08f, {0.63f, 0.51f, 0.38f}, glm::vec3(0.2f, 4.9f, 4.0f) });
	//smile
	spheres.push_back({ 0.04f, {0.63f, 0.51f, 0.38f}, glm::vec3(-0.3f, 4.63f, 4.0f) });
	spheres.push_back({ 0.04f, {0.63f, 0.51f, 0.38f}, glm::vec3(-0.15f, 4.55f, 4.0f) });
	spheres.push_back({ 0.04f, {0.63f, 0.51f, 0.38f}, glm::vec3(0.0f, 4.5f, 4.0f) });
	spheres.push_back({ 0.04f, {0.63f, 0.51f, 0.38f}, glm::vec3(0.3f, 4.63f, 4.0f) });
	spheres.push_back({ 0.04f, {0.63f, 0.51f, 0.38f}, glm::vec3(0.15f, 4.55f, 4.0f) });
	//boddy
	spheres.push_back({ 0.08f, {0.63f, 0.51f, 0.38f}, glm::vec3(0.0f,4.2f, 4.0f) });
	spheres.push_back({ 0.08f, {0.63f, 0.51f, 0.38f}, glm::vec3(0.0f,4.0f, 4.0f) });
	spheres.push_back({ 0.08f, {0.63f, 0.51f, 0.38f}, glm::vec3(0.0f,3.5f, 4.0f) });
	spheres.push_back({ 0.08f, {0.63f, 0.51f, 0.38f}, glm::vec3(0.0f,3.0f, 4.0f) });
	// Initialize GLFW
	glfwInit();



	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "RayTRacer"
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
	////cargar shaders
	Shader shader("blin_phon.vert","blin_phon.frag");
		
	//scale uniform
	GLuint uniformID = glGetUniformLocation(shader.shaderID, "scale");

	//declare the texture
	Texture popCat("Earth.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shader, "tex0", 0);
	//declare light properties
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1.0f, 2.0f, 2.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shader.Activate();
		glUniform4f(glGetUniformLocation(shader.shaderID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shader.shaderID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		// Simple timer
		//// Initializes matrices so they are not the null matrix
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// Assigns different transformations to camera
		glm::vec3 camPos = glm::vec3(0.0f, 4.0f, 10.0f);
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

		view = glm::lookAt(camPos, camPos + Orientation, Up);
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
		glm::mat4 cameraMatrix = proj * view;

		//render all the spheres
		for (const SphereProperties& sphereProps : spheres) {
			Sphere sphere(sphereProps.radius, sphereProps.color, sphereProps.position, 36, 36);
			VertexArrayObject vao;
			vao.Bind();
			VertexBuffer vbo(sphere.getVertices());
			ElementBuffer ebo(sphere.getIndices());

			vao.linkVtxBuff(vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0); //vertex
			vao.linkVtxBuff(vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float))); //color
			vao.linkVtxBuff(vbo, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float))); //texture coordinates on layer 2
			vao.linkVtxBuff(vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float))); //normals
			////unbind to avoid future modifications
			vao.Unbind();
			vbo.Unbind();
			ebo.Unbind();

			// Outputs the matrices into the Vertex Shader
			int modelLoc = glGetUniformLocation(shader.shaderID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(sphere.getModel()));
			int viewLoc = glGetUniformLocation(shader.shaderID, "camMatrix");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
			glUniform3f(glGetUniformLocation(shader.shaderID, "camPos"), camPos.x, camPos.y, camPos.z);
			// Set the scale to be 0% bigger
			glUniform1f(uniformID, 0.0f);
			// Bind the texture to apply it
			popCat.Bind();
			//// Bind the VAO so OpenGL knows to use it
			vao.Bind();
			// Draw primitives, number of indices, datatype of indices, index of indices
			glDrawElements(GL_TRIANGLES, sphere.getIndices().size(), GL_UNSIGNED_INT, (void*)0);
			vao.Delete();
			vbo.Delete();
			ebo.Delete();
		}
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	//popCat.Delete();
	shader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}