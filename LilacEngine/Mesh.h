#pragma once
#include "Globals.h"
#include "Graphic.h"
#include "Texture.h"

struct Mesh : public Graphic {
	//friend struct Face;
public:
	enum class Formats { F_V3, F_V3T2, F_V3C4, F_V3CAT2 };
	struct V3 { vec3d v; };
	struct V3C4 { vec3d v; vec4d c; };
	struct V3T2 { vec3d v; vec2d t; };

private:
	Formats _format;
	
	uint _index_buffer_id = 0; // index in VRAM 
	uint _numIndexs = 0;

	uint _vertex_buffer_id = 0; // unique vertex in VRAM
	uint _numVerts = 0;

public:
	typedef std::shared_ptr <Mesh> Ptr;
	static std::vector <Mesh::Ptr> loadFromFile(const std::string& path);

	Texture::Ptr texture;
	Mesh(Formats format, const void* vertex_data, uint numVerts, const uint* index_data, uint numIndexs);
	Mesh(Mesh&& b) noexcept;
	void draw();
	~Mesh();

private:
	Mesh(const Mesh&);
	Mesh& operator=(const Mesh&);

};
