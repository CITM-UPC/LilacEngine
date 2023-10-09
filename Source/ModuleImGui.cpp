#include "Globals.h"
#include "Application.h"
#include "ModuleImGui.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "imgui.h"
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
	
	//Enable
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
	// Close the app
	ImGui::Begin("Quit", NULL, ImGuiWindowFlags_NoCollapse);
	if (ImGui::Button("Close the app"))
		return UPDATE_STOP;
	ImGui::End();
	
#pragma region MENU
	// Configuration
	ImGui::Begin("Configuration");
	ImGui::BeginMainMenuBar();
	ImGui::EndMainMenuBar();
	ImGui::Spacing();
	if (ImGui::CollapsingHeader("Window")) {
		if (ImGui::Checkbox("Fullscreen", &fullscreen)) {
			App->window->SetFullscreen(fullscreen);
		}
		if (ImGui::Checkbox("Resizable", &resizable)) {
			App->window->SetResizable(resizable);
		}
		if (ImGui::Checkbox("Borderless", &borderless)) {
			App->window->SetBorderless(borderless);
		}
	}
	if (ImGui::CollapsingHeader("Renderer")) {
		if (ImGui::Checkbox("Vsync", &vsync)) {
			App->renderer3D->SetVsync(vsync);
		}
	}
	ImGui::CollapsingHeader("Input");
	ImGui::CollapsingHeader("Audio");
	ImGui::EndMenu();
	ImGui::End();

	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("Help")) {
		if (ImGui::MenuItem("Gui Demo")) {
			showcase = !showcase;
		}
		if (ImGui::MenuItem("Documentation")) {
			
		}
		if (ImGui::MenuItem("Download latest")) {
			
		}
		if (ImGui::MenuItem("Report a bug")) {
			
		}
		if (ImGui::MenuItem("About")) {
			about = !about;
		}
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	if (about) {
		ImGui::OpenPopup("About");
		if (ImGui::BeginPopupModal("About", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Text("Lilac Engine");
			ImGui::Text("An engine in development");
			ImGui::Text("by Júlia Serra Trujillo and Joel Chaves Moreno\n\n");
			ImGui::Text("3rd Party Libraries used:");
			ImGui::Text("- SDL 2");
			ImGui::Text("- ImGui\n\n");
			ImGui::Text("License:\n\n");
			ImGui::Text("MIT License\n\n");
			// 1st Paragraph
			ImGui::Text("Copyright (c) 2023 Júlia Serra Trujillo and Joel Chaves Moreno\n\n");
			ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy\n");
			ImGui::Text("of this software and associated documentation files(the Software), to deal\n");
			ImGui::Text("in the Software without restriction, including without limitation the rights\n");
			ImGui::Text("to use, copy, modify, merge, publish, distribute, sublicense, and /or sell\n");
			ImGui::Text("copies of the Software, and to permit persons to whom the Software is\n");
			ImGui::Text("furnished to do so, subject to the following conditions : \n\n");
			// 2nd Paragraph
			ImGui::Text("The above copyright notice and this permission notice shall be included in all\n");
			ImGui::Text("copies or substantial portions of the Software.\n\n");
			// 3rd
			ImGui::Text("THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n");
			ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n");
			ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n");
			ImGui::Text("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n");
			ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n");
			ImGui::Text("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n");
			ImGui::Text("SOFTWARE\n\n");

			if (ImGui::Button("Close the window")) {
				about = !about;
			}
			ImGui::EndPopup();
		}
	}

	if (showcase) {
		ImGui::ShowDemoWindow();
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
