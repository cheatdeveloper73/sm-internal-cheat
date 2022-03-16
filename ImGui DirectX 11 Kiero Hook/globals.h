#include "includes.h"

struct custom_script
{
	std::string name;
	std::string path;
	int id;
};

class CGlobals
{
public:

	HMODULE cheat_module;
	ID3D11DeviceContext* pContext = NULL;
	ID3D11RenderTargetView* mainRenderTargetView;

	bool menu_open = false;
	bool show_fps = false;

	char output_text[255] = "";

	std::vector<custom_script> scripts;

	int current_script_index;

};

extern CGlobals globals;