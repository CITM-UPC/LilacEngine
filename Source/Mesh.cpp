#include "Mesh.h"
#include "GL/glew.h"
#include "assimp/cimport.h" 
#include "assimp/scene.h" 
#include "assimp/postprocess.h"

Mesh::Mesh(Formats format, const void* vertex_data, uint numVerts, const uint* index_data, uint numIndexs)
{
	// glGenBuffers(1, &vertex_buffer_id);
	// glBinBuffer(_vertex_buffer_id);
	switch (_format) {
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


Mesh::Mesh(Mesh&& b) noexcept :
    _format(b._format),
    _vertex_buffer_id(b._vertex_buffer_id),
    _numVerts(b._numVerts),
    _index_buffer_id(b._index_buffer_id),
    _numIndexs(b._numIndexs),
    texture(b.texture)
{
    b._vertex_buffer_id = 0;
    b._index_buffer_id = 0;

}

Mesh::~Mesh() {
    if (_vertex_buffer_id) glDeleteBuffers(1, &_vertex_buffer_id);
    if (_index_buffer_id) glDeleteBuffers(1, &_index_buffer_id);
}

void Mesh::draw() {

    glColor4ub(255, 255, 255, 255);

    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
    glEnableClientState(GL_VERTEX_ARRAY);

    switch (_format) {
    case Formats::F_V3:
        glVertexPointer(3, GL_FLOAT, 0, nullptr);
        break;
    case Formats::F_V3C4:
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(V3C4), nullptr);
        glColorPointer(4, GL_FLOAT, sizeof(V3C4), (void*)sizeof(V3));
        break;
    case Formats::F_V3T2:
        glEnable(GL_TEXTURE_2D);
        if (texture.get()) texture->bind();
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(V3T2), nullptr);
        glTexCoordPointer(2, GL_FLOAT, sizeof(V3T2), (void*)sizeof(V3));
        break;
    }

    if (_index_buffer_id) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);
        glDrawElements(GL_TRIANGLES, _numIndexs, GL_UNSIGNED_INT, nullptr);
    }
    else {
        glDrawArrays(GL_TRIANGLES, 0, _numVerts);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);
}