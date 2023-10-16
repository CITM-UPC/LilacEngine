#pragma once
#include "Globals.h"
//#include "Face.h"

struct Mesh {
	friend struct Face;

	uint id_index = 0; // index in VRAM 
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;

	// Coses x fer segons el powerpoint
	// mVertices[];
	// mNormals[];
	// mTextureCoords[];
	struct Face mFaces[];
	// mMaterialIndex;
};
