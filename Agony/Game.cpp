#include "Game.h"
#include "Offsets.h"
#include "Macros.h"
#include "EventHandler.h"
#include <iostream>

#pragma comment(lib, "User32.lib")

Agony::Native::Game* Agony::Native::Game::GetInstance()
{
	static auto inst = new Game();
	return inst;
}

WNDPROC m_wndProc;
LRESULT WINAPI hkWndProc(HWND hwnd, UINT msg, WPARAM WParam, LPARAM LParam)
{
	printf("ON MESSAGE\n");
	auto process = Agony::Native::EventHandler<1, Agony::Native::OnWndProc, HWND, UINT, WPARAM, LPARAM>::GetInstance()->TriggerProcess(hwnd, msg, WParam, LParam);
	LRESULT returnValue;
	/*if (msg == WM_KEYUP)
	{
		if (WParam == VK_F5)
		{
			Bootstrapper::GetInstance()->Trigger(BootstrapEventType::Load);
		}
	}*/

	if (!process)
	{
		//m_blockInput = true;
		//m_lastInputBlock = GetTickCount();
	}
	else
	{
		/*if (GetTickCount() - m_lastInputBlock > 1000)
		{
			m_blockInput = false;
		}*/

		return CallWindowProc(m_wndProc, hwnd, msg, WParam, LParam);
	}

	return 1;
}

bool Agony::Native::Game::IsInGame()
{
	IS_NULL_RETN(Offsets::Base, static_cast<int>(Offsets::InGame), false);
	const int16_t gameState = *reinterpret_cast<int16_t*>(Offsets::Base + Offsets::InGame);
	return ((gameState >> 4) & 1);
}

char* Agony::Native::Game::GetGameVersion()
{
	IS_NULL_RETN(Offsets::Base, static_cast<int>(Offsets::GameVersion), "Unknown");
	return reinterpret_cast<char*>(Offsets::Base + static_cast<int>(Offsets::GameVersion));
}

bool Agony::Native::Game::ApplyHooks(void* mainWindowHandle)
{
	m_wndProc = (WNDPROC)SetWindowLongPtr((HWND)mainWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hkWndProc));
	return true;
}
