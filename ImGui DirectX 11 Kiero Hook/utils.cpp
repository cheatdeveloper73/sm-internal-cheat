#include "utils.h"
#include "globals.h"

CUtils utils;

void CUtils::unloadcheat()
{
	kiero::shutdown();
	FreeLibraryAndExitThread(globals.cheat_module, 1);
	return;
}

void CUtils::refresh_lua_scripts()
{

	globals.scripts.clear(); // clear every script

	std::string script_folder = "C:\\scrapware\\lua\\";

	int cur_id = -1;

	for (auto& entry : std::filesystem::directory_iterator(script_folder))
	{

		if (entry.path().extension() == ".lua" || entry.path().extension() == ".luac") // filters out everything that's not a lua file
		{

			std::filesystem::path file_path = entry.path();
			std::string file_name = file_path.filename().string();
			std::string file_path_string = file_path.string();
			cur_id += 1;

			custom_script script = custom_script{file_name, file_path_string, cur_id};

			globals.scripts.emplace_back(script);

			std::cout << "[scrapware] Added script #" << cur_id << " with name " << script.name << "\n";

		}

	}

}