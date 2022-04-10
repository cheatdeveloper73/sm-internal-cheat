#pragma once
#include <cstdint>

class lua_State;

namespace SM
{
	// TODO: Document vtable stuffs
	class LuaVM
	{
	public:
		lua_State* luaState;
	private:
		char char8;
		__declspec(align(8)) uint64_t qword10;
		uint64_t qword18;
		BYTE gap20[40];
		char char48;
		__declspec(align(8)) uint64_t qword50;
		uint64_t qword58;
		uint64_t qword60;
		uint64_t qword68;
		uint64_t qword70;
		uint64_t qword78;
		uint32_t dword80;
		uint32_t dword84;
		uint64_t qword88;
		uint64_t qword90;
		uint64_t qword98;
		uint64_t qwordA0;
		uint64_t qwordA8;
		uint32_t dwordB0;
		BYTE gapB4[60];
		uint64_t qwordF0;
		BYTE gapF8[56];
		uint64_t qword130;
		BYTE gap138[56];
		uint64_t qword170;
		uint64_t dword178;
		uint64_t qword180;
		uint64_t qword188;
		uint64_t qword190;
		uint64_t qword198;
		uint64_t qword1A0;
		uint64_t qword1A8;
		uint64_t qword1B0;
		uint64_t qword1B8;
		uint64_t qword1C0;
		uint64_t qword1C8;
		uint64_t qword1D0;
		uint64_t qword1D8;
		char char1E0;
		BYTE gap1E1[63];
		char char220;
		BYTE gap221[63];
		uint64_t qword260;
		uint64_t qword268;
		uint64_t qword270;
		uint64_t qword278;
		uint64_t qword280;
	};

	static_assert(sizeof(LuaVM) == 0x288, "LuaVM wrong size");
}
