#include "Globals.h"
#include "Application.h"
#include "ModuleImGui.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "SDL2/SDL_opengl.h"
#include "mmgr.h"

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
	ImGuiIO& io = ImGui::GetIO();
#pragma region UI
	// For debugging
	ImGui::ShowDemoWindow();

	// Tabs
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("General")) {
		if (ImGui::BeginMenu("Editor")) {
			if (ImGui::MenuItem("Console"))
				console = !console;
			if (ImGui::MenuItem("Configuration"))
			configuration = !configuration;
			if (ImGui::MenuItem("Hierarchy"))
				hierarchy = !hierarchy;
			if (ImGui::MenuItem("Inspector"))
				inspector = !inspector;
			if (ImGui::MenuItem("Shapes"))
				shapes = !shapes;
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Github page")) {
			ShellExecute(0, 0, "https://github.com/CITM-UPC/LilacEngine", 0, 0, SW_SHOW);
		}
		if (ImGui::MenuItem("About")) {
			about = !about;
		}	
		if (ImGui::MenuItem("Quit")) {
			return UPDATE_STOP;
		}
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
	
	// About tab
	if (about) {
		showAbout();
	}

	if (console) {
		showConsole();
	}

	// Configuration
	if (configuration) {	
		showConfiguration();
	}
	
	if (hierarchy) {
		showHierarchy();
	}
	
	if (inspector) {
		showInspector();
	}

	if (shapes) {
		showLoad();
	}

#pragma endregion UI

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
	LOG("Destroying Imgui context");
	bool ret = true; 
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

void ModuleImGui::showConsole() {
	ImGui::Begin("Console");
	ImGui::EndMenu();
	ImGui::End();
}

void ModuleImGui::showConfiguration() {
	ImGuiIO& io = ImGui::GetIO();
	
	//ImGui::Begin("Configuration");
	//if (ImGui::CollapsingHeader("Application")) {
	//	// --- Organization name ---
	//	static char orgName[100];
	//	if (App->GetOrganizationName() != nullptr)
	//		strcpy_s(orgName, 100, App->GetOrganizationName());
	//	if (ImGui::InputText("Organization Name", orgName, 100, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
	//		App->SetOrganizationName(orgName);

	//	ImGui::Separator();
	//	// --- Cap frames ---
	//	int maxFramerate = App->time->GetMaxFramerate();
	//	if (ImGui::SliderInt("Max FPS", &maxFramerate, 0, App->window->GetDisplayRefreshRate()))
	//		App->time->SetMaxFramerate(maxFramerate);
	//	
	//	char title[25];
	//	sprintf_s(title, 25, "Framerate %.1f", FPS_Tracker[FPS_Tracker.size() - 1]);
	//	ImGui::PlotHistogram("##Framerate", &FPS_Tracker[0], FPS_Tracker.size(), 0, title, 0.0f, 100.0f, ImVec2(500, 75));
	//	sprintf_s(title, 25, "Milliseconds %0.1f", MS_Tracker[MS_Tracker.size() - 1]);
	//	ImGui::PlotHistogram("##Milliseconds", &MS_Tracker[0], MS_Tracker.size(), 0, title, 0.0f, 40.0f, ImVec2(500, 75));

	//	sMStats MemoryStats = m_getMemoryStatistics(); // Using mmgr 
	//	static int speed = 0;
	//	static std::vector<float> Memory(100); // Hom many units/lines we want in the plot
	//	if (++speed > 25) // How fast the plot is plotted :)
	//	{
	//		speed = 0;
	//		if (Memory.size() == 100)
	//		{
	//			for (uint i = 0; i < 100 - 1; ++i)
	//				Memory[i] = Memory[i + 1];

	//			Memory[100 - 1] = (float)MemoryStats.totalReportedMemory;
	//		}
	//		else
	//			Memory.push_back((float)MemoryStats.totalReportedMemory);
	//	}

	//	ImGui::PlotHistogram("##Memory", &Memory[0], Memory.size(), 0, "Memory Consumption", 0.0f, (float)MemoryStats.peakReportedMemory * 1.2f, ImVec2(500, 75));

	//	ImGui::Text("Total Reported Memory: %u", MemoryStats.totalReportedMemory);
	//	ImGui::Text("Total Actual Memory: %u", MemoryStats.totalActualMemory);
	//	ImGui::Text("Peak Reported Memory: %u", MemoryStats.peakReportedMemory);
	//	ImGui::Text("Peak Actual Memory: %u", MemoryStats.peakActualMemory);
	//	ImGui::Text("Accumulated Reported Memory: %u", MemoryStats.accumulatedReportedMemory);
	//	ImGui::Text("Accumulated Actual Memory: %u", MemoryStats.accumulatedActualMemory);
	//	ImGui::Text("Accumulated Alloc Unit Count: %u", MemoryStats.accumulatedAllocUnitCount);
	//	ImGui::Text("Total Alloc Unit Count: %u", MemoryStats.totalAllocUnitCount);
	//	ImGui::Text("Peak Alloc Unit Count: %u", MemoryStats.peakAllocUnitCount);
	//}
	//if (ImGui::CollapsingHeader("Window")) {
	//	if (ImGui::SliderFloat("Brightness", &v, 0.0, 1.0))
	//		App->window->SetWindowBrightness(v);
	//	if (ImGui::Checkbox("Fullscreen", &fullscreen))
	//		App->window->SetFullscreen(fullscreen);
	//	if (ImGui::Checkbox("Resizable", &resizable))
	//		App->window->SetResizable(resizable);
	//	if (ImGui::Checkbox("Borderless", &borderless))
	//		App->window->SetBorderless(!borderless);
	//}
	//if (ImGui::CollapsingHeader("Renderer")) {
	//	if (ImGui::Checkbox("Vsync", &vsync))
	//		App->renderer3D->SetVsync(vsync);
	//}
	//if (ImGui::CollapsingHeader("Input")) {
	//	if (ImGui::IsMousePosValid())
	//		ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
	//	else
	//		ImGui::Text("Mouse Position: <invalid>");
	//	ImGui::Text("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);
	//	ImGui::Text("Mouse wheel: %.1f", io.MouseWheel);
	//}
	//if (ImGui::CollapsingHeader("Audio")) {
	//	ImGui::Text("No audio applied for now!", io.MousePos.x, io.MousePos.y);
	//	//if (ImGui::SliderFloat("Music", &v, 0.0, 1.0))
	//	//
	//	//if (ImGui::SliderFloat("Fx", &v, 0.0, 1.0))
	//	//
	//}
	//if (ImGui::CollapsingHeader("Textures")) {
	//	//if (ImGui::SliderFloat("Music", &v, 0.0, 1.0))
	//	//
	//	//if (ImGui::SliderFloat("Fx", &v, 0.0, 1.0))
	//	//
	//}
	//if (ImGui::CollapsingHeader("Hardware")) {
	//	//if (ImGui::SliderFloat("Music", &v, 0.0, 1.0))
	//	//
	//	//if (ImGui::SliderFloat("Fx", &v, 0.0, 1.0))
	//	//
	//}
	ImGui::EndMenu();
	ImGui::End();
}

void ModuleImGui::showHierarchy() {
	ImGui::Begin("Hierarchy");
	ImGui::EndMenu();
	ImGui::End();
}

void ModuleImGui::showInspector() {
	ImGui::Begin("Inspector");
	//if () {
	//	if (ImGui::TreeNode("Transform")) {
	//		ImGui::SeparatorText("Position");
	//		ImGui::DragFloat("X", &f, 0.2f, 2.0f, 100.0f, "%.0f");
	//		ImGui::DragFloat("Y", &f, 0.2f, 2.0f, 100.0f, "%.0f");
	//		ImGui::DragFloat("Z", &f, 0.2f, 2.0f, 100.0f, "%.0f");
	//		ImGui::SeparatorText("Rotate");
	//		ImGui::DragFloat("X", &f, 0.2f, 2.0f, 100.0f, "%.0f");
	//		ImGui::DragFloat("Y", &f, 0.2f, 2.0f, 100.0f, "%.0f");
	//		ImGui::DragFloat("Z", &f, 0.2f, 2.0f, 100.0f, "%.0f");
	//		ImGui::SeparatorText("Scale");
	//		ImGui::DragFloat("X", &f, 0.2f, 2.0f, 100.0f, "%.0f");
	//		ImGui::DragFloat("Y", &f, 0.2f, 2.0f, 100.0f, "%.0f");
	//		ImGui::DragFloat("Z", &f, 0.2f, 2.0f, 100.0f, "%.0f");
	//		ImGui::TreePop();
	//	}
	//	if (ImGui::TreeNode("Mesh")) {
	//		ImGui::TreePop();
	//	}
	//	if (ImGui::TreeNode("Texture")) {
	//		ImGui::TreePop();
	//	}
	//	ImGui::EndMenu();
	//	ImGui::End();
	//}
}

void ModuleImGui::showLoad() {
	ImGui::Begin("Load");
	ImGui::EndMenu();
	ImGui::End();
}

void ModuleImGui::showAbout() {
	ImGui::OpenPopup("About");
	if (ImGui::BeginPopupModal("About", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("Lilac Engine");
		ImGui::Text("An engine in development");
		ImGui::Text(u8"by Júlia Serra Trujillo and Joel Chaves Moreno\n\n");
		ImGui::Text("3rd Party Libraries used:");
		// Need to change this
		ImGui::Text("- SDL 2");
		ImGui::Text("- ImGui\n\n");
		ImGui::Text("License:\n\n");
		ImGui::Text("MIT License\n\n");
		// 1st Paragraph
		ImGui::Text(u8"Copyright (c) 2023 Júlia Serra Trujillo and Joel Chaves Moreno\n\n");
		ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy\n");
		ImGui::Text("of this software and associated documentation files (\"the Software\"), to deal\n");
		ImGui::Text("in the Software without restriction, including without limitation the rights\n");
		ImGui::Text("to use, copy, modify, merge, publish, distribute, sublicense, and /or sell\n");
		ImGui::Text("copies of the Software, and to permit persons to whom the Software is\n");
		ImGui::Text("furnished to do so, subject to the following conditions : \n\n");
		// 2nd Paragraph
		ImGui::Text("The above copyright notice and this permission notice shall be included in all\n");
		ImGui::Text("copies or substantial portions of the Software.\n\n");
		// 3rd
		ImGui::Text("THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n");
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