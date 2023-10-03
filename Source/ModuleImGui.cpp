#include "Globals.h"
#include "Application.h"
#include "ModuleImGui.h"
#include "ModuleWindow.h"
#include "vcpkg/packages/imgui_x64-windows/include/imgui.h"
//#include "vcpkg/packages/imgui_x64-windows/include/imgui_widgets.h"
#include "vcpkg/packages/imgui_x64-windows/include/imgui_impl_sdl2.h"
#include "vcpkg/packages/imgui_x64-windows/include/imgui_impl_opengl3.h"
#include "vcpkg/packages/sdl2_x64-windows/include/SDL2/SDL_opengles2.h"

ModuleImGui::ModuleImGui(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleImGui::~ModuleImGui()
{}

bool ModuleImGui::Init() 
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO();
	////JULS: This should be in ModuleInput
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
	//
	//// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);	
	//ImGui_ImplOpenGL3_Init();
	
	return true;
}

update_status ModuleImGui::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleImGui::Update(float dt) 
{
	//JULS: this is called in ModuleInput
	// (Where your code calls SDL_PollEvent())
	//ImGui_ImplSDL2_ProcessEvent(&event); // Forward your event to backend
	//
	//// (After event loop)
	//// Start the Dear ImGui frame
	//ImGui_ImplOpenGL3_NewFrame();
	//ImGui_ImplSDL2_NewFrame();
	//ImGui::NewFrame();
	//ImGui::ShowDemoWindow(); // Show demo window! :)
	//
	//// Rendering
	//// (Your code clears your framebuffer, renders your other stuff etc.)
	//ImGui::Render();
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//// (Your code calls SDL_GL_SwapWindow() etc.)

	
	return UPDATE_CONTINUE;
}

update_status ModuleImGui::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleImGui::CleanUp()
{
	//ImGui_ImplOpenGL3_Shutdown();
	//ImGui_ImplSDL2_Shutdown();
	//ImGui::DestroyContext();
	return true;
}