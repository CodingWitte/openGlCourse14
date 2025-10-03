#ifndef Block_CLASS_H
#define BLOCK_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"




class Block {
public:
	Block();
	~Block();
	// Add and build a block at position+orientation, use texture index
	void createBlock(const glm::vec3 position, const glm::vec3& orientation, int textureIndex);
	// Draw all blocks
	void drawBlocks();
private:
	void setupMesh();
	void updateInstanceData(size_t index, const glm::vec3& pos, const glm::vec3& ori);
	void uploadVertexData();

	static GLuint s_indices[36];
	static GLfloat s_vertices[192];
	static bool s_meshInitialized;

	// Per-instance storage
	std::vector<VAO>	m_vaos;
	std::vector<VBO>	m_vbos;
	std::vector<EBO>	m_ebos;
	std::vector<Texture>m_textures;
	std::vector<int>	m_activeTex;
	std::vector<GLfloat> m_instanceVertices;

	// One sharded VBO/EBO/VAO for geometry
	VAO		m_sharedVAO;
	VBO		m_sharedVBO;
	EBO		m_sharedEBO;
};

#endif
//ballad of the beaconsfield miners