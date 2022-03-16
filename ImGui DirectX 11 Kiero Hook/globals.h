#include "includes.h"

class CGlobals
{
public:

	HMODULE cheat_module;
	ID3D11DeviceContext* pContext = NULL;
	ID3D11RenderTargetView* mainRenderTargetView;

	bool menu_open = false;
	bool show_fps = false;

	char output_text[255] = "";

};

extern CGlobals globals;