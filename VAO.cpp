#include"VAO.h"



VAO::VAO() {
	glGenVertexArrays(1, &ID);// generating VAO
}
// Links a VBO attribute to the VAO using certain layouts
void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.Bind();
	//configuring the VAO
	// configuring the vertex atribute so OpenGL knows how to read the VBO
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);// enabeling vertexAttributeArray so OpenGL knows to use it(0 position of vertex attribute)
	VBO.Unbind();
}

void VAO::Bind() {
	glBindVertexArray(ID);// binding the VAO => making it the current obj IMPORTANT
}
void VAO::Unbind() {
	glBindVertexArray(0);
}
void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}