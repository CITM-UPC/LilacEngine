#pragma once

#include "p2List.h"
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
//#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
//#include "ModulePhysics3D.h"
#include "ModuleImGui.h"

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	//ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	//ModulePhysics3D* physics;
	ModuleImGui* imgui;

private:

	Timer	ms_timer;
	float	dt;
	p2List<Module*> list_modules;

public:
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	// --- Getters ---
	const char* GetAppName() const;
	const char* GetOrganizationName() const;
	
	// Setters
	void SetAppName(const char* name);
	void SetOrganizationName(const char* name);
	//void Log(const char* entry);
	void ClearLogsFromConsole();
private:
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	std::string	appName;
	std::string	orgName;
	//std::string	log;
	std::vector<std::string> logs;
};