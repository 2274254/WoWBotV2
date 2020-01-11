#ifndef STARTUP_H
#define STARTUP_H

#include <windows.h>
#include <iostream>
class Startup
{
public:
	static HINSTANCE SharedLibrary;
	static DWORD Start();
	/*
	static WNDPROC oWndProc;

	static void HookWndProc()
	{
		//WNDPROC oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(FindWindowA(nullptr, "League of Legends (TM) Client"), GWL_WNDPROC, reinterpret_cast<long>(nWndProc)));
	}

	static LRESULT nWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		//std::cout << "hWnd:" << hWnd << " message:" << message << " wParam:" << wParam << " lParam:" << lParam << std::endl;
		if (Startup::SharedLibrary == NULL) Startup::SharedLibrary = LoadLibrary(L"HesaEngine.Loader.dll");
		if (Startup::SharedLibrary == NULL) {
			return CallWindowProc(oWndProc, hWnd, message, wParam, lParam);
		}
		else {
			OnWndProcCallback start = (OnWndProcCallback)GetProcAddress(Startup::SharedLibrary, "OnWndProcCallback");
			
			BOOL result = start((DWORD)hWnd, (UINT) message, (UINT) wParam, (LONG) lParam);
			//if (result)
			{
				return CallWindowProc(oWndProc, hWnd, message, wParam, lParam);
			}
		}
		return 0;
	}

	static HWND FindTopWindow(DWORD pid)
	{
		std::pair<HWND, DWORD> params = { 0, pid };
		// Enumerate the windows using a lambda to process each window
		BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
		{
			auto pParams = (std::pair<HWND, DWORD>*)(lParam);

			DWORD processId;
			if (GetWindowThreadProcessId(hwnd, &processId) && processId == pParams->second)
			{
				// Stop enumerating
				SetLastError(-1);
				pParams->first = hwnd;
				return FALSE;
			}

			// Continue enumerating
			return TRUE;
		}, (LPARAM)&params);

		if (!bResult && GetLastError() == -1 && params.first)
		{
			return params.first;
		}

		return 0;
	}
	*/
};
#endif