#include "includes.h"
#include "gui.h"
#include "globals.h"
#include "utils.h"
#include "hooks.h"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;

void InitImGui()
{

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	io.IniFilename = nullptr;
	io.LogFilename = nullptr;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, globals.pContext);
	std::cout << "[scrapware] ImGui Initialized\n";

}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{

	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&globals.pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &globals.mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	gui.render();

	return oPresent(pSwapChain, SyncInterval, Flags);

}

void SetupFolders()
{

	CreateDirectoryA("C:\\scrapware\\", NULL);
	CreateDirectoryA("C:\\scrapware\\lua\\", NULL);

	HANDLE hFile = CreateFileA(
		"C:\\scrapware\\lua\\runme.lua",     // Filename
		GENERIC_WRITE,          // Desired access
		FILE_SHARE_READ,        // Share mode
		NULL,                   // Security attributes
		CREATE_NEW,             // Creates a new file, only if it doesn't already exist
		FILE_ATTRIBUTE_NORMAL,  // Flags and attributes
		NULL);

	std::string strText = "sm.gui.chatMessage(\"Welcome to scrapware!\")"; // For C use LPSTR (char*) or LPWSTR (wchar_t*)
	DWORD bytesWritten;
	WriteFile(
		hFile,            // Handle to the file
		strText.c_str(),  // Buffer to write
		strText.size(),   // Buffer size
		&bytesWritten,    // Bytes written
		nullptr);

	std::cout << "[scrapware] Setup directories\n";

}

DWORD WINAPI MainThread(LPVOID lpReserved)
{

	std::cout << "[scrapware] Hooking D3D11\n";

	if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
	{
		kiero::bind(8, (void**)&oPresent, hkPresent);
		std::cout << "[scrapware] Setup D3D11 Hook\n";
	}

	SetupFolders();
	utils.refresh_lua_scripts();

	std::cout << "[scrapware] Initializing steam api\n";

	SteamAPI_Init();
	globals.player_name = SteamFriends()->GetPersonaName();

	std::cout << "[scrapware] Initialized steam api\n";

	std::cout << "[scrapware] Hello " << globals.player_name << "\n";

	std::cout << "[scrapware] Finished Setup\n";

	return TRUE;

}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:

		freopen("CONOUT$", "w", stdout);
		SetConsoleTitleA("scrapware - owns you and all");
		printf("SEXXXXX");
		std::cout << "[scrapware] Entered startup routine\n";
		DisableThreadLibraryCalls(hMod);
		globals.cheat_module = hMod;
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		std::cout << "[scrapware] Finished startup routine\n";
		break;

	}
	return TRUE;
}