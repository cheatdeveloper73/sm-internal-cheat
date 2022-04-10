#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include <iostream>
#include <string>
#include <intrin.h>
#include <vector>
#include <filesystem>
#include <thread>
#include <fstream> 

#include "game-sdk/include/sdk.hpp"

#define MAX_LUA_STATES 30

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

struct _lua_error
{
	std::string error;
	int actual_code;
};