#include"VBO.h"

// Constructor that generates a Vertex Buffer Object and links it to indices
VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);								// binding the VBO specifying it's a GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);	// introducing the vertices into the VBO
}
// Binds the VBO
void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
// Unbinds the VBO
void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
// Deletes the VBO
void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}