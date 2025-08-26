#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
// vertex shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position =  vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
// fragment shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.2f, 1.0f);\n"
"}\n\0";

int main() {
	glfwInit();														// initializing GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					// version (before the dot)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);					// version (after the dot)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// defining that only the core version is used so also only modern functions
	
	
	GLfloat vertices[] = {											// vertices coordinates
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,					// lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,						// lower right corner
		0.0f ,0.5f * float(sqrt(3)) * 2 / 3, 0.0f					// upper corner
	};

	// creating window using GLFW
	GLFWwindow* window = glfwCreateWindow(800, 800, "openGLCourse", NULL, NULL);
	//width height name fullscreen ?
	if (window == NULL) {											// error handling
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);									// makes the window part of the current context
	
	gladLoadGL();													// loading GLAD to configure OpenGL
	glViewport(0,0,800,800);										// specify the viewport of OpenGL


// Shaders //
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);			// creating vertex shader object and getting its reference
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);		// attaching vertex shader source to vertex shader object
	glCompileShader(vertexShader);									// compiling shader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		// creating fragment shader object and getting its reference
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);	// attaching vertex shader source to vertex shader object
	glCompileShader(fragmentShader);								// compiling shader

	GLuint shaderProgram = glCreateProgram();						// creating shader program object and get its refernce
		
	glAttachShader(shaderProgram, vertexShader);					// attaching vertex & fragment shader to the shader program 
	glAttachShader(shaderProgram, fragmentShader);					// arg1: reference to the shaderProgram arg2: the shader itself
	
	glLinkProgram(shaderProgram);									// wrap up all shaders into the shader program arg: reference to the shader program

	
	glDeleteShader(vertexShader);									// deleting now no more used vertex shader object &
	glDeleteShader(fragmentShader);									// fragment shader object
// Shaders //


	GLuint VAO, VBO;															// creating reference containers for: vertex array object, vertex buffer object
	// specifying where to find the object / vertex array object => stores pointers to one or more vbos and defines how to interprate them
	glGenVertexArrays(1, &VAO);													// generating the VAO & the VBO with 1 object each COUTION: VAO must be generated before VBO
	glGenBuffers(1, &VBO);														// arg1: number of objs, arg2: refference to reference containers
	
	glBindVertexArray(VAO);														// binding the VAO => making it the current obj
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);											// binding the VBO specifying it's a GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// introducing the vertices into the VBO
	// from this point on the VBO is created									// stream = modifyed once used a few times, static = modifyed once used many times, dynamic = modifyed a few times used many times
																				// draw = modyfied and used to draw and img on the screen, read, copy
	//configuring the VAO
	// 1. arg: inder of vertix atribute(way of comunicating with the vertex shader from the outside), 2. arg number of vertex arguments, 3. arg kind of values, 4. arg: only important if there are coordinates as intagers 5. argument stride of vertices => amount of data between each vertex 5. arg: offset pointer to vertices begin in array (in this case they are right at the start)
	// configuring the vertex atribute so OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
	
	
	glEnableVertexAttribArray(0);												// enabeling vertexAttributeArray so OpenGL knows to use it(0 position of vertex attribute)
	
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);											// Bind the VBO & VAO to 0 so they cant be modifyed anymore
	glBindVertexArray(0);

		// concept: binding in open gl
		// making a certin object the current object
		// when a funciton is fiered to modify that type of obj it modifyes the current object / the binded object
	
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);		// specifying background color rgba like configuration 
	
	glClear(GL_COLOR_BUFFER_BIT);					// cleaning bag buffer & assigning new color to it

	
	glfwSwapBuffers(window);						// swapping buffers (back buffer with front buffer)

	
	while (!glfwWindowShouldClose(window)) {		// main while loop to keep the window displayed
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);	// specify the color of the background rgba like configuration 
		glClear(GL_COLOR_BUFFER_BIT);				// cleaning the bag buffer and assigning the new color to it
		glUseProgram(shaderProgram);				// specifying which shader program OpenGL shall use
		glBindVertexArray(VAO);						// binding the VAO so OpenGL uses it
		// type of primitive, starting index of vertices, number of vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);			// drawing function

		glfwSwapBuffers(window);					// swapping buffers (back buffer with front buffer
		glfwPollEvents();							// taking care of all GLFW events
	}
	
	
	//deleting all created objs
	glDeleteVertexArrays(1, &VAO);	
	glDeleteBuffers(1, &VBO);		
	glDeleteProgram(shaderProgram);	


	glfwDestroyWindow(window);						// deleting window before ending the programm
	glfwTerminate();								// terminating GLFW before ending the programm
	return 0;
}
