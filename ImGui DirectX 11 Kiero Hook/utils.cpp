#include "utils.h"
#include "globals.h"
#include "hooks.h"

CUtils utils;

void CUtils::unloadcheat()
{
	kiero::shutdown();
	Sleep(100);
	FreeLibrary(globals.cheat_module);
	return;
}

void CUtils::refresh_lua_scripts()
{

	std::cout << "[scrapware] Refreshing lua scripts\n";

	globals.scripts.clear(); // clear every script
	globals.running_scripts.clear(); // set this to 0, since no scripts can be running at this point

	auto loop_files = []()
	{

		int cur_id = -1;
		std::string script_folder = "C:\\scrapware\\lua\\";

		for (auto& entry : std::filesystem::directory_iterator(script_folder))
		{

			if (!entry.exists())
			{
				globals.scripts.emplace_back(custom_script{ "NO SCRIPTS", "NO SCRIPTS", cur_id, false });
				std::cout << "[scrapware] Error getting lua files, 0 files possibly exist in the folder\n";
				break;
			}

			if (entry.path().extension() == ".lua" || entry.path().extension() == ".luac") // filters out everything that's not a lua file
			{

				std::filesystem::path file_path = entry.path();
				std::string file_name = file_path.filename().string();
				std::string file_path_string = file_path.string();
				cur_id += 1;

				custom_script script = { file_name, file_path_string, cur_id, false };

				globals.scripts.emplace_back(script);

				std::cout << "[scrapware] Added script #" << cur_id << " with name " << script.name << "\n";

			}

		}

	};
	
	std::thread dir_looper(loop_files);

	std::cout << "[scrapware] Created thread dir_looper\n";

	dir_looper.join();

	std::cout << "[scrapware] Threaad dir_looper finished\n";

}