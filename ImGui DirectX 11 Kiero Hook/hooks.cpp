#include "hooks.h"
#include "kiero/minhook/include/MinHook.h"
#include "globals.h"

CHooks hooks;
_lua_offsets lua_offsets;

uintptr_t lua_baseaddr = (uintptr_t)GetModuleHandleA("lua51.dll");

typedef unsigned __int64 _QWORD;

__int64 __fastcall hkGetOp(__int64 state)
{

	if (!hooks.this_state)
		hooks.this_state = (lua_state*)state;
	
	std::cout << "[scrapware] Lua State Obtained: " << std::hex << state << "\n";

	if (hooks.this_state)
	{

		MH_DisableHook((LPVOID)(lua_baseaddr + lua_offsets.gettop));
		hooks.this_state = hooks.create_new_state(); // makes our own state to do stuff with

	}

	return (__int64)(*(_QWORD*)(state + 40) - *(_QWORD*)(state + 32)) >> 3;

}

bool CHooks::setup_hooks()
{

	if (MH_CreateHook((LPVOID)(lua_baseaddr + lua_offsets.gettop), &hkGetOp, NULL) != MH_OK)
		return false;

	if (MH_EnableHook((LPVOID)(lua_baseaddr + lua_offsets.gettop)) != MH_OK)
		return false;

	std::cout << "[scrapware] Hooked lua_gettop\n";

	return true;

}

lua_state* CHooks::create_new_state()
{

	std::cout << "[scrapware] Calling create_new_state\n";

	if (!this->this_state)
	{
		std::cout << "[scrapware] lua_state_ptr was null\n";
		return nullptr;
	}

	lua_state* state = ((lua_newthread)(lua_baseaddr + lua_offsets.newthread))(this->this_state);
	std::cout << "[scrapware] New lua_state: " << state << std::endl;

	return state;

}

int CHooks::run_string(const char* string)
{

	if (!this->this_state)
		return -1;

	int load_string_ret = ((_luaL_loadstring)(lua_baseaddr + lua_offsets.loadstring))(this->this_state, string);
	int pcall_ret = ((_lua_pcall)(lua_baseaddr + lua_offsets.pcall))(this->this_state, 0, -1, 0);

	return load_string_ret;

}