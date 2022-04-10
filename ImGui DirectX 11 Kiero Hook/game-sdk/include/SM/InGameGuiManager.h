#pragma once
#include <cstdint>

namespace SM
{
	class ChatGui;
	
#pragma pack( push, 4 )
	// TODO: Document vtable stuffs
	class InGameGuiManager
	{
		uint32_t dword8;
		uint32_t dwordC;
		uint64_t qword10;
		uint64_t qword18;
		uint64_t qword20;
		uint64_t qword28;
		uint64_t qword30;
		uint64_t qword38;
		uint64_t qword40;
		uint64_t qword48;
	public:
		ChatGui* m_chatGui;
	private:
		uint64_t qword58;
		uint64_t qword60;
		uint64_t qword68;
		uint64_t qword70;
		uint64_t qword78;
		uint64_t qword80;
		uint64_t qword88;
		uint64_t qword90;
		uint64_t qword98;
		uint64_t qwordA0;
		uint64_t qwordA8;
		uint64_t qwordB0;
		uint64_t qwordB8;
		uint64_t qwordC0;
		uint64_t qwordC8;
		uint64_t qwordD0;
		uint64_t qwordD8;
		uint64_t qwordE0;
		uint64_t qwordE8;
		uint64_t qwordF0;
		uint64_t qwordF8;
		uint64_t qword100;
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
		uint64_t qword178;
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
		uint32_t dword1E0;
	
	private:
		virtual void func0();
	public:
		// Retrieves g_contraptionInGameGuiManagerInterface
		static InGameGuiManager* getInstancePtr()
		{
			return *reinterpret_cast<InGameGuiManager**>(uintptr_t(GetModuleHandle(NULL)) + 0xE57E88);
		}
	};
#pragma pack( pop )

	static_assert(sizeof(InGameGuiManager) == 0x1E4, "InGameGuiManager wrong size");
}

