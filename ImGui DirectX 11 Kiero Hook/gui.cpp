#include "gui.h"
#include "utils.h"
#include "globals.h"
#include "hooks.h"

CGui gui;

void CGui::render()
{

	if (GetAsyncKeyState(VK_INSERT) & 1)
		globals.menu_open = !globals.menu_open;

	if (GetAsyncKeyState(VK_DELETE) & 1)
		utils.unloadcheat();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (globals.menu_open)
	{

		ImGui::SetNextWindowSize(ImVec2(430, 250));

		ImGui::Begin("scrapware", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

		ImGui::Text("Hello, Scrap mechanic.");
		ImGui::Checkbox("Enable Fps Counter", &globals.show_fps);
		ImGui::Text("Run Lua String");
		ImGui::InputText("##runstring", globals.output_text, sizeof(globals.output_text));

		if (ImGui::Button("Run String"))
		{
			int return_from_func = hooks.run_string(globals.output_text);
			std::cout << "[scrapware] return_from_func: " << return_from_func << "\n";
		}

		ImGui::End();

	}

	if (globals.show_fps)
	{

		ImGuiIO io = ImGui::GetIO();
		float window_frames = io.Framerate;

		std::string window_fps = std::to_string(window_frames);

		ImGui::SetNextWindowSize(ImVec2(200, 20));

		ImGui::Begin("performance profiler", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | (globals.menu_open ? ImGuiWindowFlags_None : ImGuiWindowFlags_NoMove));

		ImGui::Text("fps: %s", window_fps.c_str());

		ImGui::End();

	}

	ImGui::Render();

	globals.pContext->OMSetRenderTargets(1, &globals.mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}