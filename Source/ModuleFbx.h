#pragma once
#include "Module.h"
#include "Globals.h"

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
	//struct aiLogStream stream;
};