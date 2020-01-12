#include <windows.h>
#include <iostream>
#include "Navigation.h"
#include "Offsets.h"
#include "LuaFunctions.h"
#include "Drawings.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "Camera.h"
#include "Game.h"
#include "Console.h"
#include "Core.h"
#include "Utils.h"
#include "kiero.h"

#undef MANAGED_BUILD
namespace Agony
{
	namespace Native
	{		
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

			wsprintf(pszNewWindowTitle, "%d/%d", GetTickCount(), GetCurrentProcessId());

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
			//if (Utils::IsProcess("World of Warcraft"))
			{
				Console::Create();
			}

			Core::MainModule = reinterpret_cast<int>(GetModuleHandle(nullptr));
			Core* _core = new Core(GetModuleHandle(nullptr));

			//std::cout << std::hex << reinterpret_cast<uintptr_t*>(GetLocalPlayer());	
			//CameraBase* pCameraBase = *reinterpret_cast<CameraBase**>(Offsets::Base + Offsets::CameraBase);
			//std::cout << "CameraInfo:" << std::hex << reinterpret_cast<uintptr_t*>(pCameraBase->camera_ptr);
			
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

			const auto conHandle = GetConsoleWindow();
			FreeConsole();
			PostMessage(conHandle, WM_CLOSE, 0, 0);
			FreeLibraryAndExitThread(static_cast<HMODULE>(param), NULL);
		}

		BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
		{
			static HANDLE hThread = nullptr;
			Navigation* navigation = Navigation::GetInstance();
			///if (Utils::IsProcess("World of Warcraft"))
			switch (ul_reason_for_call)
			{
				case DLL_PROCESS_ATTACH:
				{
					Core::MainWindowHandle = FindMainWindow(GetCurrentProcessId());
					hThread = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Initialize), nullptr, NULL, nullptr);
					//DisableThreadLibraryCalls(hModule);
				}
				break;
				case DLL_PROCESS_DETACH:
				{
					navigation->Release();
					SuspendThread(hThread);
				}
				break;
			}
			return TRUE;
		}
	}
}