#pragma once
#include <cstdint>

namespace SM
{
	class GameInstance;
	
	// TODO: Document vtable stuffs
	class PlayState
	{
		uint64_t m_bListenServer;
		BYTE byte10;
		uint64_t qword18;
		BYTE byte20;
		float dword24;
		float dword28;
		float dword2C;
		float dword30;
		float dword34;
		float dword38;
		float dword3C;
		uint64_t qword40;
		uint32_t dword48;
		uint32_t dword4C;
		BYTE byte50;
		BYTE byte51;
		BYTE byte52;
		BYTE byte53;
		BYTE byte54;
		BYTE byte55;
		BYTE byte56;
		BYTE byte57;
		uint32_t dword58;
		uint64_t qword60;
		uint64_t qword68;
		uint64_t m_pNetworkClient;
		uint64_t qword78;
		uint64_t qword80;
	public:
		GameInstance *m_gameInstance;
	private:
		uint64_t qword90;
		uint64_t qword98;
		uint64_t qwordA0;
		uint64_t qwordA8;
		uint32_t m_connectionTimeoutIndex;
		uint64_t qwordB8;
		uint64_t qwordC0;
		BYTE byteC8;
		uint32_t dwordCC;
	private:
		virtual void func0();
	};

	static_assert(sizeof(PlayState) == 0xD0, "PlayState wrong size");
}
