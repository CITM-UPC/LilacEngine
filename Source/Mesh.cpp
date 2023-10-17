#include "Mesh.h"
#include "GL/glew.h"

Mesh::Mesh(Formats format, const void* vertex_data, uint numVerts, const uint* index_data, uint numIndexs)
{
	// glGenBuffers(1, &vertex_buffer_id);
	// glBinBuffer(_vertex_buffer_id);
	switch (_formats) {
	case Formats::F_V3T2:
		glBufferData(GL_VERTEX_ARRAY, sizeof(double) * 5 * _numVerts, vertex_data, GL_STATIC_DRAW);
	default:
		throw "not implemented";
	}
	glBindBuffer(GL_VERTEX_ARRAY, 0);

	glGenBuffers(1, &_index_buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * numIndexs, index_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertex_buffer_id);

	switch (_formats) {
	case Formats::F_V3T2:
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_DOUBLE, sizeof(double) * 5, nullptr);
		glTexCoordPointer(2, GL_DOUBLE, sizeof(double) * 5, (void*)(sizeof(double) * 5));
	default:
		throw "not implemented";
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);
}