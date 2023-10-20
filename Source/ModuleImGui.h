#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class ModuleImGui : public Module {
public:
	ModuleImGui(Application* app, bool start_enabled = true);
	~ModuleImGui();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void UI();
private:
	//// General
	bool console = false, configuration = false, hierarchy = false, inspector = true, shapes = false;
	
	//// Console

	//// Configuration
	// Framegraph
	char title[25];
	//float fps_log[];
	
	// Booleans to activate menus that are not shown
	// about -> Information about the engine
	// showcase -> Imgui Demo window
	bool about = false, showcase = false;

	// Booleans to change the properties of our window
	float v = 1.0;
	bool fullscreen, resizable, borderless, fullDesktop;

	// Bool to set Vsync
	bool vsync;

	//// Hierarchy

	//// Inspector
	float f = 12.0;

	//// Shapes

};