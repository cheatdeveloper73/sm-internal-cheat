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

void tab(std::string name, int tab_value)
{
	ImGui::SameLine();
	if (ImGui::Button(name.c_str()))
		globals.current_tab = tab_value;
} // shitty little wrapper function for tabs lmao

void CGui::watermark()
{

	ImGuiIO io = ImGui::GetIO();
	int window_frames = static_cast<int>(std::floor(io.Framerate));

	std::string window_fps = std::to_string(window_frames);

	char* out = new char[40];
	sprintf(out, "scrapware | fps: %s | %s", window_fps.c_str(), globals.player_name.c_str());

	ImGui::SetNextWindowSize(ImVec2(ImGui::CalcTextSize(out).x + 15, 20));
	ImGui::SetNextWindowPos(ImVec2(5, 5));

	ImGui::Begin("scrapware watermark", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

	ImGui::Text(out);

	ImGui::End();

	delete[] out;

}

static constexpr auto frequency = 1 / 0.45f;

float clip(float n, float lower, float upper)
{
	n = (n > lower) * n + !(n > lower) * lower;
	return (n < upper) * n + !(n < upper) * upper;
}

void CGui::handle()
{

	if (GetAsyncKeyState(VK_INSERT) & 1)
		globals.menu_open = !globals.menu_open;

}

void CGui::render()
{

	switch (globals.current_style)
	{
	case 0:
		ImGui::StyleColorsDark();
		break;
	case 1:
		ImGui::StyleColorsClassic();
		break;
	case 2:
		ImGui::StyleColorsLight();
		break;
	case 3:
		ImGui::garbagestyle();
		break;
	case 4: 
		ImGui::anotherbadstyle();
		break;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (globals.show_watermark)
		this->watermark();

	this->handle();

	if (globals.menu_open)
	{

		ImGui::SetNextWindowSize(ImVec2(490, 350));

		ImGui::Begin("scrapware", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);

		ImGui::Text("scrapware | ");

		tab("aimbot", 0);
		tab("esp", 1);
		tab("misc", 2);
		tab("lua", 3);
		tab("network", 4);

		ImGui::Spacing();

		switch (globals.current_tab)
		{
		case 0:
		{

			ImGui::BeginChild("##aimbot", ImVec2(490 - 15, 300), true, ImGuiWindowFlags_NoScrollbar);

			ImGui::Text("aimbot stuff goes here");

			ImGui::EndChild();

			break;

		}

		case 1:
		{
			ImGui::BeginChild("##esp", ImVec2(490 - 15, 300), true, ImGuiWindowFlags_NoScrollbar);

			ImGui::Text("esp stuff goes here");

			ImGui::EndChild();

			break;
		}

		case 2:
		{
			ImGui::BeginChild("##misc", ImVec2(490 - 15, 300), true, ImGuiWindowFlags_NoScrollbar);

			ImGui::Checkbox("show watermark", &globals.show_watermark);
			if (ImGui::Button("unload cheat"))
				globals.need_to_unload = true;

			ImGui::Combo("menu style", &globals.current_style, globals.items, IM_ARRAYSIZE(globals.items));

			ImGui::EndChild();

			break;
		}

		case 3:
		{

			ImGui::BeginChild("##lua", ImVec2(490 - 15, 300), true, ImGuiWindowFlags_NoScrollbar);

			std::string running_string = std::to_string(globals.running_scripts.size());
			std::string total_string = std::to_string(globals.scripts.size());
			std::string state_string = std::to_string(globals.scripts.at(globals.current_script_index).is_running);

			ImGui::Text("%s/%s scripts are running | current script state: %s", running_string.c_str(), total_string.c_str(), state_string.c_str());

			ImGui::ListBox("##scripts", &globals.current_script_index, globals.scripts);

			if (ImGui::Button("refresh scripts"))
				utils.refresh_lua_scripts();

			ImGui::SameLine();

			if (ImGui::Button("run selected"))
			{

				if (globals.scripts.at(globals.current_script_index).id > MAX_LUA_STATES)
					std::cout << "[scrapware] Cannot run script because it's id is higher than the max allowed lua states!\n";

				else
				{

					_lua_error result = hooks.run_file(globals.scripts.at(globals.current_script_index).path.c_str(), globals.scripts.at(globals.current_script_index).id);
					std::cout << "[scrapware] Result from execution: " << result.error << " : Code: " << result.actual_code << "\n";

				}

			}

			ImGui::SameLine();

			if (ImGui::Button("open lua folder"))
				ShellExecute(NULL, "open", "C:\\scrapware\\lua\\", NULL, NULL, SW_SHOWNORMAL);

			ImGui::EndChild();

			break;

		}

		case 4:

			ImGui::BeginChild("##network", ImVec2(490 - 15, 300), true, ImGuiWindowFlags_NoScrollbar);

			ImGui::Text("network stuff goes here");

			ImGui::EndChild();

			break;

		}

		ImGui::End();

	}

	ImGui::Render();

	globals.pContext->OMSetRenderTargets(1, &globals.mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}