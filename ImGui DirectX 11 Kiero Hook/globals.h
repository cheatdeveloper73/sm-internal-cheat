#include "includes.h"

struct custom_script
{
	std::string name;
	std::string path;
	int id;
	bool is_running;
	bool in_running_list;

	bool operator==(const custom_script& a) const
	{
		return (this->path == a.path);
	}

};

class CGlobals
{
public:

	HMODULE cheat_module;
	HANDLE main_thread = nullptr;
	HANDLE uninject_thread = nullptr;
	ID3D11DeviceContext* pContext = NULL;
	ID3D11RenderTargetView* mainRenderTargetView;
	ImFont* otherfont;

	bool menu_open = false;
	bool show_watermark = true;
	bool need_to_unload = false;

	char output_text[255] = "";
	const char* items[5] = {"Default", "Style 1", "Style 2", "Style 3", "Style 4"};

	std::vector<custom_script> scripts;
	std::vector<custom_script> running_scripts;
	
	std::string player_name;

	int current_script_index;
	int current_tab;
	int current_style;

};

extern CGlobals globals;