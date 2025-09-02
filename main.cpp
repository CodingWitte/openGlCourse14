#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>


#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};
GLuint indices[] = {
	0, 2, 1,														// Uppper triangle
	0, 3, 2															// Lower triangle
};


int main() {
	glfwInit();														// initializing GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					// version (before the dot)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);					// version (after the dot)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// defining that only the core version is used so also only modern functions


	
	// creating window using GLFW
	GLFWwindow* window = glfwCreateWindow(800, 800, "openGLCourse", NULL, NULL);
	//width height name fullscreen ?
	if (window == NULL) {											// error handling
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);									// makes the window part of the current context

	gladLoadGL();													// loading GLAD to configure OpenGL
	glViewport(0, 0, 800, 800);										// specify the viewport of OpenGL
	




	Shader shaderProgram("default.vert", "default.frag");			// Generates Shader object using shaders defualt.vert and default.frag

	VAO VAO1;														// Generates Vertex Array Object
	VAO1.Bind();													// Binds Vertex Array Object

	VBO VBO1(vertices, sizeof(vertices));							// Generates Vertex Buffer Object and links it to vertices
	EBO EBO1(indices, sizeof(indices));								// Generates Element Buffer Object and links it to indices

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);						// Links VBO attributes such as coordinates 
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));   //and colors to VAO 
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();




	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");	// Gets ID of uniform called scale

	// Texture
	int widthImg, heightImg, numColCh;


	unsigned char* bytes = stbi_load("pop_cat.png", &widthImg, &heightImg, &numColCh, 0);
	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// for GL clampt to border
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTextParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes); // texture (binded), leftover just put 0, type of color channels, width height, leftover just put 0, type of color channles the image has, data type of the pixels, image data
	glGenerateMipmap(GL_TEXTURE_2D);


	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0); // unbinding texture

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);


	
	while (!glfwWindowShouldClose(window)) {		// main while loop to keep the window displayed
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);	// specify the color of the background rgba like configuration 
		glClear(GL_COLOR_BUFFER_BIT);				// cleaning the bag buffer and assigning the new color to it
		shaderProgram.Activate();					// specifying which shader program OpenGL shall use
		glUniform1f(uniID, 0.5f);					// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glBindTexture(GL_TEXTURE_2D, texture);
		VAO1.Bind();								// binding the VAO so OpenGL uses it
		// type of primitive, starting index of vertices, number of vertices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);			// drawing function arg: 'shape', number of indecies, datatype of indecies, index of indecies

		glfwSwapBuffers(window);					// swapping buffers (back buffer with front buffer
		glfwPollEvents();							// taking care of all GLFW events
	}

	// deleting all objects
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glDeleteTextures(1, &texture);



	glfwDestroyWindow(window);						// deleting window before ending the programm
	glfwTerminate();								// terminating GLFW before ending the programm
	return 0;
}
