#include "Globals.h"
#include "Application.h"
#include "ModuleFbx.h"

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
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr); 
	aiAttachLogStream(&stream);


	return ret;
}

update_status ModuleFbx::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleFbx::Update(float dt) 
{
	return UPDATE_CONTINUE;
}

update_status ModuleFbx::PostUpdate(float dt) 
{
	return UPDATE_CONTINUE;
}

bool ModuleFbx::CleanUp()
{
	LOG("Init SDL ImGui event system");
	bool ret = true;

	aiDetachAllLogStreams();

	return ret;
}

void ModuleFbx::LoadFbx(const char* file_path)
{
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene % s", file_path);

}