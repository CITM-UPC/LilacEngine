#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleTextures : public Module {
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

private:
};
