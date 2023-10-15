#pragma once
#include "Module.h"
#include "Globals.h"
#include "assimp/cimport.h" 
#include "assimp/scene.h" 
#include "assimp/postprocess.h"

struct Face {
	// mIndices;
};

struct Mesh {
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

struct Material {
	// Not sure what do we have to return?
	// void getTexture() {return }
};

class ModuleFbx : public Module {
public:
	ModuleFbx(Application* app, bool start_enabled = true);
	~ModuleFbx();

	bool Init();
	//update_status PreUpdate(float dt);
	//update_status Update(float dt);
	//update_status PostUpdate(float dt);
	bool CleanUp();

private:
	struct aiLogStream stream;
};