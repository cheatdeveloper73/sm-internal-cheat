#include "hooks.h"
#include "kiero/minhook/include/MinHook.h"
#include "globals.h"

CHooks hooks;
_lua_offsets lua_offsets;

uintptr_t lua_baseaddr = (uintptr_t)GetModuleHandleA("lua51.dll");

typedef unsigned __int64 _QWORD;

__int64 __fastcall hkGetOp(__int64 state)
{

	if (hooks.need_new_state)
	{

		hooks.this_state = (lua_state*)state;
		hooks.this_state = hooks.create_new_state();

		hooks.need_new_state = false;


	} // we need to get a new lua state, either because we don't have one currently or the user decided we needed a new one


	return (__int64)(*(_QWORD*)(state + 40) - *(_QWORD*)(state + 32)) >> 3;

}

bool CHooks::setup_hooks()
{

	if (MH_CreateHook((LPVOID)(lua_baseaddr + lua_offsets.gettop), &hkGetOp, NULL) != MH_OK || MH_EnableHook((LPVOID)(lua_baseaddr + lua_offsets.gettop)) != MH_OK)
		return false;

	std::cout << "[scrapware] Hooked lua_gettop\n";

	return true;

}

lua_state* CHooks::create_new_state()
{

	std::cout << "[scrapware] Calling create_new_state\n";

	if (!this->this_state)
	{
		std::cout << "[scrapware] this->this_state was null\n";
		return nullptr;
	}

	lua_state* state = ((lua_newthread)(lua_baseaddr + lua_offsets.newthread))(this->this_state);
	std::cout << "[scrapware] New lua_state: " << state << std::endl;

	return state;

}

bool CHooks::verify_lua_state(lua_state* state)
{

	if (!state)
		return false;

	int ret = ((_luaStatus)(lua_baseaddr + lua_offsets.status))(state);

	std::cout << "[scrapware] ret: " << ret << "\n";

	if (ret != 0)
		return false;

	return true;

}

int CHooks::run_string(const char* string)
{

	if (!this->this_state || !this->verify_lua_state(this->this_state))
		return -1;

	int load_string_ret = ((_luaL_loadstring)(lua_baseaddr + lua_offsets.loadstring))(this->this_state, string);
	int pcall_ret = ((_lua_pcall)(lua_baseaddr + lua_offsets.pcall))(this->this_state, 0, -1, 0);

	return load_string_ret;

}

int CHooks::run_file(const char* filepath)
{

	if (!this->this_state || !this->verify_lua_state(this->this_state))
		return -1;

	int load_file_ret = ((_luaL_loadfilex)(lua_baseaddr + lua_offsets.loadfilex))(this->this_state, filepath, NULL);
	int pcall_ret = ((_lua_pcall)(lua_baseaddr + lua_offsets.pcall))(this->this_state, 0, -1, 0);

	return load_file_ret;

}