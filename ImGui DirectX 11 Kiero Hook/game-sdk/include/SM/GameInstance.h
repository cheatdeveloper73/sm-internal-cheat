#pragma once
#include <cstdint>

namespace SM
{
	class InGameGuiManager;
	class LuaManager;

	// TODO: Document vtable stuffs
#pragma pack( push, 4 )
	class GameInstance
	{
	public:
		bool m_bIsServer;
	private:
		BYTE gap9[7];
		uint32_t dword10;
		BYTE gap14[244];
		uint64_t qword108;
		uint64_t qword110;
		uint64_t qword118;
		uint64_t qword120;
		uint64_t qword128;
		uint64_t qword130;
		uint64_t qword138;
		uint64_t qword140;
		uint64_t qword148;
		uint64_t qword150;
		uint64_t qword158;
		uint64_t qword160;
		uint64_t qword168;
		uint64_t qword170;
		uint64_t HarvestableManager;
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
		uint64_t qword1E0;
		uint64_t qword1E8;
		uint64_t qword1F0;
		uint64_t qword1F8;
		uint64_t qword200;
		uint64_t qword208;
	public:
		InGameGuiManager *m_InGameGuiManager;
	private:
		uint64_t qword218;
		uint64_t qword220;
		uint64_t qword228;
		uint64_t qword230;
		uint64_t qword238;
	public:
		LuaManager *m_LuaManager;
	private:
		uint64_t m_LuaManagerRefCount;
		uint64_t qword250;
		uint64_t qword258;
		uint64_t qword260;
		uint64_t qword268;
		uint64_t qword270;
		uint64_t qword278;
		uint64_t qword280;
		uint64_t qword288;
		uint64_t qword290;
		uint64_t qword298;
		uint64_t qword2A0;
		uint64_t qword2A8;
		uint64_t qword2B0;
		uint64_t qword2B8;
		uint64_t qword2C0;
		uint64_t qword2C8;
		uint64_t qword2D0;
		uint64_t qword2D8;
		uint64_t qword2E0;
		uint64_t qword2E8;
		uint64_t qword2F0;
		uint64_t qword2F8;
		uint64_t qword300;
		uint64_t qword308;
		uint64_t qword310;
		uint64_t qword318;
		uint64_t qword320;
		uint64_t qword328;
		uint64_t qword330;
		uint64_t qword338;
		uint64_t qword340;
		uint64_t qword348;
		uint64_t qword350;
		uint64_t qword358;
		uint32_t dword360;
	private:
		BYTE gap69420[8];
	};
#pragma pack( pop )

	static_assert(sizeof(GameInstance) == 0x364, "GameInstance wrong size");

}