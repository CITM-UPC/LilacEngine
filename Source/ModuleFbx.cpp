#include "Globals.h"
#include "Application.h"
#include "ModuleFbx.h"
#include "assimp/cimport.h" 
#include "assimp/scene.h" 
#include "assimp/postprocess.h"

ModuleFbx::ModuleFbx(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleFbx::~ModuleFbx()
{
}

bool ModuleFbx::Init() 
{
	LOG("Init SDL ImGui event system");
	bool ret = true;
	//stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr); 
	//aiAttachLogStream(&stream);

	return ret;
}

bool ModuleFbx::CleanUp()
{
	LOG("Init SDL ImGui event system");
	bool ret = true;

	aiDetachAllLogStreams();

	return ret;
}