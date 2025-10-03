#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>



#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/glm.hpp>
#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;



GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 0.0f, // Lower left corner
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,		5.0f, 0.0f, // Upper left corner
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 0.0f, // Upper right corner
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,		5.0f, 0.0f,  // Lower right corner
	 0.0f, 0.8f,  0.0f,	    0.92f, 0.86f, 0.76f,		2.5f, 5.0f
};
GLuint indices[] = {
	0, 2, 1,														// Uppper triangle
	0, 3, 2,														// Lower triangle
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};
GLfloat lightVertices[] = {
	//	  COORDINATES    //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};
GLuint lightIndices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


int main() {
	glfwInit();														// initializing GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					// version (before the dot)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);					// version (after the dot)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// defining that only the core version is used so also only modern functions


	
	// creating window using GLFW
	GLFWwindow* window = glfwCreateWindow(width, height, "openGLCourse", NULL, NULL);
	//width height name fullscreen ?
	if (window == NULL) {											// error handling
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);									// makes the window part of the current context

	gladLoadGL();													// loading GLAD to configure OpenGL
	glViewport(0, 0, width, height);	     						// specify the viewport of OpenGL
	



//shader1
	Shader shaderProgram("default.vert", "default.frag");			// Generates Shader object using shaders defualt.vert and default.frag

	VAO VAO1;														// Generates Vertex Array Object
	VAO1.Bind();													// Binds Vertex Array Object

	VBO VBO1(vertices, sizeof(vertices));							// Generates Vertex Buffer Object and links it to vertices
	EBO EBO1(indices, sizeof(indices));								// Generates Element Buffer Object and links it to indices

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);						// Links VBO attributes such as coordinates 
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));   // And colors to VAO 
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));	// And image to VAO

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
// shader1


// shader2
	Shader lightShader("light.vert", "light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));






	Texture popCat("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window)) {		// Main while loop to keep the window displayed

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);	// Specify the color of the background rgba like configuration 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Cleaning the bag buffer and depth buffer
						// Specifying which shader program OpenGL shall use
		camera.Inputs(window);						// Handles camera inputs
		camera.updateMatrix(45.0f, 0.1f, 100.0f); // Updates and exports the camera matrix to the Vertex Shader

		shaderProgram.Activate();
		camera.Matrix(shaderProgram, "camMatrix");
		popCat.Bind();								// Binds texture so that it appears in the render
		VAO1.Bind();								// binding the VAO so OpenGL uses it
		// type of primitive, starting index of vertices, number of vertices
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);			// drawing function arg: 'shape', number of indecies, datatype of indecies, index of indecies


		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		// Draw primitives, numbr of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);					// swapping buffers (back buffer with front buffer
		glfwPollEvents();							// taking care of all GLFW events
	}

	// deleting all objects
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram.Delete();
	lightShader.Delete();

	

	glfwDestroyWindow(window);						// deleting window before ending the programm
	glfwTerminate();								// terminating GLFW before ending the programm
	return 0;
}
