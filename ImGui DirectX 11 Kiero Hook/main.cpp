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
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
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

DWORD WINAPI MainThread(LPVOID lpReserved)
{

	std::cout << "[scrapware] Hooking D3D11\n";

	if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
	{
		kiero::bind(8, (void**)&oPresent, hkPresent);
		std::cout << "[scrapware] Setup D3D11 Hook\n";
	}

	std::cout << "[scrapware] Hooking lua functions\n";

	if (!hooks.setup_hooks())
		std::cout << "[scrapware] Failed to hook lua functions\n";

	else
		std::cout << "[scrapware] Setup lua hooks\n";

	std::cout << "[scrapware] Finished Setup\n";

	return TRUE;

}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		std::cout << "[scrapware] Entered startup routine\n";
		DisableThreadLibraryCalls(hMod);
		globals.cheat_module = hMod;
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		std::cout << "[scrapware] Finished startup routine\n";
		break;
	}
	return TRUE;
}