#include "hooks.h"
#include "kiero/minhook/include/MinHook.h"
#include "globals.h"

CHooks hooks;

/*_lua_error CHooks::fork_current_state(int state_id)
{

	if (this->forked_states.size() > MAX_LUA_STATES || !SM::LuaManager::getInstancePtr() || !SM::LuaManager::getInstancePtr()->m_pLuaVM || this->forked_states.at(state_id))
		return { "sanity check failed", -1 }; // sanity checks, clear forked states if this one is invalid

	lua_State* state = SM::LuaManager::getInstancePtr()->m_pLuaVM->luaState;

	this->forked_states.at(state_id) = lua_newthread(state); // fork the state using newthread
		
	return { "no error", -2 };

}*/

_lua_error CHooks::run_file(const char* file_path, int state_id)
{

	if (!SM::LuaManager::getInstancePtr() || !SM::LuaManager::getInstancePtr()->m_pLuaVM || !SM::LuaManager::getInstancePtr()->m_pLuaVM->luaState)
		return { "sanity check failed", -1 }; // sanity checks

	int loadfile = luaL_loadfile(SM::LuaManager::getInstancePtr()->m_pLuaVM->luaState, file_path); // actually run the file
	int pcall = lua_pcall(SM::LuaManager::getInstancePtr()->m_pLuaVM->luaState, NULL, NULL, NULL); // pcall to do something (still no clue what it does other than make it actually work)

	if (loadfile != 1)
		return { "loadfile error", loadfile }; // loadfile returned an error

	if (pcall != 1)
		return { "pcall error", pcall }; // pcall returned an error

	return { "no error", -2 };

}

/*_lua_error CHooks::run_string(const char* string, int state_id)
{

	if (this->forked_states.size() > MAX_LUA_STATES || !SM::LuaManager::getInstancePtr() || !SM::LuaManager::getInstancePtr()->m_pLuaVM)
		return { "sanity check failed", -1 }; this->forked_states.clear(); // sanity checks

	if (!this->forked_states.at(state_id))
		this->fork_current_state(state_id); // if we haven't made a state for this id make it

	lua_State* execute_state = this->forked_states.at(state_id);

	int loadfile = luaL_loadstring(execute_state, string); // actually run the file
	int pcall = lua_pcall(execute_state, NULL, NULL, NULL); // pcall to do something (still no clue what it does other than make it actually work)

	if (loadfile != 1)
		return { "loadstring error", loadfile }; // loadfile return an error

	if (pcall != 1)
		return { "pcall error", pcall }; // loadfile return an error

	return { "no error", -2 };

}*/