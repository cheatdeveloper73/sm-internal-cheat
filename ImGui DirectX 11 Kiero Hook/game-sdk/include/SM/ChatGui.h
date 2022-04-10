#pragma once
#include <cstdint>

namespace MyGUI
{
	class EditBox;
	class UString;
}

namespace SM
{
	// TODO: Document vtable stuffs
	// Inherits from GuiBase
	class ChatGui
	{
	public:
		uint64_t m_widgetPanelEmpty;
	private:
		uint64_t qword10;
	public:
		uint64_t m_widgetInputBackground;
		uint64_t m_widgetBackground;
		MyGUI::EditBox* m_widgetMessage;
		MyGUI::EditBox* m_widgetReceivedMessages;
		std::string m_name;
	private:

		bool byte58;
		uint32_t dword5C;
		bool byte60;
	public:
		float m_alphaInputBackground;
	private:
		float dword68;
		float dword6C;
		float dword70;
		float dword74;
		uint32_t dword78;
		unsigned char gap7C[68];
		uint32_t dwordC0;
		uint64_t qwordC8;
		uint64_t qwordD0;
		uint64_t qwordD8;
	private:
		unsigned char gap6dfC[8];
	};
	//constexpr auto x = sizeof(ChatGui);
	//static_assert(sizeof(ChatGui) == 0xE0, "ChatGui wrong size");
}

