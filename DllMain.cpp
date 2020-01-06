#include <windows.h>
#include <iostream>
#include "Navigation.h"
#include "Offsets.h"
#include "LuaFunctions.h"
#include "kiero.h"
#include "dxgi.h"
#include "Drawings.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

/*
extern "C"
{
	__declspec(dllexport) XYZ* CalculatePath(unsigned int mapId, XYZ start, XYZ end, bool smoothPath, int* length, bool allowSwimming)
	{
        //printf("mapId %d \r\n", mapId);
        //printf("allowSwimming %d \r\n", allowSwimming);

		return Navigation::GetInstance()->CalculatePath(mapId, start, end, smoothPath, length, allowSwimming);
	}

	__declspec(dllexport) void FreePathArr(XYZ* pathArr)
	{
		return Navigation::GetInstance()->FreePathArr(pathArr);
	}
};*/

typedef HRESULT(__fastcall* D3D11Present) (IDXGISwapChain* pSwapChain, UINT syncInterval, UINT flags);
typedef HRESULT(__stdcall* D3D11ResizeBuffers) (IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

HWND MainWindowHandle = 0;
D3D11Present Od11Present = nullptr;
D3D11ResizeBuffers Od11ResizeBuffers = nullptr;
int16_t last_state = 0;
bool initialised = false;

void GameLoop()
{
	//check if in game if not set we need to re register,
	//if we are in game and need to re regiser, then reregister, ez pz :P
	const auto currentState = *reinterpret_cast<int16_t*>(Offsets::Base + Offsets::InGame);
	if (last_state != currentState)
	{
		last_state = currentState;
		if ((currentState >> 4) & 1) //its not 4 in retail will have to print it once
		{
			for (const auto function : FunctionsMap)
			{
				if (FramescriptRegister(function.first, function.second))
				{
					printf("Registered %s\n", function.first);
				}
			}
		}
	}
}

HRESULT __fastcall HkPresentD11(IDXGISwapChain* pSwapChain, UINT syncInterval, UINT flags)
{
	if (!initialised)
	{
		initialised = true;

		pSwapChain->GetDevice(__uuidof(Drawings::pDevice), (void**)&Drawings::pDevice);
		Drawings::pDevice->GetImmediateContext(&Drawings::pDeviceContext);

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDrawCursor = false;
		io.DeltaTime = 1.0f / 60.0f;
		io.Fonts->AddFontDefault();

		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		//ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();
		
		/*ID3D11Texture2D* pBackBuffer;
		pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
		Drawings::pDevice->CreateRenderTargetView(pBackBuffer, NULL, &Drawings::pRenderTarget);
		pBackBuffer->Release();*/

		// Setup Platform/Renderer bindings
		ImGui_ImplWin32_Init(MainWindowHandle);
		ImGui_ImplDX11_Init(Drawings::pDevice, Drawings::pDeviceContext);
		ImGui_ImplDX11_CreateDeviceObjects();
	}

	//pSwapChain->ResizeBuffers

	static ID3D11DepthStencilView* NormalDepthStencil;
	static D3D11_VIEWPORT viewport;
	
	ImGuiIO& io = ImGui::GetIO();

	if (Drawings::RenderTargetView == nullptr)
	{
		//viewport
		UINT vps = 1;
		Drawings::pDeviceContext->RSGetViewports(&vps, &viewport);
		
		//get backbuffer
		ID3D11Texture2D* backbuffer = nullptr;
		HRESULT hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&backbuffer));
		if (FAILED(hr))
		{
			Drawings::pDeviceContext->OMGetRenderTargets(1, &Drawings::RenderTargetView, nullptr);
			Drawings::pDeviceContext->OMSetRenderTargets(1, &Drawings::RenderTargetView, nullptr);
			return hr;
		}
		//create rendertarget
		hr = Drawings::pDevice->CreateRenderTargetView(backbuffer, nullptr, &Drawings::RenderTargetView);
		backbuffer->Release();
		if (FAILED(hr))
		{
			return hr;
		}
	}
	else
	{
		//Drawings::pDeviceContext->AddRef();

		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		depthStencilDesc.DepthEnable = TRUE;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
		depthStencilDesc.StencilEnable = FALSE;
		depthStencilDesc.StencilReadMask = 0xFF;
		depthStencilDesc.StencilWriteMask = 0xFF;

		// Stencil operations if pixel is front-facing
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// Stencil operations if pixel is back-facing
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		ID3D11Texture2D* m_depthStencilBuffer = nullptr;
		D3D11_DEPTH_STENCIL_VIEW_DESC* m_DepthStencilViewDesc = nullptr;
		ID3D11DepthStencilState* m_DepthStencilState =  nullptr;
		ID3D11DepthStencilView* m_DepthStencilView = nullptr;
		Drawings::pDevice->CreateDepthStencilState(&depthStencilDesc, &m_DepthStencilState);
		Drawings::pDeviceContext->OMSetDepthStencilState(m_DepthStencilState, 0);
		Drawings::pDevice->CreateDepthStencilView(m_depthStencilBuffer, m_DepthStencilViewDesc, &m_DepthStencilView); //try this probably not it though

		Drawings::pDeviceContext->OMGetRenderTargets(1, &Drawings::NormalTargetView, &NormalDepthStencil);		
		Drawings::pDeviceContext->OMSetRenderTargets(1, &Drawings::RenderTargetView, m_DepthStencilView);

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();

		//ImGuiIO& io = ImGui::GetIO();

		//std::cout << "X: " << io.DisplaySize.x << " Y: " << io.DisplaySize.y << std::endl;

		GameLoop();
		
		ImGui::GetOverlayDrawList()->AddText(ImVec2(10, 10), 0xFF0000FF, "HELLO WORLD");
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(10, 10), ImVec2(300, 10), 0xFF0000FF);

		const auto currentState = *reinterpret_cast<int16_t*>(Offsets::Base + Offsets::InGame);
		if ((currentState >> 4) & 1)
		{
			if (Drawings::Waypoints)
			{
				int pointsCount = 0;
				ImVec2* points = new ImVec2[Drawings::WaypointsLenght - Drawings::CurrentWaypoint + pointsCount];

				//Start at player
				//auto player = GetLocalPlayer();
				//auto playerScreenPos = Drawings::WorldToScreen(player->pos);
				//points[pointsCount] = ImVec2(playerScreenPos.x, playerScreenPos.y);

				//Add other points...
				for (int i = Drawings::CurrentWaypoint; i < Drawings::WaypointsLenght; i++)
				{
					auto screenLoc = Drawings::WorldToScreen(Vector3(Drawings::Waypoints[i].x, Drawings::Waypoints[i].y, Drawings::Waypoints[i].z));
					if (screenLoc.x != 0 || screenLoc.y != 0)
					{
						if (i != Drawings::WaypointsLenght - 1)
						{
							auto nextScreenLoc = Drawings::WorldToScreen(Vector3(Drawings::Waypoints[i + 1].x, Drawings::Waypoints[i + 1].y, Drawings::Waypoints[i + 1].z));
							if (nextScreenLoc.x != 0 || nextScreenLoc.y != 0)
							{
								points[pointsCount] = ImVec2(screenLoc.x, screenLoc.y);
								pointsCount++;
							}
						}
						else
						{
							//Last point
							auto prevScreenLoc = Drawings::WorldToScreen(Vector3(Drawings::Waypoints[i - 1].x, Drawings::Waypoints[i - 1].y, Drawings::Waypoints[i - 1].z));
							if (prevScreenLoc.x != 0 || prevScreenLoc.y != 0)
							{
								points[pointsCount] = ImVec2(screenLoc.x, screenLoc.y);
								pointsCount++;
							}
						}
					}
				}

				if (pointsCount > 1)
				{
					ImVec2* realPoints = new ImVec2[pointsCount];
					memcpy(realPoints, points, pointsCount * sizeof(ImVec2));
					ImGui::GetOverlayDrawList()->AddPolyline(realPoints, Drawings::WaypointsLenght, 0xFF0000FF, false, 3);
				}				
				delete[] points;
			}
		}

		bool open = true;

		ImGui::Begin("Hello, world!", &open);
		ImGui::Text("This is some useful text.");
		ImGui::End();

		ImGui::EndFrame();

		//Change render states here ??

		ImGui::Render();
		//Drawings::pDeviceContext->OMSetRenderTargets(1, &NormalTargetView, NormalDepthStencil);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	
	return Od11Present(pSwapChain, syncInterval, flags);
}

