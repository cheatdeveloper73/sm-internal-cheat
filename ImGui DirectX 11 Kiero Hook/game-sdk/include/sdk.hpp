#pragma once

// Disable warnings for steam_api
#pragma warning(disable:4996)

#define LUA_BUILD_AS_DLL
#include "Lua/lua.hpp"
#include "Steam/steam_api.h"
#include "MyGUI/MyGUI.h"
#include "SM/SM.h"

#pragma comment(lib, "lua51.lib")
#pragma comment(lib, "MyGUIEngine.lib")
#pragma comment(lib, "steam_api64.lib")