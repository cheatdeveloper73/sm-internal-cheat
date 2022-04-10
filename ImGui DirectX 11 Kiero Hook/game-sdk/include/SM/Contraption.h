#pragma once
#include <cstdint>

namespace SM
{
	class PlayState;
	
  	// TODO: Document vtable stuffs
	class Contraption
	{
		uint64_t qword8;
		uint64_t qword10;
		uint64_t qword18;
		uint64_t qword20;
		uint64_t qword28;
		uint64_t qword30;
		uint64_t qword38;
		uint64_t qword40;
		uint64_t qword48;
		uint64_t qword50;
		uint64_t qword58;
		uint64_t qword60;
		uint32_t dword68;
		uint32_t dword6C;
		uint32_t dword70;
		uint32_t dword74;
		BYTE gap78[16];
		BYTE byte88;
		BYTE gap89[15];
		uint64_t qword98;
		uint64_t qwordA0;
		BYTE gapA8[248];
		uint64_t m_PlayStateManager;
		uint64_t qword1A8;
		uint64_t qword1B0;
		BYTE byte1B8;
		uint32_t dword1BC;
	public:
		PlayState *m_PlayState;
	private:
		uint64_t qword1C8;
		uint64_t qword1D0;
		uint64_t qword1D8;
		uint64_t qword1E0;
		uint64_t qword1E8;
		uint64_t qword1F0;
		uint64_t qword1F8;
		uint64_t qword200;
		uint64_t qword208;
		uint64_t qword210;
		uint64_t qword218;
		uint64_t qword220;
		uint64_t qword228;
		uint64_t qword230;
		uint64_t qword238;
		uint64_t qword240;
		uint64_t qword248;
		uint64_t qword250;
		uint64_t qword258;
		uint64_t qword260;
		uint64_t qword268;
		uint64_t qword270;
		uint64_t qword278;
		uint64_t qword280;
		BYTE gap288[8];
		uint32_t dword290;
		uint32_t dword294;
		uint32_t dword298;
		uint32_t dword29C;
		uint32_t dword2A0;
		uint32_t dword2A4;
		uint32_t dword2A8;
		BYTE gap2AC[8];
		uint32_t dword2B4;
		uint64_t qword2B8;
		uint64_t qword2C0;
		uint64_t qword2C8;
		uint64_t qword2D0;
		uint64_t m_Window;
		WORD word2E0;
		uint64_t qword2E8;
		BYTE byte2F0;
		uint32_t dword2F4;
		uint64_t qword2F8;
		BYTE byte300;
		uint32_t dword304;
	private:
		virtual void func0();

	public:
		// Retrieves g_contraption
		static Contraption* getInstancePtr()
		{
			return *reinterpret_cast<Contraption**>(uintptr_t(GetModuleHandle(NULL)) + 0xE57DA0);
		}
	};

	static_assert(sizeof(Contraption) == 0x308, "Contraption wrong size");
}