HRESULT __stdcall HkResizeBuffersD11(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	ImGui_ImplDX11_InvalidateDeviceObjects();
	if (Drawings::RenderTargetView)
	{
		Drawings::RenderTargetView->Release();
		Drawings::RenderTargetView = nullptr;
	}
	std::cout << "ResizedBuffers" << std::endl;
	return Od11ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

struct handle_data {
	unsigned long process_id;
	HWND window_handle;
};

BOOL IsMainWindow(HWND handle)
{
	return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}

HWND GetConsoleHwnd(void)
{
	#define MY_BUFSIZE 1024 // Buffer size for console window titles.
	HWND hwndFound;         // This is what is returned to the caller.
	char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
										// WindowTitle.
	char pszOldWindowTitle[MY_BUFSIZE]; // Contains original
										// WindowTitle.

	// Fetch current window title.

	GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);

	// Format a "unique" NewWindowTitle.

	wsprintf(pszNewWindowTitle, "%d/%d",
		GetTickCount(),
		GetCurrentProcessId());

	// Change current window title.

	SetConsoleTitle(pszNewWindowTitle);

	// Ensure window title has been updated.

	Sleep(40);

	// Look for NewWindowTitle.

	wchar_t wtext[MY_BUFSIZE + 1];
	size_t outSize;
	mbstowcs_s(&outSize, wtext, pszNewWindowTitle, strlen(pszNewWindowTitle) + 1);

	hwndFound = FindWindowW(NULL, wtext);

	// Restore original window title.

	SetConsoleTitle(pszOldWindowTitle);

	return(hwndFound);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	handle_data& data = *(handle_data*)lParam;
	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);
	if (data.process_id != process_id || !IsMainWindow(handle) || handle == GetConsoleHwnd())
		return TRUE;
	data.window_handle = handle;
	return FALSE;
}

