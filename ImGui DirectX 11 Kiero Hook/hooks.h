#include "includes.h"

typedef void* lua_state; // defining it as void* to prevent me from having to get lua.hpp

typedef int(__fastcall* gettop)(lua_state);

typedef int(*_luaL_loadfilex)(lua_state* L, const char* filename, const char* mode);
typedef int(*_lua_pcall)(lua_state* L, int nargs, int nresults, int errfunc);

typedef lua_state* (__fastcall* lua_newthread)(lua_state*);
typedef void(__cdecl* lua_pushinteger)(lua_state*, int);
typedef int(__cdecl* lua_tointeger)(lua_state*, int);
typedef int(__cdecl* _luaStatus)(lua_state*);
typedef int(__cdecl* _luaL_loadstring)(lua_state*, const char*);

struct _lua_offsets
{

	uintptr_t gettop = 0x8640;
	uintptr_t loadfilex = 0x39460;
	uintptr_t pcall = 0x8B40;
	uintptr_t newthread = 0x88F0;
	uintptr_t pushinteger = 0x8D70;
	uintptr_t tointeger = 0x98B0;
	uintptr_t status = 0x9830;
	uintptr_t loadstring = 0x39650;

};

class CHooks
{
public:

	lua_state* this_state = nullptr;
	bool need_new_state = true;

	bool setup_hooks();
	lua_state* create_new_state();
	int run_string(const char* string);
	int run_file(const char* filepath);
	bool verify_lua_state(lua_state* state);

};

extern CHooks hooks;