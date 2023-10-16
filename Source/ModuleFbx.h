#pragma once
#include "Module.h"
#include "Globals.h"
#include "assimp/cimport.h" 
#include "assimp/scene.h" 
#include "assimp/postprocess.h"

struct Material {
	// Not sure what do we have to return?
	// void getTexture() {return }
};

class ModuleFbx : public Module {
public:
	ModuleFbx(Application* app, bool start_enabled = true);
	~ModuleFbx();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

private:
	struct aiLogStream stream;
};