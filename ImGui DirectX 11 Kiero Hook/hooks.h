#include "includes.h"

class CHooks
{
public:

	//bool setup_functions = false; // (TODO: IMPLEMENT)
	//std::vector<lua_State*> forked_states{MAX_LUA_STATES}; // vector of states for our custom scripts
	//_lua_error fork_current_state(int state_id); // forks the state so we don't corrupt anything
	_lua_error run_file(const char* file_path, int state_id); // allows us to run the file at the specified filepath
	//_lua_error run_string(const char* string, int state_id); // runs a string containing lua code
	//_lua_error setup_functions(); // sets up our custom functions for drawing primitives (TODO: IMPLEMENT)

};

extern CHooks hooks;