HWND FindMainWindow(unsigned long processId)
{
	handle_data data;
	data.process_id = processId;
	data.window_handle = 0;
	EnumWindows(EnumWindowsCallback, (LPARAM)&data);
	return data.window_handle;
}

DWORD __stdcall Initialize(LPVOID param)
{
	AllocConsole();
	FILE* f1;
	FILE* f2;
	FILE* f3;
	freopen_s(&f1, "CONOUT$", "wb", stdout);
	freopen_s(&f2, "CONOUT$", "wb", stderr);
	freopen_s(&f3, "CONIN$", "rb", stdin);

	std::cout << std::hex << *reinterpret_cast<uintptr_t*>(Offsets::Base + Offsets::CameraBase);

	//attempt to hook dxd11

	if (init(kiero::RenderType::D3D11) == kiero::Status::Success && kiero::bind(8, reinterpret_cast<void**>(&Od11Present), static_cast<void*>(HkPresentD11)) == kiero::Status::Success)
	{
		printf("Successfully hooked dxd11!\n");
		if (kiero::bind(13, reinterpret_cast<void**>(&Od11ResizeBuffers), static_cast<void*>(HkResizeBuffersD11)) == kiero::Status::Success)
		{
			printf("Loading MoveMaps. \r\n");
			Navigation* navigation = Navigation::GetInstance();
			navigation->Initialize(0);
			/*navigation->Initialize(3358);
			navigation->Initialize(3277);
			navigation->Initialize(2107);*/
			printf("Movemaps Loaded. Started. \r\n");

			while (1 & !GetAsyncKeyState(VK_F4))
				Sleep(1);
			kiero::shutdown();
		}
		else
		{
			printf("Failed to hook dxd11 closing in 5 seconds..");
			Sleep(5000);
		}
	}
	else
	{
		printf("Failed to hook dxd11 closing in 5 seconds..");
		Sleep(5000);
	}
	const auto conHandle = GetConsoleWindow();
	FreeConsole();
	PostMessage(conHandle, WM_CLOSE, 0, 0);
	FreeLibraryAndExitThread(static_cast<HMODULE>(param), NULL);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	Navigation* navigation = Navigation::GetInstance();
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			MainWindowHandle = FindMainWindow(GetCurrentProcessId());
			CreateThread(nullptr, 0, Initialize, nullptr, 0, nullptr);
			DisableThreadLibraryCalls(hModule);
		}
		break;
		case DLL_PROCESS_DETACH:
		{
			navigation->Release();
		}
		break;
		case DLL_THREAD_ATTACH:
		break;
		case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}
