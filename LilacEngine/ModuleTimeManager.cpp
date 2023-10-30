#include "ModuleTimeManager.h"
#include "Application.h"
//#include "ModuleGui.h"
//#include "ModuleSceneManager.h"
//#include "ModuleFileSystem.h"

//#include "ResourceScene.h"

#include "mmgr.h"

ModuleTimeManager::ModuleTimeManager(bool start_enabled) : Module(start_enabled)
{
	//CONSOLE_LOG("Initializing Time Manager");

	Realtime_clock.Start();
	Gametime_clock.Start();

	frame_count = 0;
	last_frame_ms = -1;
	last_fps = -1;
	capped_ms = 1000 / 60; // Get Display RR!!
	fps_counter = 0;
}

ModuleTimeManager::~ModuleTimeManager() {}

void ModuleTimeManager::PrepareUpdate()
{
	game_dt = realtime_dt = (float)Gametime_clock.Read() / 1000.0f;
	Gametime_clock.Start();

	time += realtime_dt * Time_scale;

	//switch (App->GetAppState())
	//{
	//case AppState::TO_PLAY:
	//	App->GetAppState() = AppState::PLAY;
	//
	//	// --- Create temporal directory/scene ---
	//	App->fs->CreateDirectoryA("Temp");
	//	App->scene_manager->currentScene->CopyInto(App->scene_manager->temporalScene);
	//	App->scene_manager->SaveScene(App->scene_manager->temporalScene);
	//
	//	CONSOLE_LOG("APP STATE PLAY");
	//	break;
	//
	//case AppState::PLAY:
	//	game_dt *= Time_scale;
	//	break;
	//
	//case AppState::TO_PAUSE:
	//	App->GetAppState() = AppState::PAUSE;
	//	CONSOLE_LOG("APP STATE PAUSE");
	//
	//	break;
	//
	//case AppState::PAUSE:
	//	time -= realtime_dt;
	//	game_dt = 0.0f;
	//	break;
	//
	//case AppState::TO_EDITOR:
	//	App->scene_manager->SetActiveScene(App->scene_manager->currentScene);
	//
	//	// --- Clear temporal scene, eliminate temporal files/directory ---
	//	App->scene_manager->temporalScene->NoStaticGameObjects.clear();
	//	App->scene_manager->temporalScene->StaticGameObjects.clear();
	//	App->fs->Remove(App->scene_manager->temporalScene->GetResourceFile());
	//	App->fs->Remove(std::string(App->scene_manager->temporalScene->GetResourceFile()).append(".meta").c_str());
	//	App->fs->Remove("Temp/");
	//
	//	App->GetAppState() = AppState::EDITOR;
	//	CONSOLE_LOG("APP STATE EDITOR");
	//	break;
	//
	//case AppState::EDITOR:
	//	time = 0.0f;
	//	game_dt = 0.0f;
	//	break;
	//
	//case AppState::STEP:
	//	CONSOLE_LOG("APP STATE STEP");
	//	App->GetAppState() = AppState::PAUSE;
	//	break;
	//
	//}
}

void ModuleTimeManager::FinishUpdate()
{
	// --- Recap on framecount and fps ---
	++frame_count;
	++fps_counter;

	if (fps_timer.Read() >= 1000)
	{
		last_fps = fps_counter;
		fps_counter = 0;
		fps_timer.Start();
	}

	last_frame_ms = Gametime_clock.Read();

	// --- Cap fps ---
	if (capped_ms > 0 && (last_frame_ms < capped_ms))
		SDL_Delay(capped_ms - last_frame_ms);

	// --- Send data to GUI-PanelSettings Historiograms
	App->gui->LogFPS((float)last_fps, (float)last_frame_ms);
}

uint ModuleTimeManager::GetMaxFramerate() const
{
	if (capped_ms > 0)
		return (uint)((1.0f / (float)capped_ms) * 1000.0f);
	else
		return 0;
}

float ModuleTimeManager::GetTimeScale() const
{
	return Time_scale;
}

void ModuleTimeManager::CapMs(float ms)
{
	capped_ms = ms;
}

void ModuleTimeManager::SetMaxFramerate(uint maxFramerate)
{
	if (maxFramerate > 0)
		capped_ms = 1000 / maxFramerate;
	else
		capped_ms = 0;
}

void ModuleTimeManager::SetTimeScale(float scale)
{
	Time_scale = scale;
}

float ModuleTimeManager::GetGameDt() const
{
	return game_dt;
}

float ModuleTimeManager::GetRealTimeDt() const
{
	return realtime_dt;
}