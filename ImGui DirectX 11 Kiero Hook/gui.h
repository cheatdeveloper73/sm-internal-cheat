#include "includes.h"

class CGui
{
public:

	bool menu_open;
	float menu_alpha;

	void render();
	void watermark();
	void handle();

};

extern CGui gui;