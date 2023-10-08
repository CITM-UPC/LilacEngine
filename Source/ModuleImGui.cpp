#include "Globals.h"
#include "Application.h"
#include "ModuleImGui.h"
#include "ModuleWindow.h"
#include "imgui.h"
//#include "vcpkg/packages/imgui_x64-windows/include/imgui_widgets.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "SDL2/SDL_opengles2.h"

ModuleImGui::ModuleImGui(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleImGui::~ModuleImGui()
{}

bool ModuleImGui::Init() 
{
	LOG("Init SDL ImGui event system");
	bool ret = true;
	
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//JULS: This should be in ModuleInput
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();
	
	return ret;
}

update_status ModuleImGui::PreUpdate(float dt)
{
	// (After event loop)
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleImGui::Update(float dt) 
{
	// HOMEWORK 1
	ImGui::ShowDemoWindow();
	ImGui::Begin("Homework 1");
	if (ImGui::Button("Close the app"))
		return UPDATE_STOP;
	ImGui::End();
	
#pragma region MENU
	// HOMEWORK 3
	ImGui::Begin("Configuration");
	ImGui::BeginMainMenuBar();
	ImGui::EndMainMenuBar();
	ImGui::Spacing();
	ImGui::CollapsingHeader("Window");
	ImGui::CollapsingHeader("Renderer");
	ImGui::CollapsingHeader("Input");
	ImGui::CollapsingHeader("Audio");
	ImGui::CollapsingHeader("About");
	ImGui::EndMenu();
	ImGui::End();

	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("Help")) {
		if (ImGui::MenuItem("About")) {
			about = !about;
		}
	}

	if (about) {
		ImGui::Begin("Help");
		ImGui::Text("Lilac Engine");
		ImGui::Text("A great engine in development");
		ImGui::Text("by Júlia Serra Trujillo and Joel Chaves Moreno");
		ImGui::Spacing();
		ImGui::Text("3rd Party Libraries used:");
		ImGui::Text("- SDL");
		ImGui::Text("- ImGui");
		ImGui::Spacing();
		ImGui::Text("License:");
		ImGui::Spacing();
		ImGui::Text("MIT License");
		ImGui::Spacing();
		ImGui::Text("Copyright (c) 2023 Júlia Serra Trujillo and Joel Chaves Moreno");
	}

#pragma endregion MENU

	// Rendering
	// (Your code clears your framebuffer, renders your other stuff etc.)
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// (Your code calls SDL_GL_SwapWindow() etc.)
	return UPDATE_CONTINUE;
}

update_status ModuleImGui::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleImGui::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

void ModuleImGui::UI() {

}
