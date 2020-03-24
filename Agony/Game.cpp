#include "Game.h"
#include "Offsets.h"
#include "Macros.h"
#include "EventHandler.h"
#include "Bootstrapper.h"
#include "LuaFunctions.h"
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
	//printf("ON MESSAGE\n");
	auto process = Agony::Native::EventHandler<1, Agony::Native::OnWndProc, HWND, UINT, WPARAM, LPARAM>::GetInstance()->TriggerProcess(hwnd, msg, WParam, LParam);
	LRESULT returnValue;
	if (msg == WM_KEYUP)
	{
		if (WParam == VK_F5)
		{
			Agony::Native::Bootstrapper::GetInstance()->Trigger(BootstrapEventType::Load);
		}
	}

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
	return true;
	//IS_NULL_RETN(Offsets::Base, static_cast<unsigned __int16>(Offsets::InGame), false);
	const unsigned __int16 gameState = *reinterpret_cast<unsigned __int16*>(Offsets::Base + Offsets::InGame);
	return ((gameState >> 4) & 1);
}

char* Agony::Native::Game::GetGameVersion()
{
	return "Unknown";
	//auto returnValues = LuaFunctions::Call("GetBuildInfo", { 2, 2, 2, 1 }, NULL);
	//return (std::string(std::any_cast<const char*>(returnValues[0])) + std::string(std::any_cast<const char*>(returnValues[1]))).c_str();
}

WoWObject* Agony::Native::Game::Me()
{
	return reinterpret_cast<WoWObject * (__fastcall*)(const char*)>(Offsets::Base + Offsets::GetBaseFromToken)("player");
}

bool Agony::Native::Game::ApplyHooks(void* mainWindowHandle)
{
	m_wndProc = (WNDPROC)SetWindowLongPtr((HWND)mainWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hkWndProc));
	return true;
}
