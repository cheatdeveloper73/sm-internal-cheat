#include "gui.h"
#include "utils.h"
#include "globals.h"
#include "hooks.h"

CGui gui;

namespace ImGui
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<custom_script>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).name.c_str();
		return true;
	};

	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

	bool ListBox(const char* label, int* currIndex, std::vector<custom_script>& values)
	{
		if (values.empty()) { return false; }
		return ListBox(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

	static void HelpMarker(const char* desc)
	{
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(desc);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	} // https://flyover.github.io/imgui-js/imgui/imgui_demo.cpp

}

void CGui::render()
{

	if (GetAsyncKeyState(VK_INSERT) & 1)
		globals.menu_open = !globals.menu_open;

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (globals.menu_open)
	{

		ImGui::SetNextWindowSize(ImVec2(490, 250));

		ImGui::Begin("scrapware", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

		ImGui::Text("scrapware | "); ImGui::SameLine(); ImGui::Checkbox("fps counter", &globals.show_fps); ImGui::SameLine();
		if (ImGui::Button("get new lua state"))
		{
			hooks.need_new_state = true;
		}
		ImGui::SameLine(); ImGui::HelpMarker("creates a new lua state, click this anytime you go into a new game");
		// kind of a mess, it's like a titlebar with all the useful crap in it

		ImGui::Separator();

		ImGui::Spacing();

		ImGui::InputTextWithHint("##runstring", "lua string", globals.output_text, sizeof(globals.output_text));
		if (ImGui::Button("run string"))
		{
			int return_from_func = hooks.run_string(globals.output_text);
			std::cout << "[scrapware] return_from_func: " << return_from_func << "\n";
		}

		ImGui::Separator();

		ImGui::ListBox("scripts", &globals.current_script_index, globals.scripts);

		if (ImGui::Button("refresh scripts"))
			utils.refresh_lua_scripts();

		ImGui::SameLine();

		if (ImGui::Button("execute selected"))
		{

			hooks.run_file(globals.scripts.at(globals.current_script_index).path.c_str());

			std::cout << "[scrapware] Executing script " << globals.scripts.at(globals.current_script_index).name << " at " << globals.scripts.at(globals.current_script_index).path << " with id " << globals.scripts.at(globals.current_script_index).id << "\n";

		}

		ImGui::End();

	}

	if (globals.show_fps)
	{

		ImGuiIO io = ImGui::GetIO();
		float window_frames = io.Framerate;

		std::string window_fps = std::to_string(window_frames);

		ImGui::SetNextWindowSize(ImVec2(200, 20));
		ImGui::SetNextWindowPos(ImVec2(5, 5));

		ImGui::Begin("performance profiler", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | (globals.menu_open ? ImGuiWindowFlags_None : ImGuiWindowFlags_NoMove));

		ImGui::Text("fps: %s", window_fps.c_str());

		ImGui::End();

	}

	ImGui::Render();

	globals.pContext->OMSetRenderTargets(1, &globals.mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}